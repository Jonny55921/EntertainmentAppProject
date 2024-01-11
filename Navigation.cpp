#include "Navigation.h"

#include "Navigation.h"
#include <iostream>
#include <conio.h> // For _getch()

using namespace std;

void navigateCategories(NetflixMenu& netflix, CategoryNode*& selectedCategory, MovieNode*& selectedMovie) {
    system("cls"); // Clear the console (Windows)

    cout << "Select a category:" << endl;

    // Print categories
    CategoryNode* current = netflix.firstCategory;
    do {
        if (current == selectedCategory) {
            cout << "-> ";
        }
        else {
            cout << "   ";
        }
        cout << current->name << endl;
        current = current->next;

    } while (current != netflix.firstCategory);
    cout << "Press 'e' for extra functions\n";
    int key = getArrowKeyPress();

    if (key == 72) { // Up arrow key
        selectedCategory = selectedCategory->prev;
    }
    else if (key == 80) { // Down arrow key
        selectedCategory = selectedCategory->next;
    }
    else if (key == 101) // 'e' key to navigate extra functions
    {
        navigateExtra(netflix, selectedCategory, selectedMovie);
    }
    else if (key == 13) { // Enter key
        // Handle category selection here
        if (selectedCategory) {
            selectedMovie = selectedCategory->moviesList->header->next;
        }
    }
}


void navigateMovies(CategoryNode* selectedCategory, MovieNode*& selectedMovie) {
    system("cls"); // Clear the console (Windows)

    cout << "Category: " << selectedCategory->name << endl;
    cout << "Select a movie:" << endl;

    // Print movies in the selected category
    MovieNode* current = selectedCategory->moviesList->header->next;
    do {
        if (current == selectedMovie) {
            cout << "-> ";
        }
        else {
            cout << "   ";
        }
        cout << current->title << " (Uploaded on " << current->uploadDate->month << "/"
            << current->uploadDate->day << "/" << current->uploadDate->year << ")" << endl;
        current = current->next;
    } while (current != selectedCategory->moviesList->header);

    int key = getArrowKeyPress();

    if (key == 72) { // Up arrow key
        selectedMovie = selectedMovie ? selectedMovie->prev : selectedCategory->moviesList->header->prev;
    }
    else if (key == 80) { // Down arrow key
        selectedMovie = selectedMovie ? selectedMovie->next : selectedCategory->moviesList->header->next;
    }
    else if (key == 13) { // Enter key
        // Handle movie selection here
        if (selectedMovie && selectedMovie != selectedCategory->moviesList->header) {
            cout << "Selected Movie: " << selectedMovie->title << endl;
            cout << "Uploaded on: " << selectedMovie->uploadDate->month << "/"
                << selectedMovie->uploadDate->day << "/" << selectedMovie->uploadDate->year << endl;
            cout << "Press any key to continue...";
            _getch();
        }
    }
    else if (key == 27) { // ESC key to go back to category selection
        selectedMovie = nullptr;
    }
}

