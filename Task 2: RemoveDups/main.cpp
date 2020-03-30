#include <cstring>
#include <gtest/gtest.h>
#include <tuple>
#include <vector>

void RemoveDups(char *input) {

    uint size = strlen(input);
    std::vector<std::tuple<uint, uint>> duplicateIndexes;

    bool isDuplicate = false;
    uint beginDuplicate = 0;

    for (int i = 1; i < size; ++i) {

        if (!isDuplicate && input[i - 1] == input[i]) {
            isDuplicate = true;
            duplicateIndexes.emplace_back(beginDuplicate, i);
        }
        if (isDuplicate && input[i - 1] != input[i]) {
            isDuplicate = false;
            beginDuplicate = static_cast<uint>(i);
        }
    }

    if (!isDuplicate)
        duplicateIndexes.emplace_back(beginDuplicate, size);

    uint dst = std::get<1>(duplicateIndexes[0]);
    for (int i = 1; i < duplicateIndexes.size(); ++i) {

        uint begin, end;
        std::tie(begin, end) = duplicateIndexes[i];

        std::memcpy(input + dst, input + begin, end - begin);
        dst += end - begin;
    }
    input[dst] = '\0';
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(RemoveDups, Example) {
    char actual[] = "AAA BBB AAA";
    char expected[] = "A B A";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, Empty) {
    char actual[] = "";
    char expected[] = "";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, WithoutRepeats) {
    char actual[] = "abcdfg";
    char expected[] = "abcdfg";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, OneSymbol) {
    char actual[] = "a";
    char expected[] = "a";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, RepeateOneSymbol) {
    char actual[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    char expected[] = "a";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, TwoSymbol) {
    char actual[] = "aa";
    char expected[] = "a";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, Mirror) {
    char actual[] = "abcdefghhgfedcba";
    char expected[] = "abcdefghgfedcba";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, RepeatsInBegin) {
    char actual[] = "aaaaaaaaaabcdefg";
    char expected[] = "abcdefg";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, RepeatsInMiddle) {
    char actual[] = "abcdddddddddefg";
    char expected[] = "abcdefg";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}

TEST(RemoveDups, RepeatsInEnd) {
    char actual[] = "abcdefggggggggggg";
    char expected[] = "abcdefg";
    RemoveDups(actual);

    ASSERT_EQ(strlen(expected), strlen(actual));
    ASSERT_TRUE(0 == memcmp(expected, actual, sizeof(expected)));
}
