#pragma once
#include <vector>

class LinearSystem {
private:
    std::vector<double> mat_;
    std::vector<double> vec_;
    int n_;

    static void validateData(const std::vector<double>& A, const std::vector<double>& b, int n);

public:
    LinearSystem(const std::vector<double>& A, const std::vector<double>& b, int n);

    void updateSystem(const std::vector<double>& newA, const std::vector<double>& newb, int newN);

    std::vector<double> solve() const;
    std::vector<double> residual(const std::vector<double>& x) const;
    bool checkSolution(const std::vector<double>& res, double tolerance) const noexcept;
    int getSize() const noexcept;
};