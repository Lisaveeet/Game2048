#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

#include "../Field/fieldmodel.h"
#include "../Field/fieldmodel.cpp"

using namespace testing;

typedef std::vector<std::vector<int>> matrix;

TEST(FieldAssingnment, Tests)
{
    matrix field1 = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    };

    matrix field2 = {
        { 4, 0, 0, 0 },
        { 0, 0, 8, 2 },
        { 0, 4, 0, 0 },
        { 0, 0, 0, 0 },
    };

    matrix field3 = {
        { 16, 128, 64, 16 },
        { 8,  256, 8,  2 },
        { 2,  8,   16, 4 },
        { 8,  16,  2,  2 },
    };

    FieldModel model1(field1), model2(field2), model3(field3);

    ASSERT_EQ(model1.getField(), field1);
    ASSERT_EQ(model2.getField(), field2);
    ASSERT_EQ(model3.getField(), field3);
}

TEST(FieldInvalidAssingnment, Tests)
{
    matrix field1 = {};

    matrix field2 = {
        { 4, 0, 0, 0 },
        { 0, 0, 8, 2 },
        { 0, 4, 0, 0, 2 },
        { 0, 0, 0, 0 },
    };

    matrix field3 = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 3 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    FieldModel model1, model2, model3;

    EXPECT_THROW({
        try
        {
            model1.setField(field1);
        }
        catch (const std::exception& e)
        {
            EXPECT_STREQ( "Invalid field given! Field size must be 4x4", e.what() );
            throw;
        }
    }, std::exception );

    EXPECT_THROW({
        try
        {
            model2.setField(field2);
        }
        catch (const std::exception& e)
        {
            EXPECT_STREQ( "Invalid field given! Field size must be 4x4", e.what() );
            throw;
        }
    }, std::exception );

    EXPECT_THROW({
        try
        {
            model3.setField(field3);
        }
        catch (const std::exception& e)
        {
            EXPECT_STREQ( "Invalid field given! Field must contain only zeros and 2 powers!", e.what() );
            throw;
        }
    }, std::exception );
}

TEST(FieldClear, Tests)
{
    matrix field = {
        { 16, 128, 64, 16 },
        { 8,  256, 8,  2 },
        { 2,  8,   16, 4 },
        { 8,  16,  2,  2 },
    };

    matrix empty = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    };

    FieldModel model(field);
    model.clear();

    ASSERT_EQ(model.getField(), empty);
}

TEST(FieldGenerateNumber, Tests) {
    FieldModel model;

    model.generateNumber();

    bool created = false;
    int val = 0;

    auto field = model.getField();
    for (int i = 0; i < field.size(); ++i)
        for (int j = 0; j < field.size(); ++j)
            if (field[i][j] != 0) {
                created = true; val = field[i][j]; break;
            }

    ASSERT_TRUE(created);
    ASSERT_TRUE(val == 4 || val == 2);
}

TEST(MatrixRotate, Tests) {
    matrix mat = {
        { 0, 1, 1, 0 },
        { 3, 0, 0, 4 },
        { 3, 0, 0, 4 },
        { 0, 2, 2, 0 },
    };

    matrix matRotated = {
        { 0, 2, 2, 0 },
        { 4, 0, 0, 3 },
        { 4, 0, 0, 3 },
        { 0, 1, 1, 0 },
    };

    Utils::rotateMatrix(mat, 2);

    ASSERT_EQ(mat, matRotated);
}

