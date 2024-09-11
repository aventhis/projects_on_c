#include "../s21_decimal.h"

/*

Функция для преобразования целого числа в десятичное представление с
фиксированной точкой src - исходное целое число dst - указатель на структуру,
в которую будет записан результат

Возвращаемое значение - код ошибки:

0 - OK
1 - ошибка конвертации
*/

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  if ((dst == NULL) || abs(src) > s21_MAXDEC) {
    error = 1;  // Ошибка: dst == NULL или src вне допустимого диапазона
  } else {
    *dst = (s21_decimal){{0}};
    dst->bits[0] = (src >= 0) ? src : -src;
    s21_set_sign(dst, src < 0);
  }
  return error;  // Успешное завершение, ошибок не было
}