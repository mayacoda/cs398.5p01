
#ifndef DZ04_PATH_H
#define DZ04_PATH_H

#include <list>
#include <cassert>
#include "../geometry/Vector2D.h"

class Path {
private:
    std::list<Vector2D<double> > m_points;

    std::list<Vector2D<double> >::iterator m_currentPoint;

    bool m_isLooped;

public:
    Path() : m_isLooped(false) {}

    Path(Vector2D<double> start) : m_isLooped(false) {
        set(std::list<Vector2D<double> >(1, start));
    }

    Path(int numPoints,
         double minX,
         double minY,
         double maxX,
         double maxY,
         bool looped) : m_isLooped(looped) {
        createRandomPath(numPoints, minX, minY, maxX, maxY);

        m_currentPoint = m_points.begin();
    }

    Vector2D<double> getCurrentPoint() const {
        return *m_currentPoint;
    }

    bool finished() {
        return m_currentPoint == m_points.end();
    }

    bool isLastPoint() {
        return *m_currentPoint == m_points.back();
    }

    inline void setNextPoint();

    std::list<Vector2D<double> > createRandomPath(int numPoints, double minX, double minY, double maxX, double maxY);

    void loop(bool toLoop) { m_isLooped = toLoop; }

    void set(const std::list<Vector2D<double> > &newPath) {
        m_points       = newPath;
        m_currentPoint = m_points.begin();
    }

    void clear() {
        m_points.clear();
    }


    void render(float r, float g, float b) const;
};


inline void Path::setNextPoint() {
    assert (!m_points.empty() && "Point list is empty");

    if (++m_currentPoint == m_points.end()) {
        if (m_isLooped) {
            m_currentPoint = m_points.begin();
        }
    }
}

#endif //DZ04_PATH_H
