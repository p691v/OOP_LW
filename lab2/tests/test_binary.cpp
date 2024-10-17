#include <gtest/gtest.h>
#include "../src/binary.cpp"

TEST(BinaryTest, DefaultConstructor)
{

    Binary b;

    size_t size = b.getSize();
    unsigned char *data = b.getData();

    EXPECT_EQ(size, 0);
    EXPECT_EQ(data, nullptr);
}

TEST(BinaryTest, SizeAndDefaultConstructor)
{

    size_t n = 5;
    unsigned char value = '0';
    Binary b(n, value);

    size_t size = b.getSize();
    unsigned char *data = b.getData();

    EXPECT_EQ(size, n);
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(data[i], value);
    }
}

TEST(BinaryTest, InitializerListConstructor)
{

    std::initializer_list<unsigned char> values = {'1', '0', '1', '1'};
    Binary b(values);

    size_t size = b.getSize();
    unsigned char *data = b.getData();

    EXPECT_EQ(size, values.size());
    size_t i = 0;
    for (unsigned char digit : values)
    {
        EXPECT_EQ(data[i++], digit);
    }
}

TEST(BinaryTest, StringConstructor)
{

    std::string str = "1011";
    Binary b(str);

    size_t size = b.getSize();
    unsigned char *data = b.getData();

    EXPECT_EQ(size, str.size());
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(data[i], str[i]);
    }
}

TEST(BinaryTest, AssignmentOperator)
{

    Binary b1("1011");
    Binary b2;

    b2 = b1;

    EXPECT_EQ(b2.getSize(), b1.getSize());
    for (int i = 0; i < b2.getSize(); ++i)
    {
        EXPECT_EQ(b1.getData()[i], b2.getData()[i]);
    }
}

TEST(BinaryTest, AdditionOperator)
{

    Binary b1("1010");
    Binary b2("1101");

    b1 += b2;

    EXPECT_EQ(b1.getSize(), 5);
}

TEST(BinaryTest, SubtractionOperator)
{

    Binary b1("11111");
    Binary b2("00011");

    b1 -= b2;

    std::string ans = "11100";
    EXPECT_EQ(b1.getSize(), 5);
    for (int i = 0; i < b1.getSize(); ++i)
    {
        EXPECT_EQ(b1.getData()[i], ans[i]);
    }
}

TEST(BinaryTest, EqualityOperator)
{

    Binary b1("1010");
    Binary b2("1010");
    Binary b3("1101");

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
}

TEST(BinaryTest, LessThanOperator)
{

    Binary b1("1010");
    Binary b2("1101");

    EXPECT_TRUE(b1 < b2);
    EXPECT_FALSE(b2 < b1);
}

TEST(BinaryTest, GreaterThanOperator)
{

    Binary b1("1101");
    Binary b2("1010");

    EXPECT_TRUE(b1 > b2);
    EXPECT_FALSE(b2 > b1);
}