#include "s21_decimal_test.h"

void tests_round(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_round(decimal, &result);
  int sign_check = s21_get_sign(decimal_check);
  int sign_result = s21_get_sign(result);

  ck_assert_int_eq(code, TEST_OTHER_OK);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(tests_round_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_round(decimal, NULL);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}

START_TEST(tests_round_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_round_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_round_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_round_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_round_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_round_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_round_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_round_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

///

START_TEST(tests_round_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok6) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok7) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok8) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok9) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok10) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok11) {
  // 79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
  // 79228162514264337593544
  s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok12) {
  // -79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
  // -79228162514264337593544
  s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok13) {
  // 79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  // 79228162514264337594
  s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok14) {
  // -79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
  // -79228162514264337594
  s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok15) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok16) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -8
  s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok17) {
  // 5.2818775009509558395695966890
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
  // 5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok18) {
  // -5.2818775009509558395695966890
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
  // -5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok19) {
  // 1.8446744069414584320
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok20) {
  // -1.8446744069414584320
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok21) {
  // 4294967295
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
  // 4294967295
  s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok22) {
  // -4294967295
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
  // -4294967295
  s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok23) {
  // 429496729.5
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
  // 429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok24) {
  // -429496729.5
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
  // -429496730
  s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok25) {
  // 42949672.95
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
  // 42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok26) {
  // -42949672.95
  s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
  // -42949673
  s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok27) {
  // 1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok28) {
  // -1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok29) {
  // 1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok30) {
  // -1.00
  s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok31) {
  // 1.0000000000000000000000000000
  s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok32) {
  // -1.0000000000000000000000000000
  s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok33) {
  // 1.1
  s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok34) {
  // -1.1
  s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok35) {
  // 9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok36) {
  // -9.9
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok37) {
  // 99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
  // 100
  s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok38) {
  // -99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
  // -100
  s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok39) {
  // 0.99
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok40) {
  // -0.99
  s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok41) {
  // -0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok42) {
  // 0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok43) {
  // -0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok44) {
  // 0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok45) {
  // 0.5
  s21_decimal decimal = {{0x5, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok46) {
  // -0.5
  s21_decimal decimal = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok47) {
  // 0.49
  s21_decimal decimal = {{0x31, 0x0, 0x0, 0x20000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok48) {
  // -0.49
  s21_decimal decimal = {{0x31, 0x0, 0x0, 0x80020000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok49) {
  // 0.51
  s21_decimal decimal = {{0x33, 0x0, 0x0, 0x20000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok50) {
  // -0.51
  s21_decimal decimal = {{0x33, 0x0, 0x0, 0x80020000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok51) {
  // 0.4999999999999999999999999999
  s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok52) {
  // -0.4999999999999999999999999999
  s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok53) {
  // 0.5000000000000000000000000001
  s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok54) {
  // -0.5000000000000000000000000001
  s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok55) {
  // 0.5000000000000000000000000000
  s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_round(decimal, decimal_check);
}

START_TEST(tests_round_ok56) {
  // -0.5000000000000000000000000000
  s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_round(decimal, decimal_check);
}

Suite *suite_round_mini(void) {
  Suite *s = suite_create("\033[45m-=S21_round_suite_mini=-\033[0m");
  TCase *tc = tcase_create("case_round");

  tcase_add_test(tc, tests_round_fail1);
  tcase_add_test(tc, tests_round_fail2);
  tcase_add_test(tc, tests_round_fail3);
  tcase_add_test(tc, tests_round_fail4);
  tcase_add_test(tc, tests_round_fail5);
  tcase_add_test(tc, tests_round_fail6);
  tcase_add_test(tc, tests_round_fail7);
  tcase_add_test(tc, tests_round_fail8);
  tcase_add_test(tc, tests_round_fail9);
  //
  tcase_add_test(tc, tests_round_ok1);
  tcase_add_test(tc, tests_round_ok2);
  tcase_add_test(tc, tests_round_ok3);
  tcase_add_test(tc, tests_round_ok4);
  tcase_add_test(tc, tests_round_ok5);
  tcase_add_test(tc, tests_round_ok6);
  tcase_add_test(tc, tests_round_ok7);
  tcase_add_test(tc, tests_round_ok8);
  tcase_add_test(tc, tests_round_ok9);
  tcase_add_test(tc, tests_round_ok10);
  tcase_add_test(tc, tests_round_ok11);
  tcase_add_test(tc, tests_round_ok12);
  tcase_add_test(tc, tests_round_ok13);
  tcase_add_test(tc, tests_round_ok14);
  tcase_add_test(tc, tests_round_ok15);
  tcase_add_test(tc, tests_round_ok16);
  tcase_add_test(tc, tests_round_ok17);
  tcase_add_test(tc, tests_round_ok18);
  tcase_add_test(tc, tests_round_ok19);
  tcase_add_test(tc, tests_round_ok20);
  tcase_add_test(tc, tests_round_ok21);
  tcase_add_test(tc, tests_round_ok22);
  tcase_add_test(tc, tests_round_ok23);
  tcase_add_test(tc, tests_round_ok24);
  tcase_add_test(tc, tests_round_ok25);
  tcase_add_test(tc, tests_round_ok26);
  tcase_add_test(tc, tests_round_ok27);
  tcase_add_test(tc, tests_round_ok28);
  tcase_add_test(tc, tests_round_ok29);
  tcase_add_test(tc, tests_round_ok30);
  tcase_add_test(tc, tests_round_ok31);
  tcase_add_test(tc, tests_round_ok32);
  tcase_add_test(tc, tests_round_ok33);
  tcase_add_test(tc, tests_round_ok34);
  tcase_add_test(tc, tests_round_ok35);
  tcase_add_test(tc, tests_round_ok36);
  tcase_add_test(tc, tests_round_ok37);
  tcase_add_test(tc, tests_round_ok38);
  tcase_add_test(tc, tests_round_ok39);
  tcase_add_test(tc, tests_round_ok40);
  tcase_add_test(tc, tests_round_ok41);
  tcase_add_test(tc, tests_round_ok42);
  tcase_add_test(tc, tests_round_ok43);
  tcase_add_test(tc, tests_round_ok44);
  tcase_add_test(tc, tests_round_ok45);
  tcase_add_test(tc, tests_round_ok46);
  tcase_add_test(tc, tests_round_ok47);
  tcase_add_test(tc, tests_round_ok48);
  tcase_add_test(tc, tests_round_ok49);
  tcase_add_test(tc, tests_round_ok50);
  tcase_add_test(tc, tests_round_ok51);
  tcase_add_test(tc, tests_round_ok52);
  tcase_add_test(tc, tests_round_ok53);
  tcase_add_test(tc, tests_round_ok54);
  tcase_add_test(tc, tests_round_ok55);
  tcase_add_test(tc, tests_round_ok56);

  ////

  suite_add_tcase(s, tc);
  return s;
}
