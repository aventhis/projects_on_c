#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// представление decimal числа
//  x0000000 000zzzzzz 00000000 00000000 00000000 00000000 00000000
//  bits 3 - знак и степень              bits2 bits1 bits0 - мантисса

#define s21_MAXDEC pow(2, 96) - 1

#define MINUS 0x80000000  // 10000000 00000000 00000000 00000000 //знак минус
#define SC \
  0x00ff0000  // 00000000 11111111 000000000 00000000 // scale - степень
#define MAX4BITE 0xffffffff  // 11111111 11111111 11111111 11111111
#define INCORRECTDECIMAL 0b01111111000000001111111111111111
#define ISBITSNULL 0x00000000
#define BITS_32_MASK 0b11111111111111111111111111111111

// знак числа
#define POSITIVE 0
#define NEGATIVE 1

// результат для сравнения
#define FALSE 0
#define TRUE 1

typedef struct {
  unsigned int bits[4];
} s21_decimal;

/*                     РАСШИРЕННЫЙ ДЕЦИМАЛ - ДЛЯ БОРЬБЫ С СПЕРЕПОЛНЕНИЕМ */
typedef struct {
  uint64_t bits[6];
  uint16_t scale;
  int sign;
} work_decimal;

typedef union {
  int ui;
  float fl;
} fbits;
/*=========             ARITHMETIC | АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ =========*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_main(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_overflow_check(s21_decimal value_1, s21_decimal value_2);
void s21_add_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub_main(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_sub_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_main(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_overflow_check(s21_decimal value_1, s21_decimal value_2);
void s21_mul_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_shift_div(int shift, int sub_or_add, work_decimal value_1,
                   work_decimal divider_shift, work_decimal *quotient,
                   work_decimal *remainder);
void s21_div_big(work_decimal value_1, work_decimal value_2,
                 work_decimal *result_quotient, work_decimal *result_remainder);
int s21_div_overflow_check(s21_decimal value_1, s21_decimal value_2, int *one);
int s21_fractional_div(work_decimal *result, work_decimal value_2,
                       work_decimal *remainder);
int s21_div_main(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*========               COMPARISON.C | ФУНКЦИИ СРАВНЕНИЯ =========*/

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

/*========              OTHERFUNCTIONS.C | ДРУГИЕ ФУНКЦИИ =========*/

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*=========                CONVERSION | ПРЕОБРАЗОВАТЕЛИ =========*/

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

/*=========               HELPERS | ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ =========*/

work_decimal s21_init_work_decimal(s21_decimal decimal);
s21_decimal s21_from_work_decimal_to_decimal(work_decimal decimal,
                                             int correct_scale);

int s21_is_correct_decimal(s21_decimal decimal);
int s21_is_null(s21_decimal decimal);
int s21_max_decimal(s21_decimal c);
void s21_clear_decimal(s21_decimal *value);
s21_decimal s21_decimal_get_inf(void);

int s21_get_sign(s21_decimal decimal);
void s21_set_sign(s21_decimal *decimal, int sign_to_set);

int s21_get_scale(s21_decimal decimal);
void s21_set_scale(s21_decimal *decimal, int scale);

int s21_get_bit_num(unsigned int num, int i);
int s21_get_bit(s21_decimal num, int i);
int s21_big_get_bit(work_decimal num, int i);

void s21_set_bit(s21_decimal *num, int index, int bit);
void s21_big_set_bit(work_decimal *num, int index, int bit);

void s21_normalized_scales_decimal(work_decimal *a, work_decimal *b,
                                   int overflow);
// void s21_increase_scale(work_decimal *c, int diff);  //увеличить степень
void s21_increase_scale_with_check(work_decimal *c, int diff,
                                   int check_overflow);
void s21_check_even_or_odd(int *inc, int div_scale, work_decimal value_1);

int s21_big_shift_left(work_decimal *number);
int s21_big_shift_right(work_decimal *number);

int s21_overflow(work_decimal c);

void s21_round_work_decimal(int div_scale, work_decimal whole_result_big,
                            work_decimal *result_big);
int s21_is_even(s21_decimal num);

int s21_div_ten(s21_decimal *value);
int s21_big_div_ten(work_decimal *value);

int s21_is_mantisa_both_decimal_is_equal(s21_decimal a, s21_decimal b);
int s21_is_mantisa_both_decimal_big_is_equal(work_decimal a, work_decimal b);
int s21_not_one(s21_decimal num);
int s21_equal_zero(s21_decimal value_1);
int s21_equal_zero_big(work_decimal value_1);
int s21_is_mantisa_less(s21_decimal a, s21_decimal b, int sign);
int s21_big_is_mantisa_less(work_decimal a, work_decimal b, int sign);

void adjust_mantissa(double *mantissa_double, int *scale);
void adjust_scale(double *mantissa_double, int *scale_small, int *scale_digit);

void s21_invert(work_decimal *value_1);
int s21_get_significant_bit(work_decimal value_1);

#endif
