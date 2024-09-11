#include "../s21_decimal.h"

/*
Функции возвращают код ошибки:

0 - OK
1 - число слишком велико или равно бесконечности
2 - число слишком мало или равно отрицательной бесконечности
3 - деление на 0
*/

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  if (s21_is_correct_decimal(value_1) && s21_is_correct_decimal(value_2) &&
      !(result == NULL) && !s21_is_null(value_2)) {
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    s21_clear_decimal(result);

    error = s21_div_main(value_1, value_2, result);

    if (sign_1 != sign_2) {
      s21_set_sign(result, 1);
      if (error) {
        error = 2;  // smaller error 2
      }
    }
  } else {
    error = 1;
  }

  if (s21_is_null(value_2)) {
    error = 3;
  }

  return error;
}

void s21_sub_for_div(work_decimal value_1, work_decimal value_2,
                     work_decimal *remainder) {
  work_decimal divider_additional_code = value_2;
  work_decimal one_big = {{0x1, 0x0, 0x0, 0x0, 0x0, 0x0}, 0, 0};
  work_decimal divider_additional = {0};

  s21_invert(&divider_additional_code);

  s21_add_big(divider_additional_code, one_big, &divider_additional);

  s21_add_big(value_1, divider_additional, remainder);
}

void s21_shift_div(int shift, int sub_or_add, work_decimal value_1,
                   work_decimal divider_shift, work_decimal *quotient,
                   work_decimal *remainder) {
  work_decimal dividend = value_1;
  while (shift >= 0) {
    if (sub_or_add) {
      s21_sub_for_div(dividend, divider_shift, &dividend);
    } else {
      s21_add_big(dividend, divider_shift, &dividend);
    }

    s21_big_shift_left(quotient);
    if (!s21_big_get_bit(dividend, (32 * 6) - 1)) {
      s21_big_set_bit(quotient, 0, 1);
      sub_or_add = 1;
    } else {
      sub_or_add = 0;
    }

    *remainder = dividend;

    s21_big_shift_left(&dividend);

    shift--;
  }
}

// Деление work_decimal чисел
void s21_div_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result_quotient,
                 work_decimal *result_remainder) {
  work_decimal divider_shift = value_2;
  work_decimal quotient = {0};
  work_decimal remainder = {0};

  int shift_1 = s21_get_significant_bit(value_1);
  int shift_2 = s21_get_significant_bit(divider_shift);
  int shift = shift_1 - shift_2;

  if (s21_big_is_mantisa_less(value_1, value_2, 0)) {
    *result_remainder = value_1;
  } else if (s21_equal_zero_big(value_1) ||
             ((shift_1 < 0) || (shift_2 < 0) || (shift < 0))) {
    quotient.bits[0] = 0;
  } else {
    int sub_or_add = 1;

    for (int i = shift; i > 0; i--) {
      s21_big_shift_left(&divider_shift);
    }

    s21_shift_div(shift, sub_or_add, value_1, divider_shift, &quotient,
                  &remainder);

    if (s21_big_get_bit(remainder, (32 * 6) - 1)) {
      s21_add_big(remainder, divider_shift, &remainder);
    }

    for (int i = shift_1 - shift_2; i > 0; i--) {
      s21_big_shift_right(&remainder);
    }

    *result_quotient = quotient;
    *result_remainder = remainder;
  }
}

int s21_div_overflow_check(s21_decimal value_1, s21_decimal value_2, int *one) {
  int overflow = 0;
  s21_decimal truncated_1, truncated_2;  // Целая часть
  s21_truncate(value_1, &truncated_1);
  s21_truncate(value_2, &truncated_2);

  s21_decimal fractional_1, fractional_2;  // Дробная часть
  s21_sub(value_1, truncated_1, &fractional_1);
  s21_sub(value_2, truncated_2, &fractional_2);

  if ((truncated_2.bits[0] == 1) && (truncated_2.bits[1] == 0) &&
      (truncated_2.bits[2] == 0))
    *one = 1;

  if ((s21_max_decimal(truncated_1) && truncated_2.bits[0] == 0 &&
       truncated_2.bits[1] == 0 && truncated_2.bits[2] == 0))
    overflow = 1;

  return overflow;
}

int s21_fractional_div(work_decimal *result, work_decimal value_2,
                       work_decimal *remainder) {
  int exp = 0;
  while (((remainder->bits[0] != 0) || (remainder->bits[1] != 0) ||
          (remainder->bits[2] != 0)) &&
         (exp < 28)) {
    work_decimal ten_big = {{0xA, 0x0, 0x0, 0x0, 0x0, 0x0}, 0, 0};
    work_decimal temp_digit = {0};
    work_decimal temp_result_big = {0};
    work_decimal temp_remainder = {0};

    s21_mul_big(*result, ten_big, &temp_result_big);
    s21_mul_big(*remainder, ten_big, &temp_remainder);
    s21_div_big(temp_remainder, value_2, &temp_digit, &temp_remainder);
    s21_add_big(temp_result_big, temp_digit, &temp_result_big);

    exp++;
    *remainder = temp_remainder;
    *result = temp_result_big;
  }
  return exp;
}

int s21_div_main(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int error = 0;
  int one = 0;

  if (s21_div_overflow_check(value_1, value_2, &one)) {
    error = 1;
  } else {
    work_decimal value_1_big = s21_init_work_decimal(value_1);
    work_decimal value_2_big = s21_init_work_decimal(value_2);
    work_decimal result_big = {0};
    work_decimal remainder = {0};

    s21_normalized_scales_decimal(&value_1_big, &value_2_big, 0);
    s21_div_big(value_1_big, value_2_big, &result_big,
                &remainder);  // Деление двух чисел
    int exp = s21_fractional_div(&result_big, value_2_big, &remainder);
    int exp_round = 0;
    if (!s21_overflow(result_big)) {
      exp_round = s21_fractional_div(&result_big, value_2_big, &remainder);
    }
    work_decimal whole_result_big = result_big;
    result_big.scale = exp + exp_round;
    int div_scale = 0;
    while ((result_big.scale > 28) ||
           s21_overflow(
               result_big)) {  // Приведение произведения к размеру Decimal
      s21_big_div_ten(&result_big);
      result_big.scale--;
      div_scale++;
    }
    s21_round_work_decimal(div_scale, whole_result_big, &result_big);

    if (s21_overflow(result_big)) {
      error = 1;  // Число переполнено после инкремента
    } else {
      *result = s21_from_work_decimal_to_decimal(result_big, result_big.scale);

      if ((exp + exp_round > 57) ||
          ((result_big.bits[0] == 0) && (result_big.bits[1] == 0) &&
           (result_big.bits[2] == 0) &&
           (result_big.scale > 0))) {  // Проверка на слишком маленькое число
        if (!s21_is_null(value_1)) {
          error = 2;
        }
      }
      if ((whole_result_big.bits[3] != 0) &&
          ((exp + exp_round == 0) ||
           (div_scale > 96))) {  // Проверка на слишком большое число
        error = 1;
      }
    }
  }
  return error;
}