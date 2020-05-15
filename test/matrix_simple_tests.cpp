#include "pch.h"
#include "CppUnitTest.h"
#include "../lattice/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace matrix_simple_tests {
	TEST_CLASS(test) {
	public:
		struct fixture {
			fixture() {
				_zero_matrices();
			}
			int _zero_matrices() {
				_M_1x1_0 = matrix<int>(1, 1, 0);
				_M_3x3_0 = matrix<int>(3, 3, 0);
				_M_256x256_0 = matrix<int>(256, 256, 0);

				_M_zeros.push_back(_M_1x1_0_DEFAULT);
				_M_zeros.push_back(_M_1x1_0);
				_M_zeros.push_back(_M_3x3_0);
				_M_zeros.push_back(_M_256x256_0);
				return 0;
			}
			vector<matrix<int>> _M_zeros;
			matrix<int> _M_1x1_0_DEFAULT;
			matrix<int> _M_1x1_0;
			matrix<int> _M_3x3_0;
			matrix<int> _M_256x256_0;
		};
		TEST_METHOD(init) {
			matrix<int> m1;
			matrix<int> m2(5, 5, 0);
			matrix<int> m3(5, 5, 1);
			Assert::IsTrue(true);
		}
		TEST_METHOD(vec2mat_simple) {
			vector<int> ones_1x3({ 1, 1, 1 });
			vector<vector<int>> identity_3x3({
				{1, 0, 0},
				{0, 1, 0},
				{0, 0, 1}
			});
			matrix<int> m;
			// 1 x 3 
			m.vec2mat(ones_1x3);
			Assert::IsTrue(m.N()-1 == 0);
			Assert::IsTrue(m.M()-ones_1x3.size() == 0);
			for (int i = 0; i < m.N(); i++) {
				for (int j = 0; j < m.M(); j++) {
					Assert::IsTrue(m(i, j) == ones_1x3[j]);
				}
			}
			// 3 x 3 identity
			m.vec2mat(identity_3x3);
			Assert::IsTrue(m.N() - identity_3x3.size() == 0);
			Assert::IsTrue(m.M() - identity_3x3[0].size() == 0);
			for (int i = 0; i < m.N(); i++) {
				for (int j = 0; j < m.M(); j++) {
					Assert::IsTrue(m(i, j) == identity_3x3[i][j]);
				}
			}
		}
		TEST_METHOD(vec2mat_medium) {
			// init
			srand(time(NULL));
			int lo = 0, hi = 1000;
			int params[3][2] = {
				{300, 300},
				{500, 1000},
				{1000, 500}
			};
			matrix<int> m;
			for (int* dims : params) {
				vector<vector<int>> v(dims[0], vector<int>(dims[1], 0));
				// define target vector
				for (int i = 0; i < v.size(); i++) {
					for (int j = 0; j < v[0].size(); j++) {
						v[i][j] = rand() % (hi - lo) + lo;
					}
				}
				// vec2mat
				m.vec2mat(v);
				// perform NM/2 random checks
				for (int i = 0; i < m.N() * m.M() / 2; i++) {
					int _r = rand() % m.N(), _c = rand() % m.M();
					Assert::AreEqual(m(_r,_c), v[_r][_c]);
				}
			}
		}
		TEST_METHOD(zeros1) {
			fixture fx;
			for (int i = 0; i < fx._M_zeros.size(); i++) {
				matrix<int> mat = fx._M_zeros[i];
				for (int n = 0; n < mat.N(); n++) {
					for (int m = 0; m < mat.M(); m++) {
						Assert::AreEqual(mat(n, m), 0);
					}
				}
			}
		}

		TEST_METHOD(resize) {
			// init
			srand(time(NULL)); // using random seed based on time
			const int n_params = 6;
			int params[n_params][3] = {
				{1, 1, 0},
				{1, 1, 1},
				{5, 5, 0},
				{5, 10, 0},
				{10, 10, 5},
				{256, 256, 3}
			};
			matrix<int> m;
			for (int i = 0; i < n_params; i++) {
				int N = params[i][0];
				int M = params[i][1];
				int val = params[i][2];
				m.resize(N, M, val);
				// dimensionality check
				Assert::IsTrue(N == m.N());
				Assert::IsTrue(M == m.M());
				// perform NM/2 random checks
				for (int j = 0; j < N * M / 2; j++) {
					int res = m(rand() % N, rand() % M);
					Assert::IsTrue(res == val);
				}
			}
		}
	};
}
