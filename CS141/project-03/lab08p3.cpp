//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 03 - Lab 08 Part 2 - 10/12/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

//
// Program to input movie data and reviews, store into an array of
// struct, and then allow the user to search this data by movie
// id, movie title, and highest-rated movie.
//
// ???
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 03, part 03: Solution
//

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>   // isdigit

using namespace std;

struct Movie
{
    int    MovieID;
    int    Year;
    string Title;
    int    Reviews;   // # of reviews for this movie
    int    Ratings;   // sum of all the ratings (1..5)
    double AvgRating;
    int Num5StarReviews;
};


//
// isInteger
//
// Returns true if s is an integer string such as "123", and
// returns false if not.
//
// NOTE: if s starts with "+" or "-", e.g. "-123", the function
// currently returns false.
//
bool isInteger(string s)
{
    if (s.length() == 0)  // it's empty!
    {
        return false;
    }

    for (char c : s)  // for each char in s, make sure it's a digit:
    {
        if (!isdigit(c))  // not a digit, so not an integer:
        {
            return false;
        }
    }

    // if get here, all the characters were digits!
    return true;
}


//
// sortByMovieID
//
// Given an array of N movies, sorts the movies into
// ascending order by movie id using selection sort.
//
void sortByMovieID(Movie* movies, int numMovies)
{
    //
    // selection sort:
    //
    for (int i = 0; i < numMovies - 1; i++)  // select the smallest and swap into ith position:
    {
        int minIndex = i;

        for (int j = i + 1; j < numMovies; j++)  // search for a smaller value:
        {
            if (movies[j].MovieID < movies[minIndex].MovieID)  // smaller!
            {
                minIndex = j;
            }
        }//for

        // swap smallest into ith position:
        if (minIndex != i)
        {
            Movie  temp;

            temp = movies[i];
            movies[i] = movies[minIndex];
            movies[minIndex] = temp;
        }
    }//for

    return;
}

//
// sortByMovieTitle
//
// Given an array of N movies, sorts the movies into
// ascending order by movie title using selection sort.
//
void sortByMovieTitle(Movie* movies, int N)
{
    //
    // selection sort:
    //
    for (int i = 0; i < N - 1; i++)  // select the smallest and swap into ith position:
    {
        int minIndex = i;

        for (int j = i + 1; j < N; j++)  // search for a smaller value:
        {
            if (movies[j].Title < movies[minIndex].Title)  // smaller!
            {
                minIndex = j;
            }
        }//for

        // swap smallest into ith position:
        if (minIndex != i)
        {
            Movie  temp;

            temp = movies[i];
            movies[i] = movies[minIndex];
            movies[minIndex] = temp;
        }
    }//for

    return;
}


//
// outputMovie
//
// Outputs a movie to the console: id, year, title, etc.
//
void outputMovie(Movie m)
{
    cout << m.MovieID << " "
         << m.Year << " "
         << "'" << m.Title << "' "
         << m.Reviews << " reviews "
         << m.AvgRating << " avg rating (" << m.Num5StarReviews << ")" << endl;
}


//
// outputMovies
//
// Given an array of N movies, outputs each movie to the console.
//
void outputMovies(Movie* movies, int N)
{
    for (int i = 0; i < N; i++)
    {
        outputMovie(movies[i]);
    }
}


//
// computeAvgRatings
//
// Given an array of N movies, computes the average rating
// based on the ratings sum and # of reviews.  If a movie
// has no reviews, it's average is set to 0.
//
void computeAvgRatings(Movie* movies, int N)
{
    for (int i = 0; i < N; i++)
    {
        double avg = 0.0;

        if (movies[i].Reviews > 0)  // we have at least 1 review:
        {
            avg = static_cast<double>(movies[i].Ratings) / movies[i].Reviews;
        }

        movies[i].AvgRating = avg;
    }
}


//
// findByID
//
// Given an array of N movies, performs a linear search
// for a movie with an id that matches the given id.
// Returns the index of this movie if found, -1 if not
// found.
//
// NOTE: it is assumed movie ids are unique, so we only
// search for the first match.
//
int findByID(Movie* movies, int N, int id)
{
    for (int i = 0; i < N; i++) {
        if (movies[i].MovieID == id) {
            return i;
        }
    }
    return -1;
}

