#include "../s21_decimal.h"

/* Округляет указанное Decimal число до ближайшего целого числа в сторону
   отрицательной бесконечности.
        - 0 - OK
        - 1 - ошибка вычисления
*/

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (!result) {  //||result==NULL вставить если будет сега
    error = 1;
  } else {
    error = s21_truncate(value, result);
    if (s21_get_sign(*result) && !s21_is_equal(*result, value))
      result->bits[0] += 1;
  }
  return error;
}