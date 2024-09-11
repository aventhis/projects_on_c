#include "s21_decimal_test.h"

void run_tests(fail *fails) {
  Suite *list_cases[] = {
      suite_s21_is_equal(), suite_s21_is_not_equal(), suite_s21_is_less(),
      suite_s21_is_less_or_equal(), suite_s21_is_greater(),
      suite_s21_is_greater_or_equal(),

      //  suite_is_less(), suite_is_less_or_equal(),
      //  suite_is_greater(), suite_is_greater_or_equal(),
      //  suite_is_equal(),
      // suite_is_equal_6000(),
      // 	suite_is_not_equal(),

      //  suite_s21_add(),
      //  suite_s21_sub(),
      //  suite_s21_mul(),
      //  suite_s21_div(),

      suite_s21_add_mini(), suite_s21_sub_mini(), suite_s21_mul_mini(),
      suite_s21_div_mini(),

      // suite_from_decimal_to_int(),
      // suite_from_decimal_to_float(),
      // suite_from_float_to_decimal(),

      suite_from_int_to_decimal(), suite_from_decimal_to_int_mini(),
      suite_from_float_to_decimal_mini(), suite_from_decimal_to_float_mini(),

      // suite_truncate(),
      // suite_floor(),
      // suite_round(),
      // suite_negate(),

      suite_negate_mini(), suite_floor_mini(), suite_round_mini(),
      suite_truncate_mini(),

      NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase, fails);
  }
}

void run_testcase(Suite *testcase, fail *fails) {
  int failed = 0;
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  fails->fails += failed;
  srunner_free(sr);
  // sleep(1);
  if (!failed) {
    printf("========= \033[32mPASSED\033[0m =========\n");
  } else {
    printf("========= \033[31mFAILED: %d\033[0m =========\n", failed);
  }
}

int main(void) {
  fail fails;
  fails.fails = 0;
  run_tests(&fails);
  printf("\n\n");
  if (!fails.fails) {
    printf("============ \033[32mALL PASSED\033[0m ============\n");
  } else {
    printf("============ \033[31mALL FAILED: %d\033[0m ============\n",
           fails.fails);
  }
  return 0;
}