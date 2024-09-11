#include "s21_decimal_test.h"

void tests_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
}

void tests_mul_fail1(s21_decimal decimal1, s21_decimal decimal2,
                     int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
}

void tests_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                     s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

///

START_TEST(tests_mul_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_mul(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}

START_TEST(tests_mul_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(tests_mul_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

///

START_TEST(tests_mul_manual1) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.8228162514264337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x1C0000}};
  // 61.978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x1B0000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual2) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -0.8228162514264337593543950335
  s21_decimal decimal2 = {{0x4F63FFFF, 0xBB0D25CF, 0x1A962D2F, 0x801C0000}};
  // -6.5190219687391279469416894926
  s21_decimal check = {{0x23B23CAE, 0xEC60363A, 0xD2A415FA, 0x801C0000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual3) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -0.00000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800E0000}};
  // 0.0000000000003500000000000012
  s21_decimal check = {{0x40B6C00C, 0xC6F3B, 0x0, 0x1C0000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual4) {
  // -7922816251426.4337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  // 78228162514264.337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xF0000}};
  // -619787357287241642624224547.27
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80020000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual5) {
  // -79228162514264.337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
  // 782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
  // -61978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x80000000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual6) {
  // 79228162514264.1
  s21_decimal decimal1 = {{0x70D42571, 0x2D093, 0x0, 0x10000}};
  // 78228162514264.5
  s21_decimal decimal2 = {{0x22618575, 0x2C77B, 0x0, 0x10000}};
  // 6197873572872410706900970254.4
  s21_decimal check = {{0x7F6C2E90, 0x3FD777DD, 0xC8439BCC, 0x10000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual7) {
  // 79228162514265.1
  s21_decimal decimal1 = {{0x70D4257B, 0x2D093, 0x0, 0x10000}};
  // 78228162514264.5
  s21_decimal decimal2 = {{0x22618575, 0x2C77B, 0x0, 0x10000}};
  // 6197873572872488935063484519.0
  s21_decimal check = {{0xA1CDB406, 0x3FDA3F58, 0xC8439BCC, 0x10000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual8) {
  // 5.0
  s21_decimal decimal1 = {{0x32, 0x0, 0x0, 0x10000}};
  // 4.5
  s21_decimal decimal2 = {{0x2D, 0x0, 0x0, 0x10000}};
  // 22.50
  s21_decimal check = {{0x8CA, 0x0, 0x0, 0x20000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual9) {
  // 79228162.5
  s21_decimal decimal1 = {{0x2F394219, 0x0, 0x0, 0x10000}};
  // 78228162.5555555555555
  s21_decimal decimal2 = {{0xB20798E3, 0x6856A1BC, 0x2A, 0xD0000}};
  // 6197873575027970.8333289317688
  s21_decimal check = {{0x34C52538, 0x6AFC5902, 0xC8439BCD, 0xD0000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual10) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -2.00000000000005
  s21_decimal decimal2 = {{0x20F48005, 0xB5E6, 0x0, 0x800E0000}};
  // 14.000000000000400000000000001
  s21_decimal check = {{0xF1E90001, 0xBD686F20, 0x2D3C8750, 0x1B0000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual11) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -0.0000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800D0000}};
  // 0.0000000000035000000000000125
  s21_decimal check = {{0x8723807D, 0x7C5850, 0x0, 0x1C0000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual12) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x800F0000}};
  // -0.000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x800F0000}};
  // 0.0000000000000350000000000001
  s21_decimal check = {{0xB9ABE001, 0x13E52, 0x0, 0x1C0000}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual13) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 0.00000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x50000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  tests_mul(decimal1, decimal2, check);
}

START_TEST(tests_mul_manual14) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul_manual15) {
  // 7922816251426433759354395032.8
  s21_decimal decimal1 = {{0xFFFFFFF8, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul_manual16) {
  // -7922816251426433759354395032.7
  s21_decimal decimal1 = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1B0000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul_manual17) {
  // -7922816251426433759354395032.7
  s21_decimal decimal1 = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10.000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul_manual97) {
  // -0.0000000000000025
  s21_decimal decimal1 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // too small
  // 0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1C0000}};
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(tests_mul_manual98) {
  // 792281625142643.37593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // -782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x800E0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  // tests_mul(decimal1, decimal2, decimal_check);
  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul_manual99) {
  // 792281625142643.37593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 782281625142643.37593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0xE0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  // tests_mul(decimal1, decimal2, decimal_check);
  tests_mul_fail1(decimal1, decimal2, code_check);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests all data (automatic)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(tests_mul1) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul2) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul3) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul4) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul5) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul6) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul7) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul8) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul9) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul10) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul11) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul12) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul13) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul14) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul15) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul16) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul17) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 52818775009509558395695964249
  s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul18) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -52818775009509558395695964249
  s21_decimal decimal_check = {
      {0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul19) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul20) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul21) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 13204693752377389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul22) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -13204693752377389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul23) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693752377389598923991720
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul24) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693752377389598923991720
  s21_decimal decimal_check = {
      {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul25) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693752377389598923991725
  s21_decimal decimal_check = {{0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul26) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693752377389598923991725
  s21_decimal decimal_check = {
      {0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul27) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387504754779197847983448
  s21_decimal decimal_check = {{0x55555558, 0x55555555, 0x55555555, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul28) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -26409387504754779197847983448
  s21_decimal decimal_check = {
      {0x55555558, 0x55555555, 0x55555555, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul29) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul30) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul31) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul32) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul33) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000000000000001431655765
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul34) {
  // 1431655765
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -0.0000000000000000001431655765
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul35) {
  // -26409387.504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -20923672.451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80150000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul36) {
  // -26409387.504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 20923672.451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x150000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul37) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // 57476540395758265626.742442133
  s21_decimal decimal_check = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul38) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // -57476540395758265626.742442133
  s21_decimal decimal_check = {
      {0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul39) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // 7055.820576069728775806815669
  s21_decimal decimal_check = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul40) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // -7055.820576069728775806815669
  s21_decimal decimal_check = {
      {0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul41) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 13204693752377389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul42) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -13204693752377389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul43) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 0.9999999999999999999999999500
  s21_decimal decimal_check = {{0xFFFFE0C, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul44) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.9999999999999999999999999500
  s21_decimal decimal_check = {{0xFFFFE0C, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul45) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x10000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul46) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80010000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul47) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.25
  s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x20000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul48) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -0.25
  s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x80020000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul49) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.2500000000000000000000000000
  s21_decimal decimal_check = {{0x44000000, 0x8F894098, 0x813F397, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul50) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0.2500000000000000000000000000
  s21_decimal decimal_check = {{0x44000000, 0x8F894098, 0x813F397, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul51) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 0.5000000000000000000000000000
  s21_decimal decimal_check = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul52) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.5000000000000000000000000000
  s21_decimal decimal_check = {
      {0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul53) {
  // 7055.820576069728775806815669
  s21_decimal decimal1 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // -5590196992723426894.7708082476
  s21_decimal decimal_check = {
      {0x2DC7792C, 0x10FB6E4E, 0xB4A10696, 0x800A0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1820) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0.5000000000000000000000000000
  s21_decimal decimal_check = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1821) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal_check = {
      {0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1822) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal_check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1823) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -0.5000000000000000000000000000
  s21_decimal decimal_check = {
      {0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1824) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.5000000000000000000000000000
  s21_decimal decimal_check = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1825) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -1.0000000000000000000000000000
  s21_decimal decimal_check = {
      {0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1826) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 1.0000000000000000000000000000
  s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1827) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -7.999999999999999999999999999
  s21_decimal decimal_check = {
      {0x3FFFFFFF, 0xFE8401E7, 0x19D971E4, 0x801B0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1828) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 7.999999999999999999999999999
  s21_decimal decimal_check = {{0x3FFFFFFF, 0xFE8401E7, 0x19D971E4, 0x1B0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1829) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -0.9999999999999999999999999998
  s21_decimal decimal_check = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1830) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.9999999999999999999999999998
  s21_decimal decimal_check = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1831) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1832) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1833) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -7.9228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1834) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 7.9228162514264337593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1835) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -0.7922816251426433759354395033
  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1836) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 0.7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x1C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1837) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // -792281625142643.37593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1838) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // 792281625142643.37593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1839) {
  // -0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // -0.0000000000000025000000000000
  s21_decimal decimal_check = {{0xC41E9000, 0x16BC, 0x0, 0x801C0000}};

  tests_mul(decimal1, decimal2, decimal_check);
}

