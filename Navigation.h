#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "NetflixMenu.h"
#include "MovieNode.h"
#include "CategoryList.h"

// Forward declarations
class NetflixMenu;
class CategoryNode;
class MovieNode;

void navigateCategories(NetflixMenu& netflix, CategoryNode*& selectedCategory, MovieNode*& selectedMovie);
void navigateMovies(CategoryNode* selectedCategory, MovieNode*& selectedMovie);
void navigateExtra(NetflixMenu& netflix, CategoryNode*& selectedCategory, MovieNode*& selectedMovie);
int getArrowKeyPress();

// Functions to add, search, delete, and print movies
void addMovie(CategoryNode* category, string title, Date* date);
MovieNode* searchMovie(CategoryNode* category, string title);
void deleteMovie(CategoryNode* category, const string& title);

#endif // NAVIGATION_H