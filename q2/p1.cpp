#include <iostream>
#include <string>

class Queue {
    private: 
        std::string* arr_;
        int n_;
        int f_;
        int r_;
    public:
        Queue() : arr_(new std::string[2]{}), n_(2), f_(0), r_(0) {};
        ~Queue() {
            delete[] arr_;
            arr_ = nullptr;
        }
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;    
        
        void resize(int new_capacity) {
            int count = size();
            std::string* new_arr = new std::string[new_capacity];
            for (int i = 0; i < count; ++i) {
                new_arr[i] = arr_[(f_ + i) % n_];
            }
            delete[] arr_;
            arr_ = new_arr;
            n_ = new_capacity;
            f_ = 0;
            r_ = count;
        }

        void enqueue(std::string s) {
            if (is_full()) {
                resize(n_ * 2);
            }
            arr_[r_] = s;
            r_ = (r_ + 1) % n_;
        }

        std::string dequeue() {
            if (is_empty()) {
                return "EMPTY ARRAY";
            }
            std::string dq = this->front();
            arr_[f_] = "";
            f_ = (f_ + 1) % n_;
            return dq;
        }

        std::string front() {
            return arr_[f_];
        }

        int size() {
            return (n_ - f_ + r_) % n_;
        }

        bool is_empty() {
            return size() == 0;
        }

        bool is_full() {
            return size() == n_ - 1;
        }
};

class Stack {
    private:
        std::string* arr_;
        std::size_t capacity_;
        std::size_t size_;
    public:
        Stack(int k) : arr_(new std::string[k]), capacity_(k), size_(0) {};
        ~Stack() {
            delete[] arr_;
            arr_ = nullptr;
        }

        Stack(const Stack&) = delete;
        Stack& operator=(const Stack&) = delete;

        void push(std::string s) {
            if (is_full()) {
                return;
            }
            arr_[size_] = s;
            size_++;
        }

        void pop() {
            if (is_empty()) {
                return;
            } 
            size_--;
            arr_[size_] = "";
        }

        bool is_empty() {
            return size_ == 0;
        }

        bool is_full() {
            return size_ == capacity_;
        }

        std::string top() {
            if (is_empty()) {
                return "EMPTY STACK";
            }
            return arr_[size_ - 1];
        }

        void print_stack() {
            for (std::size_t i = 0; i < size_; ++i) {
                if (i > 0) {
                    std::cout << " ";
                }
                std::cout << arr_[i];
            }
        }
};


class ParkingGarage {
    private:
        Queue q_;
        Stack s_;
        int capacity_;
    public:
        ParkingGarage(int capacity) : q_(), s_(capacity), capacity_(capacity) {};
        void arrive(std::string lp) {
            q_.enqueue(lp);
        }
        void park() {
            if (s_.is_full()) {
                std::cout << "Garage full";
                return;
            }
            if (q_.is_empty()) {
                std::cout << "No cars waiting";
                return;
            }
            std::string car = q_.front();
            s_.push(car);
            q_.dequeue();

            std::cout << "Parked: " << car;
        }
        void exit(std::string lp) {
            Stack temp(capacity_);
            
            while (!s_.is_empty() && s_.top() != lp) {
                temp.push(s_.top());
                s_.pop();
            }

            if (s_.is_empty()) {
                std::cout << "Car not found";
            } else {
                s_.pop();

                if (!temp.is_empty()) {
                    std::cout << "Moved: ";
                    temp.print_stack();
                    std::cout << "\n";
                }
                std::cout << "Exited: " << lp;
            }

            while (!temp.is_empty()) {
                s_.push(temp.top());
                temp.pop();
            }

        }
};
int main() {
    int k; 
    std::cin >> k;
    ParkingGarage pg(k);
    std::string s;
    while (std::cin >> s) {
        if (s == "TERMINATE") {
            break;
        } else if (s == "ARRIVE") {
            std::string plate;
            std::cin >> plate;
            pg.arrive(plate);        
        } else if (s == "PARK") {
             pg.park();
        } else if (s == "EXIT") {
            std::string plate;
            std::cin >> plate;
            pg.exit(plate);
        }
        if (s == "PARK" || s == "EXIT") std::cout << "\n";
    }

    return 0;

}