#include <iostream>

class Queue {
    private:
        int* arr_;
        int n_;
        int f_;
        int r_;
    public:
        Queue(int n) : arr_( new int[n] {}), n_(n), f_(0), r_(0) {}; 
        ~Queue() {
            delete[] arr_;
            arr_ = nullptr;
        }
        
        bool dequeue() {
            if (this->is_empty()) {
                return false;
            }
            arr_[f_] = 0;
            f_ = (f_ + 1) % n_;
            return true;
        }
        bool enqueue(int o){
            if (this->is_full()) {
                return false;
            }
            arr_[r_] = o;
            r_ = (r_+1) % n_;
            return true;
        }
        int size() const {
            return (n_ - f_ + r_) % n_;
        }
        bool is_empty() const {
            return this->size() == 0;
        }
        int front() const{
            if (this->is_empty()) {
                return 0;
            }
            return arr_[f_];
        }

        int back() const {
            if (this->is_empty()) {
                return 0;
            }
            return arr_[(r_ - 1 + n_) % n_];
        }

        int f() const {
            return f_;
        }
        
        int r() const {
            return r_;
        }

        bool is_full() const {
            return size() == n_ - 1;
        }
        const int& operator[] (int i) const {
            return arr_[(f_ + i) % n_];
        }


};