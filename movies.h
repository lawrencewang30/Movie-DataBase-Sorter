#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <string>

using namespace std;

class Movies {

    private:
        struct Node {
            string MovieName;
            double rating;
            Node *left, *right, *parent;
        
        Node(string c="", double v=0.0) : MovieName(c), rating(v), left(0), right(0), parent(0) { }
        };

        Node* root;

        bool insert(string myMovie, double myRating, Node* n);
        bool insertRating(string myMovie, double myRating, Node* n);
        void printInOrder(Node* n) const;
        void searchPrefixHelper(string prefix, Movies &b, Node* n);
        Node* getNodeFor(string prefix, Node* n) const;
        void printReverseOrderRating(Node* n) const;
        void findGreatestRatingHelper(string prefix, Node* n);
        

    public:

        Movies();     // constructor
        ~Movies();    // destructor
        void clear(Node* n);   // helper function for destructor
        bool insert(string myMovie, double myRating);
        bool insertRating(string myMovie, double myRating);
        void printInOrder() const;
        void searchPrefix(string prefix, Movies &a);
        void findGreatestRating(string prefix, Movies &a);
        bool contains(string prefix) const;
        void printReverseOrderRating() const;


};

#endif

