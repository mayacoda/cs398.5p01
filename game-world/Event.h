#ifndef DZ04_EVENT_H
#define DZ04_EVENT_H


#include <ostream>

class BaseGameEntity;

struct Event {

    enum eventType {
        trapAttach,
        trapExpire,
        attack,
        attackImpacted,
        attackEnded,
        enemyKill
    };

    eventType        type;
    Vector2D<double> pos;
    BaseGameEntity* sender;
    // receiver is null if all entities should be informed of the event
    BaseGameEntity* receiver;
    void          * data;

    Event(eventType type,
          const Vector2D<double> &pos,
          BaseGameEntity* sender,
          BaseGameEntity* receiver,
          void* data) : type(type),
                        pos(pos),
                        sender(sender),
                        receiver(receiver),
                        data(data) {

        m_timestamp = time(nullptr);
    }

    Event() { m_timestamp = time(nullptr); }

    friend std::ostream &operator<<(std::ostream &os, const Event &event) {
        os.precision(17);
        os << "[" << event.type << "] at " << event.pos << " (" << event.m_timestamp << ")";
        return os;
    }

private:
    double m_timestamp;
};

#endif //DZ04_EVENT_H
