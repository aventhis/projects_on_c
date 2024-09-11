#include "s21_decimal_test.h"
#define TEST_OTHER_OK 0
#define TEST_OTHER_ERROR 1

// void negate_test_function(float n, float accuracy) {
//   s21_decimal var1 = {{0}}, var2 = {{0}}, var3 = {{0}};
//   float value1 = 0.0, value2 = 0.0;
//   s21_from_float_to_decimal(n, &var1);
//   s21_negate(var1, &var2);
//   s21_from_decimal_to_float(var2, &value2);
//   value1 = -1 * n;
//   s21_from_float_to_decimal(value1, &var3);
//   ck_assert_float_eq_tol(value1, value2, accuracy);
//   return;
// }

START_TEST(test_negate_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_negate(decimal, NULL);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}

START_TEST(test_negate_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(negate_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {{0}};
  s21_decimal res = {{0}};
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

// START_TEST(negate_4) {
//   float n = s21_rand_r(-8388608, 8388608);
//   negate_test_function(n, 10);
// }
// END_TEST

// START_TEST(negate_5) {
//   s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
//   s21_set_sign(&value_1);
//   s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
//   s21_decimal result = {0};
//   int return_value = s21_negate(value_1, &result);
//   ck_assert_int_eq(s21_is_equal(result, check), 1);
//   ck_assert_int_eq(return_value, 0);
// }
// END_TEST

START_TEST(negate_6) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal check = {{1, 1, 1, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

// START_TEST(negate_7) {
//   float a = 10.1234e5;
//   float res_a = 0;
//   s21_decimal src = {0};
//   s21_from_float_to_decimal(a, &src);
//   s21_decimal res = {0};
//   s21_negate(src, &res);
//   s21_from_decimal_to_float(res, &res_a);
//   ck_assert_float_eq(-10.1234e5, res_a);
// }
// END_TEST

Suite *suite_negate(void) {
  Suite *s = suite_create("\033[45m-=S21_suite_negate=-\033[0m");
  TCase *tc = tcase_create("negate_tc");

  tcase_add_test(tc, test_negate_fail1);
  tcase_add_test(tc, test_negate_fail2);
  tcase_add_test(tc, test_negate_fail3);
  tcase_add_test(tc, test_negate_fail4);
  tcase_add_test(tc, test_negate_fail5);
  tcase_add_test(tc, test_negate_fail6);
  tcase_add_test(tc, test_negate_fail7);
  tcase_add_test(tc, test_negate_fail8);
  tcase_add_test(tc, test_negate_fail9);
  tcase_add_test(tc, negate_0);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  // tcase_add_loop_test(tc, negate_4, 0, 1000);
  // tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);
  // tcase_add_test(tc, negate_7);

  suite_add_tcase(s, tc);
  return s;
}