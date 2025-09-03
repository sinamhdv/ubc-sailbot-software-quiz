#include "stdbool.h"
#include "standard_calc.h"
#include <math.h>

/**
 * @brief Bounds the provided angle between [-180, 180) degrees.
 *
 * e.g.)
 *      bound_to_180(135) = 135.0
 *      bound_to_180(200) = -160.0
 *
 * @param angle: The input angle in degrees.
 *
 * @return float: The bounded angle in degrees.
 */
float bound_to_180(float angle) {
    float mod = fmodf(angle, 360.0f);
	if (mod < 0) mod += 360.0f;
	return mod < 180.0f ? mod : mod - 360.0f;
}

/**
 * @brief Determines whether an angle is between two other angles
 *
 *  e.g.)
 *      is_angle_between(0, 45, 90) = true
 *      is_angle_between(45, 90, 270) = false
 * 
 * @param first_angle:  The first bounding angle in degrees.
 * @param middle_angle: The angle in question in degrees.
 * @param second_angle: The second bounding angle in degrees.
 * @return bool: TRUE when `middle_angle` is not in the reflex angle of `first_angle` and `second_angle`, FALSE otherwise
 */
bool is_angle_between(float first_angle, float middle_angle, float second_angle) {
    first_angle = bound_to_180(first_angle);
    middle_angle = bound_to_180(middle_angle);
    second_angle = bound_to_180(second_angle);
	bool is_degrees_between = (first_angle <= middle_angle && middle_angle <= second_angle) \
							  || (second_angle <= middle_angle && middle_angle <= first_angle);
	return fabsf(second_angle - first_angle) < 180.0f ? is_degrees_between : !is_degrees_between;
}
