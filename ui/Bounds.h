#ifndef DZ04_BOUNDS_H
#define DZ04_BOUNDS_H

template <typename T>
struct Bounds {
    T top, bottom, left, right;

    Bounds() : top(-1), bottom(-1), left(-1), right(-1) {}

    Bounds(T top, T bottom, T left, T right) : top(top), bottom(bottom), left(left), right(right) {}

    bool isInBounds(T x, T y) {
        return x >= left && x <= right && y >= bottom && y <= top;
    }

    bool isInBounds(double x, double y) {
        return x >= left && x <= right && y >= bottom && y <= top;
    }
};

#endif //DZ04_BOUNDS_H
