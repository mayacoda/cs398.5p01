#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <GLUT/glut.h>

#endif

#include <cmath>
#include "../geometry/Vector2D.h"
#include "bmp-mac.h"

#ifndef DZ04_OPENGL_HELPERS_H
#define DZ04_OPENGL_HELPERS_H

const double DEG2RAD = 3.14159 / 180;

struct Color {
    float r;
    float g;
    float b;

    Color(float r, float g, float b) : r(r), g(g), b(b) {}

    Color() : r(0), g(0), b(0) {};
};

inline void drawCircle(double radius, Vector2D<double> pos) {
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 360; i++) {
        double degInRad = i * DEG2RAD;
        glVertex2d(cos(degInRad) * radius + pos.x, sin(degInRad) * radius + pos.y);
    }

    glEnd();
}

inline void drawText(const char* text, double x, double y, Color color) {
    const char* c;
    glPushMatrix();
    glTranslated(x, y, 0);
    glColor3f(color.r, color.g, color.b);
    glScalef(0.125, 0.125, 1);
    for (c = text; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}


// @todo make image cache?
inline void drawSpriteWithMask(const char* file, const char* mask, int x, int y) {
    BITMAPINFO* info, * maskInfo;
    unsigned char* pixels, * maskPixels;

    pixels     = ReadBitmap(file, &info);
    maskPixels = ReadBitmap(mask, &maskInfo);

    glEnable(GL_COLOR_LOGIC_OP);

    glLogicOp(GL_AND_INVERTED);
    glRasterPos2i(x, y);
    glDrawPixels(maskInfo->bmiHeader.biWidth, maskInfo->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, maskPixels);

    glLogicOp(GL_OR);
    glDrawPixels(info->bmiHeader.biWidth, info->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glDisable(GL_COLOR_LOGIC_OP);
}

#endif //DZ04_OPENGL_HELPERS_H
