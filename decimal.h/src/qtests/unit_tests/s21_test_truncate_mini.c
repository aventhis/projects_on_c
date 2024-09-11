#include "s21_decimal_test.h"

void tests_truncate(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_truncate(decimal, &result);
  int sign_check = s21_get_sign(decimal_check);
  int sign_result = s21_get_sign(result);

  ck_assert_int_eq(code, TEST_OTHER_OK);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(tests_truncate_fail1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_truncate(decimal, NULL);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}

START_TEST(tests_truncate_fail2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_truncate_fail3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_truncate_fail4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_truncate_fail5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_truncate_fail6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_truncate_fail7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_truncate_fail8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(tests_truncate_fail9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

///
START_TEST(tests_truncate_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033
  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok5) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok6) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok7) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok8) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok9) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok10) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok11) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7
  s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok12) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7
  s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok13) {
  // 6.148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
  // 6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok14) {
  // -6.148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
  // -6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok15) {
  // 4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
  // 4294967297
  s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok16) {
  // -4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
  // -4294967297
  s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok17) {
  // 429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
  // 429496729
  s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok18) {
  // -429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
  // -429496729
  s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok19) {
  // 0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok20) {
  // -0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok21) {
  // 0.0000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok22) {
  // -0.0000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok23) {
  // 1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok24) {
  // -1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok25) {
  // 1.0000000000000000000000000000
  s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok26) {
  // -1.0000000000000000000000000000
  s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok27) {
  // 1.1
  s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok28) {
  // -1.1
  s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok29) {
  // 99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
  // 99
  s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok30) {
  // -99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
  // -99
  s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok31) {
  // -0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok32) {
  // 0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok33) {
  // -0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok34) {
  // 0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok35) {
  // -0.0000000000000000000000000000
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok36) {
  // 0.0000000000000000000000000000
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok37) {
  // 0.5
  s21_decimal decimal = {{0x5, 0x0, 0x0, 0x10000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok38) {
  // -0.5
  s21_decimal decimal = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok39) {
  // 0.49
  s21_decimal decimal = {{0x31, 0x0, 0x0, 0x20000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok40) {
  // -0.49
  s21_decimal decimal = {{0x31, 0x0, 0x0, 0x80020000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok41) {
  // 0.51
  s21_decimal decimal = {{0x33, 0x0, 0x0, 0x20000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok42) {
  // -0.51
  s21_decimal decimal = {{0x33, 0x0, 0x0, 0x80020000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok43) {
  // 0.4999999999999999999999999999
  s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok44) {
  // -0.4999999999999999999999999999
  s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok45) {
  // 0.5000000000000000000000000001
  s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_truncate(decimal, decimal_check);
}

START_TEST(tests_truncate_ok46) {
  // -0.5000000000000000000000000001
  s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  tests_truncate(decimal, decimal_check);
}

Suite *suite_truncate_mini(void) {
  Suite *s = suite_create("\033[45m-=S21_truncate_suite_mini=-\033[0m");
  TCase *tc = tcase_create("case_truncate");

  ////
  tcase_add_test(tc, tests_truncate_fail1);
  tcase_add_test(tc, tests_truncate_fail2);
  tcase_add_test(tc, tests_truncate_fail3);
  tcase_add_test(tc, tests_truncate_fail4);
  tcase_add_test(tc, tests_truncate_fail5);
  tcase_add_test(tc, tests_truncate_fail6);
  tcase_add_test(tc, tests_truncate_fail7);
  tcase_add_test(tc, tests_truncate_fail8);
  tcase_add_test(tc, tests_truncate_fail9);

  tcase_add_test(tc, tests_truncate_ok1);
  tcase_add_test(tc, tests_truncate_ok2);
  tcase_add_test(tc, tests_truncate_ok3);
  tcase_add_test(tc, tests_truncate_ok4);
  tcase_add_test(tc, tests_truncate_ok5);
  tcase_add_test(tc, tests_truncate_ok6);
  tcase_add_test(tc, tests_truncate_ok7);
  tcase_add_test(tc, tests_truncate_ok8);
  tcase_add_test(tc, tests_truncate_ok9);
  tcase_add_test(tc, tests_truncate_ok10);
  tcase_add_test(tc, tests_truncate_ok11);
  tcase_add_test(tc, tests_truncate_ok12);
  tcase_add_test(tc, tests_truncate_ok13);
  tcase_add_test(tc, tests_truncate_ok14);
  tcase_add_test(tc, tests_truncate_ok15);
  tcase_add_test(tc, tests_truncate_ok16);
  tcase_add_test(tc, tests_truncate_ok17);
  tcase_add_test(tc, tests_truncate_ok18);
  tcase_add_test(tc, tests_truncate_ok19);
  tcase_add_test(tc, tests_truncate_ok20);
  tcase_add_test(tc, tests_truncate_ok21);
  tcase_add_test(tc, tests_truncate_ok22);
  tcase_add_test(tc, tests_truncate_ok23);
  tcase_add_test(tc, tests_truncate_ok24);
  tcase_add_test(tc, tests_truncate_ok25);
  tcase_add_test(tc, tests_truncate_ok26);
  tcase_add_test(tc, tests_truncate_ok27);
  tcase_add_test(tc, tests_truncate_ok28);
  tcase_add_test(tc, tests_truncate_ok29);
  tcase_add_test(tc, tests_truncate_ok30);
  tcase_add_test(tc, tests_truncate_ok31);
  tcase_add_test(tc, tests_truncate_ok32);
  tcase_add_test(tc, tests_truncate_ok33);
  tcase_add_test(tc, tests_truncate_ok34);
  tcase_add_test(tc, tests_truncate_ok35);
  tcase_add_test(tc, tests_truncate_ok36);
  tcase_add_test(tc, tests_truncate_ok37);
  tcase_add_test(tc, tests_truncate_ok38);
  tcase_add_test(tc, tests_truncate_ok39);
  tcase_add_test(tc, tests_truncate_ok40);
  tcase_add_test(tc, tests_truncate_ok41);
  tcase_add_test(tc, tests_truncate_ok42);
  tcase_add_test(tc, tests_truncate_ok43);
  tcase_add_test(tc, tests_truncate_ok44);
  tcase_add_test(tc, tests_truncate_ok45);
  tcase_add_test(tc, tests_truncate_ok46);

  suite_add_tcase(s, tc);
  return s;
}