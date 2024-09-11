#include "../s21_decimal.h"

/* Возвращает результат умножения указанного Decimal на -1.
        - 0 - OK
        - 1 - ошибка вычисления
*/

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;

  if (result == NULL || !s21_is_correct_decimal(value)) {
    error = 1;
  } else {
    memset(result, 0, sizeof(s21_decimal));
    // 2. взять знак у value
    int sign = s21_get_sign(value);
    // 3. записать value в result
    *result = value;
    // 4. если знак -, то поменять знак +
    // if (sign == NEGATIVE) {
    if (sign) {
      s21_set_bit(result, 127, 0);
      // 5. если знак +, то поменять знак на -
    } else {
      s21_set_bit(result, 127, 1);
    }
  }
  return error;
}