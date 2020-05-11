#ifndef __MATRIX_H
#define __MATRIX_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <assert.h>

using namespace std;

template <typename T> class matrix {
public:
    matrix() : matrix(1, 1, 0) {};
    matrix(uint32_t r, uint32_t c, const T& init);
    matrix(const matrix<T>& m);
    ~matrix();

    matrix<T>& operator=(const matrix<T>& m);

    // scalar operations
    matrix<T> operator+(const T& a);
    matrix<T> operator-(const T& a);
    matrix<T> operator*(const T& a);
    matrix<T> operator/(const T& a);

    // vector operations
    matrix<T> operator+(const matrix<T>& m);
    matrix<T> operator-(const matrix<T>& m);
    matrix<T> operator*(const matrix<T>& m);
    vector<T> operator*(const vector<T>& v);

    // access
    T& operator()(const uint32_t& r, const uint32_t& c);
    const T& operator()(const uint32_t& r, const uint32_t& c) const;
    uint32_t N() const;
    uint32_t M() const;

    void vec2mat(vector<T> v);
    void vec2mat(vector<vector<T>> v);
    void resize(int r, int c, const T& init = 0);

private:
    vector<vector<T>> _data;
    uint32_t _N = 1;
    uint32_t _M = 1;
};

#include "matrix.cpp"

#endif