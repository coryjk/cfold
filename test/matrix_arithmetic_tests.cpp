#include "pch.h"
#include "CppUnitTest.h"
#include "../lattice/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr int _N_PARAMS = 5;

namespace matrix_arithmetic_tests {
	TEST_CLASS(test) {
	public:
		struct fixture {
			fixture() { 
				srand(time(NULL));
			}
			const int _CEIL_VAL = 256;
			const int _MATS[_N_PARAMS][2] = {
				{3, 3},
				{10, 10},
				{50, 50},
				{50, 10},
				{100, 100}
			};
			const int _SQUARE_MATS[_N_PARAMS][2] = {
				{2, 2},
				{10, 10},
				{50, 50},
				{100, 100},
				{256, 256}
			};
		};
		static void _random_init(matrix<int>* m, struct fixture* fx) {
			for (int i = 0; i < m->N(); i++) {
				for (int j = 0; j < m->M(); j++) {
					// random value within [0, fx._CEIL_VAL)
					(*m)(i, j) = rand() % fx->_CEIL_VAL;
				}
			}
		}
		TEST_METHOD(add_scalar) {
			struct fixture fx;
			int hi = 5;
			for (const int* params : fx._MATS) {
				// init
				matrix<int> m(params[0], params[1]);
				_random_init(&m, &fx);
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
				_random_init(&m, &fx);
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
				_random_init(&m, &fx);
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
				_random_init(&m, &fx);
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
			struct fixture fx;
			for (const int* params : fx._MATS) {
				// init
				matrix<int> A(params[0], params[1]);
				matrix<int> B(params[0], params[1]);
				_random_init(&A, &fx);
				_random_init(&B, &fx);

				matrix<int> C = A + B;
				// test matrix op
				for (int i = 0; i < A.N(); i++) {
					for (int j = 0; j < A.M(); j++) {
						Assert::AreEqual(C(i, j), A(i, j) + B(i, j));
					}
				}
			}
		}

		TEST_METHOD(sub) {
			struct fixture fx;
			for (const int* params : fx._MATS) {
				// init
				matrix<int> A(params[0], params[1]);
				matrix<int> B(params[0], params[1]);
				_random_init(&A, &fx);
				_random_init(&B, &fx);

				matrix<int> C = A - B;
				// test matrix op
				for (int i = 0; i < A.N(); i++) {
					for (int j = 0; j < A.M(); j++) {
						Assert::AreEqual(C(i, j), A(i, j) - B(i, j));
					}
				}
			}
		}

		TEST_METHOD(mult_mat) {
			struct fixture fx;
			for (const int* params : fx._SQUARE_MATS) {
				// init
				matrix<int> A(params[0], params[1]);
				matrix<int> I = matrix<int>::identity_matrix(params[0]);
				_random_init(&A, &fx);

				// note: implicit test of operator==() and operator!=()
				Assert::IsTrue(A*I == A);
				Assert::IsTrue(A*I - 1 != A);
			}
		}

		TEST_METHOD(mult_vector) {

		}
	};

}