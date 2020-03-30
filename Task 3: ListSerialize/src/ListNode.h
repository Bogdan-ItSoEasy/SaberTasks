#ifndef TASK3_LISTNODE_H
#define TASK3_LISTNODE_H

#include <string>

struct ListNode {
    ListNode *prev;
    ListNode *next;
    ListNode *rand;
    std::string data;
};

#endif
