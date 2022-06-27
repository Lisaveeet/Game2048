#include "fieldmodel.h"

#include <algorithm>
#include <stdexcept>
#include <cmath>

FieldModel::FieldModel()
{
    clear();
}

FieldModel::FieldModel(std::vector<std::vector<int>> field) {
    setField(field);
}

void FieldModel::setField(std::vector<std::vector<int>> field) {
    checkField(field);

    m_field = field;
}

std::vector<std::vector<int>> FieldModel::getField() {
    return m_field;
}

void FieldModel::checkField(std::vector<std::vector<int>> field) {
    if (field.size() != FIELD_SIZE)
        throw std::runtime_error("Invalid field given! Field size must be 4x4");

    for (int i = 0; i < field.size(); ++i)
        if (field[i].size() != FIELD_SIZE)
            throw std::runtime_error("Invalid field given! Field size must be 4x4");

    for (int i = 0; i < FIELD_SIZE; ++i)
        for (int j = 0; j < FIELD_SIZE; ++j)
            if (field[i][j] != 0 && !isPowerOfTwo(field[i][j]))
                throw std::runtime_error("Invalid field given! Field must contain only zeros and 2 powers!");

}

bool FieldModel::isPowerOfTwo(int num) {
    int i = 1;
    int pw = pow(2, i);

    while (pw <= num) {
        if (pw == num) return true;

        ++i;
        pw = pow(2, i);
    }

    return false;
}

void FieldModel::clear() {
    m_field = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };
}

void FieldModel::generateNumber() {
    std::vector<Point> avalible;

    for (int i = 0; i < FIELD_SIZE; ++i)
        for (int j = 0; j < FIELD_SIZE; ++j)
            if (m_field[i][j] == 0) avalible.push_back({ j, i });

    if (avalible.empty()) return;

    Point pos = avalible[Utils::randInt(0, avalible.size() - 1)];

    int n = Utils::randInt(0, 10);
    if (n >= 9)
        m_field[pos.y][pos.x] = 4;
    else
        m_field[pos.y][pos.x] = 2;
}

int FieldModel::move(Direction dir) {
    int score = 0;

    if (dir == Direction::None) return 0;

    if (dir == Direction::Left) {
        Utils::rotateMatrix(m_field, 3);
    }
    if (dir == Direction::Right) {
        Utils::rotateMatrix(m_field, 1);
    }
    if (dir == Direction::Down) {
        Utils::rotateMatrix(m_field, 2);
    }

    bool moved = false;

    std::vector<Point> mergedPoints;

    for (int i = 1; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {

            if (m_field[i][j] != 0) {

                auto info = getColumnTop(m_field, { j, i }, mergedPoints);

                int val = m_field[i][j];

                if (info.second) {
                    val += m_field[i][j];
                    score += val;
                    mergedPoints.push_back({ j, info.first });
                }

                if (info.first != i) moved = true;

                m_field[i][j] = 0;
                m_field[info.first][j] = val;
            }
        }
    }

    if (dir == Direction::Left) {
        Utils::rotateMatrix(m_field, 1);
    }
    if (dir == Direction::Right) {
        Utils::rotateMatrix(m_field, 3);
    }
    if (dir == Direction::Down) {
        Utils::rotateMatrix(m_field, 2);
    }

    if (!moved) return -1;

    return score;
}

std::pair<int, bool> FieldModel::getColumnTop(std::vector<std::vector<int>> field, Point pos, std::vector<Point> mergedPoints) {
    bool merge = false;
    int top = 0;

    for (int i = pos.y - 1; i >= 0; --i) {

        if (field[i][pos.x] != 0) {
            bool alreadyMerged = std::find(mergedPoints.begin(), mergedPoints.end(), Point{ pos.x, i }) != mergedPoints.end();

            if (!alreadyMerged && field[pos.y][pos.x] == field[i][pos.x]) {
                merge = true; top = i;
            } else {
                top = i + 1;
            }

            break;
        }
    }

    return { top, merge };
}

bool FieldModel::isGameOver() {
    auto copy = m_field;

    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < FIELD_SIZE; ++i) {
            for (int j = 0; j < FIELD_SIZE; ++j) {
                if (copy[i][j] == 0) return false;

                if (copy[i][j] != 0) {
                    auto info = getColumnTop(copy, { j, i });
                    if (i != info.first) return false;
                }
            }
        }

        Utils::rotateMatrix(copy, 1);
    }

    Utils::rotateMatrix(copy, 1);

    return true;
}

bool FieldModel::isWin() {
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            if (m_field[i][j] == 2048) return true;
        }
    }

    return false;
}
