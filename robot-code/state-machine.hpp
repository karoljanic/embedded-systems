#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#define SQUARE_STATES         2
#define SQUARE_STATE_1        1   // go forward x cm
#define SQUARE_STATE_2        2   // rotate right 90 deg

#define TRIANGLE_STATES       2
#define TRIANGLE_STATE_1      3   // go forward x cm
#define TRIANGLE_STATE_2      4   // rotate right 120 deg

#define AUTO_STATES           17
#define AUTO_STATE_1          5   // go forward until obstacle is further than 20 cm else go to AUTO_STATE_2
#define AUTO_STATE_2          6   // stop, check distance to left and right obstacle, if left distance > 50 go to AUTO_STATE_3, if right distance > 50 go to AUTO_STATE_4, else go to AUTO_STATE_5
#define AUTO_STATE_3          7   // rotate left 90 deg, look right, go to AUTO_STATE_6
#define AUTO_STATE_4          8   // rotate right 90 deg, look left, go to AUTO_STATE_7
#define AUTO_STATE_5          9   // rotate right 180 deg, go to AUTO_STATE_1
#define AUTO_STATE_6          10  // go forward until obstacle is closer than 20 cm, go to AUTO_STATE_8
#define AUTO_STATE_7          11  // go forward until obstacle is closer than 20 cm, go to AUTO_STATE_9
#define AUTO_STATE_8          12  // rotate right 90 deg, go to AUTO_STATE_10
#define AUTO_STATE_9          13  // rotate left 90 deg, go to AUTO_STATE_11
#define AUTO_STATE_10         14  // go forward until obstacle is closer than 20 cm, go to AUTO_STATE_12
#define AUTO_STATE_11         15  // go forward until obstacle is closer than 20 cm, go to AUTO_STATE_13
#define AUTO_STATE_12         16  // rotate right 90 deg, go to AUTO_STATE_14
#define AUTO_STATE_13         17  // rotate left 90 deg, go to AUTO_STATE_15
#define AUTO_STATE_14         18  // go forward p cm, go to AUTO_STATE_16
#define AUTO_STATE_15         19  // go forward p cm, go to AUTO_STATE_17
#define AUTO_STATE_16         20  // rotate left 90 deg, go to AUTO_STATE_1
#define AUTO_STATE_17         21  // rotate right 90 deg, go to AUTO_STATE_1

#endif // STATE_MACHINE_HPP