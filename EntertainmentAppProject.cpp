// EntertainmentAppProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
    Jonathan Garza, Netflix/Hulu Menu in C++
    Application: Solidfy understanding of Linked List (DLL & CLL), Object Oriented Programming (OOP), with 
    an industry like application or problem
*/
//Libraries
#include <iostream>
#include <string>
#include <conio.h>              // For arrow key input

//HeaderFiles
#include "Date.h"
#include "MovieNode.h"
#include "CategoryList.h"
#include "NetflixMenu.h"
#include "Navigation.h"

using namespace std;

int main() 
{
    NetflixMenu netflix;

    netflix.addCategory("Action");
    netflix.addCategory("Comedy");
    netflix.addCategory("Drama");
    netflix.addCategory("Anime");
    netflix.addCategory("Science Fiction");
    netflix.addCategory("Horror");
    netflix.addCategory("Romance");

    CategoryNode* actionCategory = netflix.searchCategory("Action");
    CategoryNode* comedyCategory = netflix.searchCategory("Comedy");
    CategoryNode* dramaCategory = netflix.searchCategory("Drama");
    CategoryNode* animeCategory = netflix.searchCategory("Anime");
    CategoryNode* scifiCategory = netflix.searchCategory("Science Fiction");
    CategoryNode* horrorCategory = netflix.searchCategory("Horror");
    CategoryNode* romanceCategory = netflix.searchCategory("Romance");


    actionCategory->moviesList->addMovie("Die Hard", new Date(7, 22, 1988));
    actionCategory->moviesList->addMovie("Mad Max: Fury Road", new Date(5, 15, 2015));
    actionCategory->moviesList->addMovie("John Wick", new Date(10, 24, 2014));
    actionCategory->moviesList->addMovie("The Dark Knight", new Date(7, 18, 2008));
    actionCategory->moviesList->addMovie("Inception", new Date(7, 16, 2010));
    actionCategory->moviesList->addMovie("Gladiator", new Date(5, 5, 2000));
    actionCategory->moviesList->addMovie("The Bourne Identity", new Date(6, 14, 2002));

    comedyCategory->moviesList->addMovie("Superbad", new Date(8, 17, 2007));
    comedyCategory->moviesList->addMovie("The Hangover", new Date(6, 5, 2009));
    comedyCategory->moviesList->addMovie("Bridesmaids", new Date(5, 13, 2011));
    comedyCategory->moviesList->addMovie("Groundhog Day", new Date(2, 12, 1993));
    comedyCategory->moviesList->addMovie("Anchorman", new Date(7, 9, 2004));
    comedyCategory->moviesList->addMovie("Dumb and Dumber", new Date(12, 16, 1994));

    dramaCategory->moviesList->addMovie("The Shawshank Redemption", new Date(10, 14, 1994));
    dramaCategory->moviesList->addMovie("Forrest Gump", new Date(7, 6, 1994));
    dramaCategory->moviesList->addMovie("Fight Club", new Date(10, 15, 1999));
    dramaCategory->moviesList->addMovie("Good Will Hunting", new Date(12, 5, 1997));
    dramaCategory->moviesList->addMovie("The Godfather", new Date(3, 24, 1972));
    dramaCategory->moviesList->addMovie("Schindler's List", new Date(12, 15, 1993));

    animeCategory->moviesList->addMovie("Jujutsu Kaisen 0", new Date(3, 18, 2022));
    animeCategory->moviesList->addMovie("Your Name", new Date(8, 26, 2016));
    animeCategory->moviesList->addMovie("Spirited Away", new Date(7, 20, 2001));
    animeCategory->moviesList->addMovie("Princess Mononoke", new Date(7, 12, 1997));
    animeCategory->moviesList->addMovie("My Neighbor Totoro", new Date(4, 16, 1988));
    animeCategory->moviesList->addMovie("Akira", new Date(7, 16, 1988));

    scifiCategory->moviesList->addMovie("Blade Runner 2049", new Date(10, 6, 2017));
    scifiCategory->moviesList->addMovie("Interstellar", new Date(11, 5, 2014));
    scifiCategory->moviesList->addMovie("The Matrix", new Date(3, 31, 1999));
    scifiCategory->moviesList->addMovie("Star Wars: Episode IV - A New Hope", new Date(5, 25, 1977));
    scifiCategory->moviesList->addMovie("E.T. the Extra-Terrestrial", new Date(6, 11, 1982));
    scifiCategory->moviesList->addMovie("Jurassic Park", new Date(6, 11, 1993));
    scifiCategory->moviesList->addMovie("Back to the Future", new Date(7, 3, 1985));

    horrorCategory->moviesList->addMovie("The Conjuring", new Date(7, 19, 2013));
    horrorCategory->moviesList->addMovie("Hereditary", new Date(6, 8, 2018));
    horrorCategory->moviesList->addMovie("Psycho", new Date(9, 8, 1960));
    horrorCategory->moviesList->addMovie("The Shining", new Date(5, 23, 1980));
    horrorCategory->moviesList->addMovie("Get Out", new Date(2, 24, 2017));
    horrorCategory->moviesList->addMovie("It", new Date(9, 8, 2017));
    horrorCategory->moviesList->addMovie("A Quiet Place", new Date(4, 6, 2018));

    romanceCategory->moviesList->addMovie("La La Land", new Date(12, 9, 2016));
    romanceCategory->moviesList->addMovie("The Notebook", new Date(6, 25, 2004));
    romanceCategory->moviesList->addMovie("Titanic", new Date(12, 19, 1997));
    romanceCategory->moviesList->addMovie("Pride and Prejudice", new Date(9, 16, 2005));
    romanceCategory->moviesList->addMovie("The Great Gatsby", new Date(5, 10, 2013));
    romanceCategory->moviesList->addMovie("Eternal Sunshine of the Spotless Mind", new Date(3, 19, 2004));
    romanceCategory->moviesList->addMovie("Before Sunrise", new Date(1, 27, 1995));

    CategoryNode* selectedCategory = netflix.firstCategory;
    MovieNode* selectedMovie = nullptr;
    while (true) {
        if (!selectedMovie) {

            navigateCategories(netflix, selectedCategory, selectedMovie);
        }
        else {
            navigateMovies(selectedCategory, selectedMovie);
        }
    }

    return 0;
}
