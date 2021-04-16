/**
 * @author  zju3180101729
 */

#ifndef MYPROJECT_GAMEBOARD_H
#define MYPROJECT_GAMEBOARD_H

#include <vector>

#include "Pos.h"

#define MASK_EMPTY      0x00
#define MASK_ROAD       0x01
#define MASK_KEY        0x02
#define MASK_BREAK      0x04
#define MASK_START      0x40
#define MASK_END        0x80

#define END_DIR_RIGHT   0x00
#define END_DIR_DOWN    0x01
#define END_DIR_LEFT    0x02
#define END_DIR_UP      0x03

class GameBoard {
public:
    int width, height;
    Pos start, end;
    int endDir, keyNum;
    std::vector<std::vector<int> > mask;

    void init(int world, int level);

    bool check(Pos u, Pos v);

    bool check(const std::vector<Pos> &path);

    Pos getMedium(Pos u, Pos v);
};

#endif //MYPROJECT_GAMEBOARD_H
