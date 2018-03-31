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

inline double distanceToLineSegment(Vector2D<double> a,
                                    Vector2D<double> b,
                                    Vector2D<double> point) {

    const double l2 = a.squareDistanceTo(b);

    // a and b are the same, return distance from point to point
    if (l2 == 0.0) {return point.distanceTo(a);}

    const double t = max(0., min(1., (point - a).dotProduct(b-a))/l2);

    Vector2D<double> d = (b - a);
    const Vector2D<double> projection = a + d * t;

    return point.distanceTo(projection);


//    //if the angle is obtuse between PA and AB is obtuse then the closest
//    //vertex must be A
//    const double dotA = (point.x - segA.x) * (segB.x - segA.x) + (point.y - segA.y) * (segB.y - segA.y);
//
//    if (dotA <= 0) return segA.distanceTo(point);
//
//    //if the angle is obtuse between PB and AB is obtuse then the closest
//    //vertex must be B
//    const double dotB = (point.x - segB.x) * (segA.x - segB.x) + (point.y - segB.y) * (segA.y - segB.y);
//
//    if (dotB <= 0) return segB.distanceTo(point);
//
//    //calculate the point along AB that is the closest to p
//    Vector2D<double> d = segB - segA;
//
//    Vector2D<double> Point = segA + (d * dotA / (dotA + dotB));
//
//    //calculate the distance p-Point
//    return point.distanceTo(Point);
}

#endif //DZ04_GEOMETRY_H
