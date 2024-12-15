#include <gtest/gtest.h>
#include <memory_resource>
#include <iostream>
#include <stdexcept>

#include "../include/static-resource.hpp"
#include "../include/stack.hpp"

TEST(allocator, alloc_empty) {
    struct Item {
        int *counter;
        Item (int *counterVal) : counter{counterVal} { ++(*counter); }
        ~Item () { --(*counter); }
    };
    int counter = 0;

    StaticResource<1024> resource;
    std::pmr::polymorphic_allocator<Item> allocator(&resource);

    auto itemP = allocator.allocate(1);
    allocator.construct(itemP, &counter);

    bool result = counter == 1;
    ASSERT_TRUE(result == true);
}

TEST(allocator, alloc_some) {
    struct Item {
        int *counter;
        Item (int *counterVal) : counter{counterVal} { ++(*counter); }
        ~Item () { --(*counter); }
    };
    int counter = 0;

    StaticResource<1024> resource;
    std::pmr::polymorphic_allocator<Item> allocator(&resource);

    auto itemP = allocator.allocate(2);
    allocator.construct(itemP, &counter);
    allocator.construct(itemP + 1, &counter);

    bool result = counter == 2;
    ASSERT_TRUE(result == true);
}

TEST(allocator, alloc_begin) {
    struct Item {
        int *counter;
        Item (int *counterVal) : counter{counterVal} { ++(*counter); }
        ~Item () { --(*counter); }
    };
    int counter = 0;

    StaticResource<1024> resource;
    std::pmr::polymorphic_allocator<Item> allocator(&resource);

    auto itemP = allocator.allocate(1);
    allocator.construct(itemP, &counter);
    auto itemP2 = allocator.allocate(1);
    allocator.construct(itemP2, &counter);
    
    itemP->~Item();
    allocator.deallocate(itemP, 1);

    auto itemP3 = allocator.allocate(1);
    allocator.construct(itemP3, &counter);

    bool result = counter == 2;
    ASSERT_TRUE(result == true);
}

TEST(allocator, alloc_end) {
    struct Item {
        int *counter;
        Item (int *counterVal) : counter{counterVal} { ++(*counter); }
        ~Item () { --(*counter); }
    };
    int counter = 0;

    StaticResource<1024> resource;
    std::pmr::polymorphic_allocator<Item> allocator(&resource);

    auto itemP = allocator.allocate(1);
    allocator.construct(itemP, &counter);
    auto itemP2 = allocator.allocate(1);
    allocator.construct(itemP2, &counter);
    auto itemP3 = allocator.allocate(1);
    allocator.construct(itemP3, &counter);

    bool result = counter == 3;
    ASSERT_TRUE(result == true);
}

TEST(allocator, alloc_middle) {
    struct Item {
        int *counter;
        Item (int *counterVal) : counter{counterVal} { ++(*counter); }
        ~Item () { --(*counter); }
    };
    int counter = 0;

    StaticResource<1024> resource;
    std::pmr::polymorphic_allocator<Item> allocator(&resource);

    auto itemP = allocator.allocate(1);
    allocator.construct(itemP, &counter);
    auto itemP2 = allocator.allocate(1);
    allocator.construct(itemP2, &counter);
    auto itemP3 = allocator.allocate(1);
    allocator.construct(itemP3, &counter);

    itemP2->~Item();
    allocator.deallocate(itemP2, 1);

    auto itemP4 = allocator.allocate(1);
    allocator.construct(itemP4, &counter);

    bool result = counter == 3;
    ASSERT_TRUE(result == true);
}

TEST(allocator, dealloc) {
    struct Item {
        int *counter;
        Item (int *counterVal) : counter{counterVal} { ++(*counter); }
        ~Item () { --(*counter); }
    };
    int counter = 0;

    StaticResource<1024> resource;
    std::pmr::polymorphic_allocator<Item> allocator(&resource);

    auto itemP = allocator.allocate(1);
    allocator.construct(itemP, &counter);

    itemP->~Item();
    allocator.deallocate(itemP, 1);

    bool result = counter == 0;
    ASSERT_TRUE(result == true);
}

TEST(allocator, dealloc_some) {
    struct Item {
        int *counter;
        Item (int *counterVal) : counter{counterVal} { ++(*counter); }
        ~Item () { --(*counter); }
    };
    int counter = 0;

    StaticResource<1024> resource;
    std::pmr::polymorphic_allocator<Item> allocator(&resource);

    auto itemP = allocator.allocate(5);

    for (int i = 0; i < 5; i++) {
        allocator.construct(itemP + i, &counter);
    }

    for (int i = 0; i < 5; i++) {
        (itemP + i)->~Item();
    }

    allocator.deallocate(itemP, 5);

    bool result = counter == 0;
    ASSERT_TRUE(result == true);
}

TEST(allocator, bad_alloc) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    
    ASSERT_THROW({
        auto ptr = allocator.allocate(1025);
    }, std::bad_alloc);
}

TEST(stack, create_empty) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);
    bool result = stack.empty();

    ASSERT_TRUE(result == true);
}

TEST(stack, push_not_empty) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);

    stack.push(0);
    bool result = stack.empty();

    ASSERT_TRUE(result == false);
}

TEST(stack, top) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);

    stack.push(6);
    int result = stack.top();

    ASSERT_TRUE(result == 6);
}

TEST(stack, pop) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);

    stack.push(6);
    stack.pop();

    bool result = stack.empty();

    ASSERT_TRUE(result == true);
}

TEST(stack, filo) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);

    stack.push(0);
    stack.push(1);
    stack.push(2);

    bool correct = true;
    correct = correct && stack.top() == 2;
    stack.pop();
    correct = correct && stack.top() == 1;
    stack.pop();
    correct = correct && stack.top() == 0;
    stack.pop();

    bool result = correct == true;

    ASSERT_TRUE(result == true);
}

TEST(stack, iterators) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);

    stack.push(0);
    stack.push(1);
    stack.push(2);

    auto it = stack.begin();

    bool correct = true;
    correct = correct && *it == 2;
    it++;
    correct = correct && *it == 1;
    it++;
    correct = correct && *it == 0;
    it++;
    correct = correct && it == stack.end();

    bool result = correct == true;

    ASSERT_TRUE(result == true);
}

TEST(stack, const_iterators) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);

    stack.push(0);
    stack.push(1);
    stack.push(2);

    int i = 2;
    bool correct = true;
    for (auto it = stack.cbegin(); it != stack.cend(); ++it) {
        correct = correct && (*it == i--);
    }

    i = 2;
    const Stack<int> &stackConstLink = stack;
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        correct = correct && (*it == i--);
    }

    bool result = correct == true;

    ASSERT_TRUE(result == true);
}

TEST(stack, equal) {
    StaticResource<1024> resource;
    StackAllocator<int> allocator(&resource);
    Stack<int> stack(allocator);
    Stack<int> stack2(allocator);

    bool emptyEqual = stack == stack2;

    stack.push(0);
    stack.push(1);
    stack.push(2);

    stack2.push(0);
    stack2.push(1);
    stack2.push(2);

    bool sameEqual = stack == stack2;

    stack2.push(3);

    bool notSameNotEqual = stack != stack2;

    bool result = emptyEqual && sameEqual && notSameNotEqual;

    ASSERT_TRUE(result == true);
}

int main (int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}