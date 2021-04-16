/**
 * @author  zju3180101729
 */

#ifndef MYPROJECT_POS_H
#define MYPROJECT_POS_H

struct Pos {
    int x, y;

    Pos(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Pos &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Pos &rhs) const {
        return x != rhs.x || y != rhs.y;
    }
};

#endif //MYPROJECT_POS_H