START_TEST(tests_mul1861) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1862) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1863) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1864) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1865) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1866) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1867) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1868) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1869) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1870) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1871) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1872) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1873) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(tests_mul1874) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  tests_mul_fail1(decimal1, decimal2, code_check);
}

Suite *suite_s21_mul_mini(void) {
  Suite *s = suite_create("\033[45m-=S21_suite_mul_mini=-\033[0m");
  TCase *tc_core = tcase_create("case_mul");

  tcase_add_test(tc_core, tests_mul_fail_manual1);
  tcase_add_test(tc_core, tests_mul_fail_manual2);
  tcase_add_test(tc_core, tests_mul_fail_manual3);
  tcase_add_test(tc_core, tests_mul_fail_manual4);
  tcase_add_test(tc_core, tests_mul_fail_manual5);
  tcase_add_test(tc_core, tests_mul_fail_manual6);
  tcase_add_test(tc_core, tests_mul_fail_manual7);
  tcase_add_test(tc_core, tests_mul_fail_manual8);
  tcase_add_test(tc_core, tests_mul_fail_manual9);
  tcase_add_test(tc_core, tests_mul_fail_manual10);
  tcase_add_test(tc_core, tests_mul_fail_manual11);
  tcase_add_test(tc_core, tests_mul_fail_manual12);
  tcase_add_test(tc_core, tests_mul_fail_manual13);
  tcase_add_test(tc_core, tests_mul_fail_manual14);
  tcase_add_test(tc_core, tests_mul_fail_manual15);
  tcase_add_test(tc_core, tests_mul_fail_manual16);
  tcase_add_test(tc_core, tests_mul_fail_manual17);
  ///
  tcase_add_test(tc_core, tests_mul_manual1);
  tcase_add_test(tc_core, tests_mul_manual2);
  tcase_add_test(tc_core, tests_mul_manual3);
  tcase_add_test(tc_core, tests_mul_manual4);
  tcase_add_test(tc_core, tests_mul_manual5);
  tcase_add_test(tc_core, tests_mul_manual6);
  tcase_add_test(tc_core, tests_mul_manual7);
  tcase_add_test(tc_core, tests_mul_manual8);
  tcase_add_test(tc_core, tests_mul_manual9);
  tcase_add_test(tc_core, tests_mul_manual10);
  tcase_add_test(tc_core, tests_mul_manual11);
  tcase_add_test(tc_core, tests_mul_manual12);
  tcase_add_test(tc_core, tests_mul_manual13);
  tcase_add_test(tc_core, tests_mul_manual14);
  tcase_add_test(tc_core, tests_mul_manual15);
  tcase_add_test(tc_core, tests_mul_manual16);
  tcase_add_test(tc_core, tests_mul_manual17);
  tcase_add_test(tc_core, tests_mul_manual97);
  tcase_add_test(tc_core, tests_mul_manual98);
  tcase_add_test(tc_core, tests_mul_manual99);
  ////
  tcase_add_test(tc_core, tests_mul1);
  tcase_add_test(tc_core, tests_mul2);
  tcase_add_test(tc_core, tests_mul3);
  tcase_add_test(tc_core, tests_mul4);
  tcase_add_test(tc_core, tests_mul5);
  tcase_add_test(tc_core, tests_mul6);
  tcase_add_test(tc_core, tests_mul7);
  tcase_add_test(tc_core, tests_mul8);
  tcase_add_test(tc_core, tests_mul9);
  tcase_add_test(tc_core, tests_mul10);
  tcase_add_test(tc_core, tests_mul11);
  tcase_add_test(tc_core, tests_mul12);
  tcase_add_test(tc_core, tests_mul13);
  tcase_add_test(tc_core, tests_mul14);
  tcase_add_test(tc_core, tests_mul15);
  tcase_add_test(tc_core, tests_mul16);
  tcase_add_test(tc_core, tests_mul17);
  tcase_add_test(tc_core, tests_mul18);
  tcase_add_test(tc_core, tests_mul19);
  tcase_add_test(tc_core, tests_mul20);
  tcase_add_test(tc_core, tests_mul21);
  tcase_add_test(tc_core, tests_mul22);
  tcase_add_test(tc_core, tests_mul23);
  tcase_add_test(tc_core, tests_mul24);
  tcase_add_test(tc_core, tests_mul25);
  tcase_add_test(tc_core, tests_mul26);
  tcase_add_test(tc_core, tests_mul27);
  tcase_add_test(tc_core, tests_mul28);
  tcase_add_test(tc_core, tests_mul29);
  tcase_add_test(tc_core, tests_mul30);
  tcase_add_test(tc_core, tests_mul31);
  tcase_add_test(tc_core, tests_mul32);
  tcase_add_test(tc_core, tests_mul33);
  tcase_add_test(tc_core, tests_mul34);
  tcase_add_test(tc_core, tests_mul35);
  tcase_add_test(tc_core, tests_mul36);
  tcase_add_test(tc_core, tests_mul37);
  tcase_add_test(tc_core, tests_mul38);
  tcase_add_test(tc_core, tests_mul39);
  tcase_add_test(tc_core, tests_mul40);
  tcase_add_test(tc_core, tests_mul41);
  tcase_add_test(tc_core, tests_mul42);
  tcase_add_test(tc_core, tests_mul43);
  tcase_add_test(tc_core, tests_mul44);
  tcase_add_test(tc_core, tests_mul45);
  tcase_add_test(tc_core, tests_mul46);
  tcase_add_test(tc_core, tests_mul47);
  tcase_add_test(tc_core, tests_mul48);
  tcase_add_test(tc_core, tests_mul49);
  tcase_add_test(tc_core, tests_mul50);
  tcase_add_test(tc_core, tests_mul51);
  tcase_add_test(tc_core, tests_mul52);
  tcase_add_test(tc_core, tests_mul53);
  ///
  tcase_add_test(tc_core, tests_mul1820);
  tcase_add_test(tc_core, tests_mul1821);
  tcase_add_test(tc_core, tests_mul1822);
  tcase_add_test(tc_core, tests_mul1823);
  tcase_add_test(tc_core, tests_mul1824);
  tcase_add_test(tc_core, tests_mul1825);
  tcase_add_test(tc_core, tests_mul1826);
  tcase_add_test(tc_core, tests_mul1827);
  tcase_add_test(tc_core, tests_mul1828);
  tcase_add_test(tc_core, tests_mul1829);
  tcase_add_test(tc_core, tests_mul1830);
  tcase_add_test(tc_core, tests_mul1831);
  tcase_add_test(tc_core, tests_mul1832);
  tcase_add_test(tc_core, tests_mul1833);
  tcase_add_test(tc_core, tests_mul1834);
  tcase_add_test(tc_core, tests_mul1835);
  tcase_add_test(tc_core, tests_mul1836);
  tcase_add_test(tc_core, tests_mul1837);
  tcase_add_test(tc_core, tests_mul1838);
  tcase_add_test(tc_core, tests_mul1839);
  ///
  tcase_add_test(tc_core, tests_mul1861);
  tcase_add_test(tc_core, tests_mul1862);
  tcase_add_test(tc_core, tests_mul1863);
  tcase_add_test(tc_core, tests_mul1864);
  tcase_add_test(tc_core, tests_mul1865);
  tcase_add_test(tc_core, tests_mul1866);
  tcase_add_test(tc_core, tests_mul1867);
  tcase_add_test(tc_core, tests_mul1868);
  tcase_add_test(tc_core, tests_mul1869);
  tcase_add_test(tc_core, tests_mul1870);
  tcase_add_test(tc_core, tests_mul1871);
  tcase_add_test(tc_core, tests_mul1872);
  tcase_add_test(tc_core, tests_mul1873);
  tcase_add_test(tc_core, tests_mul1874);

  suite_add_tcase(s, tc_core);
  return s;
}