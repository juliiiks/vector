#pragma once
#include "iterator.h"

template <typename T>
class Vector {
private:
    // Длина
    int length;
    // Вместительность
    int capacity;
    // Динамический массив
    T* mass;

public:
    // конструктор с длиной
    Vector(int length) {
        this->length = length;
        this->capacity = length * 1.5;
        // Выделение памяти под динамический массив
        this->mass = new T[capacity];
    }

    // Явный конструктор со списком инициализации {}
    explicit Vector(std::initializer_list<T> lst)
        : Vector(lst.size()) {
        int index = 0;
        // Цикл
        for (auto& item : lst) {
            // Перегоняем каждый элемент из списка инициализации в массив
            mass[index] = item;
            ++index;
        }
    }

    // Конструктор копирования
    Vector(const Vector<T>& other) {
        length = other.length;
        capacity = other.capacity;
        mass = new T[other.capacity];
        // копируем другой массив в свой
        memcpy(mass, other.mass, other.length * sizeof(T));
    }

    // Деструктор
    ~Vector() {
        // Освобождаем память
        delete[] mass;
    }

    void shrink_to_fit() {
        mass = (int*)realloc(mass, length);
        capacity = length;
    }

    void print() {
        for (int i = 0; i < length; ++i)
            std::cout << mass[i] << std::endl;
    }

    int get_length() const {
        return length;
    }

    // Изменить по индексу
    void set_elem(int index, const T& elem) {
        if (index < length)
            mass[index] = elem;
        else 
            throw std::out_of_range("Out of range");
    }

    // Получить элемент
    T& get_elem(int index) {
        if (index < length)
            return mass[index];
        else 
            throw std::out_of_range("Out of range");
    }

    // Скопировать новый в массив
    T* to_array() {
        T* new_array = new T[length];
        // Копируем все в новый массив
        memcpy(new_array, mass, length * sizeof(T));
        return new_array;
    }

    // Возвращаем итератор, указывающий на первй элемент
    Iterator<T> begin() {
        return Iterator<T>(*this);
    }
    
    // Возвращаем итератор, указывающий на последний элемент
    Iterator<T> end() {
        return Iterator<T>(*this, this->length);
    }

    Vector<T>& operator=(const Vector<T>& other) {
        length = other.length;
        capacity = other.capacity;
        delete[] mass;
        mass = new T[capacity];
        // Копируем все из другого вектора
        memcpy(mass, other.mass, length * sizeof(T));
        return *this;
    }

    T& operator[](int index) {
        return mass[index];
    }

    Vector<T>& operator+=(const Vector<T>& other) {
        if (this->length != other.get_length())
            throw std::length_error("Vectors are of different length");
    
        for (int i = 0; i < length; ++i)
            mass[i] += other.mass[i];

        return *this;
    }

    Vector<T>& operator-=(const Vector<T>& other) {
        if (this->length != other.get_length())
            throw std::length_error("Vectors are of different length");
    
        for (int i = 0; i < length; ++i)
            mass[i] -= other.mass[i];

        return *this;
    }

    // Умножение вектора на число
    Vector<T>& operator*=(const T& value) {
        for (int i = 0; i < length; ++i)
            mass[i] *= value;
        return *this;
    }

    // Деление вектора на число
    Vector<T>& operator/=(const T& value) {
        for (int i = 0; i < length; ++i)
            mass[i] /= value;
        return *this;
    }

    // Оператор вывода в поток
    template <typename _T>
    friend std::ostream& operator <<(std::ostream& os, Vector<_T>& lst) {
        for (int i = 0; i < lst.get_length(); ++i)
            os << lst[i] << std::endl;
        return os;
    }

    template<typename _T>
    friend Vector<_T> operator+(const Vector<_T>& v1, const Vector<_T>& v2) {
        if (v1.get_length() != v2.get_length())
            throw std::length_error("Vectors are of different length");

        Vector<_T> result = v1;
        result += v2;
        return result;
    }

    template<typename _T>
    friend Vector<_T> operator-(const Vector<_T>& v1, const Vector<_T>& v2) {
        if (v1.get_length() != v2.get_length())
            throw std::length_error("Vectors are of different length");

        Vector<_T> result = v1;
        result -= v2;
        return result;
    }

    template<typename _T>
    friend Vector<_T> operator*(const Vector<_T>& v1, const _T& val) {
        Vector<_T> result = v1;
        result *= val;
        return result;
    }

    template<typename _T>
    friend Vector<_T> operator/(const Vector<_T>& v1, const _T& val) {
        Vector<_T> result = v1;
        result /= val;
        return result;
    }
};
