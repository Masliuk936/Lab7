#include <gtest/gtest.h>
#include "LinearSystem.h"
#include "LinearSystemExceptions.h"
#include <vector>
#include <limits>

TEST(LinearSystemTest, CreatesValidSystem) {
    std::vector<double> A = { 2, 1, 1, 3 };
    std::vector<double> b = { 4, 7 };
    EXPECT_NO_THROW(LinearSystem sys(A, b, 2));
}

TEST(LinearSystemTest, RejectsInvalidSize) {
    std::vector<double> A = { 1, 2, 3, 4 };
    std::vector<double> b = { 1 };
    EXPECT_THROW(LinearSystem(A, b, 2), InvalidSizeException);

    std::vector<double> A2 = { 1, 2, 3 };
    std::vector<double> b2 = { 1, 2 };
    EXPECT_THROW(LinearSystem(A2, b2, 2), std::invalid_argument);
}

TEST(LinearSystemTest, RejectsNonFiniteData) {
    const double inf = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();

    std::vector<double> A = { 1, inf, 3, 4 };
    std::vector<double> b = { 1, 2 };
    EXPECT_THROW(LinearSystem(A, b, 2), InvalidDataException);

    std::vector<double> A2 = { 1, 2, 3, 4 };
    std::vector<double> b2 = { nan, 2 };
    EXPECT_THROW(LinearSystem(A2, b2, 2), InvalidDataException);
}

TEST(LinearSystemTest, SolvesValidSystem) {
    std::vector<double> A = { 2, 1, 1, 3 };
    std::vector<double> b = { 5, 10 };
    LinearSystem sys(A, b, 2);

    std::vector<double> x = sys.solve();

    ASSERT_EQ(x.size(), 2);
    EXPECT_NEAR(x[0], 1.0, 1e-6);
    EXPECT_NEAR(x[1], 3.0, 1e-6);
}

TEST(LinearSystemTest, ThrowsOnSingularMatrix) {
    std::vector<double> A = { 1, 2, 2, 4 };
    std::vector<double> b = { 3, 6 };
    LinearSystem sys(A, b, 2);

    EXPECT_THROW(sys.solve(), SingularMatrixException);
}

TEST(LinearSystemTest, UpdateSystemPreservesStateOnException) {
    std::vector<double> A = { 2, 1, 1, 3 };
    std::vector<double> b = { 4, 7 };
    LinearSystem sys(A, b, 2);

    std::vector<double> bad_b = { 1 };

    EXPECT_THROW(sys.updateSystem(A, bad_b, 2), InvalidSizeException);

    EXPECT_EQ(sys.getSize(), 2);
    std::vector<double> x = sys.solve();
    EXPECT_NEAR(x[0], 1.0, 1e-6);
    EXPECT_NEAR(x[1], 2.0, 1e-6);
}

TEST(LinearSystemTest, CheckSolutionWorks) {
    std::vector<double> A = { 1, 1, 1, -1 };
    std::vector<double> b = { 2, 0 };
    LinearSystem sys(A, b, 2);

    std::vector<double> x = { 1.0, 1.0 };
    std::vector<double> res = sys.residual(x);

    EXPECT_TRUE(sys.checkSolution(res, 1e-6));
}