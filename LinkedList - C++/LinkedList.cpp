// Assignment #1
// Name:       Justin Jackson
// ASU Email Address:   justin.p.jackson@asu.edu
// Description: This program displays a menu of choices to a user
//        and performs the chosen task. It will keep asking a user to
//        enter the next choice until the choice of 'Q' (Quit) is entered.

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

void printMenu();

int main()
   {
       // local variables, can be accessed anywhere from the main method
       char input1 = 'Z';
       string inputInfo;
       string firstName, lastName;
       double amount;
       int index;
       string line;
       bool success = false;

       // instantiate a Linked List object
       LinkedList * list1 = new LinkedList();

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
             case 'A':   //Add Customer
               cout << "Please enter a customer information:\n";
               cout << "Enter a first name:\n";
               getline(cin, firstName);

               cout << "Enter a last name:\n";
               getline(cin, lastName);

               cout << "Enter some cash amount:\n";
               cin >> amount;
               cin.ignore(20, '\n'); //flush the buffer

               cout << "Enter an index to add:\n";
               cin >> index;
               cin.ignore(20, '\n'); //flush the buffer

               success = list1->addElement(firstName, lastName, amount, index);

               if (success == true)
                cout << "The customer " << firstName << " " << lastName << " added\n";
               else
                cout << "The index is out of bounds\n";
               break;
             case 'D':   //Display Courses
               list1->printList();
               break;
             case 'Q':   //Quit
               delete list1;
               break;
             case 'R':  //Remove Customer
               cout << "Please enter a customer to remove:\n";
               cout << "Enter a first name:\n";
               getline(cin, firstName);

               cout << "Enter a last name:\n";
               getline(cin, lastName);

               success = list1->removeElement(firstName, lastName);
               if (success == true)
                cout << "The customer " << firstName << " " << lastName << " removed\n";
               else
                cout << "The customer " << firstName << " " << lastName << " does not exist\n";
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
     cout << "A\t\tAdd Customer\n";
     cout << "D\t\tDisplay Customers\n";
     cout << "Q\t\tQuit\n";
     cout << "R\t\tRemove Customer\n";
     cout << "?\t\tDisplay Help\n\n";
  }


