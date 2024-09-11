#include "../s21_decimal.h"

/*

Функция s21_mul принимает два значения типа s21_decimal: value_1 и value_2,
умножает их и сохраняет результат в переменную result.

Функции возвращают код ошибки:

0 - OK
1 - число слишком велико или равно бесконечности
2 - число слишком мало или равно отрицательной бесконечности
3 - деление на 0
*/

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  if (s21_is_correct_decimal(value_1) && s21_is_correct_decimal(value_2) &&
      !(result == NULL)) {
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    s21_clear_decimal(result);

    error = s21_mul_main(value_1, value_2, result);

    if (sign_1 != sign_2) {
      if (!s21_equal_zero(value_1) && !s21_equal_zero(value_2)) {
        s21_set_sign(result, 1);
      }
      if (error) {
        error = 2;  // smaller error 2
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int s21_not_one(s21_decimal num) {
  int res = 0;

  if (!(num.bits[0] == 1) && !(num.bits[1] == 0) && !(num.bits[2] == 0) &&
      !(num.bits[3] == 0)) {
    res = 1;
  }
  return res;
}

int s21_mul_main(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int error = 0;

  if (s21_mul_overflow_check(value_1, value_2)) {
    error = 1;
  } else {
    work_decimal value_1_big = s21_init_work_decimal(value_1);
    work_decimal value_2_big = s21_init_work_decimal(value_2);
    work_decimal result_big = {0};

    if ((s21_not_one(value_1)) &&
        (s21_not_one(value_2))) {  // Проверка на умножение на 1
      s21_normalized_scales_decimal(&value_1_big, &value_2_big, 1);
    }
    s21_mul_big(value_1_big, value_2_big, &result_big);  // Умножение двух чисел
    work_decimal whole_result_big = result_big;
    result_big.scale = value_2_big.scale +
                       value_1_big.scale;  // Определение степени произведения
    int div_scale = 0;
    while ((result_big.scale > 28) ||
           s21_overflow(
               result_big)) {  // Приведение произведения к размеру Decimal
      s21_big_div_ten(&result_big);
      result_big.scale--;
      div_scale++;
    }
    s21_round_work_decimal(div_scale, whole_result_big, &result_big);
    if (s21_equal_zero(value_1) || s21_equal_zero(value_2)) {
      result_big.scale = 0;
    }
    if (s21_overflow(result_big)) {
      error = 1;  // Число переполнено после инкремента
    } else {
      *result = s21_from_work_decimal_to_decimal(result_big, result_big.scale);

      if (s21_equal_zero_big(
              result_big)) {  // Проверка на слишком маленькое число
        if (!s21_is_null(value_1) && !s21_is_null(value_2)) {
          error = 2;
        }
      }
    }
  }
  return error;
}

int s21_mul_overflow_check(s21_decimal value_1, s21_decimal value_2) {
  int overflow = 0;
  s21_decimal truncated_1, truncated_2;  // Целая часть
  s21_truncate(value_1, &truncated_1);
  s21_truncate(value_2, &truncated_2);

  s21_decimal fractional_1, fractional_2;  // Дробная часть
  s21_sub(value_1, truncated_1, &fractional_1);
  s21_sub(value_2, truncated_2, &fractional_2);

  work_decimal big_truncated_1 = s21_init_work_decimal(truncated_1);
  work_decimal big_truncated_2 = s21_init_work_decimal(truncated_2);
  work_decimal big_fractional_1 = s21_init_work_decimal(fractional_1);
  work_decimal result_big_truncated = {0};

  s21_mul_big(big_truncated_1, big_truncated_2,
              &result_big_truncated);  // Умножение целых частей чисел

  s21_add_big(result_big_truncated, big_fractional_1,
              &result_big_truncated);  // Сложение результата умножения двух
                                       // целых с дробной частью первого числа

  if ((s21_max_decimal(truncated_1) && truncated_2.bits[0] &&
       fractional_2.bits[0]) ||
      s21_overflow(result_big_truncated))
    overflow = 1;

  return overflow;
}

// Умножение work_decimal чисел
void s21_mul_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result) {
  work_decimal temp_value = {0};
  work_decimal temp_result = {0};
  unsigned int result_bit = 0;
  for (int i = 0; i < (32 * 6); i++) {
    temp_value = value_1;
    result_bit = s21_big_get_bit(value_2, i);
    if (result_bit == 1) {
      for (int j = i; j > 0; j--) {
        s21_big_shift_left(&temp_value);
      }
      s21_add_big(temp_result, temp_value, &temp_result);
    }
  }
  *result = temp_result;
}