
#ifndef DZ04_BASEGAMEENTITY_H
#define DZ04_BASEGAMEENTITY_H


#include "Vector2D.h"

class BaseGameEntity {
public:
    enum {
        defaultEntityType = -1
    };

private:
    int m_id;
    int m_entityType;

    int nextValidID() {
        static int nextId = 0;
        return nextId++;
    }

protected:
    Vector2D<double> m_pos;

    Vector2D<double> m_scale;

    double m_boundingRadius;

public:
    BaseGameEntity(int entity_type, const Vector2D<double> &pos, double r) : m_entityType(defaultEntityType),
                                                                             m_boundingRadius(r),
                                                                             m_id(nextValidID()),
                                                                             m_pos(pos),
                                                                             m_scale(Vector2D<double>(1.0, 1.0)) {}

    virtual void update(double timeElapsed) {};

    Vector2D<double> getPos() const { return m_pos; }

    double getBoundingRadius() const { return m_boundingRadius; }

    virtual void render() const {};
};


#endif //DZ04_BASEGAMEENTITY_H
