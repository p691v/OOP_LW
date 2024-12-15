#pragma once
#include <iostream>
#include <list>
#include <memory_resource>
#include <memory>
#include <stdexcept>

template <size_t poolSize>
class StaticResource : public std::pmr::memory_resource {
    private:
        struct AllocatedBlock {
            unsigned char *begin;
            size_t size;

            AllocatedBlock (unsigned char *blockBegin, size_t blockSize) : begin{blockBegin}, size{blockSize} {}
        };
        
        unsigned char pool[poolSize];
        std::list<AllocatedBlock> allocatedBlocks;

    public:
        void* do_allocate (size_t bytes, size_t alignment) override {
            if (bytes >= poolSize) throw std::bad_alloc();
            
            if (allocatedBlocks.empty()) {
                AllocatedBlock block(pool, bytes);
                allocatedBlocks.push_back(block);
                return block.begin;
            }

            if (allocatedBlocks.begin()->begin - pool >= bytes) {
                AllocatedBlock block(pool, bytes);
                allocatedBlocks.push_front(block);
                return block.begin;
            }

            for (auto usedBlock = allocatedBlocks.begin(); usedBlock != --allocatedBlocks.end(); ++usedBlock) {
                auto nextUsedBlock = std::next(usedBlock);

                if (nextUsedBlock->begin - (usedBlock->begin + usedBlock->size) >= bytes) {
                    AllocatedBlock block(usedBlock->begin + usedBlock->size, bytes);
                    allocatedBlocks.insert(nextUsedBlock, block);
                    return block.begin;
                }
            }
            
            auto lastBlock = --allocatedBlocks.end();
            if ((pool + poolSize) - (lastBlock->begin + lastBlock->size) >= bytes) {
                AllocatedBlock block(lastBlock->begin + lastBlock->size, bytes);
                allocatedBlocks.push_back(block);
                return block.begin;
            }

            throw std::bad_alloc();
        }

        void do_deallocate (void *ptr, size_t bytes, size_t alignment) override {
            for (auto it = allocatedBlocks.begin(); it != allocatedBlocks.end(); ++it) {
                if (it->begin == ptr) {
                    allocatedBlocks.erase(it);
                    return;
                }
            }

            throw std::logic_error("Trying to delete block which is not allocated.");
        } 

        bool do_is_equal (const std::pmr::memory_resource &other) const noexcept override {
            return this == &other;
        }
};