#include "../s21_decimal.h"

/*

Функция для преобразования float числа в decimal

Возвращаемое значение - код ошибки:

0 - OK
1 - ошибка конвертации
*/

void s21_round_for_float(double *temp_number) {
  double mantissa_double_temp = *temp_number;
  long int whole_part = *temp_number;

  whole_part *= 100000000;
  mantissa_double_temp *= 100000000;

  long int fraction_part = mantissa_double_temp;
  fraction_part -= whole_part;

  if (fraction_part == 50000000) {
    long int digit = whole_part / 100000000;

    digit -= (whole_part / 1000000000) * 10;

    if ((digit % 2) == 1) {
      *temp_number += 1.0;
    }
  }
  if (fraction_part != 50000000) {
    *temp_number = roundl(*temp_number);
  }
}

void s21_float_to_dec_binary(double *temp_number, fbits mantissa,
                             s21_decimal *dst) {
  mantissa.fl = (float)*temp_number;

  int exp = ((mantissa.ui & ~(1u << 31)) >> 23) - 127;

  s21_set_bit(dst, exp, 1);

  for (int i = exp - 1, j = 22; j >= 0 && i >= 0; i--, j--) {
    if ((mantissa.ui & (1 << j)) != 0) {
      s21_set_bit(dst, i, 1);
    }
  }
}

void s21_scale_adjust(double *temp_number, int *scale, int *scale_diff,
                      fbits mantissa) {
  int scale_whole_part = 0;
  double temp_whole_part = *temp_number;

  while ((*scale < 28) && (((*temp_number < 999999) && (mantissa.fl >= 1)) ||
                           ((*temp_number < 1000000) && (mantissa.fl < 1)))) {
    *temp_number *= 10;
    (*scale)++;
  }

  if (*scale == 0) {
    while (temp_whole_part > 1) {
      temp_whole_part /= 10;
      scale_whole_part++;
    }
  }

  while (scale_whole_part > 7) {
    *temp_number /= 10;
    scale_whole_part--;
    (*scale_diff)++;
  }

  while (((int)fmod(*temp_number, 10) == 0) && (*scale > 0) &&
         ((int)fmod(*temp_number * 10, 10) <= 5)) {
    *temp_number /= 10;
    (*scale)--;
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;

  if (dst == NULL || (fabs(src) > s21_MAXDEC) || (fabs(src) == INFINITY) ||
      isnan(fabs(src))) {
    error = 1;
  } else if (fabs(src) > 0 && fabs(src) < 1e-28) {
    error = 1;
    s21_clear_decimal(dst);
  } else if (src == 0.0) {
    s21_clear_decimal(dst);
  } else {
    s21_clear_decimal(dst);

    fbits mantissa = {0};
    int scale = 0;

    mantissa.fl = src;

    unsigned int sign = (mantissa.ui >> 31) & 0x00000001;
    if (sign == 1) {
      mantissa.fl *= -1;
      s21_set_sign(dst, 1);
    }

    int exp = ((mantissa.ui & ~(1u << 31)) >> 23) - 127;
    double temp_number = (double)mantissa.fl;

    if (exp >= -94 && exp < 96) {
      int scale_diff = 0;

      s21_scale_adjust(&temp_number, &scale, &scale_diff, mantissa);
      s21_round_for_float(&temp_number);
      s21_float_to_dec_binary(&temp_number, mantissa, dst);
      s21_set_scale(dst, scale);

      if (scale_diff > 0) {
        s21_decimal ten = {{0xA, 0x0, 0x0, 0x0}};
        for (int i = scale_diff; i > 0; i--) s21_mul(*dst, ten, dst);
      }
    }
  }
  return error;
}