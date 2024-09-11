#include "../s21_decimal.h"

// запись из обычного децимала в расширенный
work_decimal s21_init_work_decimal(s21_decimal decimal) {
  work_decimal new_decimal = {0};
  new_decimal.bits[0] = decimal.bits[0];
  new_decimal.bits[1] = decimal.bits[1];
  new_decimal.bits[2] = decimal.bits[2];
  new_decimal.bits[3] = 0;
  new_decimal.bits[4] = 0;
  new_decimal.bits[5] = 0;
  new_decimal.scale = s21_get_scale(decimal);
  new_decimal.sign = s21_get_sign(decimal);
  return new_decimal;
}

s21_decimal s21_from_work_decimal_to_decimal(work_decimal decimal,
                                             int correct_scale) {
  s21_decimal new_decimal = {0};
  new_decimal.bits[0] = decimal.bits[0];
  new_decimal.bits[1] = decimal.bits[1];
  new_decimal.bits[2] = decimal.bits[2];
  s21_set_scale(&new_decimal, correct_scale);
  return new_decimal;
}

int s21_get_scale(s21_decimal decimal) {
  int scale = (decimal.bits[3] & SC) >> 16;
  return scale;
}

void s21_set_scale(s21_decimal *result, int exp) {
  int i = 112;
  int k = 0;
  while (i < 119) {
    s21_set_bit(result, i, s21_get_bit_num(exp, k));
    i++;
    k++;
  }
}

int s21_get_bit_num(unsigned int num, int i) {
  int result = (num >> i) & 1;
  return result;
}

int s21_is_correct_decimal(s21_decimal decimal) {
  int res = 1;
  int scale = s21_get_scale(decimal);
  // проверка, что с 24-30 бит в bits3 - 0
  // проверка, что с 0-15 бит в bits3 - 0
  if (ISBITSNULL != (decimal.bits[3] &= INCORRECTDECIMAL)) {
    res = 0;
  }

  if (scale < 0 || scale > 28) {
    res = 0;
  }

  return res;
}

void s21_set_bit(s21_decimal *num, int index, int bit) {
  if (bit == 1)
    num->bits[index / 32] |= (1u << (index % 32));  // установить 1
  else
    num->bits[index / 32] &= ~(1u << (index % 32));  // установить 0
}

int s21_get_bit(s21_decimal num, int i) {
  int result = (num.bits[i / 32] >> (i % 32)) & 1;
  return result;
}

void s21_big_set_bit(work_decimal *num, int index, int bit) {
  if (bit == 1)
    num->bits[index / 32] |= (1u << (index % 32));  // установить 1
  else
    num->bits[index / 32] &= ~(1u << (index % 32));  // установить 0
}

int s21_big_get_bit(work_decimal num, int i) {
  return (num.bits[i / 32] >> (i % 32)) & 1;
}

// 0 это +, 1 это -
int s21_get_sign(s21_decimal decimal) {
  int sign = POSITIVE;                           // 0
  if (decimal.bits[3] & MINUS) sign = NEGATIVE;  // 1
  return sign;
}

void s21_set_sign(s21_decimal *decimal, int sign_to_set) {
  s21_set_bit(decimal, 127, sign_to_set);
}

int s21_is_null(s21_decimal decimal) {
  int is_null = FALSE;
  if ((decimal.bits[0] == 0) && (decimal.bits[1] == 0) &&
      (decimal.bits[2] == 0))
    is_null = TRUE;
  return is_null;
}

int s21_is_mantisa_both_decimal_is_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  if (a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
      a.bits[2] == b.bits[2]) {
    res = TRUE;
  } else {
    res = FALSE;
  }
  return res;
}

int s21_is_mantisa_both_decimal_big_is_equal(work_decimal a, work_decimal b) {
  int res = 0;
  if (a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
      a.bits[2] == b.bits[2] && a.bits[3] == b.bits[3] &&
      a.bits[4] == b.bits[4] && a.bits[5] == b.bits[5]) {
    res = TRUE;
  } else {
    res = FALSE;
  }
  return res;
}

int s21_equal_zero_big(work_decimal value_1) {
  int zero = 1;
  for (int i = 0; i < 6; i++) {
    if (value_1.bits[i] != 0) {
      zero = 0;
    }
  }
  return zero;
}

int s21_equal_zero(s21_decimal value_1) {
  int zero = 1;
  for (int i = 0; i < 3; i++) {
    if (value_1.bits[i] != 0) {
      zero = 0;
    }
  }
  return zero;
}

int s21_is_mantisa_less(s21_decimal a, s21_decimal b, int sign) {
  int res = 0;
  int flag = 0;

  if (sign == NEGATIVE) {
    for (int i = 2; i >= 0 && !flag; i--) {
      if (a.bits[i] == b.bits[i]) {
        continue;
      } else if (a.bits[i] < b.bits[i]) {
        res = FALSE;
        flag = 1;
      } else {
        res = TRUE;
        flag = 1;
      }
    }
  } else if (sign == POSITIVE) {
    for (int i = 2; i >= 0 && !flag; i--) {
      if (a.bits[i] == b.bits[i]) {
        continue;
      } else if (a.bits[i] > b.bits[i]) {
        res = FALSE;
        flag = 1;
      } else {
        res = TRUE;
        flag = 1;
      }
    }
  }

  return res;
}

