#include "../s21_decimal.h"

/* Округляет Decimal до ближайшего целого числа.
        - 0 - OK
        - 1 - ошибка вычисления
*/

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;

  if (!result || result == NULL) {
    error = 1;
  } else if (!s21_is_correct_decimal(value)) {
    error = 1;
    // *result = s21_decimal_get_inf();
  } else {
    int sign = s21_get_sign(value);

    s21_clear_decimal(result);

    // целая часть
    s21_decimal value_truncated;
    s21_truncate(value, &value_truncated);

    // получаем дробную часть
    s21_decimal fractional_part;
    s21_sub(value, value_truncated, &fractional_part);

    // обнуляем знаки у целой и дробной части
    s21_set_sign(&value_truncated, 0);
    s21_set_sign(&fractional_part, 0);

    // заводим два децимала 0,5 и 1
    s21_decimal zero_five = {{0x5, 0x0, 0x0, 0x10000}};
    s21_decimal one = {{0x1, 0x0, 0x0, 0x00000}};

    // если дробная часть == 0,5
    if (s21_is_equal(fractional_part, zero_five)) {
      // если целая часть четная, то оставляем целую часть
      if (s21_is_even(value_truncated) || s21_is_null(value_truncated)) {
        *result = value_truncated;
      } else {
        // целая часть нечетная, то увеливаем на 1
        s21_add(value_truncated, one, result);
      }
      // если дробная часть > 0.5 то увеличиваем на 1
    } else if (s21_is_greater(fractional_part, zero_five)) {
      s21_add(value_truncated, one, result);
      // если дробная часть < 0.5 то оставляем целую часть
    } else {
      *result = value_truncated;
    }
    s21_set_sign(result, sign);
  }

  return error;
}

void s21_round_work_decimal(int div_scale, work_decimal whole_result_big,
                            work_decimal *result_big) {
  if (div_scale > 0) {  // Округление
    int inc = 0;
    work_decimal whole_part_result_big = whole_result_big;
    work_decimal fraction = {0};

    for (int i = div_scale; i > 0; i--) {  // Получение целой части
      s21_big_div_ten(&whole_part_result_big);
    }
    // Возведение в степень целой части до размера всего числа
    s21_increase_scale_with_check(&whole_part_result_big, div_scale, 0);
    // Вычитание из всего числа целой части для получения дробной части
    s21_sub_big(whole_result_big, whole_part_result_big, &fraction);
    work_decimal whole_fraction = fraction;
    // Нахождение первой цифры дробной части
    for (int i = div_scale - 1; i > 0; i--) {
      s21_big_div_ten(&fraction);
    }
    unsigned int round = fraction.bits[0];  // Перевод первой цифры в u_int
    // Возведение в степень до полного размера дробной части
    s21_increase_scale_with_check(&fraction, div_scale - 1, 0);
    // Нахождение дробной части младших регистров (для проверки 0.5)
    s21_sub_big(whole_fraction, fraction, &whole_fraction);

    if (round > 5) {
      inc = 1;
    } else if ((round < 5) && (round != 0)) {
      inc = 0;
    } else if (round == 5) {
      if (whole_fraction.bits[0] || whole_fraction.bits[1] ||
          whole_fraction.bits[2] || whole_fraction.bits[3] ||
          whole_fraction.bits[4] || whole_fraction.bits[5]) {
        inc = 1;
      } else
        inc = 2;
    }
    s21_check_even_or_odd(&inc, div_scale, whole_result_big);
    if (inc == 1) {  // Инкремент итогового числа на +1
      work_decimal one_big = {{0x1, 0x0, 0x0, 0x0, 0x0, 0x0}, 0, 0};
      s21_add_big(*result_big, one_big, result_big);
    }
  }
}
