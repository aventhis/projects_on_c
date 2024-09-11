#include "s21_decimal_test.h"

void tests_floor(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_floor(decimal, &result);
  int sign_check = s21_get_sign(decimal_check);
  int sign_result = s21_get_sign(result);

  ck_assert_int_eq(code, TEST_OTHER_OK);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(tests_floor_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_floor(decimal, NULL);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}

START_TEST(tests_floor_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_floor_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_floor_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_floor_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_floor_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_floor_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_floor_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_floor_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

///

START_TEST(tests_floor_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok6) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439504
  s21_decimal decimal_check = {{0x28F5C290, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok7) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok8) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543951
  s21_decimal decimal_check = {{0x9DB22D0F, 0x4BC6A7EF, 0x418937, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok9) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok10) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354396
  s21_decimal decimal_check = {{0x295E9E1C, 0xBAC710CB, 0x68DB8, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok11) {
  // 79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
  // 79228162514264337593543
  s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok12) {
  // -79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
  // -79228162514264337593544
  s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok13) {
  // 5.2818774997211729016086244010
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
  // 5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok14) {
  // -5.2818774997211729016086244010
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
  // -6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok15) {
  // 1.2297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok16) {
  // -1.2297829382473034410
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok17) {
  // 4294967.296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
  // 4294967
  s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok18) {
  // -4294967.296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
  // -4294968
  s21_decimal decimal_check = {{0x418938, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok19) {
  // 4.294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
  // 4
  s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok20) {
  // -4.294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
  // -5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok21) {
  // 1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok22) {
  // -1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok23) {
  // 1.0000000000
  s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok24) {
  // -1.0000000000
  s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok25) {
  // 9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
  // 9
  s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok26) {
  // -9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok27) {
  // -0.99999
  s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok28) {
  // 0.999999
  s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok29) {
  // -0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok30) {
  // 0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok31) {
  // -0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok32) {
  // 0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok33) {
  // 0.9999999999999999999999999999
  s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_floor(decimal, decimal_check);
}

START_TEST(tests_floor_ok34) {
  // -0.9999999999999999999999999999
  s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_floor(decimal, decimal_check);
}

Suite *suite_floor_mini(void) {
  Suite *s = suite_create("\033[45m-=S21_floor_suite_mini=-\033[0m");
  TCase *tc = tcase_create("case_round");

  tcase_add_test(tc, tests_floor_fail1);
  tcase_add_test(tc, tests_floor_fail2);
  tcase_add_test(tc, tests_floor_fail3);
  tcase_add_test(tc, tests_floor_fail4);
  tcase_add_test(tc, tests_floor_fail5);
  tcase_add_test(tc, tests_floor_fail6);
  tcase_add_test(tc, tests_floor_fail7);
  tcase_add_test(tc, tests_floor_fail8);
  tcase_add_test(tc, tests_floor_fail9);
  //
  tcase_add_test(tc, tests_floor_ok1);
  tcase_add_test(tc, tests_floor_ok2);
  tcase_add_test(tc, tests_floor_ok3);
  tcase_add_test(tc, tests_floor_ok4);
  tcase_add_test(tc, tests_floor_ok5);
  tcase_add_test(tc, tests_floor_ok6);
  tcase_add_test(tc, tests_floor_ok7);
  tcase_add_test(tc, tests_floor_ok8);
  tcase_add_test(tc, tests_floor_ok9);
  tcase_add_test(tc, tests_floor_ok10);
  tcase_add_test(tc, tests_floor_ok11);
  tcase_add_test(tc, tests_floor_ok12);
  tcase_add_test(tc, tests_floor_ok13);
  tcase_add_test(tc, tests_floor_ok14);
  tcase_add_test(tc, tests_floor_ok15);
  tcase_add_test(tc, tests_floor_ok16);
  tcase_add_test(tc, tests_floor_ok17);
  tcase_add_test(tc, tests_floor_ok18);
  tcase_add_test(tc, tests_floor_ok19);
  tcase_add_test(tc, tests_floor_ok20);
  tcase_add_test(tc, tests_floor_ok21);
  tcase_add_test(tc, tests_floor_ok22);
  tcase_add_test(tc, tests_floor_ok23);
  tcase_add_test(tc, tests_floor_ok24);
  tcase_add_test(tc, tests_floor_ok25);
  tcase_add_test(tc, tests_floor_ok26);
  tcase_add_test(tc, tests_floor_ok27);
  tcase_add_test(tc, tests_floor_ok28);
  tcase_add_test(tc, tests_floor_ok29);
  tcase_add_test(tc, tests_floor_ok30);
  tcase_add_test(tc, tests_floor_ok31);
  tcase_add_test(tc, tests_floor_ok32);
  tcase_add_test(tc, tests_floor_ok33);
  tcase_add_test(tc, tests_floor_ok34);
  ///

  suite_add_tcase(s, tc);
  return s;
}
