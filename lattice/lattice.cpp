#include "lattice.h"

lattice::lattice(int len, char init) {
    _N = len;
    _seq = vector<char>(_N, init);
}

lattice::lattice(const char seq[]) {
    _N = strlen(seq);
    _seq = vector<char>(seq, seq + DIM);
}

lattice::lattice(const string& seq) : lattice(seq.c_str()) { }

lattice::lattice(const vector<char>& seq) {
    _N = seq.size();
    _seq.insert(_seq.begin(), seq.begin(), seq.end());
}

lattice::~lattice() { }

const uint32_t lattice::size() {
    return _N;
}

const vector<char>& lattice::seq() {
    return _seq;
}

const vector<matrix<int>>& lattice::pos() {
    return _pvec;
}

const string lattice::str() {
    return string(_seq.begin(), _seq.end());
}

bool lattice::self_avoiding() {

    return false;
}

bool lattice::contains(const char seq[]) {

    return false;
}

bool lattice::contains(const string& seq) {

    return false;
}

vector<matrix<int>>* lattice::walk_seq(const vector<char>& seq, const int init[3]) {
    vector<matrix<int>>* p = new vector<matrix<int>>();
    vector<int> v;
    matrix<int> m;

    v = vector<int>(init, init + DIM);
    m.vec2mat(v);

    p->push_back(m);
    // track cumulative sum of directional components to define position at index = i
    for (int i = 1; i < (int)seq.size()+1; i++) {
        // p[i] = p[i - 1] + (DIR.at(seq[i]));
        matrix<int> dir_vec;
        dir_vec.vec2mat(DIR.at(seq[i]));
        p->push_back((*p)[i - 1] + dir_vec);
    }
    return p;
}

lattice lattice::operator+(const lattice& m) {
    vector<char> union_seq(this->seq());
    union_seq.insert(union_seq.end(), m._seq.begin(), m._seq.end());
    return lattice(union_seq);
}

lattice lattice::operator+(const vector<char>& seq) {
    vector<char> union_seq(this->seq());
    union_seq.insert(union_seq.end(), seq.begin(), seq.end());
    return lattice(union_seq);
}

lattice lattice::operator=(const lattice& src) {
    return lattice(src._seq);
}

lattice lattice::operator()(const uint32_t& i, const uint32_t& j) {
    return nullptr;
}

int main() {
    return 0;
}