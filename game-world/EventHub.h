
#ifndef DZ04_EVENTLISTENER_H
#define DZ04_EVENTLISTENER_H


#include <map>
#include "BaseGameEntity.h"
#include "Event.h"

class EventHub {
private:
    std::map<int, BaseGameEntity*> entityList;

public:
    void addEntityToList(BaseGameEntity* entity) {
        entityList.insert(std::pair<int, BaseGameEntity*>(entity->getId(), entity));
    }

    void removeEntityFromList(BaseGameEntity* entity) {
        entityList.erase(entity->getId());
    }

    void emit(Event e) {
        if (e.receiver == nullptr) {
            for (auto it = entityList.begin(); it != entityList.end(); ++it) {
                it->second->notify(e);
            }
        } else {
            e.receiver->notify(e);
        }
    }

    void clear() {
        entityList.clear();
    }
};


#endif //DZ04_EVENTLISTENER_H
