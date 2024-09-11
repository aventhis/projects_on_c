#include "../s21_decimal.h"

/* Возвращает целые цифры указанного Decimal числа;
любые дробные цифры отбрасываются, включая конечные нули.
        - 0 - OK
        - 1 - ошибка вычисления
*/

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;

  if (!result) {
    // Если указатель на decimal является NULL
    error = 1;
  } else if (!s21_is_correct_decimal(value)) {
    // Проверяем, что value является корректными decimal
    error = 1;
    *result = s21_decimal_get_inf();
  } else {
    // В остальных случаях производим расчет
    *result = (s21_decimal){{0}};
    int scale = s21_get_scale(value);
    s21_decimal tmp = value;

    while (scale) {
      s21_div_ten(&tmp);
      scale--;
    }
    s21_set_scale(&tmp, 0);

    *result = tmp;
    if (s21_get_sign(value) == NEGATIVE) {
      s21_set_sign(result, NEGATIVE);
    }
  }

  return error;
}
