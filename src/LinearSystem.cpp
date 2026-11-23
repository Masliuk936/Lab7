#include "LinearSystem.h"
#include "LinearSystemExceptions.h"
#include <cmath>
#include <stdexcept>

void LinearSystem::validateData(const std::vector<double>& A, const std::vector<double>& b, int n) {
    if (n <= 0) {
        throw std::invalid_argument("Size 'n' must be positive");
    }
    if (A.size() != static_cast<size_t>(n * n)) {
        throw std::invalid_argument("Matrix A must be square (n*n)");
    }
    if (b.size() != static_cast<size_t>(n)) {
        throw InvalidSizeException(n, static_cast<int>(b.size()));
    }
    for (double val : A) {
        if (!std::isfinite(val)) throw InvalidDataException();
    }
    for (double val : b) {
        if (!std::isfinite(val)) throw InvalidDataException();
    }
}

LinearSystem::LinearSystem(const std::vector<double>& A, const std::vector<double>& b, int n) {
    validateData(A, b, n);
    mat_ = A;
    vec_ = b;
    n_ = n;
}

void LinearSystem::updateSystem(const std::vector<double>& newA, const std::vector<double>& newb, int newN) {
    validateData(newA, newb, newN);

    std::vector<double> tempA = newA;
    std::vector<double> tempb = newb;

    mat_.swap(tempA);
    vec_.swap(tempb);
    n_ = newN;
}

std::vector<double> LinearSystem::solve() const {
    std::vector<double> a = mat_;
    std::vector<double> b = vec_;
    std::vector<double> x(n_, 0.0);

    for (int i = 0; i < n_; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n_; k++) {
            if (std::abs(a[k * n_ + i]) > std::abs(a[maxRow * n_ + i])) {
                maxRow = k;
            }
        }

        if (std::abs(a[maxRow * n_ + i]) < 0.000001) {
            throw SingularMatrixException();
        }

        for (int k = i; k < n_; k++) {
            double temp = a[i * n_ + k];
            a[i * n_ + k] = a[maxRow * n_ + k];
            a[maxRow * n_ + k] = temp;
        }
        double tempB = b[i];
        b[i] = b[maxRow];
        b[maxRow] = tempB;

        for (int k = i + 1; k < n_; k++) {
            double factor = a[k * n_ + i] / a[i * n_ + i];
            for (int j = i; j < n_; j++) {
                a[k * n_ + j] = a[k * n_ + j] - factor * a[i * n_ + j];
            }
            b[k] = b[k] - factor * b[i];
        }
    }

    for (int i = n_ - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n_; j++) {
            x[i] = x[i] - a[i * n_ + j] * x[j];
        }
        // Тут я змінював / на *
        x[i] = x[i] / a[i * n_ + i];
    }

    return x;
}

std::vector<double> LinearSystem::residual(const std::vector<double>& x) const {
    if (x.size() != static_cast<size_t>(n_)) {
        throw InvalidSizeException(n_, static_cast<int>(x.size()));
    }
    std::vector<double> res(n_, 0.0);

    for (int i = 0; i < n_; i++) {
        double sum = 0;
        for (int j = 0; j < n_; j++) {
            sum += mat_[i * n_ + j] * x[j];
        }
        res[i] = vec_[i] - sum;
    }
    return res;
}

bool LinearSystem::checkSolution(const std::vector<double>& res, double tolerance) const noexcept {
    for (int i = 0; i < n_; i++) {
        if (std::abs(res[i]) > tolerance) {
            return false;
        }
    }
    return true;
}

int LinearSystem::getSize() const noexcept {
    return n_;
}