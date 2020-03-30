#include "NodeSerializer.h"
#include <unordered_map>
#include <iostream>

void NodeSerialize(FILE *file, const ListNode *node) {
    const auto length = node->data.size();
    fwrite(&node, sizeof(node), 1, file);
    fwrite(&node->rand, sizeof(node->rand), 1, file);
    fwrite(&length, sizeof(length), 1, file);
    fwrite(&node->data[0], 1, length, file);

    if (node->next != nullptr) {
        NodeSerialize(file, node->next);
    }
}

const std::string DESERIALIZE_ERROR_MESSAGE = std::string("ERROR: Couldn't deserialize file. Maybe file was corrupted");
const std::string BAD_LINK_ERROR_MESSAGE = std::string("ERROR: Couldn't find link on the random node");

ListNode *NodeDeserialize(FILE *file) {
    if (file == nullptr)
        return nullptr;

    std::unordered_map<ListNode *, ListNode *> actualPtr;

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

        if(1 != fread(&current->rand, sizeof(current->rand), 1, file))
            throw std::ios_base::failure(DESERIALIZE_ERROR_MESSAGE);

        size_t length;
        if(1!= fread(&length, sizeof(size_t), 1, file))
            throw std::ios_base::failure(DESERIALIZE_ERROR_MESSAGE);

        std::string data(length, ' ');
        if(length != fread(&data[0], 1, length, file))
            throw std::ios_base::failure(DESERIALIZE_ERROR_MESSAGE);
        current->data = data;
    }

    while (current != nullptr) {
        if(actualPtr.count(current->rand) == 0)
            throw std::ios_base::failure(BAD_LINK_ERROR_MESSAGE);
        current->rand = actualPtr[current->rand];
        current = current->prev;
    }

    return head;
}
