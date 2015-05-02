// Assignment #6
// Name:
// ASU Email Address:
// Description: This program displays a menu of choices to a user
//        and performs the chosen task. It will keep asking a user to
//        enter the next choice until the choice of 'Q' (Quit) is entered.

#include <iostream> //to use cin and cout
#include <string> //to use strings
#include <cstdlib> //to use string functions
#include "BinarySearchTree.h"

using namespace std;

void printMenu();

int main()
   {
       // instantiate a Binary Tree object
       BinarySearchTree * tree1 = new BinarySearchTree();

       char input1;
       bool success = false;
       string city, state, zipcode;
       ZipInfo * temp; //it will be used to hold a returned the input info

       printMenu();

       do  // will ask for user input
        {
           cout << "What action would you like to perform?\n";
           cin.get(input1);
           input1 = toupper(input1);
           cin.ignore(20, '\n'); //flush the buffer
           // matches one of the case statement
           switch (input1)
            {
             case 'A':   //Inorder Print
               tree1->inOrderTreePrint();               
               break;
             case 'B':   //Preorder Print
               tree1->preOrderTreePrint(); 
               break;
             case 'C':   //Postorder Print
               tree1->postOrderTreePrint(); 
               break;
             case 'D':   //Tree Minimum
               temp = tree1->treeMinimum();
               if (temp == NULL)
                 cout << "tree is empty" << endl;
               else
                {
                 cout << "The first city is ";
                 temp->print();
                 cout  << endl;
                }
               break;
             case 'E':   //Tree Maximum
               temp = tree1->treeMaximum();
               if (temp == NULL)
                 cout << "tree is empty" << endl;
               else
                {
                 cout << "The last city is ";
                 temp->print(); 
                 cout << endl;
                }
               break;
             case 'F':   //Tree Predecessor
               cout << "Please enter a city and a state to find its predecessor:\n";
               cout << "Enter a city\n";
               getline(cin,city);
               cout << "Enter a state\n";
               getline(cin,state);

               temp = tree1->treePredecessor(city, state);
               if (temp == NULL)
                 cout << "The city of " << city << " in "
                      << state << " does not have any predecessor\n";
               else
                {
                 cout << "The predecessor of the city of "
                      << city << " in "<< state << " is ";
                 temp->print();
                 cout << endl; 
                }
               break;
             case 'G':   //Tree Successor
                cout << "Please enter a city and a state to find its successor:\n";
                cout << "Enter a city\n";
                getline(cin,city);
                cout << "Enter a state\n";
                getline(cin,state);

               temp = tree1->treeSuccessor(city, state);
               if (temp == NULL)
                   cout << "The city of " << city << " in "
                   << state << " does not have any successor\n";
               else
                {
                    cout << "The successor of the city of "
                    << city << " in "<< state << " is ";
                    temp->print();
                    cout << endl;
                }
               break;
             case 'H':   //Tree Search
                cout << "Please enter a city and a state to search:\n";
                cout << "Enter a city\n";
                getline(cin,city);
                cout << "Enter a state\n";
                getline(cin,state);

               temp = tree1->treeSearch(city, state);
               if (temp != NULL)
                cout << "The city of " << city << " in "<< state << " has zipcode of "
                     << temp->getZip() << "\n";
               else
                   cout << "The city of " << city << " in "<< state
                        << " not found\n";
               break;
             case 'I':   //Tree Insert
               cout << "Please enter a city/state/zipcode to insert:\n";
               cout << "Enter a city\n";
               getline(cin,city);
               cout << "Enter a state\n";
               getline(cin,state);
               cout << "Enter a zipcode\n";
               getline(cin,zipcode);

               success = tree1->treeInsert(city,state,zipcode);

               if (success == true)
                   cout << "The city of " << city << " in "<< state << " with zipcode of "
                   << zipcode << " inserted\n";
               else
                   cout << "The city of " << city << " in "<< state << " with zipcode of "
                   << zipcode << " not inserted\n";
               break;
             case 'J':  //Tree Delete
               cout << "Please enter a city and a state to delete:\n";
               cout << "Enter a city\n";
               getline(cin,city);
               cout << "Enter a state\n";
               getline(cin,state);
                    
               temp = tree1->treeDelete(city, state);
               if (temp != NULL)
                   cout << "The city of " << city << " in "<< state << " deleted\n";
               else
                   cout << "The city of " << city << " in "<< state << " not deleted\n";
               break;
             case 'Q':   //Quit
               delete tree1;
               break;
             case '?':   //Display Menu
               printMenu();
               break;
             default:
               cout << "Unknown action\n";
               break;
            }
        } while (input1 != 'Q');

      return 0;
   }

  /** The method printMenu displays the menu to a user**/
  void printMenu()
   {
     cout << "Choice\t\tAction\n";
     cout << "------\t\t------\n";
     cout << "A\t\tInorder Print\n";
     cout << "B\t\tPreorder Print\n";
     cout << "C\t\tPostorder Print\n";
     cout << "D\t\tTree Minimum\n";
     cout << "E\t\tTree Maximum\n";
     cout << "F\t\tTree Predecessor\n";
     cout << "G\t\tTree Successor\n";
     cout << "H\t\tTree Search\n";
     cout << "I\t\tTree Insert\n";
     cout << "J\t\tTree Delete\n";
     cout << "Q\t\tQuit\n";
     cout << "?\t\tDisplay Help\n\n";
  }


