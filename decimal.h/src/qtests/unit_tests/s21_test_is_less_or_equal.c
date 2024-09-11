#include "s21_decimal_test.h"

START_TEST(s21_is_less_or_equal_0) {
  // 0
  s21_decimal val1 = {{0, 0, 0, 0}};
  // 0
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_1) {
  // 0
  s21_decimal val1 = {{0, 0, 0, 0}};
  // -0
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_sign(&val2, 1);
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  // 79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // -79228162514264337593543950335
  s21_decimal val2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_sign(&val2, 1);
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  // 10
  s21_decimal val1 = {{0xA, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // 100
  s21_decimal val2 = {{0x64, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 32, 1);
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val2, 28, 1);

  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 32, 1);
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val2, 32, 1);

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

// different scale
START_TEST(s21_is_less_or_equal_7) {
  s21_decimal src1, src2;
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100000000000000000000;

  ck_assert_int_eq(FALSE, s21_is_less_or_equal(src1, src2));
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(src1, src2));
}
END_TEST

START_TEST(s21_is_less_or_equal_9) {
  s21_decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = 9798956154578676.797564534156;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01010100010000000011110110001100;
  src2.bits[1] = 0b10001011010100100000010101011001;
  src2.bits[2] = 0b00011111101010011000000110101101;
  src2.bits[3] = 0b00000000000011000000000000000000;

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(src1, src2));
}
END_TEST

START_TEST(s21_is_less_or_equal_10) {
  s21_decimal src1, src2;
  // src1 = 9798956154578676.797564534156;
  // src2 = 9798956154578676.797564534156;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b00000000000011000000000000000000;

  src2.bits[0] = 0b01010100010000000011110110001100;
  src2.bits[1] = 0b10001011010100100000010101011001;
  src2.bits[2] = 0b00011111101010011000000110101101;
  src2.bits[3] = 0b00000000000011000000000000000000;

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(src1, src2));
}
END_TEST

START_TEST(s21_is_less_or_equal_11) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // -5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_12) {
  // 5678932
  s21_decimal val1 = {{0x56A754, 0, 0, 0}};
  // 5678932
  s21_decimal val2 = {{0x56A754, 0, 0, 0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_13) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_14) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 1431655764.999999999999999999
  s21_decimal val2 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_15) {
  // -1431655765
  s21_decimal val1 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -1431655765
  s21_decimal val2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_16) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.0
  s21_decimal val2 = {{0xA, 0x0, 0x0, 0x10000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_17) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_18) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.22
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x20000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_19) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_20) {
  // -10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_21) {
  // 10
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00000000}};
  // 122
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00000000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_22) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_23) {
  // 1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x00010000}};
  // 12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x00010000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_24) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_25) {
  // -1.0
  s21_decimal val1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -12.2
  s21_decimal val2 = {{0x7A, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_26) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // -100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80020000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_27) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_28) {
  // -100.3
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x80010000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_29) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_30) {
  // 10.03
  s21_decimal val1 = {{0x3EB, 0x0, 0x0, 0x00020000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_31) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_32) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 100.30
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x00020000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_33) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_34) {
  // -79228162514264337593543950335
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10030
  s21_decimal val2 = {{0x272E, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_35) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_36) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_or_equal_37) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}
END_TEST

START_TEST(s21_is_less_or_equal_38) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_39) {
  // 52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val2, val1));
}

START_TEST(s21_is_less_or_equal_40) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val2, val1));
}

