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
        bool resizable_;
        int minCap_;

        void resize(int newCap) {
            T* fresh = new T[newCap]{};
            for (int i = 0; i < count_; ++i) {
                fresh[i] = arr_[(f_ + i) % cap_];
            }
            delete[] arr_;
            arr_ = fresh;
            cap_ = newCap;
            f_ = 0;
        }

        // Called at the start of each push. Returns false if the push must be rejected.
        bool makeRoom() {
            if (count_ < cap_) return true;
            if (!resizable_) return false;
            resize(cap_ > 0 ? cap_ * 2 : 1);
            return true;
        }

        // Called at the end of each pop.
        void maybeShrink() {
            if (resizable_ && cap_ > minCap_ && count_ <= cap_ / 4) {
                int half = cap_ / 2;
                resize(half > minCap_ ? half : minCap_);
            }
        }

    public:
        Deque(int n, bool resizable = false)
            : arr_(new T[n]{}), cap_(n), f_(0), count_(0),
              resizable_(resizable), minCap_(n) {}

        ~Deque() {
            delete[] arr_;
            arr_ = nullptr;
        }

        Deque(const Deque&) = delete;
        Deque& operator=(const Deque&) = delete;

        Status push_back(const T& x) {
            if (!makeRoom()) {
                return Status::Full;
            }
            arr_[(f_ + count_) % cap_] = x;
            count_++;
            return Status::Ok;
        }

        Status push_front(const T& x) {
            if (!makeRoom()) {
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
            maybeShrink();
            return {Status::Ok, temp};
        }

        Result<T> pop_back() {
            if (isEmpty()) {
                return {Status::Empty, T{}};
            }
            T temp = arr_[(f_ + count_ - 1) % cap_];
            count_--;
            maybeShrink();
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
        bool isFull() const { return !resizable_ && count_ == cap_; }
        bool isEmpty() const { return count_ == 0; }
        int size() const { return count_; }
        int capacity() const { return cap_; }
};