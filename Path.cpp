#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <OpenGL/gl.h>
#include <iostream>

#endif

#include "Path.h"
#include "geometry.h"


std::list<Vector2D<double> > Path::createRandomPath(int numPoints, double minX, double minY, double maxX, double maxY) {

    m_points.clear();

    double midX = (maxX + minX) / 2.0;
    double midY = (maxY + minY) / 2.0;

    double smaller = min(midX, midY);

    // number of radians at which each point should be placed
    double spacing = (2.0 * M_PI) / (double) numPoints;

    for (int i = 0; i < numPoints; i++) {
        double radialDist = iRandomRange(static_cast<int>(floor(smaller * 0.2f)), static_cast<int>(floor(smaller)));

        Vector2D<double> tmp(radialDist, 0.0);
        rotateAroundOrigin(tmp, i * spacing);

        tmp.x += midX;
        tmp.y += midY;

        m_points.push_back(tmp);

    }

    m_currentPoint = m_points.begin();

    return m_points;
}

void Path::render(float r, float g, float b) const {

    glColor3f(r, g, b);
    glBegin(GL_LINES);
	glLineWidth(3.0);

    auto iterator = m_points.begin();

    Vector2D<double> point = *iterator++;

    while (iterator != m_points.end()) {
        glVertex2d(point.x, point.y);
        glVertex2d((*iterator).x, (*iterator).y);

        point = *iterator++;
    }

    if (m_isLooped) {
        Vector2D<double> last = *--iterator;

        glVertex2d(last.x, last.y);
        glVertex2d(m_points.begin()->x, m_points.begin()->y);
    }

    glEnd();
}
