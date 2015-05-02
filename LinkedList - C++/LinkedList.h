// Assignment #1
// Name:    Justin Jackson
// ASU Email Address:   justin.p.jackson@asu.edu
// Description: LinkedList of customers ordered by insertion sort of given index

#include <iostream> //to use cout
#include <string> //to use strings

using namespace std;

//struct Customer represents some customer information
struct Customer
 {
  string firstName;
  string lastName;
  double amount;
  int index;
  struct Customer * next;
 };

//class LinkedList will contains a linked list of customers
class LinkedList
 {
  private:
     struct Customer * head;

  public:
     LinkedList();
     ~LinkedList();
     bool addElement(string firstname, string lastname, double amt, int index);
     bool removeElement(string firstname, string lastname);
     void printList();
 };

//Constructor
//It sets head to be NULL to create an empty linked list
LinkedList::LinkedList()
 {
   head = NULL;
 }

//Destructor
//Description: ~LinkedList() loops to delete linked list and displays the number of nodes removed
LinkedList::~LinkedList()
 {
    struct Customer *next = NULL, *node = head;
    int counter = 0;
    while(node != NULL){
        next = node->next;
        delete node;
        node = next;
        counter++;
    }
    cout << "The number of deleted customers is: " << counter++ << "\n";
    delete next, node, head;
 }

//Description: addElement(string, string, double, int) returns true if new customer added at given index
bool LinkedList::addElement(string firstname, string lastname, double amt, int index)
 {
    struct Customer *prev, *next, *node = new Customer();
    node->amount = amt;
    node->index = index;
    node->firstName = firstname;
    node->lastName = lastname;
    node->next = NULL;
    if (node->index < 0){
        delete node;
        return false;
    }
    //Insertion sort algorithm
    if (head==NULL)
        head = node; //empty list case
    else{
        prev = NULL;
        next = head;
        while(next != NULL && next->index <= index){ //loop for insertion new nodes to existing list
            prev = next;
            next = next->next;
        }
        if (next == NULL) //new node after nodes already on list
            prev->next = node;
        else{
            if (prev != NULL){ //new node between nodes already on list
                node->next = prev->next;
                prev->next = node;
            }else{ //new node ahead of nodes already on list
                node->next = head;
                head = node;
            }
        }
    }
    return true;
 }

//Description: removeElement(string,string) returns true if givrn customer is found and removed otherwise returns false
bool LinkedList::removeElement(string firstname, string lastname)
 {
    struct Customer *prev, *node = head;
    while (node != NULL){
        if((firstname.compare(node->firstName) != 0) || (lastname.compare(node->lastName) != 0)){
            prev = node;
            node = node->next;
        }else{
            if (node != head)
                prev->next = node->next;
            else
                head = head->next;
            delete node;
            return true;
        }
   }
   return false;
 }

//Description: printList() displays customer list
void LinkedList::printList()
 {
   struct Customer *node = head;
   while(node != NULL){
        cout << "Customer Name: " << node->firstName << " " << node->lastName;
        cout << "\nBalance Amount: $" << node->amount << " dollars\n\n";
        node = node->next;
   }
 }

