/**
 * @author  zju3180101729
 */

#include <stdio.h>
#include <vector>

#include "MyProject.h"

USING_NS_CC;

static MyController *sharedController = nullptr;

MyController::MyController() {}

MyController::~MyController() {
    sharedController = nullptr;
}

MyController *MyController::getInstance() {
    if (!sharedController) {
        sharedController = new(std::nothrow) MyController;
        sharedController->init();
    }
    return sharedController;
}

int MyController::getCurrentLevel() {
    return currentLevel;
}

int MyController::getCurrentWorld() {
    return currentWorld;
}

GameBoard *MyController::getGame() {
    return &game;
}

bool MyController::getLevelEnable(int i, int j) {
    if (i < 0 || i >= WORLDS_NUM || j < 0 || j >= LEVELS_PER_WORLD) return false;
    return isLevelEnable[i][j];
}

bool MyController::getWorldEnable(int i) {
    if (i < 0 || i >= WORLDS_NUM) return false;
    return isWorldEnable[i];
}

const std::vector <Pos> &MyController::getPath() {
    return path;
}

static Pos last(-1, -1);

void MyController::onTouchBegan(Pos pos) {
    path.push_back(pos);
    last = pos;
}

void MyController::onTouchMoved(Pos pos) {
    Pos back = *--path.end();
    if (pos != Pos(0, -1) && (pos.x % 2 || pos.y % 2))
        pos = Pos(-1, -1);
    if (last != pos && pos != Pos(-1, -1)) {
        if (pos == back) {
            if (pos != game.start) {
                if (pos != Pos(0, -1))
                    path.pop_back();
                path.pop_back();
            }
        } else if (game.check(back, pos)) {
            bool inPath = false;
            for (auto i : path)
                if (pos == i) {
                    inPath = true;
                    break;
                }
            if (!inPath) {
                if (pos != Pos(0, -1))
                    path.push_back(game.getMedium(back, pos));
                path.push_back(pos);
            }
        }
    }
    last = pos;
}

void MyController::onTouchEnded(Pos pos) {
    if (*--path.end() != Pos(0, -1)) {
        path.clear();
    } else if (game.check(path)) {
        setLevelEnable(currentWorld, currentLevel + 1, true);
    } else
        path.clear();
    last = Pos(-1, -1);
}

bool MyController::init() {
    auto userDefault = UserDefault::getInstance();
    if (!userDefault->getBoolForKey("isDataInit", false)) {
        userDefault->setBoolForKey("isDataInit", true);
        for (int i = 0; i < WORLDS_NUM; ++i) {
            isWorldEnable[i] = false;
            for (int j = 0; j < LEVELS_PER_WORLD; ++j) {
                isLevelEnable[i][j] = false;
            }
        }
        isWorldEnable[0] = isLevelEnable[0][0] = true;
        isWorldEnable[1] = isLevelEnable[1][0] = true;
        save();
    } else {
        load();
    }
    return true;
}

void MyController::initGame() {
    game.init(currentWorld, currentLevel);
    path.clear();
}

void MyController::load() {
    char key[100];
    auto userDefault = UserDefault::getInstance();
    for (int i = 0; i < WORLDS_NUM; ++i) {
        sprintf(key, "isWorld%dEnable", i + 1);
        isWorldEnable[i] = userDefault->getBoolForKey(key, false);
        for (int j = 0; j < LEVELS_PER_WORLD; ++j) {
            sprintf(key, "isLevel%d-%02dEnable", i + 1, j + 1);
            isLevelEnable[i][j] = userDefault->getBoolForKey(key, false);
        }
    }
}

void MyController::save() {
    char key[100];
    auto userDefault = UserDefault::getInstance();
    for (int i = 0; i < WORLDS_NUM; ++i) {
        sprintf(key, "isWorld%dEnable", i + 1);
        userDefault->setBoolForKey(key, isWorldEnable[i]);
        for (int j = 0; j < LEVELS_PER_WORLD; ++j) {
            sprintf(key, "isLevel%d-%02dEnable", i + 1, j + 1);
            userDefault->setBoolForKey(key, isLevelEnable[i][j]);
        }
    }
}

void MyController::setCurrentLevel(int value) {
    currentLevel = value;
}

void MyController::setCurrentWorld(int value) {
    currentWorld = value;
}

void MyController::setLevelEnable(int i, int j, bool value) {
    if (i < 0 || i >= WORLDS_NUM || j < 0 || j > LEVELS_PER_WORLD) return;
    if (j < LEVELS_PER_WORLD)
        isLevelEnable[i][j] = value;
    else if (j == LEVELS_PER_WORLD && i + 1 < WORLDS_NUM) {
        isWorldEnable[i + 1] = true;
        isLevelEnable[i + 1][0] = true;
    }
    save();
}

void MyController::setWorldEnable(int i, bool value) {
    if (i < 0 || i >= WORLDS_NUM) return;
    isWorldEnable[i] = value;
    save();
}

