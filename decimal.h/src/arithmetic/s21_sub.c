#include "../s21_decimal.h"

/*

Функция s21_sub принимает два значения типа s21_decimal: value_1 и value_2,
вычитает их и сохраняет результат в переменную result.

Функции возвращают код ошибки:

0 - OK
1 - число слишком велико или равно бесконечности
2 - число слишком мало или равно отрицательной бесконечности
3 - деление на 0
*/

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  // Проверка на корректность значений и наличие результата
  if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2) ||
      result == NULL) {
    error = 1;
  } else {
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    s21_clear_decimal(result);

    if (sign_1 != sign_2) {  // Сложение, если знаки чисел разные
      error = s21_add_main(value_1, value_2, result);
      if (error && sign_1) {
        error = 2;  // smaller errror 2
      }
      if (sign_1) {  // Установка знака результата
        s21_set_sign(result, 1);
      }
    } else {  // Вычитание, если знаки чисел одинаковые
      if (s21_is_equal(value_1, value_2)) {
        s21_clear_decimal(result);
        s21_set_sign(result, 1);
        s21_set_scale(result, s21_get_scale(value_1));
      } else if (s21_is_greater(value_1, value_2)) {
        error = s21_sub_main(value_1, value_2, result);
        if (sign_1 && sign_2) {
          s21_set_sign(result, 1);
        }
      } else {
        error = s21_sub_main(value_2, value_1, result);
        if ((s21_is_null(value_1) || s21_is_null(value_2)) && sign_1 &&
            sign_2) {
          s21_set_sign(result, 0);
        } else if (!sign_1) {
          s21_set_sign(result, 1);
        } else {
          s21_set_sign(result, 0);
        }
      }
    }
  }
  return error;
}

int s21_sub_main(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int error = 0;
  work_decimal value_1_big = s21_init_work_decimal(value_1);
  work_decimal value_2_big = s21_init_work_decimal(value_2);

  int min_scale = 0;
  if (value_1_big.scale > value_2_big.scale) {
    min_scale = value_1_big.scale;
  } else {
    min_scale = value_2_big.scale;
  }

  s21_normalized_scales_decimal(&value_1_big, &value_2_big, 0);
  work_decimal result_big = {0};

  s21_sub_big(value_1_big, value_2_big, &result_big);

  work_decimal whole_result_big = result_big;

  result_big.scale = min_scale;  // Определение степени произведения

  int div_scale = 0;
  while (result_big.scale > 28 ||
         s21_overflow(result_big)) {  // Приведение числа к размеру в 96 бит
    s21_big_div_ten(&result_big);
    result_big.scale--;
    div_scale++;
  }

  s21_round_work_decimal(div_scale, whole_result_big, &result_big);

  *result = s21_from_work_decimal_to_decimal(result_big, result_big.scale);

  return error;
}

// Вычитание work_decimal чисел
void s21_sub_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result) {
  unsigned int memory = 0;
  int result_bit = 0;
  for (int i = 0; i < (32 * 6); i++) {  // вычитание из итогового числа целой
                                        // части для получения дробной части
    result_bit = 0;
    if (memory) {
      result_bit =
          (memory - s21_big_get_bit(value_1, i)) - s21_big_get_bit(value_2, i);
      if (s21_big_get_bit(value_1, i) && !s21_big_get_bit(value_2, i))
        memory = 0;
    } else {
      result_bit = s21_big_get_bit(value_1, i) - s21_big_get_bit(value_2, i);
      if (!s21_big_get_bit(value_1, i) && s21_big_get_bit(value_2, i))
        memory = 1;
    }
    s21_big_set_bit(result, i, abs(result_bit));
  }
}