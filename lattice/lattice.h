#ifndef LATTICE_H
#define LATTICE_H

#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>

#include "matrix.h"
#include "aa.h"

using namespace std;

#define UNIT_VEC_COUNT 6
#define DIM 3

class lattice {
public:
    lattice(int len, char init = 'B');
    lattice(const char seq[]);
    lattice(const string& seq);
    lattice(const vector<char>& seq);
    ~lattice();

    const uint32_t size();
    const vector<char>& seq();
    const vector<matrix<int>>& pos();

    const string str();
    bool self_avoiding();
    bool contains(const char seq[]);
    bool contains(const string& seq);

    lattice operator+(const lattice& m);
    lattice operator+(const vector<char>& seq);
    lattice operator=(const lattice& src);
    lattice operator()(const uint32_t& i, const uint32_t& j);

    vector<matrix<int>>* walk_seq(const vector<char>& seq, const int init[3] = { 0 });

private:
    uint32_t _N;
    vector<char> _seq;
    vector<matrix<int>> _pvec;
};

#endif
