#include <check.h>
#include "src/main.h"

START_TEST(INTERPRET_FACTORIAL){
    run("tests/factorial", INTERPRETER_TYPE, 0, NULL);
}
END_TEST

Suite *TEST_INTERPRETER(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("INTERPRETER");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, INTERPRET_FACTORIAL);
    suite_add_tcase(s, tc_core);

}
int main(){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = TEST_INTERPRETER();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}