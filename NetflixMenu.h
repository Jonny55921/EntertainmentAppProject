#ifndef NETFLIXMENU_H
#define NETFLIXMENU_H

#include "MovieNode.h"
#include "Date.h"
#include "CategoryList.h"
#include <iostream>
#include <string>
#include <conio.h> // For arrow key input
#include <vector>
#include <tuple>
#include <algorithm>

class NetflixMenu {
public:
    CategoryNode* firstCategory;
    CategoryNode* allMoviesCategory;

    NetflixMenu()
    {
        firstCategory = nullptr;
        allMoviesCategory = new CategoryNode("All Movies");
    }

    void addCategory(string name);

    CategoryNode* searchCategory(const string& categoryName);

    void deleteCategory(const string &name);

    void deleteMovies(Date* date);

    vector<tuple<MovieNode*, string>> getAllMovies();
    void printAllMovies();
};
#endif // NETFLIXMENU_H
