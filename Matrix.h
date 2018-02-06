#ifndef DZ04_MATRIX_H
#define DZ04_MATRIX_H

#include "Vector2D.h"
#include <cmath>
#include <vector>

class Matrix2D {
private:
    struct Matrix {
        double _11, _12, _13;
        double _21, _22, _23;
        double _31, _32, _33;

        Matrix() {
            _11 = 0.0;
            _12 = 0.0;
            _13 = 0.0;
            _21 = 0.0;
            _22 = 0.0;
            _23 = 0.0;
            _31 = 0.0;
            _32 = 0.0;
            _33 = 0.0;
        }
    };

    Matrix m_matrix;

public:
    Matrix2D() {
        identity();
    }

    inline void identity();

    inline void translate(double x, double y);

    inline void matrixMultiply(Matrix matrix);

    inline void rotate(double rotation);

    inline void rotate(const Vector2D<double> &fwd, const Vector2D<double> &side);

    inline void transformVector2Ds(std::vector<Vector2D<double> > &points);

    inline void transformVector2Ds(Vector2D<double> &point);
};

inline void Matrix2D::identity() {
    m_matrix._11 = 1;
    m_matrix._12 = 0;
    m_matrix._13 = 0;

    m_matrix._21 = 0;
    m_matrix._22 = 1;
    m_matrix._23 = 0;

    m_matrix._31 = 0;
    m_matrix._32 = 0;
    m_matrix._33 = 1;
}

inline void Matrix2D::translate(double x, double y) {
    Matrix mat;

    mat._11 = 1;
    mat._12 = 0;
    mat._13 = 0;

    mat._21 = 0;
    mat._22 = 1;
    mat._23 = 0;

    mat._31 = x;
    mat._32 = y;
    mat._33 = 1;

    //and multiply
    matrixMultiply(mat);
}

inline void Matrix2D::matrixMultiply(Matrix2D::Matrix matrix) {
    Matrix2D::Matrix mat_temp;

    //first row
    mat_temp._11 = (m_matrix._11 * matrix._11) + (m_matrix._12 * matrix._21) + (m_matrix._13 * matrix._31);
    mat_temp._12 = (m_matrix._11 * matrix._12) + (m_matrix._12 * matrix._22) + (m_matrix._13 * matrix._32);
    mat_temp._13 = (m_matrix._11 * matrix._13) + (m_matrix._12 * matrix._23) + (m_matrix._13 * matrix._33);

    //second
    mat_temp._21 = (m_matrix._21 * matrix._11) + (m_matrix._22 * matrix._21) + (m_matrix._23 * matrix._31);
    mat_temp._22 = (m_matrix._21 * matrix._12) + (m_matrix._22 * matrix._22) + (m_matrix._23 * matrix._32);
    mat_temp._23 = (m_matrix._21 * matrix._13) + (m_matrix._22 * matrix._23) + (m_matrix._23 * matrix._33);

    //third
    mat_temp._31 = (m_matrix._31 * matrix._11) + (m_matrix._32 * matrix._21) + (m_matrix._33 * matrix._31);
    mat_temp._32 = (m_matrix._31 * matrix._12) + (m_matrix._32 * matrix._22) + (m_matrix._33 * matrix._32);
    mat_temp._33 = (m_matrix._31 * matrix._13) + (m_matrix._32 * matrix._23) + (m_matrix._33 * matrix._33);

    m_matrix = mat_temp;
}


void Matrix2D::rotate(double rotation) {
    Matrix2D::Matrix mat;

    double sinVal = sin(rotation);
    double cosVal = cos(rotation);

    mat._11 = cosVal;
    mat._12 = sinVal;
    mat._13 = 0;

    mat._21 = -sinVal;
    mat._22 = cosVal;
    mat._23 = 0;

    mat._31 = 0;
    mat._32 = 0;
    mat._33 = 1;

    matrixMultiply(mat);
}


void Matrix2D::rotate(const Vector2D<double> &fwd, const Vector2D<double> &side) {
    Matrix2D::Matrix mat;

    mat._11 = fwd.x;
    mat._12 = fwd.y;
    mat._13 = 0;

    mat._21 = side.x;
    mat._22 = side.y;
    mat._23 = 0;

    mat._31 = 0;
    mat._32 = 0;
    mat._33 = 1;

    //and multiply
    matrixMultiply(mat);

}

void Matrix2D::transformVector2Ds(std::vector<Vector2D<double> > &points) {
    for (unsigned int i = 0; i < points.size(); i++) {
        Vector2D<double> point = points.at(i);

        double tempX = (m_matrix._11 * point.x) + (m_matrix._21 * point.y) + (m_matrix._31);

        double tempY = (m_matrix._12 * point.x) + (m_matrix._22 * point.y) + (m_matrix._32);

        point.x = tempX;

        point.y = tempY;
    }
}

void Matrix2D::transformVector2Ds(Vector2D<double> &point) {

    double tempX = (m_matrix._11 * point.x) + (m_matrix._21 * point.y) + (m_matrix._31);

    double tempY = (m_matrix._12 * point.x) + (m_matrix._22 * point.y) + (m_matrix._32);

    point.x = tempX;

    point.y = tempY;
}

#endif //DZ04_MATRIX_H
