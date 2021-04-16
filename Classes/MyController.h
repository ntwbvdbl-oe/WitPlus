/**
 * @author  zju3180101729
 */

#ifndef MYPROJECT_MYCONTROLLER_H
#define MYPROJECT_MYCONTROLLER_H

#include "cocos2d.h"
#include "GameBoard.h"

#include <vector>

#define LEVELS_PER_WORLD 16
#define WORLDS_NUM 2

class MyController : public cocos2d::Ref {
private:
    int currentLevel = 0;
    int currentWorld = 0;
    bool isWorldEnable[WORLDS_NUM];
    bool isLevelEnable[WORLDS_NUM][LEVELS_PER_WORLD];

    GameBoard game;
    std::vector <Pos> path;

public:
    CREATE_FUNC(MyController);

    MyController();

    ~MyController();

    static MyController *getInstance();

    int getCurrentLevel();

    int getCurrentWorld();

    GameBoard *getGame();

    bool getLevelEnable(int i, int j);

    bool getWorldEnable(int i);

    const std::vector <Pos> &getPath();

    void onTouchBegan(Pos pos);

    void onTouchMoved(Pos pos);

    void onTouchEnded(Pos pos);

    bool init();

    void initGame();

    void load();

    void save();

    void setCurrentLevel(int value);

    void setCurrentWorld(int value);

    void setLevelEnable(int i, int j, bool value);

    void setWorldEnable(int i, bool value);

};

#endif //MYPROJECT_CONTROLLER_H
