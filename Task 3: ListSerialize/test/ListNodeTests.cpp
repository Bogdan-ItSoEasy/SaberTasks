#include "List.h"
#include <gtest/gtest.h>

TEST(SerializerTests, Equal) {
    auto headLeft = new ListNode();
    headLeft->data = "head";
    auto childLeft = new ListNode();
    childLeft->data = "child";
    childLeft->rand = headLeft;
    childLeft->prev = headLeft;
    headLeft->rand = childLeft;
    headLeft->next = childLeft;
    auto left = new List(headLeft);

    auto headRight = new ListNode();
    headRight->data = "head";
    auto childRight = new ListNode();
    childRight->data = "child";
    childRight->rand = headRight;
    childRight->prev = headRight;
    headRight->rand = childRight;
    headRight->next = childRight;
    auto right = new List(headRight);

    ASSERT_EQ(*left, *right);
}

TEST(SerializerTests, NotEqual) {
    auto headLeft = new ListNode();
    headLeft->data = "head";
    auto childLeft = new ListNode();
    childLeft->data = "child";
    childLeft->rand = headLeft;
    childLeft->prev = headLeft;
    headLeft->rand = childLeft;
    headLeft->next = childLeft;
    auto left = new List(headLeft);

    auto headRight = new ListNode();
    headRight->data = "head";
    auto childRight = new ListNode();
    childRight->data = "other_child";
    childRight->rand = nullptr;
    childRight->prev = headRight;
    headRight->rand = childRight;
    headRight->next = childRight;
    auto right = new List(headRight);

    ASSERT_NE(*left, *right);
}

TEST(SerializerTests, SerializeEmptyList) {
    auto list = new List();

    FILE *fp = fopen("serialize_empty_list_test", "wb");
    list->Serialize(fp);
    fclose(fp);

    fp = fopen("test", "rb");
    auto actual = new List();
    actual->Deserialize(fp);
    if (fp != nullptr)
        fclose(fp);

    remove("serialize_empty_list_test");
    ASSERT_TRUE(*list == *actual);
}

TEST(SerializerTests, SerializeEmptyStringList) {
    auto head = new ListNode();
    head->data = "";
    auto child = new ListNode();
    child->data = "";
    child->rand = head;
    child->prev = head;
    head->rand = child;
    head->next = child;

    auto list = new List(head);

    FILE *fp = fopen("serialize_simple_list_test", "wb");
    list->Serialize(fp);
    fclose(fp);

    fp = fopen("serialize_simple_list_test", "rb");
    auto actual = new List();
    actual->Deserialize(fp);
    fclose(fp);
    remove("serialize_simple_list_test");
    ASSERT_TRUE(*list == *actual);
}

TEST(SerializerTests, SerializeSimpleList) {

    auto head = new ListNode();
    head->data = "head";
    auto child = new ListNode();
    child->data = "child";
    child->rand = head;
    child->prev = head;
    head->rand = child;
    head->next = child;

    auto list = new List(head);

    FILE *fp = fopen("serialize_simple_list_test", "wb");
    list->Serialize(fp);
    fclose(fp);

    fp = fopen("serialize_simple_list_test", "rb");
    auto actual = new List();
    actual->Deserialize(fp);
    fclose(fp);
    remove("serialize_simple_list_test");
    ASSERT_TRUE(*list == *actual);
}

TEST(SerializerTests, SerializeList) {
    auto head = new ListNode();
    head->data = "head";

    auto firstChild = new ListNode();
    firstChild->data = "first_child";
    head->next = firstChild;
    firstChild->prev = head;

    auto secondChild = new ListNode();
    secondChild->data = "second_child";
    firstChild->next = secondChild;
    secondChild->prev = firstChild;

    auto thirdChild = new ListNode();
    thirdChild->data = "third_child";
    secondChild->next = thirdChild;
    thirdChild->prev = secondChild;

    auto fourthChild = new ListNode();
    fourthChild->data = "fourth_child";
    thirdChild->next = fourthChild;
    fourthChild->prev = thirdChild;

    auto fifthChild = new ListNode();
    fifthChild->data = "fifth_child";
    fourthChild->next = fifthChild;
    fifthChild->prev = fourthChild;

    auto sixChild = new ListNode();
    sixChild->data = "six_child";
    fifthChild->next = sixChild;
    sixChild->prev = fifthChild;

    head->rand = fifthChild;
    firstChild->rand = thirdChild;
    secondChild->rand = fourthChild;
    thirdChild->rand = secondChild;
    fourthChild->rand = thirdChild;
    fifthChild->rand = firstChild;
    sixChild->rand = head;

    auto list = new List(head);

    FILE *fp = fopen("serialize_list_test", "wb");
    list->Serialize(fp);
    fclose(fp);

    fp = fopen("serialize_list_test", "rb");
    auto actual = new List();
    actual->Deserialize(fp);
    fclose(fp);

    ASSERT_TRUE(*list == *actual);
    remove("serialize_list_test");
}

