struct B; // Forward declaration

struct A {
    std::shared_ptr<B> b_ptr;
};

struct B {
    std::shared_ptr<A> a_ptr;
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;
    // Even after main() ends, a and b will NOT be destroyed!
}

/*
A weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object managed by shared_ptr. It does not increase the reference count. This means it allows you to observe or access the object, without participating in its ownership.

Solution to circular reference:
To break the cycle, make one of the pointers a weak_ptr:

*/
struct B; // Forward declaration

struct A {
    std::shared_ptr<B> b_ptr;
};

struct B {
    std::weak_ptr<A> a_ptr; // Notice the weak_ptr here!
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;
    // Now, when a and b go out of scope, memory is freed correctly.
}
