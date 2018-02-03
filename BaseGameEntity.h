
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

public:
	virtual ~BaseGameEntity() {};

    BaseGameEntity(const Vector2D<double> &pos, const Vector2D<double> &scale) : m_pos(pos), m_scale(scale) {}

    virtual void update(double timeElapsed) {};

    virtual void render() {};
};


#endif //DZ04_BASEGAMEENTITY_H
