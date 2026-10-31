#include <iostream>
#include <string>

struct Printer {
    template <typename T>
    static void printAll(const T& obj, const char* label = "") {
        std::cout << label << "[";
        for (int i = 0; i < obj.size(); ++i) {
            std::cout << (i ? ", " : "") << obj.at(i);
        }
        std::cout << "] size=" << obj.size() << "\n";
    }

    template <typename T>
    static void printAt(const T& obj, int i) {
        if (i < 0 || i >= obj.size()) {
            std::cout << "index: " << i << " out of range\n";
            return;
        }
        std::cout << "[" << i << "] = " << obj.at(i) << "\n";
    }
};

enum class Status { Ok, Empty, Full };

template <typename T>
struct Result {
    Status status;
    T value;
    bool ok() const { return status == Status::Ok; }
};

template <typename T>
class Deque {
    private:
        T* arr_;
        int cap_;
        int f_;
        int count_;
    public:
        Deque(int n) : arr_(new T[n]{}), cap_(n), f_(0), count_(0) {};
        ~Deque() {
            delete[] arr_;
            arr_ = nullptr;
        }
        Deque(const Deque&) = delete;
        Deque& operator=(const Deque&) = delete;

        Status push_back(const T& x) {
            if (isFull()) {
                return Status::Full;
            }
            arr_[(f_ + count_) % cap_] = x;
            count_++;
            return Status::Ok;
        }   

        Status push_front(const T& x) {
            if (isFull()) {
                return Status::Full;
            }
            f_ = (f_ - 1 + cap_) % cap_;
            arr_[f_] = x;
            count_++;
            return Status::Ok;
        }

        Result<T> pop_front() {
            if (isEmpty()) {
                return {Status::Empty, T{}};
            }
            T temp = arr_[f_];
            f_ = (f_ + 1) % cap_;
            count_--;
            return {Status::Ok, temp};
        }

        Result<T> pop_back() {
            if (isEmpty()) {
                return {Status::Empty, T{}};
            }
            T temp = arr_[(f_ + count_ - 1) % cap_];
            count_--;
            return {Status::Ok, temp};
        }

        Result<T> front() const {
            if (isEmpty()) {
                return {Status::Empty, T{}};
            }
            return {Status::Ok, arr_[f_]};
        }

        Result<T> back() const {
            if (isEmpty()) {
                return {Status::Empty, T{}};
            }
            return {Status::Ok, arr_[(f_ + count_ - 1) % cap_]};
        }

        T at(int i) const { return arr_[(f_ + i) % cap_]; }
        bool isFull() const { return cap_ == count_; }
        bool isEmpty() const { return count_ == 0; }
        int size() const { return count_; }
};

// sample code for solving Q1

void handleExit(Deque<std::string>& garage, const std::string& plate, int k) {
    Deque<std::string> temp(k);
    while (!garage.isEmpty() && garage.back().value != plate)
        temp.push_back(garage.pop_back().value);

    bool found = garage.pop_back().ok();

    if (found) {
        if (!temp.isEmpty()) {
            std::cout << "Moved:";
            for (int i = 0; i < temp.size(); ++i) std::cout << " " << temp.at(i);
            std::cout << "\n";
        }
        std::cout << "Exited: " << plate << "\n";
    } else {
        std::cout << "Car not found\n";
    }
    while (!temp.isEmpty()) garage.push_back(temp.pop_back().value);
}

int main() {
    int k;
    std::cin >> k;
    Deque<std::string> waiting(1000), garage(k);
    std::string cmd, plate;

    while (std::cin >> cmd && cmd != "TERMINATE") {
        if (cmd == "ARRIVE") {
            std::cin >> plate;
            waiting.push_back(plate);
        } else if (cmd == "PARK") {
            if (garage.isFull()) { std::cout << "Garage full\n"; continue; }
            Result<std::string> car = waiting.pop_front();
            if (!car.ok()) { std::cout << "No cars waiting\n"; continue; }
            garage.push_back(car.value);
            std::cout << "Parked: " << car.value << "\n";
        } else if (cmd == "EXIT") {
            std::cin >> plate;
            handleExit(garage, plate, k);
        }
    }
    return 0;
}