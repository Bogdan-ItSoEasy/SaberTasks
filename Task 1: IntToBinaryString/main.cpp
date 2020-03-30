#include <gtest/gtest.h>
#include <stdio.h>

constexpr uint BITS_IN_BYTE = 8;

int GetBinaryViewSize(int32_t value) {
    uint32_t testBit = 0x80000000;

    //Search for the index of the first value (non-zero) bit
    uint32_t firstValueIndex = 0;
    while ((testBit & value) == 0) {
        testBit = testBit >> 1;
        ++firstValueIndex;
    }

    //Binary view length. sizeof(int32_t)*8 - max binary view length.
    return sizeof(int32_t) * BITS_IN_BYTE - firstValueIndex;
}

char *IntToBinaryString(int32_t value) {
    if (value == 0) {
        char *null = new char[2]{'0', '\0'};
        return null;
    }

    const uint32_t viewSize = GetBinaryViewSize(value);

    char *result = new char[viewSize + 1];
    result[viewSize] = '\0';
    uint32_t handling = static_cast<uint32_t>(value);
    int32_t index = viewSize;

    while (handling && index > 0) {
        result[--index] = '0' + handling % 2;
        handling = handling / 2;
    }

    return result;
}

void PrintBinaryView(int32_t value) {
    printf("%s\n", IntToBinaryString(value));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(IntToBinaryString, MinValue) {
    char *actual = IntToBinaryString(INT32_MIN);
    const char expected[33] = "10000000000000000000000000000000";

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(IntToBinaryString, NullValue) {
    const char *actual = IntToBinaryString(0);
    const char expected[2] = "0";

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(IntToBinaryString, MaxValue) {
    const char *actual = IntToBinaryString(INT32_MAX);
    const char expected[32] = "1111111111111111111111111111111";

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(IntToBinaryString, MinusOne) {
    const char *actual = IntToBinaryString(-1);
    const char expected[33] = "11111111111111111111111111111111";

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(IntToBinaryString, CommonValue) {
    const char *actual = IntToBinaryString(0xABCD);
    const char expected[17] = "1010101111001101";

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(IntToBinaryString, CommonNegValue) {
    const char *actual = IntToBinaryString(-255);
    const char expected[33] = "11111111111111111111111100000001";

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}