//
// findByPartialTitleMatch
//
// Given an array of N movies, performs a linear search
// for a movie whose title contains the given substring.
// Returns the index of the movie if found, -1 if not
// found.
//
// NOTE: since multiple movies might match, the last
// argument "searchStartIndex" controls where to start the
// search.  Pass 0 to start the search at the beginning
// of the array; if find a match at position i and want
// to search for another match, pass i+1.
//
int findByPartialTitleMatch(Movie* movies, int N, string substring, int searchStartIndex)
{
    for (int i = searchStartIndex; i < N; i++)
    {
        if (movies[i].Title.find(substring) != string::npos)  // found a match!
        {
            return i;
        }
    }

    // if get here, not found:
    return -1;
}


//
// findHighestRated
//
// Given an array of N movies, returns the index of the movie with
// the highest average rating.  If there's a tie, the movies with
// the smaller index is returned.
//
int findHighestRated(Movie* movies, int N)
{
    int maxIndex = 0;  // assume 1st movie has highest rating:

    for (int i = 1; i < N; i++)  // check all the other movies:
    {
        if (movies[i].AvgRating > movies[maxIndex].AvgRating)  // found a higher rating;
        {
            maxIndex = i;
        }
    }

    // when get here, movie with highest rating is maxIndex:
    return maxIndex;
}


//
// readMovies
//
// Given the name of a file of movie data, we read each movie
// and store the id, year, and title into an array of Movie struct.
// This array is dynamically-allocated, and a pointer to this
// array is returned; the # of movies is returned via the reference
// parameter.
//
// NOTE: the caller needs to free this array before the program ends.
//
Movie* readMovies(string filename, int& numMovies)
{
    ifstream moviesfile(filename);
    string   header;

    //
    // movies file:
    //
    // first line is the column header: ID YEAR TITLE
    getline(moviesfile, header);

    // second line has # of movies: NUMBER_MOVIES: 252
    string word;
    moviesfile >> word;
    moviesfile >> numMovies;

    cout << "**Number_Movies: " << numMovies << endl;

    //
    // dynamically-allocated array for movie data:
    //
    Movie* movies;
    movies = new Movie[numMovies];

    //
    // read movie data into arrays, each line has the format
    // ID YEAR TITLE
    //
    int     id, year;
    string  title;
    int     i = 0;
    int     movieCount = 0;

    while (!moviesfile.eof())
    {
        moviesfile >> id;
        moviesfile >> year;
        getline(moviesfile, title);

        if (!moviesfile.fail())  // we successfully input a movie:
        {
            movies[i].MovieID = id;
            movies[i].Year = year;
            movies[i].Title = title.substr(1);  // trim off 1 space in the front:

            i++;
            movieCount++;
        }
    }

    //
    // sanity check: did we read all the movies properly?
    //
    if (movieCount != numMovies)  // something is wrong:
    {
        cout << "**WARNING: internal movie count != number of movies?" << endl;
    }

    //
    // return movies array (pointer) back to main:
    //
    return movies;
}


//
// readReviews
//
// Given the name of a file of review data, we read each review
// and match that data with the correct movie.  The sum of the
// ratings, and the # of reviews, are aggregated into the movies
// array.
//
// NOTE: reviews not associated with a movie are ignored.
//
void readReviews(string filename, Movie* movies, int numMovies)
{
    ifstream reviewsfile(filename);
    string   header, word;

    //
    // reviews file:
    //
    // first line is the column header: REVIEWID MOVIEID RATING
    getline(reviewsfile, header);

    // second line has # of reviews: NUMBER_REVIEWS: 123981
    int numReviews;
    reviewsfile >> word;
    reviewsfile >> numReviews;

    cout << "**Number_Reviews: " << numReviews << endl;

    //
    // read the reviews and aggregate the review data into the
    // movies array:
    //

    // initialize the counts and sums before we start:
    for (int i = 0; i < numMovies; i++)
    {
        movies[i].Reviews = 0;
        movies[i].Ratings = 0;
        movies[i].Num5StarReviews = 0;
    }

    int reviewCount = 0;

    while (!reviewsfile.eof())  // read each review...
    {
        int reviewid, movieid, rating;

        reviewsfile >> reviewid;
        reviewsfile >> movieid;
        reviewsfile >> rating;

        if (!reviewsfile.fail())  // we successfully input a review:
        {
            //
            // find the movie and update review data:
            //
            // Note: there may be reviews movies that don't exist,
            // so we just ignore those reviews.
            //
            int index;

            index = findByID(movies, numMovies, movieid);
            if (index >= 0) // found movie:
            {
                movies[index].Reviews++;
                movies[index].Ratings += rating;
                if (rating == 5) {
                    movies[index].Num5StarReviews += 1;
                }
            }

            reviewCount++;
        }
    }

    if (reviewCount != numReviews)  // something is wrong:
    {
        cout << "**WARNING: internal review count != number of reviews?" << endl;
    }
}

