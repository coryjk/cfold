#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "matrix.h"

/* =================================================
    Constructors, destructor
   ================================================= */
template <class T>
matrix<T>::matrix(uint32_t r, uint32_t c, const T& init) {
    if (r < 1 || c < 1) {
        r = 1; c = 1;
    }
    _N = r;
    _M = c;
    this->resize(_N, _M, init);
}

/*
    Copy constructor
*/
template <class T>
matrix<T>::matrix(const matrix<T>& m) {
    _N = m._N;
    _M = m._M;
    _data = m._data;
}

/*
    Flat vector constructor

        produces 1 x |v| matrix, given a vector v (note that
        the underlying data is represented by std::vector<std::vector<T>>,
        whereas the input is of type std::vector<T>
*/
template <class T>
matrix<T>::matrix(const vector<T>& v) {
    _N = 1;
    _M = v.size();
    _data = vector<vector<T>>();
    _data.push_back(v);
}

template <class T>
matrix<T>::~matrix() { }

/* =================================================
    Operator overloads
   ================================================= */

/*
    Assignment operator

        assigns current matrix (*this) to input matrix
*/
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

/*
    Helper function for scalar operations

        private helper function for generic scalar operations, where
        the applied elementwise function is passed as a parameter
*/
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

/*
    Scalar addition
        
        X = [a b]   X + n = [a+n, b+n]   
            [c d]           [c+n, d+n]
*/
template <class T>
matrix<T> matrix<T>::operator+(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x + y;
    }, a);
}

/*
    Scalar subtraction

        X = [a b]   X - n = [a-n, b-n]
            [c d]           [c-n, d-n]
*/
template <class T>
matrix<T> matrix<T>::operator-(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x - y;
    }, a);
}

/*
    Scalar multiplication

        X = [a b]   nX = [na, nb]
            [c d]        [nc, nd]
*/
template <class T>
matrix<T> matrix<T>::operator*(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x * y;
    }, a);
}

/*
    Scalar division

        X = [a b]   X/n = [a/n, b/n]
            [c d]         [c/n, d/n]
*/
template <class T>
matrix<T> matrix<T>::operator/(const T& a) {
    return this->_operator_scalar([](const T& x, const T& y) -> T {
        return x / y;
    }, a);
}

/*
    Helper function for some matrix operations

        private helper function for matrix operations that accept
        a function of two matrix elements
*/
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

/*
    Matrix addition

        X = [x1, x2, x3     ] Y = [y1, y2, y3   ]
            [ ...           ]     [ ...         ]

        X + Y = [x1 + y1, x2 + y2, x3 + y3  ]
                [   ...                     ]
*/
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

/*
    Matrix subtraction

        X = [x1, x2, x3     ] Y = [y1, y2, y3   ]
            [ ...           ]     [ ...         ]

        X + Y = [x1 - y1, x2 - y2, x3 - y3  ]
                [   ...                     ]
*/
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

/*
    Matrix multiplication

        provided two matrices X, Y, where both must have
        the same number of columns and rows respectively:

        e.g.
        X: 3 x 2 = [a b]  Y: 2 x 4 = [g h i j]
                   [c d]             [k l m n]
                   [e f]
        
        XY: 3 x 4 = [ag+bk ah+bl ai+bm aj+bn]  
                    [cg+dk ch+dl ci+dm cj+dn]
                    [eg+fk eh+fl ei+fm ej+fn]

        this particular implementation is best used for 
        smaller matrices... there exist more scalable alternatives, 
        such as the Strassen algorithm, multithreading, etc.
*/
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

/*
    Matrix multiplication (1)

        matrix multiplication given an input vector v...
        although the vector shape is technically 1 x |v|, this
        function is for the common case of multiplying N x M
        matrices with an M x 1 vector

        this is done, as representing a 1 x |v| vector literally
        using this class is very space inefficient, requiring
        |v| additional std::vector instances with 1 element each
        (including the extra hidden space)...

        multiplication with 1 x |v| "matrices" is done most easily
        by using the matrix class (can be done via constructor or
        vec2mat)

        v: |v| x 1 (*)
        X: N x M, M = |v|

        Xv: N x 1, also represented by a std::vector
*/
template <class T>
vector<T> matrix<T>::operator*(const vector<T>& v) { 
    if (_M != v.size()) {
        string expected = to_string(_M) + " x 1";
        string actual = to_string(v.size()) + " x 1";
        throw runtime_error("Expected input " + expected + "vector, got " + actual);
    }
    vector<T> res(_N);
    for (int i = 0; i < _N; i++) {
        for (int k = 0; k < v.size(); k++) {
            res[i] += (*this)(i, k) * v[k];
        }
    }
    return res;
}

/*
    Equality check

        two matrices are equal if they have the same shape and
        same elements in the same order
*/
template <class T>
bool matrix<T>::operator==(const matrix<T>& m) {
    if (_N - m.N() + _M - m.M() != 0) {
        return false;
    }
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            if ((*this)(i, j) != m(i, j)) {
                return false;
            }
        }
    }
    return true;
}

/*
    Access operator

        X(i, j) = the j'th element on the i'th row

        may be used for assignment of X(i, j)
*/
template <class T>
T& matrix<T>::operator()(const uint32_t& r, const uint32_t& c) { 
    return _data[r][c];
}

/*
    Access operator (1)

        X(i, j) = the j'th element on the i'th row
*/
template <class T>
const T& matrix<T>::operator()(const uint32_t& r, const uint32_t& c) const {
    return _data[r][c];
}

/* =================================================
    Class methods
   ================================================= */
template <class T>
uint32_t matrix<T>::N() const {
    return _N;
}

template <class T>
uint32_t matrix<T>::M() const { 
    return _M;
}

/*
    Vector to matrix

        modifies current matrix to reflect input std::vector<T> v,
        with shape 1 x |v|, |v| = v.size()

        (*) overrides all current instance data
*/
template <class T>
void matrix<T>::vec2mat(vector<T> v) {
    _N = 1;
    _M = v.size();
    _data = vector<vector<T>>();
    _data.push_back(v);
}

/*
    Vector to matrix (1)

        modifies current instance to reflect input std::vector<std::vector<T>> v,
        with shape v.size() x v[0].size(), corresponding to the number of
        rows and columns respectively

        (*) overrides all current instance data
*/
template <class T>
void matrix<T>::vec2mat(vector<vector<T>> v) {
    _N = v.size();
    _M = v[0].size();
    _data = v;
}

/*
    Resize

        resizes current instance following input number of rows and columns...
        also wipes all data and reinitializes to a set init value
*/
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