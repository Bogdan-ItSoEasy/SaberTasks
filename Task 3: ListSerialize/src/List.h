#ifndef TASK3_LIST_H
#define TASK3_LIST_H

#include "ListNode.h"
#include <cstdio>

class List {
  public:
    List();
    explicit List(ListNode *head);

    void Serialize(FILE *file); // сохранение в файл (файл открыт с помощью
                                // fopen(path, "wb"))
    void Deserialize(FILE *file); // загрузка из файла (файл открыт с помощью
                                  // fopen(path, "rb"))

    ListNode *GetHead() const;

  private:
    ListNode *head{};
};

bool operator==(const List &left, const List &right);
bool operator!=(const List &left, const List &right);

#endif // TASK3_LIST_H
