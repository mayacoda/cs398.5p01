#ifndef DZ04_GEOMETRY_H
#define DZ04_GEOMETRY_H


#include "Vector2D.h"
#include "Matrix.h"

inline Vector2D<float> pointToWorldSpace(const Vector2D<float> &point,
                                          const Vector2D<float> &heading,
                                          const Vector2D<float> &side,
                                          const Vector2D<float> &position) {
    //make a copy of the point
    Vector2D<float> transPoint = point;

    Matrix2D mat;

    //rotate
    mat.rotate(heading, side);

    //and translate
    mat.translate(position.x, position.y);

    //now transform the vertices
    mat.transformVector2Ds(transPoint);

    return transPoint;
}

#endif //DZ04_GEOMETRY_H
