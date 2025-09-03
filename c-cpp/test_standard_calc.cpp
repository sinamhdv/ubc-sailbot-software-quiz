#include "stdio.h"
#include "cutest/CuTest.h"
#include "standard_calc.h"

#define EPS 1e-4

/**************** Tests for bound_to_180() *******************/
void test_bound_positive(CuTest *tc) {
	CuAssertDblEquals(tc, 0, bound_to_180(0), EPS);
	CuAssertDblEquals(tc, 179, bound_to_180(179), EPS);
	CuAssertDblEquals(tc, -179, bound_to_180(181), EPS);
	CuAssertDblEquals(tc, 90, bound_to_180(90), EPS);
	CuAssertDblEquals(tc, -90, bound_to_180(270), EPS);
	CuAssertDblEquals(tc, 0, bound_to_180(360), EPS);
	CuAssertDblEquals(tc, -179, bound_to_180(541), EPS);
	CuAssertDblEquals(tc, 179, bound_to_180(539), EPS);
	CuAssertDblEquals(tc, 90, bound_to_180(450), EPS);
	CuAssertDblEquals(tc, -90, bound_to_180(630), EPS);
    CuAssertDblEquals(tc, -160, bound_to_180(200), EPS);
}

void test_bound_negative(CuTest *tc) {
	CuAssertDblEquals(tc, -179, bound_to_180(-179), EPS);
	CuAssertDblEquals(tc, 179, bound_to_180(-181), EPS);
	CuAssertDblEquals(tc, -90, bound_to_180(-90), EPS);
	CuAssertDblEquals(tc, 90, bound_to_180(-270), EPS);
	CuAssertDblEquals(tc, 0, bound_to_180(-360), EPS);
	CuAssertDblEquals(tc, 179, bound_to_180(-541), EPS);
	CuAssertDblEquals(tc, -179, bound_to_180(-539), EPS);
	CuAssertDblEquals(tc, -90, bound_to_180(-450), EPS);
	CuAssertDblEquals(tc, 90, bound_to_180(-630), EPS);
}

/**************** Tests for is_angle_between() *******************/
void test_between_basic1(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 45, 90));
    CuAssertTrue(tc, is_angle_between(-45, 0, 45));
    CuAssertTrue(tc, is_angle_between(45, 90, 135));
    CuAssertTrue(tc, is_angle_between(135, 180, -135));
    CuAssertTrue(tc, is_angle_between(-135, 270, -45));
    CuAssertTrue(tc, is_angle_between(-135, 270, -90));
    CuAssertTrue(tc, is_angle_between(170, -170, -160));

    CuAssertTrue(tc, !is_angle_between(-45, 540+720, 45));
    CuAssertTrue(tc, !is_angle_between(45, 0-360, 135));
    CuAssertTrue(tc, !is_angle_between(45, 180+360, 135));
    CuAssertTrue(tc, !is_angle_between(135, 270, 180+45));
    CuAssertTrue(tc, !is_angle_between(135, 90, 180+45));
    CuAssertTrue(tc, !is_angle_between(135, 0, 180+45));
    CuAssertTrue(tc, !is_angle_between(-135, 180, -45));
    CuAssertTrue(tc, !is_angle_between(-135, 0, -45));
    CuAssertTrue(tc, !is_angle_between(-135, 90-720, -45));
    CuAssertTrue(tc, !is_angle_between(-135, 271, -90));
    CuAssertTrue(tc, !is_angle_between(45, 90, 270));
}

int main(int argc, char const *argv[]) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_bound_positive);
    SUITE_ADD_TEST(suite, test_bound_negative);
    SUITE_ADD_TEST(suite, test_between_basic1);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return suite->failCount > 0 ? 1 : 0;
}
