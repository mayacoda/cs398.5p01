#ifndef DZ04_GEOMETRY_H
#define DZ04_GEOMETRY_H


#include "Vector2D.h"
#include "Matrix.h"

inline Vector2D<double> vectorToWorldSpace(const Vector2D<double> &vec,
                                           const Vector2D<double> &heading,
                                           const Vector2D<double> &side) {
    Vector2D<double> transVec = vec;

    Matrix2D mat;

    mat.rotate(heading, side);

    mat.transformVector2Ds(transVec);

    return transVec;
}

inline Vector2D<double> pointToWorldSpace(const Vector2D<double> &point,
                                          const Vector2D<double> &heading,
                                          const Vector2D<double> &side,
                                          const Vector2D<double> &position) {
    //make a copy of the point
    Vector2D<double> transPoint = point;

    Matrix2D mat;

    //rotate
    mat.rotate(heading, side);

    //and translate
    mat.translate(position.x, position.y);

    //now transform the vertices
    mat.transformVector2Ds(transPoint);

    return transPoint;
}

inline Vector2D<double> pointToLocalSpace(const Vector2D<double> &point,
                                          const Vector2D<double> &heading,
                                          const Vector2D<double> &side,
                                          const Vector2D<double> &position) {

    Vector2D<double> transPoint = point;

    Matrix2D mat;

    double tX = -position.dotProduct(heading);
    double tY = -position.dotProduct(side);

    mat._11(heading.x);
    mat._12(side.x);
    mat._21(heading.y);
    mat._22(side.y);
    mat._31(tX);
    mat._32(tY);

    mat.transformVector2Ds(transPoint);

    return transPoint;
}

inline void rotateAroundOrigin(Vector2D<double> &v, double ang) {
    //create a transformation matrix
    Matrix2D mat;

    //rotate
    mat.rotate(ang);

    //now transform the object's vertices
    mat.transformVector2Ds(v);
}

#endif //DZ04_GEOMETRY_H
