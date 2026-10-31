#include <iostream>

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

struct Result {
    Status status;
    int value;
    bool ok() const { return status == Status::Ok; }
};

class Stack {
    private:
        int* arr_;
        int cap_;
        int t_;
    public:
        Stack(int n) : arr_(new int[n]()), cap_(n), t_(-1) {}

        ~Stack() {
            delete[] arr_;
            arr_ = nullptr;
        }

        Stack(const Stack&) = delete;
        Stack& operator=(const Stack&) = delete;

        Status push(int x) {
            if (size() == cap_) return Status::Full;
            arr_[++t_] = x;
            return Status::Ok;
        }

        Result pop() {
            if (isEmpty()) return {Status::Empty, 0};
            return {Status::Ok, arr_[t_--]};
        }

        Result top() const {
            if (isEmpty()) return {Status::Empty, 0};
            return {Status::Ok, arr_[t_]};
        }

        int size() const { return t_ + 1; }
        int at(int i) const { return arr_[i]; }
        bool isEmpty() const { return t_ < 0; }
};

class Queue {
    private:
        int* arr_;
        int n_;
        int f_;
        int r_;
    public:
        Queue(int n) : arr_(new int[n + 1]{}), n_(n + 1), f_(0), r_(0) {}

        ~Queue() {
            delete[] arr_;
            arr_ = nullptr;
        }

        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

        Status enqueue(int x) {
            if (size() == n_ - 1) return Status::Full;
            arr_[r_] = x;
            r_ = (r_ + 1) % n_;
            return Status::Ok;
        }

        Result dequeue() {
            if (isEmpty()) return {Status::Empty, 0};
            int temp = arr_[f_];
            f_ = (f_ + 1) % n_;
            return {Status::Ok, temp};
        }

        Result front() const {
            if (isEmpty()) return {Status::Empty, 0};
            return {Status::Ok, arr_[f_]};
        }

        int size() const { return (n_ - f_ + r_) % n_; }
        int at(int i) const { return arr_[(f_ + i) % n_]; }
        bool isEmpty() const { return size() == 0; }
};

// Reverses a queue in place by moving everything through a stack.
void reverseQueue(Queue& q, int capacity) {
    Stack s(capacity);
    while (true) {
        auto [st, v] = q.dequeue();
        if (st != Status::Ok) break;
        s.push(v);
    }
    while (true) {
        auto [st, v] = s.pop();
        if (st != Status::Ok) break;
        q.enqueue(v);
    }
}

// True if the digits read the same forwards (queue) and backwards (stack).
bool isPalindrome(const int* digits, int n) {
    Stack s(n);
    Queue q(n);
    for (int i = 0; i < n; ++i) {
        s.push(digits[i]);
        q.enqueue(digits[i]);
    }
    while (!s.isEmpty()) {
        if (s.pop().value != q.dequeue().value) return false;
    }
    return true;
}

int main() {
    std::cout << "=== Stack ===\n";
    Stack s(3);
    for (int x : {10, 20, 30, 40}) {
        if (s.push(x) == Status::Full) std::cout << "push " << x << " failed: full\n";
    }
    Printer::printAll(s, "stack: ");

    if (Result r = s.top(); r.ok()) std::cout << "top = " << r.value << "\n";

    while (true) {
        auto [st, v] = s.pop();
        if (st == Status::Empty) { std::cout << "pop failed: empty\n"; break; }
        std::cout << "popped " << v << "\n";
    }

    std::cout << "\n=== Queue ===\n";
    Queue q(3);
    for (int x : {1, 2, 3, 4}) {
        if (q.enqueue(x) == Status::Full) std::cout << "enqueue " << x << " failed: full\n";
    }
    Printer::printAll(q, "queue: ");

    if (Result r = q.front(); r.ok()) std::cout << "front = " << r.value << "\n";

    q.dequeue();                       // discard 1
    std::cout << "dequeued " << q.dequeue().value << "\n";
    q.enqueue(5);                      // wraps around the buffer
    q.enqueue(6);
    Printer::printAll(q, "after wrap: ");
    Printer::printAt(q, 1);
    Printer::printAt(q, 5);

    std::cout << "\n=== Both together ===\n";
    Queue r(5);
    for (int x : {1, 2, 3, 4, 5}) r.enqueue(x);
    Printer::printAll(r, "before reverse: ");
    reverseQueue(r, 5);
    Printer::printAll(r, "after reverse:  ");

    int a[] = {1, 2, 3, 2, 1};
    int b[] = {1, 2, 3, 4};
    std::cout << "12321 palindrome? " << (isPalindrome(a, 5) ? "yes" : "no") << "\n";
    std::cout << "1234 palindrome?  " << (isPalindrome(b, 4) ? "yes" : "no") << "\n";

    return 0;
}