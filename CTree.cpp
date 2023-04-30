#include <cstdlib>
#include <string>
#include "CTree.h"
#include <iostream>
using std::cout; using std::endl;
//constructor, sets all pointer value to nullptr
CTree::CTree(char ch): data(ch), kids(NULL), sibs(NULL), prev(NULL) {}

CTree::~CTree() {
    if (this->kids){
        delete this->kids; //recursive call to the destructor
    }
    if (this->sibs){
        delete this->sibs; //recursive call to the destructor
    }
}


/*
 *The first add child function creates a new CTree node and calls the second addChild function
 */
bool CTree::addChild(char ch) { //add after
        CTree * tree = new CTree(ch);    
        return addChild(tree);
}

/*
 *This works recursively and checks through three situations in which pointers will be rearranged while adding a child.
 returns true if successful and false otherwise.
 */
bool CTree::addChild(CTree *root){ //root is the thing your adding below
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
 *The first add sibling function creates a new CTree node and calls the second function
 */
bool CTree::addSibling(char ch){
    CTree * tree =new CTree(ch);
    return addSibling(tree);
}
/*
 *This works recursively and checks through three situations in which the pointers will be rearranged to add a sibling. 
returns true if it was successful and false otherwise.
 */
bool CTree::addSibling(CTree *root){
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
//returns a string representaion of the data
std::string CTree::toString(){
    std::string output = "";
    output += this->data;
    output += '\n';
    if (this->kids){
        output += this->kids->toString();
    }
    if (this->sibs){
        output += this->sibs->toString();
    }
    return output;
}

//overloaded ^ operator that does the same thing as the addChild funtion
CTree& CTree::operator^(CTree& rt){ 
   CTree * first = this;
   CTree * child = &rt;
   first->addChild(child);
   return *first;
}

//overloaded << operator that displays the value returned by toString()
std::ostream& operator<<(std::ostream& os, CTree& rt){
    std::string output = rt.toString();
    os << output;
    return os;
}



