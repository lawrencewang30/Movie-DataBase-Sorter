#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include "movies.h"
using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){ //argc = number of arguments, argv = each argument, use this for sorting algorithm in for loop
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
  // Create an object of a STL data-structure to store all the movies
  Movies Movies, MoviesPrefix;

  string line, movieName;
  double movieRating;
  // Read each file and store the name and rating
  while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        // Use std::string movieName and double movieRating
        // to construct your Movie objects
        // cout << movieName << " has rating " << movieRating << endl;
        // insert elements into your data structure
        Movies.insert(movieName, movieRating);
  }
  /* log(n) since insertion of bst depends on amount of data added */
  /* O(n) space complexity since n is depth of tree */

  movieFile.close();

  if (argc == 2) {
      Movies.printInOrder();
  }
  /* O(h) = 0(n) time since printing through the bst tree is based on the height of the tree (amount of data)*/
  /* O(h) = O(n) is space complexity since it has to traverse and print down nodes at depth h */
  for (int i = 0; i < (argc - 2); ++i) {
    if (Movies.contains(argv[2+i])) {
        MoviesPrefix.searchPrefix(argv[2 + i], Movies);
        cout << endl;
    } 
    /* Contains: O(h) = O(n) is worst case scenario for searching node*/
    /* O(h) = O(n) is space complexity since worst case is to traverse down height h of tree */
    /* searchPrefix: O(h) = O(m) is worst case scenario since it needs to traverse through whole tree to find movie with same prefix*/
    /* also uses printReverseOrderRating, which is O(h) = O(m)*/
    /* Space complexity also O(h) = O(m) since worst case is to traverse whole tree to find matching prefix*/
    /* and printing the tree requires the same steps */
    else {
        cout << "No movies found with prefix " << argv[2 + i] << endl;
        cout << endl;
    }
  }
  

  //  For each prefix,
  //  Print the highest rated movie with that prefix if it exists.
  for (int i = 0; i < (argc - 2); ++i) {
      if (Movies.contains(argv[2+i])) {
          MoviesPrefix.findGreatestRating(argv[2 + i], Movies);
      }
  }
  /* Contains: O(h) = O(n) is worst case scenario for searching node*/
  /* Space complexity is O(h) = O(n) since worst case for search is traverse whole height of tree */
  /* findGreatestRating: uses searchPrefix function, which is O(h) = O(m) time. Helper function best/worst case is O(h) time*/
  /* since greatest rating is always at furthest right of tree*/
  /* Space complexity also O(h) = O(m) since worst case is to traverse whole tree, which is depth h of data used */

  return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

/* 3a. Time complexity: O(log(n)) + O(n) + O(n) + O(m) = O(n) + O(m) = O(h). Using the worst case scenario,*/
/* we see that linear time is the biggest one. Both O(n) and O(m) use the height of the tree, h,*/
/* so we end up with O(h) as our time complexity */ 

/* 3b. Space complexity: O(n) + O(m) = O(h). Linear time is the only Big O space complexity used.*/
/* This is because the worst case scenario is traversing through the depth h of the tree, which then utilizes*/
/* h amount of data.*/

/* 3c Both my time and space complexities were the same at O(h). Space complexity was easier to calculate since*/
/* the amount of data used was solely dependent on the height of the tree, which varied. */
/* Time complexity was a little more complicated because inserting the data was not constant (therefore log(h) time) */
/* however, the rest of the functions all used O(h) time because the worst cases for them was needing to traverse down */
/* the max depth h of the tree. While linear time is decent, I think there is a more efficient algorithm */
/* that can be implemented to solve this problem */

bool parseLine(string &line, string &movieName, double &movieRating) {
    if (line.length() <= 0) return false;
    string tempRating = "";

    bool flag = false;
    movieName = tempRating = "", movieRating = 0.0, flag = false;

    for (int i = 0; i < line.length(); i++){
        if(flag) tempRating += line[i];
        else if(line[i]==','&& line[0]!='"') flag = true;
        else {
            if(i==0 && line[0]=='"') continue;
            if(line[i]=='"'){ i++; flag=true; continue;}
            movieName += line[i];
        }
    }
    
    movieRating = stod(tempRating);
    return true;
}
