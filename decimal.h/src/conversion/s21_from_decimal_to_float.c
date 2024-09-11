#include "../s21_decimal.h"

/*

Функция для преобразования decimal числа во float

Возвращаемое значение - код ошибки:

0 - OK
1 - ошибка конвертации
*/

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  if ((dst == NULL) || !s21_is_correct_decimal(src)) {
    error = 1;
  } else {
    *dst = 0;
    int minus = 1;
    long double result = 0, two = 1;
    int exp = s21_get_scale(src);
    if (s21_get_sign(src) == 1) minus = -1;
    for (int k = 0; k < 96; k++) {
      if (s21_get_bit(src, k)) {
        result += two;
      }
      two *= 2;
    }
    for (int k = 0; k < exp; k++) {
      result /= 10;
    }
    *dst = minus * result;
  }
  return error;
}