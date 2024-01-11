#include "CategoryList.h"

CategoryList::CategoryList() 
{
    header = new MovieNode("Header", nullptr);
    header->next = header;
}
void CategoryList::addMovie(string title, Date* date)
{
    MovieNode* newMovie = new MovieNode(title, date);

    MovieNode* prev = header;
    MovieNode* current = header->next;

    // Find the correct position to insert the movie in sorted order
    while (current != header && title > current->title)
    {
        prev = current;
        current = current->next;
    }

    if (current != header && title == current->title)
    {
        cout << "Movie already exists in this category." << endl;
        delete newMovie;
    }
    else
    {
        prev->next = newMovie;
        newMovie->prev = prev;
        newMovie->next = current;

        // Update the next node's previous pointer
        if (current != header)
        {
            current->prev = newMovie;
        }
    }
}
MovieNode* CategoryList::searchMovie(string title)
{
    MovieNode* current = header->next;

    while (current != header)
    {
        if (current->title == title)
        {
            return current;
        }
        current = current->next;
    }

    return nullptr; // Movie not found
}

void CategoryList::printMovies()
{
    MovieNode* current = header->next;

    while (current != header)
    {
        cout << current->title << " (Uploaded on " << current->uploadDate->month << "/"
            << current->uploadDate->day << "/" << current->uploadDate->year << ")" << endl;
        current = current->next;
    }
}
void CategoryList::deleteMovie(const string& title) {
    if (header->next == header) {
        // List is empty
        cout << "No movies to delete in this category." << endl;
        return;
    }

    MovieNode* current = header->next;
    MovieNode* prev = header;

    while (current != header && current->title != title) {
        prev = current;
        current = current->next;
    }

    if (current == header) {
        // Movie not found
        cout << "Movie not found in this category." << endl;
        return;
    }

    // Movie found, perform deletion
    prev->next = current->next;
    if (current->next != header) {
        current->next->prev = prev;
    }

    delete current->uploadDate; // Assuming dynamic allocation of Date
    delete current;

    cout << "Movie '" << title << "' deleted successfully." << endl;
}
