/**
 * @author  zju3180101729
 */

#include <math.h>

#include "MyProject.h"

USING_NS_CC;

void GameBoard::init(int world, int level) {
    auto fileUtils = FileUtils::getInstance();
    Data fileData = fileUtils->getDataFromFile(
            std::string("levels/") + std::to_string(world) + "/" + std::to_string(level));
    int *data = (int *) fileData.getBytes();
    width = data[0], height = data[1];
    mask.resize(2 * width - 1);
    keyNum = 0;
    for (int i = 0; i < 2 * width - 1; ++i) {
        mask[i].resize(2 * height - 1);
        for (int j = 0; j < 2 * height - 1; ++j) {
            mask[i][j] = data[i * (2 * height - 1) + j + 2];
            if (mask[i][j] & MASK_START)
                start = Pos(i, j);
            if (mask[i][j] & MASK_END)
                end = Pos(i, j);
            if (mask[i][j] & MASK_KEY)
                ++keyNum;
        }
    }
    endDir = END_DIR_UP;    //TODO
    /*
    width = height = 2;
    mask.resize(2 * width - 1);
    for (int i = 0; i < 2 * width - 1; ++i) {
        mask[i] = vector<int>(2 * height - 1, MASK_EMPTY);
    }
    mask[0][0] = mask[0][1] = mask[0][2] = mask[1][0] = mask[1][2] = mask[2][0] = mask[2][1] = mask[2][2] = MASK_ROAD;
    start = Pos(0, 0);
    mask[start.x][start.y] = MASK_ROAD | MASK_START;
    end = Pos(2, 2);
    mask[end.x][end.y] = MASK_ROAD | MASK_END;
    endDir = END_DIR_UP;*/
}

bool GameBoard::check(Pos u, Pos v) {
    if (u == end && v == Pos(0, -1))
        return true;
    Pos mid = getMedium(u, v);
    if (mid == Pos(-1, -1))
        return false;
    return (mask[mid.x][mid.y] & MASK_BREAK) == 0;
}

bool GameBoard::check(const std::vector <Pos> &path) {
    int num = 0;
    for (auto i : path)
        if (i != Pos(0, -1) && (mask[i.x][i.y] & MASK_KEY))
            ++num;
    return num == keyNum;
}

Pos GameBoard::getMedium(Pos u, Pos v) {
    if (u.x == v.x && abs(u.y - v.y) == 2)
        return Pos(u.x, (u.y + v.y) / 2);
    if (u.y == v.y && abs(u.x - v.x) == 2)
        return Pos((u.x + v.x) / 2, u.y);
    return Pos(-1, -1);
}
