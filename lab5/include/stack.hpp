#pragma once
#include <memory>
#include <type_traits>
#include <concepts>
#include <type_traits>

template <class T>
struct StackItem {
    T element;
    std::shared_ptr<StackItem<T>> next{nullptr};

    StackItem (T elementValue) : element{elementValue} {}
};

template <class T, bool Const>
class StackIter {
    private:
        std::shared_ptr<StackItem<T>> item{nullptr};

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = typename std::conditional<Const, const T*, T*>::type;
        using reference = typename std::conditional<Const, const T&, T&>::type;

        StackIter (std::shared_ptr<StackItem<T>> itemToWrap) {
            item = itemToWrap;
        }

        StackIter (const StackIter &other) {
            item = other.item;
        }

        StackIter (StackIter &&other) {
            item = std::move(other.item);
        }

        StackIter& operator= (const StackIter &other) {
            if (this == &other) return *this;

            item.reset();
            item = other.item;

            return *this;
        }

        StackIter& operator= (StackIter other) {
            item.reset();
            item = std::move(other.item);
            return *this;
        }

        StackIter& operator++() {
            item = item->next;
            return *this;
        } 

        StackIter operator++(int) {
            StackIter copy{*this};
            item = item->next;
            return copy;
        } 

        reference operator* () const {
            return item->element;
        }

        pointer operator->() const {
            return &item->element;
        }

        bool operator== (const StackIter &other) const {
            return item == other.item;
        }

        bool operator!= (const StackIter &other) const {
            return item != other.item;
        }
};

template <class T>
using StackAllocator = std::pmr::polymorphic_allocator<StackItem<T>>;

template <class T>
class Stack {
    private:
        class DestructionStrategy {
            private:
                StackAllocator<T> allocator;
                
            public:
                DestructionStrategy (StackAllocator<T> allocatorObject) : allocator{allocatorObject} {}

                void operator() (StackItem<T> *ptr) {
                    ptr->~StackItem();
                    allocator.deallocate(ptr, 1);
                }
        };

        StackAllocator<T> allocator;
        std::shared_ptr<StackItem<T>> topItem{nullptr};

    public:
        Stack (StackAllocator<T> allocatorObject) : allocator{allocatorObject} {}

        bool operator== (const Stack &other) const {
            auto it1 = begin(), it2 = other.begin();

            for (; it1 != end() && it2 != end(); ++it1, ++it2) {
                if (*it1 != *it2) return false;
            }

            return it1 == end() && it2 == end();
        }

        bool operator!= (const Stack &other) const {
            return !(*this == other);
        }

        StackIter<T, false> begin () {
            return StackIter<T, false>(topItem);
        }

        StackIter<T, true> begin () const {
            return StackIter<T, true>(topItem);
        }

        StackIter<T, false> end () {
            return StackIter<T, false>(nullptr);
        }

        StackIter<T, true> end () const {
            return StackIter<T, true>(nullptr);
        }

        StackIter<T, true> cbegin () {
            return StackIter<T, true>(topItem);
        }

        StackIter<T, true> cbegin () const {
            return StackIter<T, true>(topItem);
        }

        StackIter<T, true> cend () {
            return StackIter<T, true>(nullptr);
        }

        StackIter<T, true> cend () const {
            return StackIter<T, true>(nullptr);
        }

        bool empty () {
            return topItem == nullptr;
        }

        T top () {
            if (empty()) throw std::logic_error("Trying to get top of empty stack");

            return topItem->element;
        }

        void push (T elem) {
            auto itemP = allocator.allocate(1);
            allocator.construct(itemP, elem);
            std::shared_ptr<StackItem<T>> item(itemP, DestructionStrategy(allocator));
            item->next = topItem;
            topItem = item;
        }

        void pop () {
            if (empty()) throw std::logic_error("Trying to pop from empty stack");

            topItem = std::move(topItem->next);
        }
};