
#ifndef DZ01_UTILS_H
#define DZ01_UTILS_H

#include <cmath>


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

inline int randomRange(int min, int max) {
    srand(time(NULL));
    int random = rand() % (max + 1) + min;
    return random;
}

template<typename T>
T min(T a, T b) {
    return a > b ? b : a;
}


#endif //DZ01_UTILS_H
