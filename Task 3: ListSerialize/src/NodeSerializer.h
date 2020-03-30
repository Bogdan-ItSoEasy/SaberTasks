#ifndef TASK3_SERIALIZER_H
#define TASK3_SERIALIZER_H

#include "ListNode.h"

void NodeSerialize(FILE *file, const ListNode *node);

ListNode *NodeDeserialize(FILE *file);

#endif
