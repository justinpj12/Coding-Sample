// Assignment #6
// Programmer: Justin Jackson
// ASU Email Address: justin.p.jackson@asu.edu
// Description: Methods for Binary Search Tree with ZipCode Class as nodes

#include <iostream> //to use cout
#include <string> //to use strings

using namespace std;

//ZipInfo represents a combination of city, state, and zip code
class ZipInfo
 {
  private:
    string city, state, zipcode;
    ZipInfo * left, * right, * parent;

  public:
    //The following three functions are constructors
    ZipInfo()
     {
      city = "?";
      state = "?";
      zipcode = "?";
      parent = NULL;
      left = NULL;
      right = NULL;
     }

    ZipInfo(string city1, string state1, string zip1)
     {
      zipcode = zip1;
      city = city1;
      state = state1;
      parent = NULL;
      left = NULL;
      right = NULL;
     }
     ZipInfo(string city1, string state1)
     {
         zipcode = "?";
         city = city1;
         state = state1;
         parent = NULL;
         left = NULL;
         right = NULL;
     }
    //The following functions are accessor functions
    ZipInfo * getLeft()
     {
      return left;
     }

    ZipInfo * getRight()
     {
      return right;
     }

    ZipInfo * getParent()
     {
      return parent;
     }

    string getCity()
     {
         return city;
     }
    string getState()
     {
         return state;
     }
    string getZip()
     {
         return zipcode;
     }
    //The following three functions are mutator functions
    void setLeft(ZipInfo * other)
     {
       left = other;
     }

    void setRight(ZipInfo * other)
     {
       right = other;
     }

    void setParent(ZipInfo * other)
     {
       parent = other;
     }

    //The print method prints the city, state, and zip code
    void print()
     {
         cout << city << " in " << state << " with zipcode of " << zipcode << endl << endl;
     }

   //you can add more functions

 }; //end of ZipInfo class


//class BinarySearchTree will contains cities
class BinarySearchTree
 {
  private:
     ZipInfo * root;

  public:
     BinarySearchTree();
     ~BinarySearchTree();
     bool isEmpty();
     void inOrderTreePrint();
     void preOrderTreePrint();
     void postOrderTreePrint();
     void inOrderTreeWalk(ZipInfo *);
     void preOrderTreeWalk(ZipInfo *);
     void postOrderTreeWalk(ZipInfo *);
     void transplant(ZipInfo *, ZipInfo *, ZipInfo *);
//      void transplant(ZipInfo * root, ZipInfo * current, ZipInfo * child);
     ZipInfo * treeMinimum();
     ZipInfo * treeMaximum();
     ZipInfo * treeSuccessor(string,string);
     ZipInfo * treePredecessor(string,string);
     ZipInfo * treeSearch(string, string);
     bool treeInsert(string,string,string);
     ZipInfo * treeDelete(string,string);
 };

//The constructor initialize the root to be NULL
BinarySearchTree::BinarySearchTree()
 {
  root = NULL;
 }

//The destructor should delete all nodes in the tree
//and perform garbage collections starting from leaves (bottom-up order).
//The destructor should also print “The number of nodes deleted: X”
//where X is the number of nodes deleted
BinarySearchTree::~BinarySearchTree()//Destructor
 {
    int x = 0;
    ZipInfo * node = root;

    if (isEmpty()) {//If the tree is empty nothing to delete.
        cout << "Zero nodes deleted.\n";
    return;
    }

    //While theres nodes on the tree
    while (node != NULL) {
        if (node->getLeft() != NULL){ //if left child getleft
            node = node->getLeft();
        }
        else if (node->getRight() != NULL){ //if right child getRight
            node = node->getRight();
        }
        else { // no children
            //if node is left of it's parent make left null
            if ((node->getParent() != NULL) && (node == node->getParent()->getLeft())) {
                node->getParent()->setLeft(NULL);
            }
            //if node is right of it's parent make right null
            if (node->getParent() != NULL && node == node->getParent()->getRight()) {
                node->getParent()->setRight(NULL);
            }\
            //delete node and getParent for next node
            x++;
            node = node->getParent();
            delete node;
        }
    }
    std::cout << "The number of nodes deleted: " << x << endl;

 }


//isEmpty() return true if the tree is empty, false otherwise
bool BinarySearchTree::isEmpty()
 {
   if (root == NULL)
    return true;
   else
    return false;
 }

//prints all nodes using in-order starting from root
//and in-order walk function
void BinarySearchTree::inOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    inOrderTreeWalk(root);
    cout << "\n";
   }
 }

//it prints all nodes using pre-order starting from root
//and pre-order walk function
void BinarySearchTree::preOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    preOrderTreeWalk(root);
    cout << "\n";
   }
 }

//it prints all nodes using post-order starting from root
//and post-order walk
void BinarySearchTree::postOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    postOrderTreeWalk(root);
    cout << "\n";
   }
 }

//print nodes under the parameter x using in-order
void BinarySearchTree::inOrderTreeWalk(ZipInfo * x)
 {
    //calls itself inorder most left then right
    if (x != NULL) {
        inOrderTreeWalk(x->getLeft());
        x->print();
        inOrderTreeWalk(x->getRight());
    }
 }

//print nodes under the parameter x using pre-order
void BinarySearchTree::preOrderTreeWalk(ZipInfo * x)
 {
     //calls itself preorder goes left then right
     if (x != NULL) {
         x->print();
         preOrderTreeWalk(x->getLeft());
         preOrderTreeWalk(x->getRight());
      }
 }

//print nodes under the parameter x using post-order
void BinarySearchTree::postOrderTreeWalk(ZipInfo * x)
 {
    //calls itself inorder most right then left
     if (x != NULL) {
         postOrderTreeWalk(x->getLeft());
         postOrderTreeWalk(x->getRight());
         x->print();
         }
 }

