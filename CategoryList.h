#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include "MovieNode.h"
#include "Date.h"
#include <iostream>
#include <string>
#include <conio.h> // For arrow key input


using namespace std;

class CategoryList {
public:
    MovieNode* header;
    CategoryList();
    void addMovie(string title, Date* date);
    MovieNode* searchMovie(string title);
    void printMovies();
    void deleteMovie(const string& title);
};

class CategoryNode {
public:
    string name;
    CategoryList* moviesList;
    CategoryNode* prev;
    CategoryNode* next;

    CategoryNode(string n) : name(n), prev(nullptr), next(nullptr)
    {
        moviesList = new CategoryList();
    }
};
#endif // CATEGORYLIST_H

