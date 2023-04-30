#include <cstdlib>
#include <string>
#include "Tree.h"
#include <iostream>
#include <sstream>
using std::cout; using std::endl;
using std::stringstream;
//constructor, sets all pointer value to nullptr
template <typename T>
Tree<T>::Tree(T ch): data(ch), kids(NULL), sibs(NULL), prev(NULL) {}

template <typename T>
Tree<T>::~Tree() {
    if (this->kids){
        delete this->kids; //recursive call to the destructor
    }
    if (this->sibs){
        delete this->sibs; //recursive call to the destructor
    }
}


/*
*The add child function creates a new Tree node and calls the second adChild function
*/
template <typename T>
bool Tree<T>::addChild(T ch) { //add after
    Tree<T> * tree = new Tree<T>(ch);
    return addChild(tree);
}
/*
This works recursively to add a child to the Tree, returns true if it was successful and false otherwise
*/
template <typename T>
bool Tree<T>::addChild(Tree<T> *root){ 
    if (this->kids == NULL){
        this->kids = root;
        root->prev = this;
        return true;
    }
    else if (root->data == this->kids->data){
        delete root;
        return false;
    }
    else if (root->data < this->kids->data){
        this->kids->prev = root;
        root->sibs = this->kids;
        this->kids = root;
        root->prev = this;
        return true;
    }
    else {
        return this->kids->addSibling(root);
    }
}
/*
Adds a sibling by first creating a new Tree node and passing it to the second addSibling function 
*/
template <typename T>
bool Tree<T>::addSibling(T ch){
    Tree<T> * tree =new Tree<T>(ch);
    return addSibling(tree);
}

/*
This function returns true if a sibling was succesfully added and false otherwise
*/
template <typename T>
bool Tree<T>::addSibling(Tree<T> *root){
    if (this->prev == NULL){
        delete root;
        return false;
    }
    if (this->sibs == NULL){
        if (this->data == root->data){
            delete root;
            return false;
        } 
        this->sibs = root;     
        root->prev = this;
        return true;
    }
    else if (this->sibs->data == root->data){
        delete root;
        return false;
    }
    else if (this->sibs->data > root->data){
        this->sibs->prev = root;
        root->sibs = this->sibs;
        this->sibs = root;
        root->prev = this->sibs;
        return true;
    }
    else {
        return this->sibs->addSibling(root);
    }
}

//returns a string representation of the data
template <typename T>
std::string Tree<T>::toString(){
    std::stringstream output;
    output << this->data;
    output << '\n';
    if (this->kids){
        output << this->kids->toString();
    }
    if (this->sibs){
        output << this->sibs->toString();
    }
    return output.str();
}

//overloaded ^ operator that does the same thing as the addChild function
template <typename T>
Tree<T>& Tree<T>::operator^(Tree<T>& rt){ //check for mem leaks
    Tree * first = this;
    Tree * child = &rt;
    first->addChild(child);
    return *first;
}
//overloaded << operator that displays the value returned by the toSting() funciton
template <typename E>
std::ostream& operator<<(std::ostream& os, Tree<E>& rt){
    std::string output = rt.toString();
    os << output;
    return os;
}

