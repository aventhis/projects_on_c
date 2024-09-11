
#include "../s21_decimal.h"

/*

Функция s21_add принимает два значения типа s21_decimal: value_1 и value_2,
складывает их и сохраняет результат в переменную result.

Функции возвращают код ошибки:

0 - OK
1 - число слишком велико или равно бесконечности
2 - число слишком мало или равно отрицательной бесконечности
3 - деление на 0
*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (s21_is_correct_decimal(value_1) && s21_is_correct_decimal(value_2) &&
      !(result == NULL)) {
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    s21_clear_decimal(result);

    if (sign_1 == sign_2) {
      error = s21_add_main(value_1, value_2, result);
      if (sign_1) {
        s21_set_sign(result, 1);
        if (error) {
          error = 2;  // smaller errror 2
        }
      }
    } else {  // вычитанием
      if (sign_2) {
        error = s21_sub(value_1, value_2, result);
      } else {
        error = s21_sub(value_2, value_1, result);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_add_main(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int error = 0;

  work_decimal value_1_big = s21_init_work_decimal(value_1);
  work_decimal value_2_big = s21_init_work_decimal(value_2);
  s21_normalized_scales_decimal(&value_1_big, &value_2_big, 0);
  work_decimal result_big = {0};

  if (s21_add_overflow_check(value_1, value_2)) {
    error = 1;
  } else {
    s21_add_big(value_1_big, value_2_big, &result_big);

    work_decimal whole_result_big = result_big;

    result_big.scale = value_1_big.scale;  // Определение степени произведения

    int div_scale = 0;
    while (result_big.scale > 28 ||
           s21_overflow(result_big)) {  // Приведение числа к размеру в 96 бит
      s21_big_div_ten(&result_big);
      result_big.scale--;
      div_scale++;
    }

    s21_round_work_decimal(div_scale, whole_result_big, &result_big);

    if (s21_overflow(result_big)) {
      error = 1;  // отрицательное число переполнено
    } else {
      *result = s21_from_work_decimal_to_decimal(result_big, result_big.scale);
    }
  }
  return error;
}

int s21_add_overflow_check(s21_decimal value_1, s21_decimal value_2) {
  int overflow = 0;
  s21_decimal value_truncated_1, value_truncated_2;
  s21_truncate(value_1, &value_truncated_1);
  s21_truncate(value_2, &value_truncated_2);

  work_decimal value_1_big_truncated = s21_init_work_decimal(value_truncated_1);
  work_decimal value_2_big_truncated = s21_init_work_decimal(value_truncated_2);
  work_decimal result_big_truncated = {0};

  s21_add_big(value_1_big_truncated, value_2_big_truncated,
              &result_big_truncated);

  if (s21_overflow(result_big_truncated)) overflow = 1;

  return overflow;
}

// Сложение work_decimal чисел
void s21_add_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result) {
  unsigned int result_bit = 0;
  unsigned int memory = 0;
  for (int j = 0; j < (32 * 6); j++) {  // Сложение
    result_bit =
        s21_big_get_bit(value_1, j) + s21_big_get_bit(value_2, j) + memory;
    memory = result_bit / 2;
    result_bit %= 2;
    s21_big_set_bit(result, j, result_bit);
  }
}