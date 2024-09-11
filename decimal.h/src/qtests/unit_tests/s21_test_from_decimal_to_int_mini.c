#include "s21_decimal_test.h"

void tests_from_decimal_to_int(s21_decimal decimal, int check) {
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, TEST_CONVERSION_OK);
}

void tests_from_decimal_to_int_fail(s21_decimal decimal) {
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}

////

START_TEST(tests_from_decimal_to_int_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_from_decimal_to_int(decimal, NULL);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}

START_TEST(tests_from_decimal_to_int_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_decimal_to_int_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_decimal_to_int_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_decimal_to_int_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_decimal_to_int_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_decimal_to_int_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_decimal_to_int_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_decimal_to_int_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

/////

START_TEST(tests_from_decimal_to_int_ok1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int check = 792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok2) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  int check = -792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok3) {
  // 79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
  int check = 79228162;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok4) {
  // -79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
  int check = -79228162;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok5) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int check = 7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok6) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int check = -7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok7) {
  // 528187750.09509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
  int check = 528187750;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok8) {
  // -528187750.09509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
  int check = -528187750;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok9) {
  // 5.2818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
  int check = 5;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok10) {
  // -5.2818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
  int check = -5;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok11) {
  // 286331153.0
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
  int check = 286331153;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok12) {
  // -286331153.0
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
  int check = -286331153;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok13) {
  // 429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
  int check = 429496729;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok14) {
  // -429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
  int check = -429496729;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok15) {
  // 1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
  int check = 1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok16) {
  // -1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
  int check = -1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok17) {
  // 0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok18) {
  // -0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok19) {
  // 0.0000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok20) {
  // -0.0000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok21) {
  // -2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok22) {
  // 214748364.8
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
  int check = 214748364;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok23) {
  // -214748364.8
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
  int check = -214748364;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok24) {
  // 8460288
  s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
  int check = 8460288;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok25) {
  // -8460288
  s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
  int check = -8460288;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok26) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int check = 792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok27) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  int check = -792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok28) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int check = 7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok29) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int check = -7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok30) {
  // 1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
  int check = 1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok31) {
  // -1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
  int check = -1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok32) {
  // 99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
  int check = 99;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok33) {
  // -99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
  int check = -99;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok34) {
  // -0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok35) {
  // 0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok36) {
  // -0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok37) {
  // 0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok38) {
  // 2147483647
  s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};
  int check = 2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok39) {
  // -2147483647
  s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};
  int check = -2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok40) {
  // 2147483647.00
  s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x20000}};
  int check = 2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok41) {
  // -2147483647.00
  s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x80020000}};
  int check = -2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok42) {
  // -2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok43) {
  // -2147483648.00
  s21_decimal decimal = {{0x0, 0x32, 0x0, 0x80020000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok44) {
  // -2147483648.99
  s21_decimal decimal = {{0x63, 0x32, 0x0, 0x80020000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok45) {
  // 21474836.48
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
  int check = 21474836;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok46) {
  // -21474836.48
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
  int check = -21474836;

  tests_from_decimal_to_int(decimal, check);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests for incorrect data (auto)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(tests_from_decimal_to_int_fail1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail5) {
  // 52818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail6) {
  // -52818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail7) {
  // 5281877500950955839283265536.0
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail8) {
  // -5281877500950955839283265536.0
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail9) {
  // 26409387504754779196416327680
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail10) {
  // -26409387504754779196416327680
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail11) {
  // 2640938750475477919641632768.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail12) {
  // -2640938750475477919641632768.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail13) {
  // 26409387498605864508043122005
  s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail17) {
  // -26409387498605864508043122005
  s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail18) {
  // 6148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail19) {
  // -6148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail20) {
  // 614891468980486144.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail21) {
  // -614891468980486144.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail22) {
  // 4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail23) {
  // -4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail24) {
  // 39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail25) {
  // -39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail26) {
  // 39614081257132168798919458816
  s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail27) {
  // -39614081257132168798919458816
  s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail28) {
  // 9223372039002259456
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail29) {
  // -9223372039002259456
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail30) {
  // 2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail31) {
  // 7922816251426433758924898304.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail32) {
  // -7922816251426433758924898304.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail33) {
  // 1844674406941458432.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail34) {
  // -1844674406941458432.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail35) {
  // 2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail36) {
  // 2147483648.00
  s21_decimal decimal = {{0x0, 0x32, 0x0, 0x20000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail37) {
  // 2147483648.99
  s21_decimal decimal = {{0x63, 0x32, 0x0, 0x20000}};

  tests_from_decimal_to_int_fail(decimal);
}

Suite *suite_from_decimal_to_int_mini(void) {
  Suite *s = suite_create("\033[45m-=S21_from_decimal_to_int_mini=-\033[0m");
  TCase *tc = tcase_create("case_from_int_to_decimal");

  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual1);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual2);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual3);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual4);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual5);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual6);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual7);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual8);
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual9);
  ///

  tcase_add_test(tc, tests_from_decimal_to_int_ok1);
  tcase_add_test(tc, tests_from_decimal_to_int_ok2);
  tcase_add_test(tc, tests_from_decimal_to_int_ok3);
  tcase_add_test(tc, tests_from_decimal_to_int_ok4);
  tcase_add_test(tc, tests_from_decimal_to_int_ok5);
  tcase_add_test(tc, tests_from_decimal_to_int_ok6);
  tcase_add_test(tc, tests_from_decimal_to_int_ok7);
  tcase_add_test(tc, tests_from_decimal_to_int_ok8);
  tcase_add_test(tc, tests_from_decimal_to_int_ok9);
  tcase_add_test(tc, tests_from_decimal_to_int_ok10);
  tcase_add_test(tc, tests_from_decimal_to_int_ok11);
  tcase_add_test(tc, tests_from_decimal_to_int_ok12);
  tcase_add_test(tc, tests_from_decimal_to_int_ok13);
  tcase_add_test(tc, tests_from_decimal_to_int_ok14);
  tcase_add_test(tc, tests_from_decimal_to_int_ok15);
  tcase_add_test(tc, tests_from_decimal_to_int_ok16);
  tcase_add_test(tc, tests_from_decimal_to_int_ok17);
  tcase_add_test(tc, tests_from_decimal_to_int_ok18);
  tcase_add_test(tc, tests_from_decimal_to_int_ok19);
  tcase_add_test(tc, tests_from_decimal_to_int_ok20);
  tcase_add_test(tc, tests_from_decimal_to_int_ok21);
  tcase_add_test(tc, tests_from_decimal_to_int_ok22);
  tcase_add_test(tc, tests_from_decimal_to_int_ok23);
  tcase_add_test(tc, tests_from_decimal_to_int_ok24);
  tcase_add_test(tc, tests_from_decimal_to_int_ok25);
  tcase_add_test(tc, tests_from_decimal_to_int_ok26);
  tcase_add_test(tc, tests_from_decimal_to_int_ok27);
  tcase_add_test(tc, tests_from_decimal_to_int_ok28);
  tcase_add_test(tc, tests_from_decimal_to_int_ok29);
  tcase_add_test(tc, tests_from_decimal_to_int_ok30);
  tcase_add_test(tc, tests_from_decimal_to_int_ok31);
  tcase_add_test(tc, tests_from_decimal_to_int_ok32);
  tcase_add_test(tc, tests_from_decimal_to_int_ok33);
  tcase_add_test(tc, tests_from_decimal_to_int_ok34);
  tcase_add_test(tc, tests_from_decimal_to_int_ok35);
  tcase_add_test(tc, tests_from_decimal_to_int_ok36);
  tcase_add_test(tc, tests_from_decimal_to_int_ok37);
  tcase_add_test(tc, tests_from_decimal_to_int_ok38);
  tcase_add_test(tc, tests_from_decimal_to_int_ok39);
  tcase_add_test(tc, tests_from_decimal_to_int_ok40);
  tcase_add_test(tc, tests_from_decimal_to_int_ok41);
  tcase_add_test(tc, tests_from_decimal_to_int_ok42);
  tcase_add_test(tc, tests_from_decimal_to_int_ok43);
  tcase_add_test(tc, tests_from_decimal_to_int_ok44);
  tcase_add_test(tc, tests_from_decimal_to_int_ok45);
  tcase_add_test(tc, tests_from_decimal_to_int_ok46);
  ///
  tcase_add_test(tc, tests_from_decimal_to_int_fail1);
  tcase_add_test(tc, tests_from_decimal_to_int_fail2);
  tcase_add_test(tc, tests_from_decimal_to_int_fail3);
  tcase_add_test(tc, tests_from_decimal_to_int_fail4);
  tcase_add_test(tc, tests_from_decimal_to_int_fail5);
  tcase_add_test(tc, tests_from_decimal_to_int_fail6);
  tcase_add_test(tc, tests_from_decimal_to_int_fail7);
  tcase_add_test(tc, tests_from_decimal_to_int_fail8);
  tcase_add_test(tc, tests_from_decimal_to_int_fail9);
  tcase_add_test(tc, tests_from_decimal_to_int_fail10);
  tcase_add_test(tc, tests_from_decimal_to_int_fail11);
  tcase_add_test(tc, tests_from_decimal_to_int_fail12);
  tcase_add_test(tc, tests_from_decimal_to_int_fail13);
  tcase_add_test(tc, tests_from_decimal_to_int_fail17);
  tcase_add_test(tc, tests_from_decimal_to_int_fail18);
  tcase_add_test(tc, tests_from_decimal_to_int_fail19);
  tcase_add_test(tc, tests_from_decimal_to_int_fail20);
  tcase_add_test(tc, tests_from_decimal_to_int_fail21);
  tcase_add_test(tc, tests_from_decimal_to_int_fail22);
  tcase_add_test(tc, tests_from_decimal_to_int_fail23);
  tcase_add_test(tc, tests_from_decimal_to_int_fail24);
  tcase_add_test(tc, tests_from_decimal_to_int_fail25);
  tcase_add_test(tc, tests_from_decimal_to_int_fail26);
  tcase_add_test(tc, tests_from_decimal_to_int_fail27);
  tcase_add_test(tc, tests_from_decimal_to_int_fail28);
  tcase_add_test(tc, tests_from_decimal_to_int_fail29);
  tcase_add_test(tc, tests_from_decimal_to_int_fail30);
  tcase_add_test(tc, tests_from_decimal_to_int_fail31);
  tcase_add_test(tc, tests_from_decimal_to_int_fail32);
  tcase_add_test(tc, tests_from_decimal_to_int_fail33);
  tcase_add_test(tc, tests_from_decimal_to_int_fail34);
  tcase_add_test(tc, tests_from_decimal_to_int_fail35);
  tcase_add_test(tc, tests_from_decimal_to_int_fail36);
  tcase_add_test(tc, tests_from_decimal_to_int_fail37);

  suite_add_tcase(s, tc);
  return s;
}
