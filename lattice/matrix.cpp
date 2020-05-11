#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "matrix.h"

template <class T>
matrix<T>::matrix(uint32_t r, uint32_t c, const T& init) {
    _N = r;
    _M = c;
    _data.resize(_N);
    for (int i = 0; i < _N; i++) {
        _data[i].resize(_M, init);
    }
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
    _N = m.N();
    _M = m.M();
    _data.resize(_N);
    for (int i = 0; i < _N; i++) {
        _data[i].resize(_M);
    }
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            _data[i][j] = m(i, j);
        }
    }
    return *this;
}

template <class T>
matrix<T> matrix<T>::operator+(const T& a) {
    matrix<T> res;
    vector<vector<T>> new_data(_N, vector<T>(_M, _data[0][0]));
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            new_data[i][j] = _data[i][j] + a;
        }
    }
    res.vec2mat(new_data);
    return res;
}

template <class T>
matrix<T> matrix<T>::operator-(const T& a) {
    matrix<T> res;
    vector<vector<T>> new_data(_N, vector<T>(_M, _data[0][0]));
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            new_data[i][j] = _data[i][j] - a;
        }
    }
    res.vec2mat(new_data);
    return res;
}

template <class T>
matrix<T> matrix<T>::operator*(const T& a) {
    matrix<T> res;
    vector<vector<T>> new_data(_N, vector<T>(_M, _data[0][0]));
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            new_data[i][j] = _data[i][j] * a;
        }
    }
    res.vec2mat(new_data);
    return res;
}

template <class T>
matrix<T> matrix<T>::operator/(const T& a) {
    matrix<T> res;
    vector<vector<T>> new_data(_N, vector<T>(_M, _data[0][0]));
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            new_data[i][j] = _data[i][j] / a;
        }
    }
    res.vec2mat(new_data);
    return res;
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

#endif