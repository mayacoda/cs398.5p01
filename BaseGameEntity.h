
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
    Vector2D<float> m_pos;

    Vector2D<float> m_scale;

public:
    virtual ~BaseGameEntity() = default;

    BaseGameEntity(const Vector2D<float> &pos, const Vector2D<float> &scale) : m_pos(pos), m_scale(scale) {}

    virtual void update(double timeElapsed) {};

    virtual void render() {};
};


#endif //DZ04_BASEGAMEENTITY_H
