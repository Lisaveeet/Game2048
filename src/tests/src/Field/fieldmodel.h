#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <vector>
#include <random>

#include "../constants.h"
#include "../utils.h"

struct Point {
    int x, y;

    bool operator==(const Point& right) {
        return x == right.x && y == right.y;
    }
};

class FieldModel
{

private:
    std::vector<std::vector<int>> m_field;

    std::pair<int, bool> getColumnTop(std::vector<std::vector<int>> field, Point pos, std::vector<Point> mergedPoints = {});

    bool isPowerOfTwo(int num);
    void checkField(std::vector<std::vector<int>> field);

public:
    FieldModel();
    FieldModel(std::vector<std::vector<int>> field);

    FieldModel(FieldModel& copy);

    void clear();
    int move(Direction dir);
    void generateNumber();
    bool isGameOver();
    bool isWin();

    void setField(std::vector<std::vector<int>> field);
    std::vector<std::vector<int>> getField();
};

#endif // FIELDMODEL_H