//Using the string parameter of city and state, it returns
//its zipcode information (node) within the tree if found
//return NULL if not found
ZipInfo * BinarySearchTree::treeSearch(string city, string state)
 {
     ZipInfo * node = root;
     //While the tree's node is not empty.
     while (node != NULL) {
         if (state == node->getState()) {
             if (city == node->getCity()) {
                 return node; //if city and state match return node
             }
             //if state match check for cities
             else if (city < node->getCity()) {
                 node = node->getLeft();
             }
             else if (city > node->getCity()) {
                 node = node->getRight();
             }
         }
         //set node to find matching state
         else if (state < node->getState()) {
             node = node->getLeft();
         }
         else {
             node = node->getRight();
         }
     }

     return NULL; //if not found return null
 }


//Searches and returns the node with the minimum key within the tree
ZipInfo * BinarySearchTree::treeMinimum()
 {
     ZipInfo * node = root;
     if (node == NULL) {
         return NULL;
     }
    //Goes to lowest left node which should be lowest key
     while (node->getLeft() != NULL) {
         node = node->getLeft();
     }
     return node;
 }

//Searches and returns the node with the maximum key within the tree
ZipInfo * BinarySearchTree::treeMaximum()
 {
     ZipInfo * node = root;
     if (node == NULL) {
         return NULL;
     }
    //Goes to lowest right node which should be largest key
     while (node->getRight() != NULL) {
         node = node->getRight();
     }
     return node;
 }

//Searches and returns the successor of the parameters city and state
ZipInfo * BinarySearchTree::treeSuccessor(string city, string state)
 {
     //Node set to the return value of the treeSearch function.
     ZipInfo * node = treeSearch(city, state);

     if (node == NULL) {
         return NULL;      //If the node not found return null
     }
     else {
         if (node->getRight() != NULL) {   //if right child
             node = node->getRight();
             while (node->getLeft() != NULL) {
                 node = node->getLeft();
             }
                 return node; //return node, which is the successor.
         }
         else {
            // node turned into parent until parent is successor.
             ZipInfo * parent = node->getParent();
             while ((parent != NULL) && (node == parent->getRight())) {
                 node = parent;
                 parent = parent->getParent();
             }
             return parent;
         }
     }
 }

//Searches and returns the predecessor of the parameter city and state
ZipInfo * BinarySearchTree::treePredecessor(string city, string state)
 {
     //Node set to the return value of the treeSearch function.
     ZipInfo * node = treeSearch(city, state);
     if (node == NULL) {
         return NULL;    //If the node not found return null
      }
     else {
         if (node->getLeft() != NULL) {   //if left child
             node = node->getLeft();
             while (node->getRight() != NULL) {
                 node = node->getRight();
             }
             return node;   //return node, which is the predecessor.
         }
         else {
            // node turned into parent until parent is predecessor.
             ZipInfo * parent = node->getParent();
             while (parent != NULL && node == parent->getLeft()) {
                 node = parent;
                 parent = parent->getParent();
             }
             return parent;
         }
     }
 }

//It inserts the parameter city, state zipcode
//and returns tree if successful, false otherwise
bool BinarySearchTree::treeInsert(string city, string state, string zipcode)
 {
     bool leftChild = false;
     ZipInfo * node = root;
     ZipInfo * previous = node;
     while (node != NULL) {
         if (state == node->getState()) {
             if (city == node->getCity()) {
                 return false;
             }
             else if (city < node->getCity()) {
                 leftChild = true;
                 previous = node;
                 node = node->getLeft();
                 }
             else {
                 leftChild = false;
                 previous = node;
                 node = node->getRight();
                 }
         }
         else if (state < node->getState()) {
             leftChild = true;
             previous = node;
             node = node->getLeft();
         }
         else {
             leftChild = false;
             previous = node; 
			 node = node->getRight(); 
		}
     }
     ZipInfo *newNode = new ZipInfo(city, state, zipcode);

     if (isEmpty()) {
         root = newNode;
         }
     else if(node != root) {
         newNode->setParent(previous);
         if (leftChild)
             previous->setLeft(newNode);
         else
            previous->setRight(newNode);
     }
     return true;
 }


//It deletes the node specified by the parameters city and state
//and deletes and returns the node if it is found in the tree
//It returns NULL if not found
ZipInfo * BinarySearchTree::treeDelete(string city, string state)
 {
    //Node set to the return value of the treeSearch function.
     ZipInfo * current = treeSearch(city, state);
     if (current == NULL) {
         return NULL;
         }
     else {
         if (current->getLeft() == NULL) {
             transplant(root, current, current->getRight());
             }
         else if (current->getRight() == NULL) {
             transplant(root, current, current->getLeft());
             }
         else {
             ZipInfo * successor = treeSuccessor(current->getCity(), current->getState());
             if (successor->getParent() != current) {
                 transplant(root, successor, successor->getRight());
                 successor->setRight(current->getRight());
                 successor->getRight()->setParent(successor);
                 }
             transplant(root, current, successor);
             successor->setLeft(current->getLeft());
             successor->getLeft()->setParent(successor);
         }
     }
     delete current;
     return current;
 }

//Transplant used for deleting node without loss of other part of tree.
void BinarySearchTree::transplant(ZipInfo * root, ZipInfo * current, ZipInfo * child)
{
    if (current->getParent() == NULL) {
        root = child;
        }
    else if (current == current->getParent()->getLeft()) {
        current->getParent()->setLeft(child);
        }
    else {
        current->getParent()->setRight(child);
        }
    if (child != NULL) {
        child->setParent(current->getParent());
        }
}

