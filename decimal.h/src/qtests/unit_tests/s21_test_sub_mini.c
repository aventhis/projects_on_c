#include "s21_decimal_test.h"

#define TEST_ARITHMETIC_OK 0
#define TEST_ARITHMETIC_BIG 1
#define TEST_ARITHMETIC_SMALL 2
#define TEST_ARITHMETIC_ZERO_DIV 3

void tests_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void tests_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, check);
}

START_TEST(tests_sub_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_sub(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}

START_TEST(tests_sub_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_sub_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

///

START_TEST(tests_sub_manual1) {
  // 7.922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 3.9614081257132168796771975172
  s21_decimal check = {{0x4, 0x0, 0x80000000, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

///

START_TEST(tests_sub1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub17) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub18) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub19) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub20) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub21) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub22) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub23) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub24) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub25) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub26) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub27) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub28) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub29) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 7922816251426433759354395037
  s21_decimal check = {{0x9999999D, 0x99999999, 0x19999999, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub30) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub31) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub32) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x1A0000}};
  // 7922816251426433759354394387.2
  s21_decimal check = {{0xFFFFE6C0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub33) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // 7922816251426433759354395680
  s21_decimal check = {{0x99999C20, 0x99999999, 0x19999999, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub34) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub35) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -15845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub36) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub37) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub38) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub39) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub40) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395042
  s21_decimal check = {{0x999999A2, 0x99999999, 0x19999999, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub41) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395026
  s21_decimal check = {{0x99999992, 0x99999999, 0x19999999, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub42) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395036
  s21_decimal check = {{0x9999999C, 0x99999999, 0x19999999, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub43) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub44) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 2
  s21_decimal check = {{0x2, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub45) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub46) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 1.5
  s21_decimal check = {{0xF, 0x0, 0x0, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub47) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.5000000000000000000000000001
  s21_decimal check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub48) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 1.4999999999999999999999999999
  s21_decimal check = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub49) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.4999999999999999999999999999
  s21_decimal check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub50) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 1.5000000000000000000000000001
  s21_decimal check = {{0x98000001, 0x5D378391, 0x3077B58D, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub51) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -0.9999999999999999999999999000
  s21_decimal check = {{0xFFFFC18, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub52) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 2.9999999999999999999999999000
  s21_decimal check = {{0x2FFFFC18, 0xBA6F0723, 0x60EF6B1A, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub53) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub54) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 2.0000000000000000000000000001
  s21_decimal check = {{0x20000001, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub55) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387504754779197847983444
  s21_decimal check = {{0x55555554, 0x55555555, 0x55555555, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub56) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387504754779197847983446
  s21_decimal check = {{0x55555556, 0x55555555, 0x55555555, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub57) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -26409387498605864508043122004
  s21_decimal check = {{0x55555554, 0x0, 0x55555555, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub58) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -26409386
  s21_decimal check = {{0x192F9AA, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub59) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 26409388
  s21_decimal check = {{0x192F9AC, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub60) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -6.9228162514264337593543950335
  s21_decimal check = {{0xEFFFFFFF, 0xC1DAFD9E, 0xDFB031A1, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub61) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 8.922816251426433759354395034
  s21_decimal check = {{0x8199999A, 0x396A19D6, 0x1CD4C7D6, 0x1B0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub62) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -7
  s21_decimal check = {{0x7, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub63) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 9
  s21_decimal check = {{0x9, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub64) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // -2.6336660283201536
  s21_decimal check = {{0x90C01800, 0x5D910D, 0x0, 0x80100000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub65) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 4.6336660283201536
  s21_decimal check = {{0x70421800, 0xA49EF2, 0x0, 0x100000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub66) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub67) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub68) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 1.0000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub69) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 1.0000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub70) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.9999999999999999999999999999
  s21_decimal check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub71) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 1.0000000000000000000000000001
  s21_decimal check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub72) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.9999999999999999999999999990
  s21_decimal check = {{0xFFFFFF6, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub73) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 1.0000000000000000000000000010
  s21_decimal check = {{0x1000000A, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub74) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub75) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub76) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -1.0000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub77) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -1.0000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub78) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -1.0000000000000000000000000001
  s21_decimal check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub79) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -0.9999999999999999999999999999
  s21_decimal check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub80) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub81) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub82) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub83) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub84) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub85) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub86) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub87) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub88) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 1.5
  s21_decimal check = {{0xF, 0x0, 0x0, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub89) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub90) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -26409386.5
  s21_decimal check = {{0xFBDC0A9, 0x0, 0x0, 0x80010000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub91) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 26409387.5
  s21_decimal check = {{0xFBDC0B3, 0x0, 0x0, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub92) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 1.5000000000000000000000000000
  s21_decimal check = {{0x98000000, 0x5D378391, 0x3077B58D, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub93) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -7.5000000000000000000000000001
  s21_decimal check = {{0xF8000001, 0xD21591D7, 0xF2568BC2, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub94) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 8.500000000000000000000000000
  s21_decimal check = {{0xB4000000, 0x4E6C4205, 0x1B770903, 0x1B0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub95) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 6148914689804861441
  s21_decimal check = {{0x1, 0x55555555, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub96) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 6148914689804861439.5
  s21_decimal check = {{0xFFFFFFFB, 0x55555551, 0x3, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub97) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 6148914689804861440.5
  s21_decimal check = {{0x5, 0x55555552, 0x3, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub98) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 6148914689804861439.5000000000
  s21_decimal check = {{0xD5FA0E00, 0x8EA6B3FE, 0xC6AEA154, 0xA0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub99) {
  // -1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -1458065152.4986058645080431220
  s21_decimal check = {{0x3948DA74, 0xFB715ABA, 0x2F1CD50E, 0x80130000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub100) {
  // -1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -1405246377.5013941354919568780
  s21_decimal check = {{0x6AC7258C, 0xAEA48DED, 0x2D67ECF3, 0x80130000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub101) {
  // -1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -1458065152
  s21_decimal check = {{0x56E84F00, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub102) {
  // -1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -1405246378
  s21_decimal check = {{0x53C25BAA, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub103) {
  // -26409387.498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -52818774.498605864508043122005
  s21_decimal check = {{0xAA355555, 0xF8741FF5, 0xAAAAAA8E, 0x80150000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub104) {
  // -26409387.498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -0.498605864508043122005
  s21_decimal check = {{0x755555, 0x78BE00B, 0x1B, 0x80150000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub105) {
  // -26409387.498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -26409395.421422115934476881359
  s21_decimal check = {{0x49DACDCF, 0x7F29ABCB, 0x55555702, 0x80150000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub106) {
  // -26409387.498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -26409379.575789613081609362651
  s21_decimal check = {{0x60CFDCDB, 0x80D65435, 0x555553A7, 0x80150000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub107) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // -3.6336660283201536000000000000
  s21_decimal check = {{0x89800000, 0xFEE8FB1C, 0x7568FB1C, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub108) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 3.6336660283201536000000000000
  s21_decimal check = {{0x89800000, 0xFEE8FB1C, 0x7568FB1C, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub109) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub110) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub111) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub112) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub113) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x801C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub114) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x1C0000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub115) {
  // -60233732531769558296976156804
  s21_decimal decimal1 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  tests_sub_fail(decimal1, decimal2, check);
}

START_TEST(tests_sub116) {
  // -60233732531769558296976156804
  s21_decimal decimal1 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // -60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub117) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub118) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub119) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub120) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub121) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 18486571247179430748688726972
  s21_decimal check = {{0xBBBBBBBC, 0x66666666, 0x3BBBBBBB, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub122) {
  // -8
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395027
  s21_decimal check = {{0x99999993, 0x99999999, 0x19999999, 0x0}};

  tests_sub(decimal1, decimal2, check);
}

START_TEST(tests_sub123) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_sub(decimal1, decimal2, check);
}

Suite *suite_s21_sub_mini(void) {
  Suite *s = suite_create("\033[45m-=S21_suite_sub_mini=-\033[0m");
  TCase *tc = tcase_create("case_sub");

  tcase_add_test(tc, tests_sub_fail_manual1);
  tcase_add_test(tc, tests_sub_fail_manual2);
  tcase_add_test(tc, tests_sub_fail_manual3);
  tcase_add_test(tc, tests_sub_fail_manual4);
  tcase_add_test(tc, tests_sub_fail_manual5);
  tcase_add_test(tc, tests_sub_fail_manual6);
  tcase_add_test(tc, tests_sub_fail_manual7);
  tcase_add_test(tc, tests_sub_fail_manual8);
  tcase_add_test(tc, tests_sub_fail_manual9);
  tcase_add_test(tc, tests_sub_fail_manual10);
  tcase_add_test(tc, tests_sub_fail_manual11);
  tcase_add_test(tc, tests_sub_fail_manual12);
  tcase_add_test(tc, tests_sub_fail_manual13);
  tcase_add_test(tc, tests_sub_fail_manual14);
  tcase_add_test(tc, tests_sub_fail_manual15);
  tcase_add_test(tc, tests_sub_fail_manual16);
  tcase_add_test(tc, tests_sub_fail_manual17);
  //
  tcase_add_test(tc, tests_sub_manual1);
  //
  tcase_add_test(tc, tests_sub1);
  tcase_add_test(tc, tests_sub2);
  tcase_add_test(tc, tests_sub3);
  tcase_add_test(tc, tests_sub4);
  tcase_add_test(tc, tests_sub5);
  tcase_add_test(tc, tests_sub6);
  tcase_add_test(tc, tests_sub7);
  tcase_add_test(tc, tests_sub8);
  tcase_add_test(tc, tests_sub9);
  tcase_add_test(tc, tests_sub10);
  tcase_add_test(tc, tests_sub11);
  tcase_add_test(tc, tests_sub12);
  tcase_add_test(tc, tests_sub13);
  tcase_add_test(tc, tests_sub14);
  tcase_add_test(tc, tests_sub15);
  tcase_add_test(tc, tests_sub16);
  tcase_add_test(tc, tests_sub17);
  tcase_add_test(tc, tests_sub18);
  tcase_add_test(tc, tests_sub19);
  tcase_add_test(tc, tests_sub20);
  tcase_add_test(tc, tests_sub21);
  tcase_add_test(tc, tests_sub22);
  tcase_add_test(tc, tests_sub23);
  tcase_add_test(tc, tests_sub24);
  tcase_add_test(tc, tests_sub25);
  tcase_add_test(tc, tests_sub26);
  tcase_add_test(tc, tests_sub27);
  tcase_add_test(tc, tests_sub28);
  tcase_add_test(tc, tests_sub29);
  tcase_add_test(tc, tests_sub30);
  tcase_add_test(tc, tests_sub31);
  tcase_add_test(tc, tests_sub32);
  tcase_add_test(tc, tests_sub33);
  tcase_add_test(tc, tests_sub34);
  tcase_add_test(tc, tests_sub35);
  tcase_add_test(tc, tests_sub36);
  tcase_add_test(tc, tests_sub37);
  tcase_add_test(tc, tests_sub38);
  tcase_add_test(tc, tests_sub39);
  tcase_add_test(tc, tests_sub40);
  tcase_add_test(tc, tests_sub41);
  tcase_add_test(tc, tests_sub42);
  tcase_add_test(tc, tests_sub43);
  tcase_add_test(tc, tests_sub44);
  tcase_add_test(tc, tests_sub45);
  tcase_add_test(tc, tests_sub46);
  tcase_add_test(tc, tests_sub47);
  tcase_add_test(tc, tests_sub48);
  tcase_add_test(tc, tests_sub49);
  tcase_add_test(tc, tests_sub50);
  tcase_add_test(tc, tests_sub51);
  tcase_add_test(tc, tests_sub52);
  tcase_add_test(tc, tests_sub53);
  tcase_add_test(tc, tests_sub54);
  tcase_add_test(tc, tests_sub55);
  tcase_add_test(tc, tests_sub56);
  tcase_add_test(tc, tests_sub57);
  tcase_add_test(tc, tests_sub58);
  tcase_add_test(tc, tests_sub59);
  tcase_add_test(tc, tests_sub60);
  tcase_add_test(tc, tests_sub61);
  tcase_add_test(tc, tests_sub62);
  tcase_add_test(tc, tests_sub63);
  tcase_add_test(tc, tests_sub64);
  tcase_add_test(tc, tests_sub65);
  tcase_add_test(tc, tests_sub66);
  tcase_add_test(tc, tests_sub67);
  tcase_add_test(tc, tests_sub68);
  tcase_add_test(tc, tests_sub69);
  tcase_add_test(tc, tests_sub70);
  tcase_add_test(tc, tests_sub71);
  tcase_add_test(tc, tests_sub72);
  tcase_add_test(tc, tests_sub73);
  tcase_add_test(tc, tests_sub74);
  tcase_add_test(tc, tests_sub75);
  tcase_add_test(tc, tests_sub76);
  tcase_add_test(tc, tests_sub77);
  tcase_add_test(tc, tests_sub78);
  tcase_add_test(tc, tests_sub79);
  tcase_add_test(tc, tests_sub80);
  tcase_add_test(tc, tests_sub81);
  tcase_add_test(tc, tests_sub82);
  tcase_add_test(tc, tests_sub83);
  tcase_add_test(tc, tests_sub84);
  tcase_add_test(tc, tests_sub85);
  tcase_add_test(tc, tests_sub86);
  tcase_add_test(tc, tests_sub87);
  tcase_add_test(tc, tests_sub88);
  tcase_add_test(tc, tests_sub89);
  tcase_add_test(tc, tests_sub90);
  tcase_add_test(tc, tests_sub91);
  tcase_add_test(tc, tests_sub92);
  tcase_add_test(tc, tests_sub93);
  tcase_add_test(tc, tests_sub94);
  tcase_add_test(tc, tests_sub95);
  tcase_add_test(tc, tests_sub96);
  tcase_add_test(tc, tests_sub97);
  tcase_add_test(tc, tests_sub98);
  tcase_add_test(tc, tests_sub99);
  tcase_add_test(tc, tests_sub100);
  tcase_add_test(tc, tests_sub101);
  tcase_add_test(tc, tests_sub102);
  tcase_add_test(tc, tests_sub103);
  tcase_add_test(tc, tests_sub104);
  tcase_add_test(tc, tests_sub105);
  tcase_add_test(tc, tests_sub106);
  tcase_add_test(tc, tests_sub107);
  tcase_add_test(tc, tests_sub108);
  tcase_add_test(tc, tests_sub109);
  tcase_add_test(tc, tests_sub110);
  tcase_add_test(tc, tests_sub111);
  tcase_add_test(tc, tests_sub112);
  tcase_add_test(tc, tests_sub113);
  tcase_add_test(tc, tests_sub114);
  tcase_add_test(tc, tests_sub115);
  tcase_add_test(tc, tests_sub116);
  tcase_add_test(tc, tests_sub117);
  tcase_add_test(tc, tests_sub118);
  tcase_add_test(tc, tests_sub119);
  tcase_add_test(tc, tests_sub120);
  tcase_add_test(tc, tests_sub121);
  tcase_add_test(tc, tests_sub122);
  tcase_add_test(tc, tests_sub123);

  suite_add_tcase(s, tc);
  return s;
}
