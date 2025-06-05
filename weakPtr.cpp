#include <cstddef> // for std::size_t

// Forward declaration
template<typename T> class WeakPtr;

template<typename T>
class SharedPtr {
    T* ptr;
    std::size_t* ref_count;
    std::size_t* weak_count;
    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            if (*weak_count == 0) {
                delete ref_count;
                delete weak_count;
            }
        }
    }
    void decrease_weak() {
        if (weak_count && --(*weak_count) == 0 && (!ref_count || *ref_count == 0)) {
            delete ref_count;
            delete weak_count;
        }
    }
public:
    SharedPtr(T* p = nullptr)
        : ptr(p), ref_count(new std::size_t(p ? 1 : 0)), weak_count(new std::size_t(0)) {}

    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        if (ptr) ++(*ref_count);
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            if (ptr) ++(*ref_count);
        }
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
    std::size_t use_count() const { return ref_count ? *ref_count : 0; }

    // For WeakPtr
    friend class WeakPtr<T>;
    SharedPtr(T* p, std::size_t* rc, std::size_t* wc)
        : ptr(p), ref_count(rc), weak_count(wc) {
        if (ptr) ++(*ref_count);
    }
};

template<typename T>
class WeakPtr {
    T* ptr;
    std::size_t* ref_count;
    std::size_t* weak_count;
public:
    WeakPtr() : ptr(nullptr), ref_count(nullptr), weak_count(nullptr) {}

    WeakPtr(const SharedPtr<T>& sp)
        : ptr(sp.ptr), ref_count(sp.ref_count), weak_count(sp.weak_count) {
        if (weak_count) ++(*weak_count);
    }

    WeakPtr(const WeakPtr& other)
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        if (weak_count) ++(*weak_count);
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            if (weak_count) decrease_weak();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            if (weak_count) ++(*weak_count);
        }
        return *this;
    }

    ~WeakPtr() {
        if (weak_count) decrease_weak();
    }

    std::size_t use_count() const { return ref_count ? *ref_count : 0; }
    bool expired() const { return use_count() == 0; }

    SharedPtr<T> lock() const {
        if (!expired())
            return SharedPtr<T>(ptr, ref_count, weak_count);
        else
            return SharedPtr<T>();
    }

private:
    void decrease_weak() {
        if (weak_count && --(*weak_count) == 0 && (!ref_count || *ref_count == 0)) {
            delete ref_count;
            delete weak_count;
        }
    }
};
