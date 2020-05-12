#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "matrix.h"

template <class T>
matrix<T>::matrix(uint32_t r, uint32_t c, const T& init) {
    if (r < 1 || c < 1) {
        r = 1; c = 1;
    }
    _N = r;
    _M = c;
    this->resize(_N, _M, init);
}

template <class T>
matrix<T>::matrix(const matrix<T>& m) {
    _N = m._N;
    _M = m._M;
    _data = m._data;
}

template <class T>
matrix<T>::~matrix() { }

template <class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m) {
    if (&m == this) {
        return *this;
    }
    this->resize(m.N(), m.M());
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            _data[i][j] = m(i, j);
        }
    }
    return *this;
}

template<class T>
matrix<T> matrix<T>::_operator_scalar(function<T(const T&, const T&)> f, const T& a) {
    matrix<int> res(*this);
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            res(i, j) = f((*this)(i, j), a);
        }
    }
    return res;
}

template <class T>
matrix<T> matrix<T>::operator+(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x + y;
    }, a);
}

template <class T>
matrix<T> matrix<T>::operator-(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x - y;
    }, a);
}

template <class T>
matrix<T> matrix<T>::operator*(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x * y;
    }, a);
}

template <class T>
matrix<T> matrix<T>::operator/(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x / y;
    }, a);
}

template <class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) { 
    matrix<T> res;
    return res;
}

template <class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) { 
    matrix<T> res;
    return res;
}

template <class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) { 
    matrix<T> res;
    return res;
}

template <class T>
vector<T> matrix<T>::operator*(const vector<T>& v) { 
    matrix<T> res;
    return res;
}

template <class T>
T& matrix<T>::operator()(const uint32_t& r, const uint32_t& c) { 
    return _data[r][c];
}

template <class T>
const T& matrix<T>::operator()(const uint32_t& r, const uint32_t& c) const {
    return _data[r][c];
}

template <class T>
uint32_t matrix<T>::N() const {
    return _N;
}

template <class T>
uint32_t matrix<T>::M() const { 
    return _M;
}

template <class T>
void matrix<T>::vec2mat(vector<T> v) {
    _N = 1;
    _M = v.size();
    _data = vector<vector<T>>();
    _data.push_back(v);
}

template <class T>
void matrix<T>::vec2mat(vector<vector<T>> v) {
    _N = v.size();
    _M = v[0].size();
    _data = v;
}

template <class T>
void matrix<T>::resize(int r, int c, const T& init) {
    if (r < 1 || c < 1) {
        return;
    }
    _N = r;
    _M = c;
    _data.resize(_N);
    for (int i = 0; i < _N; i++) {
        _data[i].resize(_M);
        fill(_data[i].begin(), _data[i].end(), init);
    }
}

#endif