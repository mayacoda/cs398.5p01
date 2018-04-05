#ifndef DZ01_VECTOR2D_H
#define DZ01_VECTOR2D_H


#include <cmath>
#include <iosfwd>
#include <ostream>
#include "../helpers/utils.h"

template<class T>
class Vector2D {
public:
    T x;
    T y;

    Vector2D(T x, T y) : x(x), y(y) {}

	Vector2D() : x(0), y(0) {}

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

    const Vector2D operator-(const Vector2D &v2) const {
        T nX = x - v2.x;
        T nY = y - v2.y;

        return Vector2D<T>(nX, nY);
    }

    const Vector2D operator+(const Vector2D &v2) const {
        T nX = x + v2.x;
        T nY = y + v2.y;

        return Vector2D<T>(nX, nY);
    }

    const Vector2D operator*=(const T scalar) {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    const Vector2D operator*(const T scalar) const {
        T nX = x * scalar;
        T nY = y * scalar;

        return Vector2D<T>(nX, nY);
    }

    const Vector2D operator/=(const T scalar) {
        x /= scalar;
        y /= scalar;

        return *this;
    }

    const Vector2D operator/(const T scalar) const {
        T nX = x / scalar;
        T nY = y / scalar;

        return Vector2D<T>(nX, nY);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2D &d) {
        os << "<" << d.x << ", " << d.y << ">";
        return os;
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

    double distanceTo(const Vector2D &v2) const {
        T ySep = v2.y - y;
        T xSep = v2.x - x;

        return sqrt((xSep * xSep) + (ySep * ySep));
    }

    double squareDistanceTo(const Vector2D &v2) const {
        T ySep = v2.y - y;
        T xSep = v2.x - x;

        return (xSep * xSep) + (ySep * ySep);
    }

    Vector2D getNormalized() const {
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

    Vector2D getProjection(const Vector2D &v2) const {
        Vector2D temp = v2.getNormalized();
        T mag = magnitude();
        double theta = angle(v2);

        temp *= (mag * cosine(theta));
        return temp;
    }

    void truncate(double max) {
        if (magnitude() > max) {
            Vector2D<T> norm = getNormalized();
            x = norm.x;
            y = norm.y;
            *this *= max;
        }
    }

    void zero() {
        x = 0;
        y = 0;
    }

    Vector2D getOrtho() const {
        return Vector2D(-y, x);
    }

    //treats a window as a toroid
    void wrapAround(int MaxX, int MaxY) {
        if (x > MaxX) { x = 0.0; }

        if (x < 0) { x = (double) MaxX; }

        if (y < 0) { y = (double) MaxY; }

        if (y > MaxY) { y = 0.0; }
    }
};


#endif //DZ01_VECTOR2D_H
