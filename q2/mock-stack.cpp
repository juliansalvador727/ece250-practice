#include <iostream>

class Stack {
    private:
        int *arr_;
        std::size_t size_;
        std::size_t capacity_;

        void grow() {
            std::size_t new_cap = capacity_ * 2;
            int* new_arr = new int[new_cap];
            for (int i = 0; i < size_; ++i) {
                new_arr[i] = arr_[i];
            }
            delete[] arr_;
            arr_ = new_arr;
            capacity_ = new_cap;
        }
    public:
        Stack(std::size_t n) : arr_(new int[n+1]{}), size_(0), capacity_(n+1) {};
        ~Stack() {
            delete[] arr_;
            arr_ = nullptr;
        };

        int pop() {
            if (empty()) {
                return -1;
            }
            return arr_[--size_];
        }
        void push(int x) {
            if (size_ == capacity_) grow();
            arr_[size_++] = x;
        }
        int top () {
            return arr_[size_ -1];
        }
        bool empty() {
            return size_ == 0;
        }
        std::size_t size() {
            return size_;
        }

        void print() {
            std::cout << "[";
            bool first = true;
            for (int i = size_; i > 0; --i) {
                if (first) {
                    std::cout << arr_[i-1];
                    first = false;
                } else {
                    std::cout << ", " << arr_[i-1];
                }
            }
            std::cout << "]\n";
        }
};