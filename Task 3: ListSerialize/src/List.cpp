#include <cstdio>

#include "List.h"
#include "NodeSerializer.h"

List::List() = default;

List::List(ListNode *head) { this->head = head; }

void List::Deserialize(FILE *file) { this->head = NodeDeserialize(file); }

void List::Serialize(FILE *file) const{
    if (this->head == nullptr) {
        return;
    }
    auto node = head;
    if (node->prev != nullptr)
        node = node->prev;

    NodeSerialize(file, node);
}

ListNode *List::GetHead() const { return this->head; }

bool operator==(const List &left, const List &right) {
    auto left_node = left.GetHead();
    if (left_node == nullptr)
        return right.GetHead() == nullptr;
    while (left_node->prev != nullptr)
        left_node = left_node->prev;

    auto right_node = right.GetHead();
    if (right_node == nullptr)
        return false;
    while (right_node->prev != nullptr)
        right_node = right_node->prev;

    while (left_node != nullptr || right_node != nullptr) {
        if (left_node == nullptr || right_node == nullptr ||
            left_node->data != right_node->data)
            return false;

        if ((left_node->rand != nullptr && right_node->rand == nullptr) ||
            (left_node->rand == nullptr && right_node->rand != nullptr) ||
            (left_node->rand != nullptr && right_node->rand != nullptr &&
             left_node->rand->data != right_node->rand->data))
            return false;

        left_node = left_node->next;
        right_node = right_node->next;

        if (left_node != nullptr && right_node != nullptr)
            if (left_node->prev == nullptr || right_node->prev == nullptr ||
                left_node->prev->data != right_node->prev->data)
                return false;
    }

    return true;
}

bool operator!=(const List &left, const List &right) {
    return !(left == right);
}
