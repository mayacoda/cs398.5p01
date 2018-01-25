#ifndef DZ01_VECTOR3D_H
#define DZ01_VECTOR3D_H

#include <cmath>
#include <ostream>
#include "utils.h"

template<class T>
class Vector3D {
public:
    T x;
    T y;
    T z;

    Vector3D<T>(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    const Vector3D operator+=(const Vector3D &v2) {
        x += v2.x;
        y += v2.y;
        z += v2.z;


        return *this;
    }

    const Vector3D operator-=(const Vector3D &v2) {
        x -= v2.x;
        y -= v2.y;
        z -= v2.z;

        return *this;
    }

    const Vector3D operator*=(const T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    const Vector3D operator*(const T scalar) {
        T nX = x * scalar;
        T nY = y * scalar;
        T nZ = z * scalar;

        return Vector3D<T> (nX, nY, nZ);
    }

    const Vector3D operator/=(const T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }

    const Vector3D operator/(const T scalar) {
        T nX = x / scalar;
        T nY = y / scalar;
        T nZ = z / scalar;

        return Vector3D<T> (nX, nY, nZ);
    }

    bool operator==(const Vector3D &v2) const {
        return (x == v2.x) && (y == v2.y) && (z == v2.z);
    }

    bool operator!=(const Vector3D &v2) const {
        return (x != v2.x) || (y != v2.y) || (z != v2.z);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3D &d) {
        os  << " x: " << d.x << " y: " << d.y << " z: " << d.z;
        return os;
    }

    double magnitude() const {
        return sqrt((y * y) + (x * x) + (z * z));
    }

    double distance(const Vector3D &v2) const {
        T ySep = v2.y - y;
        T xSep = v2.x - x;
        T zSep = v2.z - z;

        return sqrt((xSep * xSep) + (ySep * ySep) + (zSep * zSep));
    }

    T dotProduct(const Vector3D &v2) const {
        return (x * v2.x) + (y * v2.y) + (z * v2.z);
    }

    double angle(const Vector3D &v2) const {
        return arccosine(this->dotProduct(v2) / (this->magnitude() * v2.magnitude()));
    }

    Vector3D crossProduct(const Vector3D &v2) const {
        T i = (this->y * v2.z - this->z * v2.y);
        T j = (this->z * v2.x - this->x * v2.z);
        T k = (this->x * v2.y - this->y * v2.x);

        return Vector3D(i, j, k);
    }
};


#endif //DZ01_VECTOR3D_H
