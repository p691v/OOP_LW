#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <concepts>

template <class T>
class Array {
    private:
        static const std::size_t INITIAL_EXTEND = 10;
        static const std::size_t CAPACITY_GROW_FACTOR = 2;

        static constexpr bool IS_ARRAY_OF_PTRS = std::is_pointer_v<T>;

        std::size_t size;
        std::size_t capacity;

        std::unique_ptr<T[]> elems{nullptr};

        void extend () {
            if (capacity == 0) {
                elems = std::make_unique<T[]>(INITIAL_EXTEND);
                capacity = INITIAL_EXTEND;
                return;
            }

            capacity *= CAPACITY_GROW_FACTOR;

            std::unique_ptr<T[]> newElems = std::make_unique<T[]>(capacity);

            for (int i = 0; i < size; i++) {
                newElems[i] = std::move(elems[i]);
            }

            if constexpr (IS_ARRAY_OF_PTRS) cleanLinks();

            elems.reset();
            elems = std::move(newElems);
        }

        void cleanLinks () {
            for (int i = 0; i < size; i++) {
                delete elems[i];
            }
        }

    public:
        Array () : size{0}, capacity{0} {}

        Array (const Array<T> &other) : size{other.size}, capacity{other.capacity} {
            if (other.capacity == 0) return; 

            elems = std::make_unique<T[]>(other.capacity);

            for (int i = 0; i < other.size; i++) {
                elems[i] = other.elems[i];
            }
        }
        
        Array (Array<T> &&other) : size{other.size}, capacity{other.capacity} {
            elems = std::move(other.elems);

            other.size = 0;
            other.capacity = 0;
        }

        Array<T>& operator= (const Array<T> &other) {
            if (this == &other) return *this;

            if constexpr (IS_ARRAY_OF_PTRS) cleanLinks();
            elems.reset();

            if (other.capacity == 0) return *this; 

            elems = std::make_unique<T[]>(other.capacity);

            for (int i = 0; i < other.size; i++) {
                elems[i] = other.elems[i];
            }

            return *this;
        }

        Array<T>& operator= (Array<T> &&other) {
            if (capacity != 0) {
                if constexpr (IS_ARRAY_OF_PTRS) cleanLinks();
                elems.reset();
            }

            size = other.size;
            capacity = other.capacity;
            elems = std::move(other.elems);

            other.size = 0;
            other.capacity = 0;

            return *this;
        }

        ~Array () {
            if constexpr (IS_ARRAY_OF_PTRS) cleanLinks();
        };
        
        T& operator[] (std::size_t index) {
            if (index >= size) {
                throw std::out_of_range("Array index is out of range.");
            }

            return elems[index];
        }

        const T& operator[] (std::size_t index) const {
            if (index >= size) {
                throw std::out_of_range("Array index is out of range.");
            }

            return elems[index];
        }

        void append (const T &newElement) {
            if (size >= capacity) extend();

            elems[size] = newElement;
            size++;
        }

        void append (T &&newElement) {
            if (size >= capacity) extend();

            elems[size] = std::move(newElement);
            size++;
        }

        void append (const Array<T> &other) {
            for (int i = 0; i < other.size; i++) {
                append(other.elems[i]);
            }
        }

        void deleteOnIndex (std::size_t index) {
            if (index >= size) {
                throw std::out_of_range("Array index is out of range.");
            }

            if constexpr (IS_ARRAY_OF_PTRS) delete elems[index];

            size--;

            for (int i = index; i < size; i++) {
                elems[i] = std::move(elems[i + 1]);
            }
        }

        std::size_t getSize () const {
            return size;
        }

        bool operator== (const Array<T> &other) const {
            if (size != other.getSize()) return false;

            for (int i = 0; i < size; i++) {
                if (elems[i] != other[i]) return false;
            }

            return true;
        }
};
