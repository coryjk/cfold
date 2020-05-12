#include "pch.h"
#include "CppUnitTest.h"
#include "../lattice/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace matrix_arithmetic_tests {
	TEST_CLASS(test) {
	public:
		struct fixture {
			fixture() { 
				srand(time(NULL));
			}
			const int _CEIL_VAL = 256;
			const int _MATS[5][2] = {
				{3, 3},
				{10, 10},
				{50, 50},
				{50, 10},
				{100, 100}
			};
		};
		TEST_METHOD(add_scalar) {
			struct fixture fx;
			int hi = 5;
			for (const int* params : fx._MATS) {
				// init
				matrix<int> m(params[0], params[1]);
				for (int i = 0; i < m.N(); i++) {
					for (int j = 0; j < m.M(); j++) {
						// random value within [0, fx._CEIL_VAL)
						m(i, j) = rand() % fx._CEIL_VAL;
					}
				}
				// test scalar op using a = [0, hi)
				for (int a = 0; a < hi; a++) {
					matrix<int> res = m + a;
					for (int i = 0; i < m.N(); i++) {
						for (int j = 0; j < m.M(); j++) {
							Assert::AreEqual(res(i, j), m(i, j) + a);
						}
					}
				}
			}
		}

		TEST_METHOD(sub_scalar) {
			struct fixture fx;
			int hi = 5;
			for (const int* params : fx._MATS) {
				// init
				matrix<int> m(params[0], params[1]);
				for (int i = 0; i < m.N(); i++) {
					for (int j = 0; j < m.M(); j++) {
						// random value within [0, fx._CEIL_VAL)
						m(i, j) = rand() % fx._CEIL_VAL;
					}
				}
				// test scalar op using a = [0, hi)
				for (int a = 0; a < hi; a++) {
					matrix<int> res = m - a;
					for (int i = 0; i < m.N(); i++) {
						for (int j = 0; j < m.M(); j++) {
							Assert::AreEqual(res(i, j), m(i, j) - a);
						}
					}
				}
			}
		}

		TEST_METHOD(mult_scalar) {
			struct fixture fx;
			int hi = 5;
			for (const int* params : fx._MATS) {
				// init
				matrix<int> m(params[0], params[1]);
				for (int i = 0; i < m.N(); i++) {
					for (int j = 0; j < m.M(); j++) {
						// random value within [0, fx._CEIL_VAL)
						m(i, j) = rand() % fx._CEIL_VAL;
					}
				}
				// test scalar op using a = [0, hi)
				for (int a = 0; a < hi; a++) {
					matrix<int> res = m * a;
					for (int i = 0; i < m.N(); i++) {
						for (int j = 0; j < m.M(); j++) {
							Assert::AreEqual(res(i, j), m(i, j) * a);
						}
					}
				}
			}
		}

		TEST_METHOD(div_scalar) {
			struct fixture fx;
			int hi = 5;
			for (const int* params : fx._MATS) {
				// init
				matrix<int> m(params[0], params[1]);
				for (int i = 0; i < m.N(); i++) {
					for (int j = 0; j < m.M(); j++) {
						// random value within [0, fx._CEIL_VAL)
						m(i, j) = rand() % fx._CEIL_VAL;
					}
				}
				// test scalar op using a = (0, hi)
				for (int a = 1; a < hi; a++) {
					matrix<int> res = m / a;
					for (int i = 0; i < m.N(); i++) {
						for (int j = 0; j < m.M(); j++) {
							Assert::AreEqual(res(i, j), m(i, j) / a);
						}
					}
				}
			}
		}

		TEST_METHOD(add) {

		}

		TEST_METHOD(sub) {

		}

		TEST_METHOD(mult) {

		}

		TEST_METHOD(div) {

		}
	};

}