#pragma once
#include <stdexcept>
#include <string>

class LinearSystemException : public std::runtime_error {
public:
    explicit LinearSystemException(const std::string& message)
        : std::runtime_error(message) {}
};

class SingularMatrixException : public LinearSystemException {
public:
    SingularMatrixException()
        : LinearSystemException("Matrix is singular or has a zero pivot") {
    }
};

class InvalidSizeException : public LinearSystemException {
private:
    int expected_;
    int actual_;
public:
    InvalidSizeException(int expected, int actual)
        : LinearSystemException("Incompatible sizes: expected " + std::to_string(expected) + ", got " + std::to_string(actual)),
        expected_(expected), actual_(actual) {
    }

    int expected() const noexcept { return expected_; }
    int actual() const noexcept { return actual_; }
};

class InvalidDataException : public LinearSystemException {
public:
    InvalidDataException()
        : LinearSystemException("Matrix or vector contains NaN or Inf values") {
    }
};