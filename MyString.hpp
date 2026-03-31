#ifndef SIMPLE_STRING_SIMPLESTRING_HPP
#define SIMPLE_STRING_SIMPLESTRING_HPP

#include <stdexcept>
#include <cstring>

class MyString {
private:
    static constexpr size_t SSO_SIZE = 15;

    union {
        char* heap_ptr;
        char small_buffer[16];
    };

    size_t length;
    size_t cap;

    bool is_sso() const {
        return cap == SSO_SIZE;
    }

    char* data_ptr() {
        return is_sso() ? small_buffer : heap_ptr;
    }

    const char* data_ptr() const {
        return is_sso() ? small_buffer : heap_ptr;
    }

public:
    MyString() : length(0), cap(SSO_SIZE) {
        small_buffer[0] = '\0';
    }

    MyString(const char* s) {
        if (s == nullptr) {
            length = 0;
            cap = SSO_SIZE;
            small_buffer[0] = '\0';
            return;
        }

        length = std::strlen(s);

        if (length <= SSO_SIZE) {
            cap = SSO_SIZE;
            std::memcpy(small_buffer, s, length + 1);
        } else {
            cap = length;
            heap_ptr = new char[cap + 1];
            std::memcpy(heap_ptr, s, length + 1);
        }
    }

    MyString(const MyString& other) {
        length = other.length;
        cap = other.cap;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, length + 1);
        } else {
            heap_ptr = new char[cap + 1];
            std::memcpy(heap_ptr, other.heap_ptr, length + 1);
        }
    }

    MyString(MyString&& other) noexcept {
        length = other.length;
        cap = other.cap;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, length + 1);
        } else {
            heap_ptr = other.heap_ptr;
            other.heap_ptr = nullptr;
        }

        other.length = 0;
        other.cap = SSO_SIZE;
        other.small_buffer[0] = '\0';
    }

    MyString& operator=(MyString&& other) noexcept {
        if (this == &other) return *this;

        if (!is_sso()) {
            delete[] heap_ptr;
        }

        length = other.length;
        cap = other.cap;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, length + 1);
        } else {
            heap_ptr = other.heap_ptr;
            other.heap_ptr = nullptr;
        }

        other.length = 0;
        other.cap = SSO_SIZE;
        other.small_buffer[0] = '\0';

        return *this;
    }

    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;

        if (!is_sso()) {
            delete[] heap_ptr;
        }

        length = other.length;
        cap = other.cap;

        if (other.is_sso()) {
            std::memcpy(small_buffer, other.small_buffer, length + 1);
        } else {
            heap_ptr = new char[cap + 1];
            std::memcpy(heap_ptr, other.heap_ptr, length + 1);
        }

        return *this;
    }

    ~MyString() {
        if (!is_sso()) {
            delete[] heap_ptr;
        }
    }

    const char* c_str() const {
        return data_ptr();
    }

    size_t size() const {
        return length;
    }

    size_t capacity() const {
        if (is_sso()) {
            return SSO_SIZE;
        }
        return cap;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity()) {
            return;
        }

        if (is_sso() && new_capacity > SSO_SIZE) {
            char* new_ptr = new char[new_capacity + 1];
            std::memcpy(new_ptr, small_buffer, length + 1);
            heap_ptr = new_ptr;
            cap = new_capacity;
        } else if (!is_sso()) {
            char* new_ptr = new char[new_capacity + 1];
            std::memcpy(new_ptr, heap_ptr, length + 1);
            delete[] heap_ptr;
            heap_ptr = new_ptr;
            cap = new_capacity;
        }
    }

    void resize(size_t new_size) {
        if (new_size > capacity()) {
            reserve(new_size);
        }

        if (new_size > length) {
            char* ptr = data_ptr();
            for (size_t i = length; i < new_size; ++i) {
                ptr[i] = '\0';
            }
            ptr[new_size] = '\0';
        } else if (new_size < length) {
            data_ptr()[new_size] = '\0';
        }

        length = new_size;
    }

    char& operator[](size_t index) {
        return data_ptr()[index];
    }

    MyString operator+(const MyString& rhs) const {
        MyString result;
        size_t new_length = length + rhs.length;

        if (new_length > SSO_SIZE) {
            result.cap = new_length;
            result.heap_ptr = new char[result.cap + 1];
            std::memcpy(result.heap_ptr, data_ptr(), length);
            std::memcpy(result.heap_ptr + length, rhs.data_ptr(), rhs.length + 1);
        } else {
            result.cap = SSO_SIZE;
            std::memcpy(result.small_buffer, data_ptr(), length);
            std::memcpy(result.small_buffer + length, rhs.data_ptr(), rhs.length + 1);
        }

        result.length = new_length;
        return result;
    }

    void append(const char* str) {
        if (str == nullptr || *str == '\0') return;

        size_t str_len = std::strlen(str);
        size_t new_length = length + str_len;

        if (new_length > capacity()) {
            size_t new_cap = capacity();
            while (new_cap < new_length) {
                new_cap = new_cap * 3 / 2 + 1;
            }
            reserve(new_cap);
        }

        char* ptr = data_ptr();
        std::memcpy(ptr + length, str, str_len + 1);
        length = new_length;
    }

    const char& at(size_t pos) const {
        if (pos >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data_ptr()[pos];
    }

    class const_iterator;

    class iterator {
    private:
        char* ptr;

    public:
        iterator(char* p) : ptr(p) {}

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }

        iterator& operator--() {
            --ptr;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --ptr;
            return temp;
        }

        char& operator*() const {
            return *ptr;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }

        friend class const_iterator;
    };

    class const_iterator {
    private:
        const char* ptr;

    public:
        const_iterator(const char* p) : ptr(p) {}

        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++ptr;
            return temp;
        }

        const_iterator& operator--() {
            --ptr;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator temp = *this;
            --ptr;
            return temp;
        }

        const char& operator*() const {
            return *ptr;
        }

        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        friend class iterator;
    };

    iterator begin() {
        return iterator(data_ptr());
    }

    iterator end() {
        return iterator(data_ptr() + length);
    }

    const_iterator cbegin() const {
        return const_iterator(data_ptr());
    }

    const_iterator cend() const {
        return const_iterator(data_ptr() + length);
    }
};

#endif
