#include "s21_decimal_test.h"

void tests_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void tests_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, check);
}

START_TEST(tests_add_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_add(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}

START_TEST(tests_add_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_add1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add21) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add22) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add23) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 2
  s21_decimal check = {{0x2, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add24) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add25) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 1.5
  s21_decimal check = {{0xF, 0x0, 0x0, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add26) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add27) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1.4999999999999999999999999999
  s21_decimal check = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add28) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.5000000000000000000000000001
  s21_decimal check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add29) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1.5000000000000000000000000001
  s21_decimal check = {{0x98000001, 0x5D378391, 0x3077B58D, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add30) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.4999999999999999999999999999
  s21_decimal check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add31) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 2.9999999999999999999999999000
  s21_decimal check = {{0x2FFFFC18, 0xBA6F0723, 0x60EF6B1A, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add32) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.9999999999999999999999999000
  s21_decimal check = {{0xFFFFC18, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add33) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 2.0000000000000000000000000001
  s21_decimal check = {{0x20000001, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add34) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add35) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add36) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add37) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 1.0000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add38) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 1.0000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add39) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 1.0000000000000000000000000001
  s21_decimal check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add40) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0.9999999999999999999999999999
  s21_decimal check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add41) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 1.0000000000000000000000000010
  s21_decimal check = {{0x1000000A, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add42) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 0.9999999999999999999999999990
  s21_decimal check = {{0xFFFFFF6, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add43) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add44) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add45) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add46) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add47) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add48) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -2
  s21_decimal check = {{0x2, 0x0, 0x0, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add49) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add50) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -1.5
  s21_decimal check = {{0xF, 0x0, 0x0, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add51) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.5000000000000000000000000001
  s21_decimal check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add52) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -1.4999999999999999999999999999
  s21_decimal check = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add53) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.4999999999999999999999999999
  s21_decimal check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add54) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -1.5000000000000000000000000001
  s21_decimal check = {{0x98000001, 0x5D378391, 0x3077B58D, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add55) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 0.9999999999999999999999999000
  s21_decimal check = {{0xFFFFC18, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add56) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -2.9999999999999999999999999000
  s21_decimal check = {{0x2FFFFC18, 0xBA6F0723, 0x60EF6B1A, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add57) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add58) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -2.0000000000000000000000000001
  s21_decimal check = {{0x20000001, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add59) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387504754779197847983444
  s21_decimal check = {{0x55555554, 0x55555555, 0x55555555, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add60) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387504754779197847983446
  s21_decimal check = {{0x55555556, 0x55555555, 0x55555555, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add61) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = TEST_ARITHMETIC_BIG;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add62) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add63) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add64) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add65) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add66) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add67) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add68) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add69) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0.5000000000000000000000000000
  s21_decimal check = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add70) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0.5000000000000000000000000000
  s21_decimal check = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add71) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.5000000000000000000000000001
  s21_decimal check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add72) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0.4999999999999999999999999999
  s21_decimal check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add73) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.5000000000000000000000000010
  s21_decimal check = {{0x8800000A, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add74) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 0.4999999999999999999999999990
  s21_decimal check = {{0x87FFFFF6, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add75) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add76) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.4999999999999999999999999999
  s21_decimal check = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add77) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add78) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.9999999999999999999999999999
  s21_decimal check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add79) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add80) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.9999999999999999999999999998
  s21_decimal check = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add81) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.0000000000000000000000000000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add82) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1.0000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add83) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -0.0000000000000000000000000002
  s21_decimal check = {{0x2, 0x0, 0x0, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add84) {
  // 0.4999999999999999999999999999
  s21_decimal decimal1 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 2.4999999999999999999999998999
  s21_decimal check = {{0xA7FFFC17, 0x9B5C85F2, 0x50C783EB, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add85) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add86) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = TEST_ARITHMETIC_SMALL;

  tests_add_fail(decimal1, decimal2, check);
}

START_TEST(tests_add87) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add88) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add89) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add90) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add91) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add92) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add93) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 15.845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x1B0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add94) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 0.0000000000000000000000000000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add95) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 15.922816251426433759354395034
  s21_decimal check = {{0xD999999A, 0x981D9B80, 0x33730B7E, 0x1B0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add96) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -0.0771837485735662406456049665
  s21_decimal check = {{0x80000001, 0xF1281308, 0x27E72F1, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add97) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 11.556482279746587359354395034
  s21_decimal check = {{0xA759999A, 0xB3174C4F, 0x25574C4F, 0x1B0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add98) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 4.2891502231062801593543950335
  s21_decimal check = {{0x767FFFFF, 0x11704E3, 0x8A9704E3, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add99) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add100) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add101) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 7.9228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add102) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add103) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 7.922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add104) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 7.9228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add105) {
  // -8
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7.5
  s21_decimal check = {{0x4B, 0x0, 0x0, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add106) {
  // -8
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -8.5
  s21_decimal check = {{0x55, 0x0, 0x0, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add107) {
  // -8
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -7.5000000000000000000000000001
  s21_decimal check = {{0xF8000001, 0xD21591D7, 0xF2568BC2, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add108) {
  // -8
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -8.500000000000000000000000000
  s21_decimal check = {{0xB4000000, 0x4E6C4205, 0x1B770903, 0x801B0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add109) {
  // -8
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -7.4999999999999999999999999999
  s21_decimal check = {{0xF7FFFFFF, 0xD21591D7, 0xF2568BC2, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add110) {
  // -8
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -8.500000000000000000000000000
  s21_decimal check = {{0xB4000000, 0x4E6C4205, 0x1B770903, 0x801B0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add111) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add112) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}
START_TEST(tests_add113) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add114) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add115) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add116) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add117) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.4999999999999999999999999999
  s21_decimal check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add118) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -0.4999999999999999999999999999
  s21_decimal check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add119) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add120) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add121) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add122) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add123) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add124) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add125) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 1.0000000000000000000000000001
  s21_decimal check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add126) {
  // -0.0000000000000000000000000000
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1.0000000000000000000000000001
  s21_decimal check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add127) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add128) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add129) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add130) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.9999999999999999999999999999
  s21_decimal check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add131) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add132) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add133) {
  // 26409387
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add134) {
  // -26409387
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -26409395
  s21_decimal check = {{0x192F9B3, 0x0, 0x0, 0x80000000}};

  tests_add(decimal1, decimal2, check);
}