START_TEST(s21_is_less_or_equal_41) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_42) {
  // 1.2297829382473034410
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 1.2297829382473034410
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_43) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966890
  s21_decimal val2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_44) {
  // -52818775009509558395695966890
  s21_decimal val1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_45) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_46) {
  // 52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_47) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -52818775009509558395695966891
  s21_decimal val2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(FALSE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_48) {
  // -52818775009509558395695966891
  s21_decimal val1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // -0
  s21_decimal val2 = {{0x0, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}

START_TEST(s21_is_less_or_equal_49) {
  // -0
  s21_decimal val1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 5.281877500950955839569596690
  s21_decimal val2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};

  ck_assert_int_eq(TRUE, s21_is_less_or_equal(val1, val2));
}

Suite *suite_s21_is_less_or_equal(void) {
  Suite *s = suite_create("\033[45m-=S21_suite_is_less_or_equal=-\033[0m");
  TCase *tc = tcase_create("case_is_less_or_equal");

  tcase_add_test(tc, s21_is_less_or_equal_0);
  tcase_add_test(tc, s21_is_less_or_equal_1);
  tcase_add_test(tc, s21_is_less_or_equal_2);
  tcase_add_test(tc, s21_is_less_or_equal_3);
  tcase_add_test(tc, s21_is_less_or_equal_4);
  tcase_add_test(tc, s21_is_less_or_equal_5);
  tcase_add_test(tc, s21_is_less_or_equal_6);
  tcase_add_test(tc, s21_is_less_or_equal_7);
  tcase_add_test(tc, s21_is_less_or_equal_8);
  tcase_add_test(tc, s21_is_less_or_equal_9);
  tcase_add_test(tc, s21_is_less_or_equal_10);
  tcase_add_test(tc, s21_is_less_or_equal_11);
  tcase_add_test(tc, s21_is_less_or_equal_12);
  tcase_add_test(tc, s21_is_less_or_equal_13);
  tcase_add_test(tc, s21_is_less_or_equal_14);
  tcase_add_test(tc, s21_is_less_or_equal_15);
  tcase_add_test(tc, s21_is_less_or_equal_16);
  tcase_add_test(tc, s21_is_less_or_equal_17);
  tcase_add_test(tc, s21_is_less_or_equal_18);
  tcase_add_test(tc, s21_is_less_or_equal_19);
  tcase_add_test(tc, s21_is_less_or_equal_20);
  tcase_add_test(tc, s21_is_less_or_equal_21);
  tcase_add_test(tc, s21_is_less_or_equal_22);
  tcase_add_test(tc, s21_is_less_or_equal_23);
  tcase_add_test(tc, s21_is_less_or_equal_24);
  tcase_add_test(tc, s21_is_less_or_equal_25);
  tcase_add_test(tc, s21_is_less_or_equal_26);
  tcase_add_test(tc, s21_is_less_or_equal_27);
  tcase_add_test(tc, s21_is_less_or_equal_28);
  tcase_add_test(tc, s21_is_less_or_equal_29);
  tcase_add_test(tc, s21_is_less_or_equal_30);
  tcase_add_test(tc, s21_is_less_or_equal_31);
  tcase_add_test(tc, s21_is_less_or_equal_32);
  tcase_add_test(tc, s21_is_less_or_equal_33);
  tcase_add_test(tc, s21_is_less_or_equal_34);
  tcase_add_test(tc, s21_is_less_or_equal_35);
  tcase_add_test(tc, s21_is_less_or_equal_36);
  tcase_add_test(tc, s21_is_less_or_equal_37);
  tcase_add_test(tc, s21_is_less_or_equal_38);
  tcase_add_test(tc, s21_is_less_or_equal_39);
  tcase_add_test(tc, s21_is_less_or_equal_40);
  tcase_add_test(tc, s21_is_less_or_equal_41);
  tcase_add_test(tc, s21_is_less_or_equal_42);
  tcase_add_test(tc, s21_is_less_or_equal_43);
  tcase_add_test(tc, s21_is_less_or_equal_44);
  tcase_add_test(tc, s21_is_less_or_equal_45);
  tcase_add_test(tc, s21_is_less_or_equal_46);
  tcase_add_test(tc, s21_is_less_or_equal_47);
  tcase_add_test(tc, s21_is_less_or_equal_48);
  tcase_add_test(tc, s21_is_less_or_equal_49);

  suite_add_tcase(s, tc);
  return s;
}