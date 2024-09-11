// #include "../s21_decimal.h"

// /*
// Функции возвращают код ошибки:

// 0 - OK
// 1 - число слишком велико или равно бесконечности
// 2 - число слишком мало или равно отрицательной бесконечности
// 3 - деление на 0
// */

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int error = 0;

// 	if (s21_is_correct_decimal(value_1) && s21_is_correct_decimal(value_2)
// && !(result == NULL)) { 		int sign_1 = s21_get_sign(value_1);
// int sign_2 = s21_get_sign(value_2); 		s21_set_sign(&value_1, 0);
// s21_set_sign(&value_2, 0); 		s21_clear_decimal(result);

// 		error = s21_div_same_sign(value_1, value_2, result);

// 		if (sign_1 != sign_2) {
// 			s21_set_sign(result, 1);
// 			if (error) {
// 				error = 2;  // smaller error 2
// 			}
// 		}
// 	} else {
// 		error = 1;
// 	}

//   return error;
// }

// int s21_big_shift_right(work_decimal *number) {
//   int is_overflow = s21_big_get_bit(*number, (32 * 6) - 1);
//   for (int i = 0; i <= (32 * 6) - 1; i++) {
//     if (i != (32 * 6) - 1) {
//       s21_big_set_bit(number, i, s21_big_get_bit(*number, i + 1));
//     } else {
//       s21_big_set_bit(number, i, 0);
//     }
//   }
//   return is_overflow;
// }

// // void s21_increase_scale_big(work_decimal *c, int diff) {
// //   c->scale += diff;
// // 	int diff_s = diff;
// // 	while (diff > 0) {
// //     uint64_t carry = 0;
// //     for (int i = 0; i < 6; i++) {
// //       uint64_t sum = c->bits[i] * 10 + carry;
// //       c->bits[i] = sum & MAX4BITE;
// //       carry = sum >> 32;
// //     }
// //     diff--;
// // 		diff_s--;
// // 		if (s21_overflow(*c)) {
// // 			diff = 0;
// // 			s21_big_div_ten(c);
// // 			diff_s++;
// // 		}
// //   }
// // 	c->scale -= diff_s;
// // }

// // void s21_normalized_scales_decimal_big(work_decimal *a, work_decimal *b) {
// //   int scale_a = a->scale;
// //   int scale_b = b->scale;
// //   int scale_dif = scale_a - scale_b;
// //   if (scale_dif < 0) {
// //     s21_increase_scale_big(a, abs(scale_dif));
// //   } else if (scale_dif > 0) {
// //     s21_increase_scale_big(b, abs(scale_dif));
// //   }
// // }

// int s21_div_overflow_check(s21_decimal value_1, s21_decimal value_2) {
// 	int overflow = 0;
//   s21_decimal truncated_1, truncated_2; // Целая часть
//   s21_truncate(value_1, &truncated_1);
//   s21_truncate(value_2, &truncated_2);

//   s21_decimal fractional_1, fractional_2; // Дробная часть
//   s21_sub(value_1, truncated_1, &fractional_1);
//   s21_sub(value_2, truncated_2, &fractional_2);

// 	work_decimal big_truncated_1 = s21_init_work_decimal(truncated_1);
//   work_decimal big_truncated_2 = s21_init_work_decimal(truncated_2);
// 	work_decimal big_fractional_1 = s21_init_work_decimal(fractional_1);
// 	work_decimal result_big_truncated = {0};

// 	s21_mul_big(big_truncated_1, big_truncated_2, &result_big_truncated); //
// Умножение целых частей чисел

// 	s21_add_big(result_big_truncated, big_fractional_1,
// &result_big_truncated); // Сложение результата умножения двух целых с дробной
// частью первого числа

// 	if ((s21_max_decimal(truncated_1) && truncated_2.bits[0] &&
// fractional_2.bits[0]) || s21_overflow(result_big_truncated))
// overflow = 1;

// 	return overflow;
// }

// // Деление work_decimal чисел
// void s21_div_big(work_decimal value_1, work_decimal value_2, work_decimal
// *result) {
//   // work_decimal temp_value = {0};
// 	work_decimal temp_value_1 = value_1;
// 	work_decimal one_big = {{0x1, 0x0, 0x0, 0x0, 0x0, 0x0}, 0, 0};
// 	// unsigned int result_bit = 0;

// 	// for (int i = 0; i < 4; i++) {
// 	// 	printf("temp_value_1: bits[%d]: %lx\n", i,
// temp_value_1.bits[i]);
// 	// }
// 	// printf("==============\n");

// 	while ( !((temp_value_1.bits[0] == 0) && (temp_value_1.bits[1] == 0) &&
// (temp_value_1.bits[2] == 0)) || s21_overflow(*result)) {
// 		s21_sub_big(temp_value_1, value_2, &temp_value_1);
// 		s21_add_big(*result, one_big, result);

// 		for (int i = 0; i < 4; i++) {
// 			printf("result_big: bits[%d]: %lx\n", i,
// result->bits[i]);
// 		}
// 		printf("==============\n");
// 	}

// }

// int s21_div_same_sign(s21_decimal value_1, s21_decimal value_2, s21_decimal
// *result) {
//   int error = 0;

// 	// if (s21_mul_overflow_check(value_1, value_2)) {
// 	// 	error = 1;
// 	// } else {
// 		work_decimal value_1_big = s21_init_work_decimal(value_1);
// 		work_decimal value_2_big = s21_init_work_decimal(value_2);
// 		work_decimal result_big = {0};

// 		// s21_normalized_scales_decimal_big(&value_1_big,
// &value_2_big,1); 		for (int i = 0; i < 4; i++) {
// printf("result_big: bits[%d]: %lx\n", i, value_1_big.bits[i]);
// 		}
// 		printf("==============\n");

// 		for (int i = 0; i < 4; i++) {
// 			printf("result_big: bits[%d]: %lx\n", i,
// value_2_big.bits[i]);
// 		}
// 		printf("==============\n");

// 		s21_div_big(value_1_big, value_2_big, &result_big); // Деление
// двух чисел

// 		for (int i = 0; i < 4; i++) {
// 			printf("result_big: bits[%d]: %lx\n", i,
// result_big.bits[i]);
// 		}
// 		printf("==============\n");

// 		// work_decimal whole_result_big = result_big;

// 		result_big.scale = value_2_big.scale + value_1_big.scale; //
// Определение степени произведения

// 		int div_scale = 0;
// 		while ((result_big.scale > 28) || s21_overflow(result_big)) { //
// Приведение произведения к размеру Decimal
// s21_big_div_ten(&result_big); 			result_big.scale--;
// div_scale++;
// 		}

// 		for (int i = 0; i < 4; i++) {
// 			printf("result_big: bits[%d]: %lx\n", i,
// result_big.bits[i]);
// 		}
// 		printf("==============\n");

// 		// s21_round_work_decimal(div_scale, whole_result_big,
// &result_big);

// 		if (s21_overflow(result_big)) {
// 			error = 1; // Число переполнено после инкремента
// 		} else {
// 			*result = s21_from_work_decimal_to_decimal(result_big,
// result_big.scale);

// 			if ((result_big.bits[0] == 0) && (result_big.bits[1] ==
// 0)
// && (result_big.bits[2] == 0)) { // Проверка на слишком маленькое число
// if
// (!s21_is_null(value_1) && !s21_is_null(value_2)) {
// error = 2;
// 				}
// 			}

// 		}

// 	// }
//   return error;
// }