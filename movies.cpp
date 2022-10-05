#include "movies.h"
#include <string>
#include <vector>
#include <iomanip>

#include <iostream>
using namespace std;

Movies::Movies() {
    root = nullptr;
}

Movies::~Movies() {
    clear(root);
}

void Movies::clear(Node* n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

bool Movies::insert(string myMovie, double myRating) {
    if (root == nullptr) {
        root = new Node (myMovie, myRating);
        return true;
    }
    return insert(myMovie, myRating, root);
}

// recursive helper for insert function above
bool Movies::insert(string myMovie, double myRating, Node* n) {
    if (myMovie == n->MovieName) {
        return false;
    }

    if (myMovie < n->MovieName) {
        if (n->left != nullptr) {
            return insert(myMovie, myRating, n->left);
        }
        else {
            n->left = new Node (myMovie, myRating);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->right != nullptr) {
            return insert(myMovie, myRating, n->right);
        }
        else {
            n->right = new Node (myMovie, myRating);
            n->right->parent = n;
            return true;
        }
    }
}

void Movies::printInOrder() const {
    printInOrder(root);
}

void Movies::printInOrder(Node* n) const {
    if (n != nullptr) {
        printInOrder(n->left);

        cout << n->MovieName << ", " << setprecision(1) << fixed << n->rating << endl;

        printInOrder(n->right);
    }
}

void Movies::printReverseOrderRating() const {
    printReverseOrderRating(root);
}

void Movies::printReverseOrderRating(Node* n) const {
    if (n != nullptr) {
        printReverseOrderRating(n->right);

        cout << n->MovieName << ", " << setprecision(1) << fixed << n->rating << endl;

        printReverseOrderRating(n->left);
    }
}

// used for part 2
bool Movies::insertRating(string myMovie, double myRating) {
    if (root == nullptr) {
        root = new Node (myMovie, myRating);
        return true;
    }
    return insertRating(myMovie, myRating, root);
}

bool Movies::insertRating(string myMovie, double myRating, Node* n) {
    if (myRating == n->rating) {
        if (myMovie < n->MovieName) {
            if (n->right != nullptr) {
                return insertRating(myMovie, myRating, n->right);
            }
            else {
                n->right = new Node (myMovie, myRating);
                n->right->parent = n;
                return true;
            }
        }
        else {
            if (n->left != nullptr) {
                return insertRating(myMovie, myRating, n->left);
            }
            else {
                n->left = new Node (myMovie, myRating);
                n->left->parent = n;
                return true;
            }
        }
    }

    if (myRating < n->rating) {
        if (n->left != nullptr) {
            return insertRating(myMovie, myRating, n->left);
        }
        else {
            n->left = new Node (myMovie, myRating);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->right != nullptr) {
            return insertRating(myMovie, myRating, n->right);
        }
        else {
            n->right = new Node (myMovie, myRating);
            n->right->parent = n;
            return true;
        }
    }
}

void Movies::searchPrefix(string prefix, Movies &a) {
    Movies b;
    if (a.root == nullptr) {
        return;
    }
    searchPrefixHelper(prefix, b, a.root);
    b.printReverseOrderRating();
}

void Movies::searchPrefixHelper(string prefix, Movies &b, Node* n) {
    if (n != nullptr) {
        searchPrefixHelper(prefix, b, n->left);
        if (n->MovieName.substr(0, prefix.length()) == prefix) {
            b.insertRating(n->MovieName, n->rating);
        }
        searchPrefixHelper(prefix, b, n->right);
    }
}

Movies::Node* Movies::getNodeFor(string prefix, Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }

    if (n->MovieName.substr(0, prefix.length()) == prefix) {
        return n;
    }

    if (n->MovieName.substr(0, prefix.length()) < prefix) {
        return getNodeFor(prefix, n->right);
    }
    else {
        return getNodeFor(prefix, n->left);
    }
}

bool Movies::contains(string prefix) const {
    if (getNodeFor(prefix, root)) {
        return true;
    }
    else {
        return false;
    }
}

void Movies::findGreatestRating(string prefix, Movies &a) {
    Movies b;
    b.searchPrefixHelper(prefix, b, a.root);
    if (b.root == nullptr) {
        return;
    }
    findGreatestRatingHelper(prefix, b.root);
}
void Movies::findGreatestRatingHelper(string prefix, Node* n) {
    while (n->right != nullptr) {
        n = n->right;
    }
    cout << "Best movie with prefix " << prefix << " is: " << n->MovieName << " with rating " << n->rating << endl;
}


