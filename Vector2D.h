#ifndef DZ01_VECTOR2D_H
#define DZ01_VECTOR2D_H


#include <cmath>
#include <iosfwd>
#include <ostream>
#include "utils.h"

template<class T>
class Vector2D {
public:
    T x;
    T y;

    Vector2D(T x, T y) {
        this->x = x;
        this->y = y;
    };

    const Vector2D operator+=(const Vector2D &v2) {
        x += v2.x;
        y += v2.y;

        return *this;
    }

    const Vector2D operator-=(const Vector2D &v2) {
        x -= v2.x;
        y -= v2.y;

        return *this;
    }

    const Vector2D operator*=(const T scalar) {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    const Vector2D operator*(const T scalar) {
        T nX = x * scalar;
        T nY = y * scalar;

        return Vector2D<T>(nX, nY);
    }

    const Vector2D operator/=(const T scalar) {
        x /= scalar;
        y /= scalar;

        return *this;
    }

    const Vector2D operator/(const T scalar) {
        T nX = x / scalar;
        T nY = y / scalar;

        return Vector2D<T>(nX, nY);
    }

    bool operator==(const Vector2D &v2) const {
        return (x == v2.x) && (y == v2.y);
    }

    bool operator!=(const Vector2D &v2) const {
        return (x != v2.x) || (y != v2.y);
    }

    double magnitude() const {
        return sqrt((y * y) + (x * x));
    }

    double squareMagnitude() const {
        return (y * y) + (x * x);
    }

    double distance(const Vector2D &v2) const {
        T ySep = v2.y - y;
        T xSep = v2.x - x;

        return sqrt((xSep * xSep) + (ySep * ySep));
    }

    Vector2D normalize() const {
        Vector2D v = *this;
        v /= this->magnitude();
        return v;
    }

    T dotProduct(const Vector2D &v2) const {
        return (x * v2.x) + (y * v2.y);
    }

    double angle(const Vector2D &v2) const {
        return arccosine(this->dotProduct(v2) / (this->magnitude() * v2.magnitude()));
    }

    Vector2D project(const Vector2D &v2) const {
        Vector2D temp = v2.normalize();
        T mag = magnitude();
        double theta = angle(v2);

        temp *= (mag * cosine(theta));
        return temp;
    }

    void truncate(double max) {
        if (magnitude() > max) {
            normalize();
            *this *= max;
        }
    }

    Vector2D ortho() const {
        return Vector2D(-y, x);
    }
};


#endif //DZ01_VECTOR2D_H