void navigateExtra(NetflixMenu& netflix, CategoryNode*& selectedCategory, MovieNode*& selectedMovie)
{
    while (true)
    {
        system("cls"); // Clear the console (Windows)

        cout << "Extra Functions Menu:" << endl;
        cout << "1. Add Movie to Category" << endl;
        cout << "2. Search Movie" << endl;
        cout << "3. Delete Movie" << endl;
        cout << "4. Print All Movies" << endl;
        cout << "5. Delete Category and Movies" << endl;
        cout << "6. Search Category" << endl;
        cout << "7. Back to Main Navigation" << endl;

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Add Movie to Category
            if (selectedCategory)
            {
                string categoryName;
                cout << "Enter the name of the category: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, categoryName);

                CategoryNode* categoryToAdd = netflix.searchCategory(categoryName);
                if (categoryToAdd)
                {
                    string newMovieTitle;
                    cout << "Enter the title of the new movie: ";
                    getline(cin, newMovieTitle);
                    int month, day, year;
                    cout << "Enter the upload date (mm dd yyyy): ";
                    cin >> month >> day >> year;
                    Date* newMovieDate = new Date(month, day, year);
                    addMovie(categoryToAdd, newMovieTitle, newMovieDate);
                }
                else
                {
                    cout << "Category not found." << endl;
                }
            }
            else
            {
                cout << "Please select a category first." << endl;
            }
            system("pause");
            break;

        case 2:
            // Search Movie by Title
            if (selectedCategory)
            {
                string searchTitle;
                cout << "Enter the title of the movie you want to search for: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, searchTitle);

                // Use binary search to find the movie
                MovieNode* foundMovie = selectedCategory->moviesList->searchMovie(searchTitle);

                if (foundMovie)
                {
                    cout << "Movie found: " << foundMovie->title << " (Uploaded on "
                        << foundMovie->uploadDate->month << "/"
                        << foundMovie->uploadDate->day << "/"
                        << foundMovie->uploadDate->year << ")" << endl;
                }
                else
                {
                    cout << "Movie not found in this category." << endl;
                }
            }
            else
            {
                cout << "Please select a category first." << endl;
            }
            system("pause");
            break;
        case 3:
            if (selectedCategory) {
                string categoryName;
                cout << "Enter the name of the category: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, categoryName);

                CategoryNode* categoryToDeleteFrom = netflix.searchCategory(categoryName);
                if (categoryToDeleteFrom) {
                    string movieTitle;
                    cout << "Enter the title of the movie to delete: ";
                    getline(cin, movieTitle);
                    deleteMovie(categoryToDeleteFrom, movieTitle);
                }
                else {
                    cout << "Category not found." << endl;
                }
            }
            else {
                cout << "Please select a category first." << endl;
            }
            system("pause");
            break;
        case 4:
            netflix.printAllMovies();
            system("pause");
            break;
        case 5: {
            string categoryName;
            cout << "Enter the name of the category to delete: ";
            cin.ignore(); // Clear the input buffer
            getline(cin, categoryName);

            netflix.deleteCategory(categoryName);
            system("pause");
            break;
        }
        case 6: {
            string categoryName;
            cout << "Enter the name of the category to search: ";
            cin.ignore(); // Clear the input buffer
            getline(cin, categoryName);

            CategoryNode* category = netflix.searchCategory(categoryName);
            if (category) {
                cout << "Category found: " << categoryName << endl;

                // List movies in this category
                MovieNode* currentMovie = category->moviesList->header->next;
                if (currentMovie == category->moviesList->header) {
                    cout << "No movies in this category." << endl;
                }
                else {
                    cout << "Movies in " << categoryName << ":" << endl;
                    while (currentMovie != category->moviesList->header) {
                        cout << "Title: " << currentMovie->title << ", Date: "
                            << currentMovie->uploadDate->month << "/"
                            << currentMovie->uploadDate->day << "/"
                            << currentMovie->uploadDate->year << endl;
                        currentMovie = currentMovie->next;
                    }
                }
            }
            else {
                cout << "Category not found." << endl;
            }
            system("pause");
            break;
        }
        case 7:
            // Back to Main Navigation
            return;

        default:
            while (true) {
                cout << "Invalid choice. Please try again or enter 7 to go back to Main Navigation: ";
                cin >> choice;

                if (cin.fail()) {
                    // Clear error state
                    cin.clear();

                    // Ignore remaining input on the line
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Continue to the next iteration of the loop
                    continue;
                }

                if (choice == 7) {
                    // User wants to go back to Main Navigation
                    return;
                }

                if (choice >= 1 && choice <= 6) {
                    // Valid choice for other options
                    break;
                }
            }
            break;
        }
    }
}

int getArrowKeyPress() {
    int ch = _getch();
    if (ch == 224 || ch == 0) {
        ch = _getch();
        return ch;
    }
    return ch;
}

void addMovie(CategoryNode* category, string title, Date* date)
{
    if (category)
    {
        MovieNode* existingMovie = category->moviesList->searchMovie(title);
        if (existingMovie)
        {
            cout << "Movie already exists in this category." << endl;
        }
        else
        {
            category->moviesList->addMovie(title, date);
            cout << "Movie added to category: " << category->name << endl;
        }
    }
    else
    {
        cout << "Category not found." << endl;
    }
}
void deleteMovie(CategoryNode* category, const string& title) {
    if (category) {
        MovieNode* movieToDelete = category->moviesList->searchMovie(title);
        if (movieToDelete) {
            category->moviesList->deleteMovie(title);
            cout << "Movie deleted from category: " << category->name << endl;
        }
        else {
            cout << "Movie not found in this category." << endl;
        }
    }
    else {
        cout << "Category not found." << endl;
    }
}
void printAllMovies(CategoryNode* category)
{
    if (category)
    {
        cout << "Movies in Category: " << category->name << endl;

        // Create an array to store all movies in the category
        MovieNode** movieArray = new MovieNode * [100]; // Assuming a maximum of 100 movies

        // Copy movies to the array and count them
        int index = 0;
        MovieNode* current = category->moviesList->header->next;
        while (current != category->moviesList->header)
        {
            movieArray[index] = current;
            current = current->next;
            index++;
        }

        // Sort the array alphabetically
        for (int i = 0; i < index - 1; i++)
        {
            for (int j = 0; j < index - i - 1; j++)
            {
                if (movieArray[j]->title > movieArray[j + 1]->title)
                {
                    MovieNode* temp = movieArray[j];
                    movieArray[j] = movieArray[j + 1];
                    movieArray[j + 1] = temp;
                }
            }
        }

        // Print the sorted movies
        for (int i = 0; i < index; i++)
        {
            cout << movieArray[i]->title << " (Uploaded on " << movieArray[i]->uploadDate->month << "/"
                << movieArray[i]->uploadDate->day << "/" << movieArray[i]->uploadDate->year << ")" << endl;
        }

        // Clean up allocated memory
        delete[] movieArray;
    }
    else
    {
        cout << "Category not found." << endl;
    }
}
