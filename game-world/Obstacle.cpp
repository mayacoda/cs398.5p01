
#include "Obstacle.h"


#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#endif

#include "../graphics/opengl_helpers.h"

void Obstacle::render() {
    glColor3f(0.3, 0.2, 0.5);
    drawCircle(m_boundingRadius, m_pos);
}
