#ifndef MOVIENODE_H
#define MOVIENODE_H

#include "Date.h"
#include <string>
using namespace std;

class MovieNode {
public:
    string title;
    Date* uploadDate;
    MovieNode* prev;
    MovieNode* next;

    MovieNode(string t, Date* date) : title(t), uploadDate(date), prev(nullptr), next(nullptr) {}
};

#endif // MOVIENODE_H
