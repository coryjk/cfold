#include "pch.h"
#include "CppUnitTest.h"
#include "../lattice/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace matrix_simple_tests {
	TEST_CLASS(test) {
	public:
		TEST_METHOD(init) {
			matrix<int> m1();
			matrix<int> m2(5, 5, 0);
			matrix<int> m3(5, 5, 1);
		}
	};
}
