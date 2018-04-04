
#ifndef DZ04_GAMEWORLD_H
#define DZ04_GAMEWORLD_H


#include "../character/Character.h"
#include "Obstacle.h"
#include "../map/Map.h"
#include "../character/attack/Attack.h"
#include <vector>

class Wall2D;

class GameWorld {

public:
    enum characterClass {
        sneakClass,
        thugClass,
        runnerClass
    };

    struct Boundaries {
        Boundaries(int left, int right, int bottom, int top) : left(left), right(right), bottom(bottom), top(top) {}

        Boundaries() : left(0), right(0), bottom(0), top(0) {}

        int top, bottom, left, right;
    };

private:

    Vector2D<double> randomTraversableLocation() const;

    Vector2D<double> windowPointToWorldSpace(int x, int y) const;

    Character* characterAtWindowPoint(int x, int y) const;

    std::vector<Character*> m_characters;
    std::vector<Obstacle*>  m_obstacles;
    std::vector<Attack*>    m_projectiles;

    int m_width;
    int m_height;

    Boundaries m_Boundaries;

    Character* m_player;

    Character* m_enemy;

    Map* m_map;

    void (* endGame)(bool won);

public:
    GameWorld(int m_width, int m_height);

    ~GameWorld() {
        delete m_player;
        delete m_map;
    }

    void update(double timeElapsed);

    void render();

    void setDimensions(int width, int height);

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    std::vector<Character*> getCharacters() const { return m_characters; }

    std::vector<Obstacle*> getObstacles() const { return m_obstacles; }

    MapNode* getNodeByPosition(Vector2D<double> pos) const {
        return m_map->getNodeByPosition(pos);
    }

    void clickHandler(int button, int state, int x, int y);

    void keyboardHandler(unsigned char i, int i1, int i2);

    void passiveMouseMotionHandler(int x, int y);

    void setEndGameCallback(void (* cb)(bool won)) {
        endGame = cb;
    }

    void callEndGameCallback(bool won) {
        endGame(won);
    }

    void setClippingBoundaries(int left, int right, int bottom, int top);

    Boundaries getClippingBoundaries() const { return m_Boundaries; }

    Vector2D<double> getPlayerPos() const {
        if (m_player == nullptr) return Vector2D<double>(0, 0);

        return m_player->getPos();
    }

    int getPlayerHealth() const {
        if (m_player == nullptr) return -1;

        return m_player->getHealth();
    }

    Character* getPlayer() const {
        return m_player;
    }

    Character* getEnemy() const {
        return m_enemy;
    }

    void selectCharacter(characterClass aClass);

    void addProjectile(Attack* p) {
        m_projectiles.push_back(p);
    }

    Graph* getGraph() const {
        return m_map->getGraph();
    }
};


#endif //DZ04_GAMEWORLD_H