START_TEST(tests_add_scale_check) {
  // Initialize two decimals with different scales
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};  // Decimal  1 with scale  0
  s21_decimal decimal2 = {
      {0x5, 0x0, 0x0, 0x80010000}};  // Decimal  2 with scale  1

  // Expected result after adding both decimals
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};  // Result with scale  1

  tests_add(decimal1, decimal2, check);
}

Suite *suite_s21_add_mini(void) {
  Suite *s = suite_create("\033[45m-=S21_suite_add_mini=-\033[0m");
  TCase *tc = tcase_create("case_add");

  tcase_add_test(tc, tests_add_fail_manual1);
  tcase_add_test(tc, tests_add_fail_manual2);
  tcase_add_test(tc, tests_add_fail_manual3);
  tcase_add_test(tc, tests_add_fail_manual4);
  tcase_add_test(tc, tests_add_fail_manual5);
  tcase_add_test(tc, tests_add_fail_manual6);
  tcase_add_test(tc, tests_add_fail_manual7);
  tcase_add_test(tc, tests_add_fail_manual8);
  tcase_add_test(tc, tests_add_fail_manual9);
  tcase_add_test(tc, tests_add_fail_manual10);
  tcase_add_test(tc, tests_add_fail_manual11);
  tcase_add_test(tc, tests_add_fail_manual12);
  tcase_add_test(tc, tests_add_fail_manual13);
  tcase_add_test(tc, tests_add_fail_manual14);
  tcase_add_test(tc, tests_add_fail_manual15);
  tcase_add_test(tc, tests_add_fail_manual16);
  tcase_add_test(tc, tests_add_fail_manual17);
  ///
  tcase_add_test(tc, tests_add1);
  tcase_add_test(tc, tests_add2);
  tcase_add_test(tc, tests_add3);
  tcase_add_test(tc, tests_add4);
  tcase_add_test(tc, tests_add5);
  tcase_add_test(tc, tests_add6);
  tcase_add_test(tc, tests_add7);
  tcase_add_test(tc, tests_add8);
  tcase_add_test(tc, tests_add9);
  tcase_add_test(tc, tests_add10);
  tcase_add_test(tc, tests_add11);
  tcase_add_test(tc, tests_add12);
  tcase_add_test(tc, tests_add13);
  tcase_add_test(tc, tests_add14);
  tcase_add_test(tc, tests_add15);
  tcase_add_test(tc, tests_add16);
  tcase_add_test(tc, tests_add17);
  tcase_add_test(tc, tests_add18);
  tcase_add_test(tc, tests_add19);
  tcase_add_test(tc, tests_add20);
  tcase_add_test(tc, tests_add21);
  tcase_add_test(tc, tests_add22);
  tcase_add_test(tc, tests_add23);
  tcase_add_test(tc, tests_add24);
  tcase_add_test(tc, tests_add25);
  tcase_add_test(tc, tests_add26);
  tcase_add_test(tc, tests_add27);
  tcase_add_test(tc, tests_add28);
  tcase_add_test(tc, tests_add29);
  tcase_add_test(tc, tests_add30);
  tcase_add_test(tc, tests_add31);
  tcase_add_test(tc, tests_add32);
  tcase_add_test(tc, tests_add33);
  tcase_add_test(tc, tests_add34);
  tcase_add_test(tc, tests_add35);
  tcase_add_test(tc, tests_add36);
  tcase_add_test(tc, tests_add37);
  tcase_add_test(tc, tests_add38);
  tcase_add_test(tc, tests_add39);
  tcase_add_test(tc, tests_add40);
  tcase_add_test(tc, tests_add41);
  tcase_add_test(tc, tests_add42);
  tcase_add_test(tc, tests_add43);
  tcase_add_test(tc, tests_add44);
  tcase_add_test(tc, tests_add45);
  tcase_add_test(tc, tests_add46);
  tcase_add_test(tc, tests_add47);
  tcase_add_test(tc, tests_add48);
  tcase_add_test(tc, tests_add49);
  tcase_add_test(tc, tests_add50);
  tcase_add_test(tc, tests_add51);
  tcase_add_test(tc, tests_add52);
  tcase_add_test(tc, tests_add53);
  tcase_add_test(tc, tests_add54);
  tcase_add_test(tc, tests_add55);
  tcase_add_test(tc, tests_add56);
  tcase_add_test(tc, tests_add57);
  tcase_add_test(tc, tests_add58);
  tcase_add_test(tc, tests_add59);
  tcase_add_test(tc, tests_add60);
  tcase_add_test(tc, tests_add61);
  tcase_add_test(tc, tests_add62);
  tcase_add_test(tc, tests_add63);
  tcase_add_test(tc, tests_add64);
  tcase_add_test(tc, tests_add65);
  tcase_add_test(tc, tests_add66);
  tcase_add_test(tc, tests_add67);
  tcase_add_test(tc, tests_add68);
  tcase_add_test(tc, tests_add69);
  tcase_add_test(tc, tests_add70);
  tcase_add_test(tc, tests_add71);
  tcase_add_test(tc, tests_add72);
  tcase_add_test(tc, tests_add73);
  tcase_add_test(tc, tests_add74);
  tcase_add_test(tc, tests_add75);
  tcase_add_test(tc, tests_add76);
  tcase_add_test(tc, tests_add77);
  tcase_add_test(tc, tests_add78);
  tcase_add_test(tc, tests_add79);
  tcase_add_test(tc, tests_add80);
  tcase_add_test(tc, tests_add81);
  tcase_add_test(tc, tests_add82);
  tcase_add_test(tc, tests_add83);
  tcase_add_test(tc, tests_add84);
  tcase_add_test(tc, tests_add85);
  tcase_add_test(tc, tests_add86);
  tcase_add_test(tc, tests_add87);
  tcase_add_test(tc, tests_add88);
  tcase_add_test(tc, tests_add89);
  tcase_add_test(tc, tests_add90);
  tcase_add_test(tc, tests_add91);
  tcase_add_test(tc, tests_add92);
  tcase_add_test(tc, tests_add93);
  tcase_add_test(tc, tests_add94);
  tcase_add_test(tc, tests_add95);
  tcase_add_test(tc, tests_add96);
  tcase_add_test(tc, tests_add97);
  tcase_add_test(tc, tests_add98);
  tcase_add_test(tc, tests_add99);
  tcase_add_test(tc, tests_add100);
  tcase_add_test(tc, tests_add101);
  tcase_add_test(tc, tests_add102);
  tcase_add_test(tc, tests_add103);
  tcase_add_test(tc, tests_add104);
  tcase_add_test(tc, tests_add105);
  tcase_add_test(tc, tests_add106);
  tcase_add_test(tc, tests_add107);
  tcase_add_test(tc, tests_add108);
  tcase_add_test(tc, tests_add109);
  tcase_add_test(tc, tests_add110);
  tcase_add_test(tc, tests_add111);
  tcase_add_test(tc, tests_add112);
  tcase_add_test(tc, tests_add113);
  tcase_add_test(tc, tests_add114);
  tcase_add_test(tc, tests_add115);
  tcase_add_test(tc, tests_add116);
  tcase_add_test(tc, tests_add117);
  tcase_add_test(tc, tests_add118);
  tcase_add_test(tc, tests_add119);
  tcase_add_test(tc, tests_add120);
  tcase_add_test(tc, tests_add121);
  tcase_add_test(tc, tests_add122);
  tcase_add_test(tc, tests_add123);
  tcase_add_test(tc, tests_add124);
  tcase_add_test(tc, tests_add125);
  tcase_add_test(tc, tests_add126);
  tcase_add_test(tc, tests_add127);
  tcase_add_test(tc, tests_add128);
  tcase_add_test(tc, tests_add129);
  tcase_add_test(tc, tests_add130);
  tcase_add_test(tc, tests_add131);
  tcase_add_test(tc, tests_add132);
  tcase_add_test(tc, tests_add133);
  tcase_add_test(tc, tests_add134);
  ///
  tcase_add_test(tc, tests_add_scale_check);

  suite_add_tcase(s, tc);
  return s;
}