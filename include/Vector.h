#pragma once
#include <algorithm>
#include <exception>

template<class T>
class Vector
{
private:
    T* data;
    size_t capacity, size;

public:
    Vector(const int& size = 0, T init = T()) : capacity(2 * size + 1), size(size)
    {
        if (size < 0)
        {
            throw std::exception("invalid vector size");
        }
        data = new T[capacity];
        std::fill(data, data + size, init);
    }
    Vector(const char* str)
    {
        size = 0;
        capacity = 1;
        data = new T[capacity];
        size_t i = 0;
        while (str[i] != '\0') push_back(str[i++]);
    }
    Vector(Vector&& v)
    {
        data = nullptr;
        std::swap(data, v.data);
        capacity = v.capacity;
        size = v.size;
    }
    Vector(Vector& v) : capacity(v.capacity), size(v.size)
    {
        data = new T[capacity];
        std::copy(v.data, v.data + v.capacity, data);
    }
    ~Vector()
    {
        capacity = 0;
        size = 0;
        delete[] data;
    }
    Vector& operator=(const Vector& v)
    {
        if (this == &v) return *this;
        if (capacity < v.capacity)
        {
            T* tmp = new T[v.capacity];
            delete[] data;
            data = tmp;
            capacity = v.capacity;
        }
        std::copy(v.data, v.data + v.capacity, data);
        size = v.size;
        return *this;
    }
    Vector& operator=(Vector&& v)
    {
        delete[] data;
        data = nullptr;
        std::swap(data, v.data);
        capacity = v.capacity;
        size = v.size;
        return *this;
    }
    bool operator==(const Vector& v) const noexcept
    {
        if (size != v.size) return false;
        for (int i = 0; i < size; i++)
        {
            if (data[i] != v.data[i]) return false;
        }
        return true;
    }
    bool operator!=(const Vector& v) const noexcept
    {
        return !(*this == v);
    }
    size_t length() const noexcept
    {
        return size;
    }
    T& operator[](const int& ind) noexcept
    {
        return data[ind];
    }
    const T& operator[](const int& ind) const noexcept
    {
        return data[ind];
    }
    void push_back(const T& item)
    {
        if (size == capacity)
        {
            T* tmp = new T[2 * capacity];
            std::copy(data, data + capacity, tmp);
            delete[] data;
            data = tmp;
            capacity = 2 * capacity;
        }
        data[size++] = item;
        return;
    }
    void pop_back() noexcept
    {
        size--;
        return;
    }
    T& back() const noexcept
    {
        return data[size - 1];
    }
    void clear()
    {
        capacity = 1;
        size = 0;
        delete[] data;
        data = new T[capacity];
        return;
    }
};