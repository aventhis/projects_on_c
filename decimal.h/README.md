# s21_decimal

Custom implementation of a `decimal` type in C.

## Introduction

The `s21_decimal` project involves creating a custom version of a `decimal` data type library in the C programming language. Decimal types are essential for applications where floating-point precision is critical, such as financial and accounting software. The aim of this project is to provide accurate decimal calculations while adhering to structured programming principles.

### Overview of `decimal` functions

| No. | Function | Description |
| --- | -------- | ----------- |
| 1 | `int s21_add(decimal x, decimal y, decimal* result)` | Adds two decimal numbers and stores the result in `result` |
| 2 | `int s21_sub(decimal x, decimal y, decimal* result)` | Subtracts `y` from `x` and stores the result in `result` |
| 3 | `int s21_mul(decimal x, decimal y, decimal* result)` | Multiplies two decimal numbers and stores the result in `result` |
| 4 | `int s21_div(decimal x, decimal y, decimal* result)` | Divides `x` by `y` and stores the result in `result` |
| 5 | `int s21_mod(decimal x, decimal y, decimal* result)` | Calculates the remainder of `x` divided by `y` and stores the result |
| 6 | `int s21_floor(decimal x, decimal* result)` | Rounds down `x` to the nearest whole number and stores the result |
| 7 | `int s21_round(decimal x, decimal* result)` | Rounds `x` to the nearest integer and stores the result |
| 8 | `int s21_truncate(decimal x, decimal* result)` | Truncates the decimal part of `x` and stores the result |
| 9 | `int s21_negate(decimal x, decimal* result)` | Changes the sign of `x` and stores the result |
| 10 | `int s21_is_equal(decimal x, decimal y)` | Compares two decimals and returns 1 if they are equal, otherwise 0 |
| 11 | `int s21_is_not_equal(decimal x, decimal y)` | Returns 1 if the two decimals are not equal |
| 12 | `int s21_is_greater(decimal x, decimal y)` | Returns 1 if `x` is greater than `y` |
| 13 | `int s21_is_less(decimal x, decimal y)` | Returns 1 if `x` is less than `y` |
| 14 | `int s21_is_greater_or_equal(decimal x, decimal y)` | Returns 1 if `x` is greater than or equal to `y` |
| 15 | `int s21_is_less_or_equal(decimal x, decimal y)` | Returns 1 if `x` is less than or equal to `y` |

## Part 1. Implementation of the `s21_decimal` library functions

The functions for the custom `s21_decimal` library were implemented as follows:

- The library was developed using C, following the C11 standard with the gcc compiler;
- The source code of the library is located in the `src` directory;
- Legacy and obsolete constructs in the C language were avoided. We followed the POSIX.1-2017 standard;
- The coding style adheres to Google’s coding guidelines;
- The solution is structured as a static library named `s21_decimal.a` with a header file `s21_decimal.h`;
- All functions are thoroughly tested with unit tests using the Check library;
- Unit tests compare the results of the custom implementation with expected results;
- Tests cover at least 80% of each function;
- A `Makefile` is provided with targets for building the library and running the tests (`all`, `clean`, `test`, `s21_decimal.a`, `gcov_report`);
- A coverage report is generated using `gcov`, and the results are displayed in an HTML format;
- Copying implementations from other sources or using standard decimal libraries is not allowed;
- Functions comply with the structured programming principles, and code duplication was avoided.

## Project Build

To build the project, follow these steps:

1. Clone the repository and navigate to the project folder:

    ```bash
    git clone <repository_url>
    cd <project_folder>
    ```

### Makefile Targets

- **make all**: This target compiles all source files and builds the static library `s21_decimal.a`.
- **make clean**: This target removes all generated object files and executables, cleaning up the build environment.
- **make s21_decimal.a**: This target creates the static library `s21_decimal.a` from the source files.
- **make test**: This target compiles and runs the unit tests to validate the functionality of the library.
- **make gcov_report**: This target runs tests with coverage flags and generates a code coverage report in HTML format.

## Conclusion

This project implements a custom `decimal` type in C to handle decimal arithmetic without floating-point errors. The project is designed with structured programming principles and includes comprehensive unit tests to ensure the correctness and robustness of the implementation.