TEST(FieldMove, Tests) {
    matrix mat1 = {
        { 0, 0, 0, 0 },
        { 0, 2, 2, 0 },
        { 4, 0, 0, 4 },
        { 0, 8, 8, 0 },
    };

    matrix matMoved1 = {
        { 4, 2, 2, 4 },
        { 0, 8, 8, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    };

    FieldModel model1(mat1);
    model1.move(Direction::Up);

    ASSERT_EQ(model1.getField(), matMoved1);

    matrix mat2 = {
        { 2, 0,   4, 0 },
        { 4, 256, 0, 128 },
        { 4, 0,   0, 16 },
        { 2, 0,   8, 0 },
    };

    matrix matMoved2 = {
        { 2, 4,   0,   0 },
        { 4, 256, 128, 0 },
        { 4, 16,  0,   0 },
        { 2, 8,   0,   0 },
    };

    FieldModel model2(mat2);
    model2.move(Direction::Left);

    ASSERT_EQ(model2.getField(), matMoved2);
}

TEST(FieldUselessMove, Tests) {
    matrix mat = {
        { 4, 2, 2, 4 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    };

    FieldModel model(mat);

    int ret = model.move(Direction::Up);

    ASSERT_EQ(ret, -1);
    ASSERT_EQ(mat, model.getField());
}

TEST(FieldMerge, Tests) {
    matrix mat1 = {
        { 2, 4, 4, 2 },
        { 2, 4, 4, 2 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    matrix matMerged1 = {
        { 4, 8, 8, 4 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    FieldModel model1(mat1);
    model1.move(Direction::Up);

    ASSERT_EQ(model1.getField(), matMerged1);

    matrix mat2 = {
        { 2, 8, 4, 4 },
        { 2, 4, 4, 2 },
        { 0, 4, 4, 0 },
        { 8, 0, 0, 8 }
    };

    matrix matMerged2 = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 4 },
        { 4, 8, 4, 2 },
        { 8, 8, 8, 8 }
    };

    FieldModel model2(mat2);
    model2.move(Direction::Down);

    ASSERT_EQ(model2.getField(), matMerged2);
}

TEST(FieldDoubleMerge, Tests) {
    matrix mat = {
        { 2, 4, 4, 2 },
        { 2, 4, 4, 2 },
        { 2, 4, 2, 8 },
        { 2, 4, 2, 8 }
    };

    matrix matMerged = {
        { 4, 8, 8, 4  },
        { 4, 8, 4, 16 },
        { 0, 0, 0, 0  },
        { 0, 0, 0, 0  }
    };

    FieldModel model(mat);
    model.move(Direction::Up);

    ASSERT_EQ(model.getField(), matMerged);
}

TEST(FieldScores, Tests) {
    matrix mat1 = {
        { 2, 4, 4, 2 },
        { 2, 4, 4, 2 },
        { 2, 4, 4, 2 },
        { 2, 4, 4, 2 }
    };

    matrix mat2 = {
        { 4, 8, 8, 4 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    FieldModel model1(mat1), model2(mat2);

    int score1 = model1.move(Direction::Up);
    int score2 = model2.move(Direction::Down);

    ASSERT_EQ(score1, 48);
    ASSERT_EQ(score2, 0);
}

TEST(FieldGameOver, Tests) {
    matrix mat1 = {
        { 2, 32, 4,  2 },
        { 8, 64, 8,  4 },
        { 4, 32, 16, 8 },
        { 2, 4,  8,  2 }
    };

    matrix mat2 = {
        { 2, 32, 4,  4 },
        { 2, 64, 8,  4 },
        { 4, 32, 16, 8 },
        { 2, 4,  8,  2 }
    };

    FieldModel model1(mat1), model2(mat2);

    ASSERT_TRUE(model1.isGameOver());
    ASSERT_FALSE(model2.isGameOver());
}

TEST(FieldGameWin, Tests) {
    matrix mat1 = {
        { 0, 0, 0, 0 },
        { 0, 2048, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    };

    matrix mat2 = {
        { 0, 0, 16, 0 },
        { 0, 4, 0,  0 },
        { 0, 0, 8,  0 },
        { 0, 0, 0,  0 },
    };

    FieldModel model1(mat1), model2(mat2);

    ASSERT_TRUE(model1.isWin());
    ASSERT_FALSE(model2.isWin());
}