//
// countMoviesInRange
//
int countMoviesInRange(Movie* movies, int numMovies, double min, double max) {
    int count = 0;
    for (int i = 0; i < numMovies; i++) {
        if (min <= movies[i].AvgRating && movies[i].AvgRating <= max) {
            count++;
        }
    }
    return count;
}


// ################################################################################
// main
//
int main()
{
    //
    // Prompt user for file names, and check that this exist:
    //
    string moviesfilename, reviewsfilename;

    cout << "Movies filename> ";
    cin >> moviesfilename;
    cout << "Reviews filename> ";
    cin >> reviewsfilename;

    ifstream  moviesfile(moviesfilename);

    if (!moviesfile.good())
    {
        cout << "**Error: unable to open movies file '" << moviesfilename << "'" << endl;
        return 0;
    }

    ifstream  reviewsfile(reviewsfilename);

    if (!reviewsfile.good())
    {
        cout << "**Error: unable to open reviews file '" << reviewsfilename << "'" << endl;
        return 0;
    }

    //
    // we know the input files exist, let's input the movie and
    // review data.  The reviews will be aggregated into the
    // movie data, which is stored in an array of Movie struct.
    //
    Movie* movies;
    int    numMovies;

    movies = readMovies(moviesfilename, numMovies);

    readReviews(reviewsfilename, movies, numMovies);

    //
    // now that review data has been aggregated into the movies
    // array, let's run through the array and compute the average
    // ratings for each movie:
    //
    computeAvgRatings(movies, numMovies);

    //
    // Now we interact with the user and allow them to
    //   1. find by movie id
    //   2. find by word appearing in movie title
    //   3. output highest-rated movie
    //   4. list the movies by id and title
    //   5. quit
    //
    string cmd;

    cout << endl;
    cout << "Enter command (c min max, f id, f title, l, mp, q): ";
    cin >> cmd;

    while (cmd != "q")
    {
        if (cmd == "c")  // movies in range:
        {
            double min, max;

            cin >> min;
            cin >> max;

            cout << "# of movies in that range: " << countMoviesInRange(movies, numMovies, min, max) << endl;
        }
        else if (cmd == "mp")  // most popular movie:
        {
            int index;

            index = findHighestRated(movies, numMovies);

            outputMovie(movies[index]);
        }
        else if (cmd == "f")
        {
            string operand;
            cin >> operand;

            if (isInteger(operand))  // find by movie id:
            {
                int index = findByID(movies, numMovies, stoi(operand));

                if (index < 0)
                {
                    cout << "Movie not found..." << endl;
                }
                else
                {
                    outputMovie(movies[index]);
                }
            }
            else // find by movie title:
            {
                sortByMovieTitle(movies, numMovies);

                int index = findByPartialTitleMatch(movies, numMovies, operand, 0 /*starting index*/);
                int count = 0;

                while (index >= 0)  // while we keep finding matches:
                {
                    outputMovie(movies[index]);
                    count++;

                    index = findByPartialTitleMatch(movies, numMovies, operand, index + 1);
                }

                if (count == 0)  // no matches:
                {
                    cout << "Movie not found..." << endl;
                }
            }
        }
        else if (cmd == "l")  // list by id and then by title:
        {
            sortByMovieID(movies, numMovies);

            cout << "**MOVIES BY ID**" << endl;

            outputMovies(movies, numMovies);

            sortByMovieTitle(movies, numMovies);

            cout << "**MOVIES BY TITLE**" << endl;

            outputMovies(movies, numMovies);
        }
        else  // unknown command:
        {
            cout << "**Error, unknown command, ignored..." << endl;
        }

        cout << endl;
        cout << "Enter command (c min max, f id, f title, l, mp, q): ";
        cin >> cmd;
    }


    //
    // Done:
    //
    cout << "**Done**" << endl;

    delete[] movies;

    return 0;
}


