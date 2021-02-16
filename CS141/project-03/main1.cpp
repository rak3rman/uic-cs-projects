//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 03 - 10/03/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Movie struct
struct movie_struct {
    int movie_id;
    int year;
    string title;
};

// Review struct
struct review_struct {
    int review_id;
    int movie_id;
    int rating;
};

// get_count : Gets the number of movies/reviews from a movie/review file, returns count
int get_count(string file_name) {
    ifstream infile(file_name);
    if (!infile.good()) {
        cout << "**Error: unable to open " << file_name << endl;
        return 0;
    } else {
        int line = 0;
        while (!infile.eof()) {
            if (line == 0) {
                //If on first line, get line and ignore
                string full_line;
                getline(infile, full_line);
            } else if (line == 1) {
                //If on second line, get count
                string full_line;
                getline(infile, full_line);
                return stoi(full_line.substr(full_line.find(": ") + 2));
            }
            line++;
        }
    }
    return 0;
}

// parse_movies : Parses a given movie file into movies struct array
void parse_movies(string& fileMovies, movie_struct* movies, int& movie_count) {
    ifstream infile(fileMovies);
    if (!infile.good()) {
        cout << "**Error: unable to open " << fileMovies << endl;
    } else {
        int line = 0;
        while (!infile.eof() && ((line-2) < movie_count)) {
            if (line == 0 || line == 1) {
                //If on first or second line, get line and ignore
                string full_line;
                getline(infile, full_line);
            } else {
                infile >> movies[line-2].movie_id;
                infile >> movies[line-2].year;
                string unformatted_title;
                getline(infile, unformatted_title);
                movies[line-2].title = unformatted_title.substr(1);
            }
            line++;
        }
    }
}

// sort_movies_by_id : Sorts movies by id, stores to movies array
void sort_movies_by_id(movie_struct* movies, int& movie_count) {
    for (int i = 0; i < movie_count-1; i++) {
        // Find index of smallest remaining element by movie_id
        int indexSmallest = i;
        for (int j = i + 1; j < movie_count; j++) {
            if (movies[j].movie_id < movies[indexSmallest].movie_id) {
                indexSmallest = j;
            }
        }
        // Swap movies[i] and movies[indexSmallest]
        int temp_movie_id = movies[i].movie_id;
        int temp_year = movies[i].year;
        string temp_title = movies[i].title;

        movies[i].movie_id = movies[indexSmallest].movie_id;
        movies[i].year = movies[indexSmallest].year;
        movies[i].title = movies[indexSmallest].title;

        movies[indexSmallest].movie_id = temp_movie_id;
        movies[indexSmallest].year = temp_year;
        movies[indexSmallest].title = temp_title;
    }
}

// sort_movies_by_title : Sorts movies by title, stores to movies array
void sort_movies_by_title(movie_struct* movies, int& movie_count) {
    for (int i = 0; i < movie_count-1; i++) {
        // Find index of smallest remaining element by title
        int indexSmallest = i;
        for (int j = i + 1; j < movie_count; j++) {
            if (movies[j].title < movies[indexSmallest].title) {
                indexSmallest = j;
            }
        }
        // Swap movies[i] and movies[indexSmallest]
        int temp_movie_id = movies[i].movie_id;
        int temp_year = movies[i].year;
        string temp_title = movies[i].title;

        movies[i].movie_id = movies[indexSmallest].movie_id;
        movies[i].year = movies[indexSmallest].year;
        movies[i].title = movies[indexSmallest].title;

        movies[indexSmallest].movie_id = temp_movie_id;
        movies[indexSmallest].year = temp_year;
        movies[indexSmallest].title = temp_title;
    }
}

// print_movies_array : Prints movies array to console
void print_movies_array(movie_struct* movies, int& movie_count) {
    for (int i = 0; i < movie_count; i++) {
        cout << movies[i].movie_id << " " << movies[i].year << " '" << movies[i].title << "'" << endl;
    }
}

// Main loop
int main() {
    // Gather and store filenames from user
    string fileMovies;
    string fileReviews;
    cout << "Movies filename> ";
    cin >> fileMovies;
//    cout << "movies0.txt" << endl;
//    fileMovies = "movies0.txt";

    // Create configuration values
    int movie_count = get_count(fileMovies);
    cout << "**Number_Movies: " << movie_count << endl;
//    int review_count = get_count(fileReviews);
//    cout << "**Number_Reviews: " << review_count << endl;

    // Dynamically create an array of movies and reviews
    movie_struct* movies;
    movies = new movie_struct[movie_count];
//    review_struct* reviews;
//    reviews = new review_struct[review_count];

    // Run parse_movies function
    parse_movies(fileMovies, movies, movie_count);

    // Return first and last movie data
    cout << "**First movie: " << movies[0].movie_id << " " << movies[0].year << " '" << movies[0].title << "'" << endl;
    cout << "**Last movie: " << movies[movie_count-1].movie_id << " " << movies[movie_count-1].year << " '" << movies[movie_count-1].title << "'" << endl;

    // Sort and print movies by id and by title
    cout << "**MOVIES BY ID**" << endl;
    sort_movies_by_id(movies, movie_count);
    print_movies_array(movies, movie_count);
    cout << "**MOVIES BY TITLE**" << endl;
    sort_movies_by_title(movies, movie_count);
    print_movies_array(movies, movie_count);

    // Print **Done**
    cout << "**Done**" << endl;

    // Clear arrays and exit
    delete[] movies;
//    delete[] reviews;
    return 0;
}
