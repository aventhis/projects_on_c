#ifndef SRC_S21_DECIMAL_TEST_H_
#define SRC_S21_DECIMAL_TEST_H_

#include <check.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "../../s21_decimal.h"

#define TRUE 1
#define FALSE 0

#define TEST_OTHER_OK 0
#define TEST_OTHER_ERROR 1

#define TEST_CONVERSION_OK 0
#define TEST_CONVERSION_ERROR 1

#define TEST_ARITHMETIC_OK 0
#define TEST_ARITHMETIC_BIG 1
#define TEST_ARITHMETIC_SMALL 2
#define TEST_ARITHMETIC_ZERO_DIV 3

typedef struct {
  int fails;
} fail;

void run_tests(fail *fails);
void run_testcase(Suite *testcase, fail *fails);

Suite *suite_s21_add(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_div(void);

// mini arith
Suite *suite_s21_add_mini(void);
Suite *suite_s21_sub_mini(void);
Suite *suite_s21_mul_mini(void);
Suite *suite_s21_div_mini(void);

Suite *suite_is_less(void);
Suite *suite_is_less_or_equal(void);
Suite *suite_is_greater(void);
Suite *suite_is_greater_or_equal(void);
Suite *suite_is_equal(void);
Suite *suite_is_equal_6000(void);
Suite *suite_is_not_equal(void);

Suite *suite_from_decimal_to_int(void);

Suite *suite_from_decimal_to_float(void);

Suite *suite_from_decimal_to_float_mini(void);
Suite *suite_from_float_to_decimal_mini(void);

Suite *suite_from_decimal_to_int_mini(void);
Suite *suite_from_int_to_decimal(void);

Suite *suite_truncate(void);
Suite *suite_truncate2(void);
Suite *suite_floor(void);
Suite *suite_round(void);
// Suite *suite_round2(void);
Suite *suite_negate(void);

// mini other
Suite *suite_negate_mini(void);
Suite *suite_floor_mini(void);
Suite *suite_round_mini(void);
Suite *suite_truncate_mini(void);

Suite *suite_s21_is_equal(void);
Suite *suite_s21_is_not_equal(void);
Suite *suite_s21_is_less(void);
Suite *suite_s21_is_less_or_equal(void);
Suite *suite_s21_is_greater(void);
Suite *suite_s21_is_greater_or_equal(void);

#endif  //  SRC_S21_DECIMAL_TEST_H_
