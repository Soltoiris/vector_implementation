#include <algorithm>
#include <cstddef>
#include <initializer_list>

template <typename T>
class my_vector {
private:
    T* data;
    size_t cap;
    size_t sz;

    void rebuild(size_t new_cap) {
        T* new_data = new T[new_cap];
        
        for (size_t i = 0; i < std::min(sz, new_cap); ++i) {
            new_data[i] = data[i];
        }
        
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

public:
    my_vector() : data(nullptr), cap(0), sz(0) {}
    
    my_vector(size_t new_sz) : cap(new_sz), sz(new_sz) {
        data = new T[cap];
    }
    
    my_vector(size_t new_sz, const T& a) : cap(new_sz), sz(new_sz) {
        data = new T[cap];
        for (size_t i = 0; i < sz; ++i) {
            data[i] = a;
        }
    }
    
    ~my_vector() {
        delete[] data;
    }

    my_vector(const my_vector& other) : cap(other.cap), sz(other.sz) {
        data = new T[cap];
        for (size_t i = 0; i < sz; ++i) {
            data[i] = other.data[i];
        }
    }
    
    my_vector& operator=(const my_vector& other) {
        if (this != &other) {
            delete[] data;
            cap = other.cap;
            sz = other.sz;
            data = new T[cap];
            for (size_t i = 0; i < sz; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T& operator[](size_t i) {
        return data[i];
    }
    
    T& front() {
        return data[0];
    }
    
    T& back() {
        return data[sz - 1];
    }

    T* begin() {
        return data;
    }
    
    T* end() {
        return data + sz;
    }

    void push_back(const T& value) {
        if (sz + 1 > cap) {
            size_t new_cap = std::max(cap, 1);
            new_cap  <<= 1;

            rebuild(new_cap);
        }

        data[sz] = value;
        sz++;
    }
    
    void pop_back() {
        if (sz > 0) {
            sz--;
        }
    }
    
    void resize(size_t new_sz) {
        size_t sz_was = sz;
        size_t new_cap = std::max(cap, 1);

        while (new_sz > new_cap) {
            new_cap <<= 1;
        }

        if (new_cap > cap) {
            rebuild(new_cap);
        }

        sz = new_sz;
    }
    
    void resize(size_t new_sz, const T& value) {
        size_t sz_was = sz;
        size_t new_cap = std::max(cap, 1);

        while (new_sz > new_cap) {
            new_cap <<= 1;
        }

        if (new_cap > cap) {
            rebuild(new_cap);
        }

        sz = new_sz;
        
        if (new_sz > sz_was) {
            for (size_t i = sz_was; i < new_sz; ++i) {
                data[i] = value;
            }
        }
    }

    void assign(size_t new_sz) {
        delete[] data;
    
        data = new T[new_sz];
        cap = new_sz;
        sz = new_sz;
    }

    void assign(size_t new_sz, const T& value) {
        delete[] data;
    
        data = new T[new_sz];
        cap = new_sz;
        sz = new_sz;
        
        for (size_t i = 0; i < new_sz; ++i) {
            data[i] = value;
        }
    }

    void assign(std::initializer_list<T> ilist) {
        size_t new_sz = ilist.size();
        
        delete[] data;
        
        data = new T[new_sz];
        cap = new_sz;
        sz = new_sz;
        
        size_t i = 0;
        for (const auto& item : ilist) {
            data[i] = item;
            i++;
        }
    }

    
    void clear() {
        sz = 0;
    }

    size_t size() const {
        return sz;
    }
    
    size_t capacity() const {
        return cap;
    }
    
    bool empty() const {
        return sz == 0;
    }
};
