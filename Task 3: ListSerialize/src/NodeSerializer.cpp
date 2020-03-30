#include "NodeSerializer.h"
#include <map>

void NodeSerialize(FILE *file, ListNode *node) {
    auto length = node->data.size();
    fwrite(&node, sizeof(node), 1, file);
    fwrite(&node->rand, sizeof(node->rand), 1, file);
    fwrite(&length, sizeof(length), 1, file);
    fwrite(&node->data[0], 1, length, file);

    if (node->next != nullptr) {
        NodeSerialize(file, node->next);
    }
}

ListNode *NodeDeserialize(FILE *file) {
    if (file == nullptr)
        return nullptr;

    std::map<ListNode *, ListNode *> actualPtr;

    auto *head = new ListNode();
    ListNode *current = nullptr;
    ListNode *oldPtr = nullptr;

    while (fread(&oldPtr, sizeof(ListNode *), 1, file) == 1) {
        if (current == nullptr) {
            current = head;
        } else {
            current->next = new ListNode();
            current->next->prev = current;
            current = current->next;
        }

        actualPtr[oldPtr] = current;

        fread(&current->rand, sizeof(current->rand), 1, file);

        size_t length;
        fread(&length, sizeof(size_t), 1, file);
        std::string data(length, ' ');
        fread(&data[0], 1, length, file);
        current->data = data;
    }

    while (current != nullptr) {
        current->rand = actualPtr[current->rand];
        current = current->prev;
    }

    return head;
}
