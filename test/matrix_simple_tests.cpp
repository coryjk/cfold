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
				_M_3x3_0 = matrix<int>(3, 3, 0);
				_M_zeros.push_back(_M_3x3_0);
				return 0;
			}
			vector<matrix<int>> _M_zeros;
			matrix<int> _M_3x3_0;
		};
		TEST_METHOD(init) {
			matrix<int> m1;
			matrix<int> m2(5, 5, 0);
			matrix<int> m3(5, 5, 1);
			Assert::IsTrue(true);
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
	};
}
