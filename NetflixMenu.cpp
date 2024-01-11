#include "NetflixMenu.h"

void NetflixMenu::addCategory(string name)
{
    CategoryNode* newCategory = new CategoryNode(name);

    if (!firstCategory)
    {
        // If the list is empty, set newCategory as the only node in the list
        firstCategory = newCategory;
        newCategory->prev = newCategory;
        newCategory->next = newCategory;
    }
    else
    {
        // Insert the newCategory node at the end of the DLL
        newCategory->next = firstCategory;
        newCategory->prev = firstCategory->prev;
        firstCategory->prev->next = newCategory;
        firstCategory->prev = newCategory;
    }
    CategoryNode* current = firstCategory;
    do {
        MovieNode* currentMovie = current->moviesList->header->next;
        while (currentMovie != current->moviesList->header) {
            // Create a copy of the movie in the "All Movies" category
            allMoviesCategory->moviesList->addMovie(currentMovie->title, currentMovie->uploadDate);
            currentMovie = currentMovie->next;
        }
        current = current->next;
    } while (current != firstCategory);
}


CategoryNode* NetflixMenu::searchCategory(const string& categoryName) {
    if (firstCategory == nullptr) return nullptr; // Empty list check

    CategoryNode* current = firstCategory;
    do {
        if (current->name == categoryName) {
            return current;
        }
        current = current->next;
    } while (current != firstCategory);

    return nullptr; // Category not found
}


void NetflixMenu::deleteCategory(const string& categoryName) {
    // Check if the list is empty
    if (firstCategory == nullptr) {
        cout << "No categories to delete." << endl;
        return;
    }

    CategoryNode* current = firstCategory;
    CategoryNode* prev = nullptr;
    bool found = false;

    // Handling a circular linked list
    do {
        if (current->name == categoryName) {
            found = true;
            break;
        }
        prev = current;
        current = current->next;
    } while (current != firstCategory);

    if (!found) {
        cout << "Category not found." << endl;
        return;
    }

    // Delete all movies in the category
    MovieNode* currentMovie = current->moviesList->header->next;
    while (currentMovie != current->moviesList->header) {
        MovieNode* nextMovie = currentMovie->next;

        // If Date is dynamically allocated, delete it
        delete currentMovie->uploadDate;

        delete currentMovie;
        currentMovie = nextMovie;
    }

    if (current == current->next) { // Only one category in the list
        firstCategory = nullptr;
    }
    else {
        if (prev) {
            prev->next = current->next;
        }
        else { // current is the firstCategory
            // Find the last category to update its next pointer
            CategoryNode* lastCategory = firstCategory;
            while (lastCategory->next != firstCategory) {
                lastCategory = lastCategory->next;
            }
            lastCategory->next = current->next;
            firstCategory = current->next; // Update the firstCategory pointer
        }
    }

    // Delete the category node
    delete current;
    cout << "Category '" << categoryName << "' and all its movies have been deleted." << endl;
}



void NetflixMenu::deleteMovies(Date* date)
{
    CategoryNode* current = firstCategory;

    if (!current)
    {
        cout << "No categories available." << endl;
        return;
    }

    do
    {
        MovieNode* currentMovie = current->moviesList->header->next;
        MovieNode* prevMovie = current->moviesList->header;

        while (currentMovie != current->moviesList->header)
        {
            if (currentMovie->uploadDate->year < date->year ||
                (currentMovie->uploadDate->year == date->year && currentMovie->uploadDate->month < date->month) ||
                (currentMovie->uploadDate->year == date->year && currentMovie->uploadDate->month == date->month &&
                    currentMovie->uploadDate->day <= date->day))
            {
                prevMovie->next = currentMovie->next;
                delete currentMovie;
                currentMovie = prevMovie->next;
            }
            else
            {
                prevMovie = currentMovie;
                currentMovie = currentMovie->next;
            }
        }

        current = current->next;
    } while (current != firstCategory);
}

vector<tuple<MovieNode*, string>> NetflixMenu::getAllMovies() 
{
    vector<tuple<MovieNode*, string>> allMovies;
    if (!firstCategory) return allMovies;

    CategoryNode* currentCategory = firstCategory;


    do {
        MovieNode* currentMovie = currentCategory->moviesList->header->next; // Assuming each category has a header dummy node

        while (currentMovie != currentCategory->moviesList->header) { // Iterate through all movies in the current category
            allMovies.push_back(make_tuple(currentMovie, currentCategory->name));
            currentMovie = currentMovie->next;
        }

        currentCategory = currentCategory->next;
    } while (currentCategory != firstCategory);
    return allMovies;
}

void NetflixMenu::printAllMovies() 
{
    auto allMovies = getAllMovies();

    // Sort movies alphabetically
    sort(allMovies.begin(), allMovies.end(),
        [](const tuple<MovieNode*, string>& a, const tuple<MovieNode*, string>& b) {
            return get<0>(a)->title < get<0>(b)->title;
        });

    // Print sorted movies
    for (const auto& movieInfo : allMovies) {
        MovieNode* movie = get<0>(movieInfo);
        string category = get<1>(movieInfo);
        cout << movie->title << ", " << movie->uploadDate->month << "/"
            << movie->uploadDate->day << "/" << movie->uploadDate->year
            << ", " << category << endl;
    }
}