#include <check.h>

#include "brain.h"

START_TEST(test_convert) {
  double *arrDouble = NULL;
  int *arrInt = NULL;
  int count_of_facets = 0;
  int max = 0;
  int min = 0;
  int countVert = 0;
  int res = 0;
  char *filename =
      "ctest.txt";
  res = converter(&arrDouble, &arrInt, &count_of_facets, &min,&max, &countVert,
                  filename);
  ck_assert_int_eq(6, res);
  ck_assert_int_eq(-1, min);
  ck_assert_int_eq(1, max);
  ck_assert_int_eq(8, countVert);
  ck_assert_int_eq(48, count_of_facets);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_convert);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}