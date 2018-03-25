
#ifndef DZ01_UTILS_H
#define DZ01_UTILS_H

#include <cmath>
#include <random>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

// Korišćena aproksimacija Tejlorov polinom https://www.mathportal.org/formulas/pdf/taylor-series-formulas.pdf
template<typename T>
double cosine(T theta) {
    return 1 - ((theta * theta) / 2)
           + ((pow(theta, 4)) / 24)
           - ((pow(theta, 6)) / 720)
           + ((pow(theta, 8)) / 40320)
           - ((pow(theta, 10)) / 3628800);
}

template<typename T>
double arccosine(T x) {
    return M_PI / 2 - x - pow(x, 3) / 6 - 3 * pow(x, 5) / 40 - 5 * pow(x, 7) / 112 - 35 * pow(x, 9) / 1152 -
           63 * pow(x, 11) / 2816 - 231 * pow(x, 13) / 13312 - 143 * pow(x, 15) / 10240 - 6435 * pow(x, 17) / 557056;
}

inline int iRandomRange(int min, int max) {
    int random = rand() % (max + 1) + min;
    return random;
}

inline float fRandomRange(int min, int max) {

	float r3 = min + static_cast <float> (random()) /( static_cast <float> (RAND_MAX/(max-min)));
	return r3;
}

inline double r2d(double rad) {
    return rad * 180 / M_PI;
}

inline double d2r(double deg) {
    return deg * M_PI / 180;
}

template<typename T>
T min(T a, T b) {
    return a > b ? b : a;
}

template<typename T>
T max(T a, T b) {
    return a < b ? b : a;
}


#endif //DZ01_UTILS_H