int s21_big_is_mantisa_less(work_decimal a, work_decimal b, int sign) {
  int res = 0;
  int flag = 0;

  if (sign == NEGATIVE) {
    for (int i = 5; i >= 0 && !flag; i--) {
      if (a.bits[i] == b.bits[i]) {
        continue;
      } else if (a.bits[i] < b.bits[i]) {
        res = FALSE;
        flag = 1;
      } else {
        res = TRUE;
        flag = 1;
      }
    }
  } else if (sign == POSITIVE) {
    for (int i = 5; i >= 0 && !flag; i--) {
      if (a.bits[i] == b.bits[i]) {
        continue;
      } else if (a.bits[i] > b.bits[i]) {
        res = FALSE;
        flag = 1;
      } else {
        res = TRUE;
        flag = 1;
      }
    }
  }

  return res;
}

void s21_normalized_scales_decimal(work_decimal *a, work_decimal *b,
                                   int overflow) {
  int scale_diff = (int)a->scale - (int)b->scale;
  work_decimal *rescalable = scale_diff > 0 ? b : a;
  s21_increase_scale_with_check(rescalable, abs(scale_diff), overflow);
}

void s21_increase_scale(work_decimal *c, int diff) {
  c->scale += diff;
  while (diff > 0) {
    uint64_t carry = 0;
    for (int i = 0; i < 6; i++) {
      uint64_t sum = c->bits[i] * 10 + carry;
      c->bits[i] = sum & MAX4BITE;
      carry = sum >> 32;
    }
    diff--;
  }
}

void s21_increase_scale_with_check(work_decimal *c, int diff,
                                   int check_overflow) {
  c->scale += diff;
  int local_diff = diff;

  while (diff > 0) {
    uint64_t carry = 0;
    for (int i = 0; i < 6; i++) {
      uint64_t sum = c->bits[i] * 10 + carry;
      c->bits[i] = sum & MAX4BITE;
      carry = sum >> 32;
    }
    diff--;
    local_diff--;

    if (check_overflow && s21_overflow(*c)) {
      diff = 0;
      s21_big_div_ten(c);
      local_diff++;
    }
  }
  if (check_overflow) c->scale -= local_diff;
}

s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

  return result;
}

void s21_clear_decimal(s21_decimal *result) { *result = (s21_decimal){{0}}; }

/* Функция s21_shift_left сдвигает число типа s21_decimal на один бит влево
и возвращает флаг переполнения. */

int s21_big_shift_left(work_decimal *number) {
  int is_overflow = s21_big_get_bit(*number, (32 * 6) - 1);
  for (int i = (32 * 6) - 1; i >= 0; i--) {
    if (i != 0) {
      s21_big_set_bit(number, i, s21_big_get_bit(*number, i - 1));
    } else {
      s21_big_set_bit(number, i, 0);
    }
  }
  return is_overflow;
}

int s21_overflow(work_decimal c) { return c.bits[3] || c.bits[4] || c.bits[5]; }

int s21_is_even(s21_decimal num) {
  int res = 0;

  if ((num.bits[0] & 1) == 0) res = 1;

  return res;
}

int s21_big_shift_right(work_decimal *number) {
  int is_overflow = s21_big_get_bit(*number, (32 * 6) - 1);
  for (int i = 0; i <= (32 * 6) - 1; i++) {
    if (i != (32 * 6) - 1) {
      s21_big_set_bit(number, i, s21_big_get_bit(*number, i + 1));
    } else {
      s21_big_set_bit(number, i, 0);
    }
  }
  return is_overflow;
}

int s21_div_ten(s21_decimal *value) {
  int error = 0;
  unsigned long long residue = 0;  // остаток от деления
  unsigned long long x = 0;
  for (int i = 2; i >= 0; --i) {
    x = value->bits[i];
    x += (residue << 32);  // сдвигаем остаток на 64 бита
    residue = x % 10;
    x /= 10;
    value->bits[i] = x;
  }

  return error;
}

int s21_big_div_ten(work_decimal *value) {
  int error = 0;
  unsigned long long residue = 0;  // остаток от деления
  unsigned long long x = 0;
  for (int i = 5; i >= 0; --i) {
    x = value->bits[i];
    x += (residue << 32);  // сдвигаем остаток на 64 бита
    residue = x % 10;
    x /= 10;
    value->bits[i] = x;
  }
  return error;
}

int s21_max_decimal(s21_decimal c) {
  int overflow = 0;
  if (c.bits[0] == MAX4BITE && c.bits[1] == MAX4BITE && c.bits[2] == MAX4BITE) {
    overflow = 1;
  }
  return overflow;
}

void s21_check_even_or_odd(int *inc, int div_scale, work_decimal value_1) {
  if (*inc == 2) {
    work_decimal truncated_big = value_1;

    for (int i = div_scale + 1; i > 0;
         i--) {  // Получение целой части на 1 десяток меньше
      s21_big_div_ten(&truncated_big);
    }

    s21_increase_scale(&truncated_big, div_scale + 1);
    s21_sub_big(value_1, truncated_big, &truncated_big);
    truncated_big.bits[5] = 0;

    for (int i = div_scale; i > 0; i--) {  // Получение целой части
      s21_big_div_ten(&truncated_big);
    }

    if ((truncated_big.bits[0] % 2) == 1) {
      *inc = 1;
    }
  }
}

void s21_invert(work_decimal *value_1) {
  value_1->bits[0] = ~value_1->bits[0];
  value_1->bits[1] = ~value_1->bits[1];
  value_1->bits[2] = ~value_1->bits[2];
  value_1->bits[3] = ~value_1->bits[3];
  value_1->bits[4] = ~value_1->bits[4];
  value_1->bits[5] = ~value_1->bits[5];
}

int s21_get_significant_bit(work_decimal value_1) {
  int significant_bit_index = 0;
  for (int i = (32 * 6) - 1; i >= 0; i--) {
    if (s21_big_get_bit(value_1, i)) {
      significant_bit_index = i;
      i = -1;
    }
  }
  return significant_bit_index;
}