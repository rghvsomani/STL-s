class ResourceManager {
    int* data;
    size_t size;

public:
    ResourceManager(size_t sz = 0)
      : data(sz ? new int[sz] : nullptr), size(sz) {}

    ~ResourceManager() { delete[] data; }

    // Copy constructor (deep copy)
    ResourceManager(const ResourceManager& other)
      : data(other.size ? new int[other.size] : nullptr),
        size(other.size) {
        std::copy(other.data, other.data + size, data);
    }

    // Copy assignment operator
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.size ? new int[other.size] : nullptr;
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    // Move constructor
    ResourceManager(ResourceManager&& other) noexcept
      : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // Move assignment operator
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
