#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif

#include <cmath>
#include "Vector2D.h"

#ifndef DZ04_OPENGL_HELPERS_H
#define DZ04_OPENGL_HELPERS_H

const double DEG2RAD = 3.14159 / 180;

inline void drawCircle(double radius, Vector2D<double> pos) {
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 360; i++) {
        double degInRad = i * DEG2RAD;
        glVertex2d(cos(degInRad) * radius + pos.x, sin(degInRad) * radius + pos.y);
    }

    glEnd();
}

#endif //DZ04_OPENGL_HELPERS_H
