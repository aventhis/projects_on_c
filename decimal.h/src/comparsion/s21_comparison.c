#include "../s21_decimal.h"

/* ОПЕРАТОРЫ СРАВНЕНИЯ

Возвращаемое значение:
- 0 - FALSE
- 1 - TRUE
*/

int s21_is_less(s21_decimal a, s21_decimal b) {
  int error = FALSE;

  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);
  int scale_a = s21_get_scale(a);
  int scale_b = s21_get_scale(b);
  int scale_dif = scale_a - scale_b;

  if (s21_is_equal(a, b) == TRUE) {
    error = FALSE;

  } else if (sign_a == sign_b) {
    if (scale_dif == 0) {
      error = s21_is_mantisa_less(a, b, sign_a);
    } else {
      work_decimal a_big = s21_init_work_decimal(a);
      work_decimal b_big = s21_init_work_decimal(b);

      s21_normalized_scales_decimal(&a_big, &b_big, 0);

      error = s21_big_is_mantisa_less(a_big, b_big, sign_a);
    }
  } else if (sign_a > sign_b) {
    error = TRUE;
  } else {
    error = FALSE;
  }

  return error;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int error = FALSE;

  if (s21_is_less(a, b)) error = TRUE;

  if (s21_is_equal(a, b)) error = TRUE;

  return error;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int error = FALSE;

  error = !s21_is_less(a, b);
  if (s21_is_equal(a, b) == TRUE) error = FALSE;

  return error;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int error = FALSE;

  error = !s21_is_less(a, b);

  return error;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int error = FALSE;

  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);
  int scale_a = s21_get_scale(a);
  int scale_b = s21_get_scale(b);
  int scale_dif = scale_a - scale_b;

  // 1. если оба числа нули
  if ((s21_is_null(a) == TRUE) && (s21_is_null(b) == TRUE)) {
    error = TRUE;
    // 2. если знаки у чисел
  } else if (sign_a == sign_b) {
    // проверяем степени 2-х чисел - если разные нужно приводить к одному виду
    if (scale_dif == 0) {
      // возвращает TRUE - если да, FALSE - если нет
      error = s21_is_mantisa_both_decimal_is_equal(a, b);

    } else {
      work_decimal a_big = s21_init_work_decimal(a);
      work_decimal b_big = s21_init_work_decimal(b);

      s21_normalized_scales_decimal(&a_big, &b_big, 0);
      error = s21_is_mantisa_both_decimal_big_is_equal(a_big, b_big);
    }
    // 2. если знаки у чисел разные
  } else {
    error = FALSE;
  }

  return error;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}
