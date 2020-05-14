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
    matrix<T> res(*this);
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
matrix<T> matrix<T>::_operator_matrix(function<T(const T&, const T&)> f, const matrix<T>& m) {
    matrix<T> res(*this);
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            res(i, j) = f((*this)(i, j), m(i, j));
        }
    }
    return res;
}

template <class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) { 
    if (_N - m.N() + _M - m.M() != 0) {
        string expected = to_string(_N) + " x " + to_string(_M);
        string actual   = to_string(m.N()) + " x " + to_string(m.M());
        throw runtime_error("Expected input " + expected + "matrix, got " + actual);
    }
    return this->_operator_matrix([](const T& x, const T& y) -> T {
        return x + y;
    }, m);
}

template <class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) { 
    if (_N - m.N() + _M - m.M() != 0) {
        string expected = to_string(_N) + " x " + to_string(_M);
        string actual   = to_string(m.N()) + " x " + to_string(m.M());
        throw runtime_error("Expected input " + expected + "matrix, got " + actual);
    }
    return this->_operator_matrix([](const T& x, const T& y) -> T {
        return x - y;
    }, m);
}

template <class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) { 
    if (_M != m.N()) {
        string expected = to_string(_M) + " x _";
        string actual = to_string(m.N()) + " x " + to_string(m.M());
        throw runtime_error("Expected input " + expected + "matrix, got " + actual);
    }
    matrix<T> res(_N, _M);
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < m.M(); j++) {
            for (int k = 0; k < m.N(); k++) {
                res(i, j) += (*this)(i, k) * m(k, j);
            }
        }
    }
    return res;
}

template <class T>
vector<T> matrix<T>::operator*(const vector<T>& v) { 
    matrix<T> res(_N, _M);

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