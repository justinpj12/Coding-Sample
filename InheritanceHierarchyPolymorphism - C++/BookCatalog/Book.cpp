/***********************************************************
* Program: Online Shopping and Recommendation
* Programmers: Justin Jackson and Vanessa Averill-Edwards
* Date: 12/12/2012
************************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;

class Book { // Book Class sets book details and returns infomation
private:
    char title[256];
    int bookId;
    double price;
    int amount;

public:
    enum BookType { //enum for different book types
        book,magazine,fiction,textbook
    } bType;
    void setTitle(char *title) {strcpy(this->title, title);}
    void setBookId(int bookId) { this->bookId = bookId; }
    void setAmount(int amount) { this->amount = amount; }
    void setPrice(int price) { this->price = price; }
    char* getTitle() { return title; }
    int getBookId() { return bookId;}
    int getAmount(){ return amount;}
    double getPrice(){return price;}

    void setType(int t) {
        switch(t) {
            case 0:
                bType=book;
                break;
            case 1:
                bType=magazine;
                break;
            case 2:
                bType=fiction;
                break;
            case 3:
                bType=textbook;
                break;
            default:
                cout << "Not an acceptable Type." << endl;
                break;
        }
     }

    BookType getType(){return bType;}

    virtual void display() {
        cout << "\nBOOK" <<endl;
        cout << "Title:\t" << getTitle() << endl;
        cout << "BookID:\t" << getBookId() << endl;
        cout << "Price:\t$" << getPrice() << endl;
        cout << "Amount:\t" << getAmount() << endl;
    }
    Book(){}//empty constructor
    Book(char *title, double price, int amount, int bType){ //constructor
        static int bookIdCounter = 1;
        setTitle(title);
        setBookId(bookIdCounter);	// set Id by a self-incremental counter
			bookIdCounter++;
        setAmount(amount);
        setPrice(price);
        setType(bType);
    }

    virtual ~Book(){}//destructor
};

class Fiction : public Book { //inheritance from book class
private:
    char author[75];
public:
    void setAuthor(char *author) {strcpy(this->author, author);}
    char* getAuthor() { return author; }

    virtual void display() {
    cout << "FICTION" << endl;
    cout << "Author:\t" << getAuthor();
    Book :: display();
    }

    Fiction(char *title, double price, int amount, int bType, char *author) //constructor
    : Book(title,price,amount,bType)
    {
        setType(bType);
        setAuthor(author);
    }

    virtual ~Fiction(){}//destructor
};

class Magazine : public Book { //inheritance from book class
private:
    int issue;
public:
    void setIssue(int issue) { this->issue = issue; }
    int getIssue() { return issue;}

    virtual void display() {
    cout << "MAGAZINE" << endl;
    cout << "Issue Number:\t" << getIssue();
    Book :: display();
    }

    Magazine(char *title, double price, int amount, int bType, int issue) //constructor
    : Book(title,price,amount, bType)
    {
        setType(bType);
        setIssue(issue);
    }

    virtual ~Magazine(){}//destructor
};

class Textbook : public Book { //inheritance from book class
private:
    char author[75];
    int edition;
    char isbn[75];
public:
    void setAuthor(char *author) {strcpy(this->author, author);}
    char* getAuthor() { return author; }
    void setEdition(int edition) { this->edition = edition; }
    int getEdition() { return edition;}
    void setISBN(char *isbn) {strcpy(this->isbn, isbn);}
    char* getISBN() { return isbn; }

    virtual void display() {
    cout << "TEXTBOOK" << endl;
    cout << "Author:\t" << getAuthor() << endl;
    cout << "Edition:\t" << getEdition() << endl;
    cout << "ISBN:\t" << getISBN();
    Book :: display();
    }

    Textbook(char *title, double price, int amount, int bType, char *author, int edition, char *isbn) //constructor
    : Book(title,price,amount,bType)
    {
        setType(bType);
        setAuthor(author);
        setEdition(edition);
        setISBN(isbn);
    }
    virtual ~Textbook(){} //destructor
};

class BookNode{
private:
    Book     	*bNode;	// It contains a Book class
    BookNode	*bNext;	// pointer used to form a linked list
public:
    void setNode(Book *bNode) { this->bNode = bNode; }
    void setNext(BookNode *bNext) { this->bNext = bNext; }
    Book* getNode() { return bNode; }
    BookNode* getNext() { return bNext; }

    void copyBook(Book *cNode){
        bNode = cNode;
        bNext = NULL;
    }

    BookNode() {		// constructor
        bNode = NULL;
        bNext = NULL;
    }
} *bookHead, *cartHead, *popHead = NULL;	// declare a global pointer variable for booklist, cartlist, most popular list

int main(); //main function to run program
void readData();    //reads input file bookFile.txt and creates booklist
void writeData();   //writes booklist to file bookfile.txt
void menu();        //displays main menu for catalog options
void option(char);  //llows for choosing options from main menu
void insertMenu();  //displays sub-menu for insertion of books
void optionBook(char);  //allows for selection of insertMenu sub-menu
void addToCatalog(char*,double, int); //adds book to booklist
void addMagCatalog(char*,double,int,int); //adds Magazine to booklist
void addFictCatalog(char*,double,char*,int);//adds Fiction to booklist
void addTBookCatalog(char*,double,char*,int,char*,int);//adds Textbook to booklist
void addToCart(BookNode*); //adds any book on booklist to cartlist
void removeFromCart(BookNode*); //removes a booknode form cartlist
void removeFromList(BookNode*); //removes a booknode from booklist
void display_book_all(); //displays all the books on the booklist
void display_cart_all(); //displays all the books on the cartlist
void displayPopList();//displays all the books on the most popular list
void emptyCart(); //removes all books from cartlist after checkout
double checkOut(); //returns double of total price for all books on cartlist
void mostPopular(BookNode*); //returns a list of most popular books
void display_node(Book*, int); //displays a node used for displaying all booklist and cartlist
BookNode* searchByTitle(char*); //returns a booknode searched by books title
BookNode* searchBook(int);  //returns a booknode searched by book id

int main() {	// main function is the entry point of the program
	char m;
	readData();
	do {
		 menu();
		 cin >> m;			// enter a choice from the keyboard
		 m = tolower(m);	// convert to lower case
		 option(m);		// branch to the chosen function
	}
	while (m != 'q');			// 'q' for quit
	writeData();
	return 0;
}

void menu(){ //Displays main options of program
    cout << "\n ONLINE SHOPPING -- BOOK LISTS" << endl;
	cout << "***********************************************" << endl;
    cout <<	endl << endl << "MENU" << endl;
	cout << "----" << endl;
	cout << " d: Display the Booklist." << endl;
    cout << " h: Display the Shopping Cart." << endl;
	cout << " b: Add an Item to the Booklist." << endl;
	cout << " a: Add an Item to the Shopping Cart." << endl;
	cout << " r: Remove an Item from the Shopping Cart." << endl;
    cout << " p: Display the Most Popular Books." << endl;
    cout << " c: Check-out the Shopping Cart." << endl;
    cout << " s: Search for an Item in the Booklist." << endl;
	cout << " q: Quit the program and write a updated Booklist file." << endl;
	cout << endl << "Please enter your choice (d, h, b, a, r, p, c, s, or q ) --> ";
}

void readData(){ //reads in info for creating new booklist
    Book *book = NULL;
    BookNode *node = NULL;

    char title[256];    //local variable for new books
    string line, lineSkip;
    double price;
    int amount, id, bType;

    fstream myfile; //variable for input file
    myfile.open("bookFile.txt",ios::in); //open input file in read mode
    if (myfile.is_open()){ //while the file is open and has lines the       following creates and adds new books to booklist
        while(getline(myfile, line)){

            myfile.getline(title, 256);
            myfile >> id;
            myfile.ignore();
            myfile >> price;
            myfile >> bType;
            myfile >> amount;
            getline(myfile, lineSkip);

            book = new Book(title,price,amount,bType);
            node = new BookNode();
            if((book != NULL) && (node != NULL)) {
                node->setNode(book);
                node->setNext(bookHead);
                bookHead = node;
            }
        }
    }
    else cout << "Unable to open file";
    myfile.close(); //close input file
}

void writeData(){ //write to putput file current booklist
    ofstream myOutput;//output file variable
    myOutput.open("bookFile.txt",ios::out);//opens file in write mode
    BookNode *node = bookHead;
    Book *book = NULL;
    int bType;

    while(bookHead!=NULL){ //while there are still books on the list the following writes booklist to output file
        book = node->getNode();
        myOutput << endl << book->getTitle() << endl << book->getBookId() << endl << book->getPrice() << endl << book->getType() << endl << book->getAmount() << endl;
        node = node->getNext();
        }
    myOutput.close(); //close output file
}

void option(char c) { //contains switch statement of menu choice
	 int BookID;
	 char m;
	 double total, tax = 0.9;
	 BookNode *node = NULL;
	 switch(c) {
        case 'a': // prompts for bookid, searches by that id and if found adds book to cartlisr
                cout << endl << "To add a Book to the Cart, Enter a BookID: ";
                cin >> BookID;
                node = searchBook(BookID);
                addToCart(node);
				break;
        case 'b': //enters sub-menu for adding books until r which returns to main menu
                do {
                    insertMenu();
                    cin >> m;
                    m = tolower(m);
                    optionBook(m);
                    }
                while (m != 'r');
				break;
 		case 'd':	display_book_all(); //displays entire booklist
				break;
        case 'h':	display_cart_all();//displays entire cartlist
				break;
        case 'p':	displayPopList();//displays entire most popular list
				break;
 		case 'r'://displays cart then prompts for id, searches by that id, if found removes from cart.
                display_cart_all();
                cout << endl << "To remove a Book to the Cart, Enter a BookID: ";
                cin >> BookID;
                node = searchBook(BookID);
                removeFromCart(node);
				break;
        case 'c':
            {       //displays cart, calls checkout returns total and finds tax to give final total
                display_cart_all();
                total = checkOut();
                cout << "\nThe cart Total: $" << total << endl;
                cout << "Tax: " << tax << endl;
                tax = total * tax;
                total = total + tax;
                cout << "Final Total: $" << total << endl;
                //emptyCart();
                }
				break;
        case 's': //prompts for id displays if found
                cout << endl << "To search for a Book, enter a BookID: ";
                cin >> BookID;
                searchBook(BookID);
				break;
		case 'q': //quits program
                cout << endl << "Exiting the program..............." << endl;
				cin.get();	//type any key.
				break;
		default:
                cout << endl << "ERROR - Invalid input." << endl;
				cout << "Please Try again....." << endl;
	 }
}

void insertMenu(){ //sub-menu for book insertion
    cout <<	endl << endl << "BOOK MENU" << endl;
	cout << "----" << endl;
	cout << " b: Add a Book to the Booklist." << endl;
    cout << " m: Add a Magazine to the Booklist." << endl;
    cout << " f: Add a Fiction to the Booklist." << endl;
    cout << " t: Add a Textbook to the Booklist." << endl;
    cout << " r: Return to Main Menu." << endl;
	cout << endl << "Please enter your choice (b, m, f, t, or r ) --> ";
}

void optionBook(char c){ //options for book insert
    char title[256], author[256], isbn[256];
    double price;
    int issue, edition, bType;
    switch(c){
        case 'b': //prompts for book info calls function to add book to booklist
            cout << endl << "To add a Book to the Booklist, " << endl;
            cout << "Enter the title: ";
            cin.ignore();
            cin.getline(title, 256);
            cout << "Enter the Price: ";
            cin >> price;
            bType = 0; //default booktype
            addToCatalog(title, price, bType);
            break;
        case 'm': //prompts for magazine info calls function to add magazine to booklist
            cout << endl << "To add a Magazine to the Booklist, " << endl;
            cout << "Enter the title: ";
            cin.ignore();
            cin.getline(title, 256);
            cout << "Enter the Price: ";
            cin >> price;
            cout << "Enter the Issue number: ";
            cin >> issue;
            bType = 1;//default booktype
            addMagCatalog(title, price, issue,bType);
            break;
        case 'f': //prompts for fiction info calls function to add fiction to booklist
            cout << endl << "To add a Fiction Book to the Booklist, " << endl;
            cout << "Enter the title: ";
            cin.ignore();
            cin.getline(title, 256);
            cout << "Enter the Price: ";
            cin >> price;
            cout << "Enter the Author: ";
            cin.ignore();
            cin.getline(author, 256);
            bType = 2;//default booktype
            addFictCatalog(title, price, author,bType);
            break;
        case 't': //prompts for textbook info calls function to add textbook to booklist
            cout << endl << "To add a Textbook to the Booklist, " << endl;
            cout << "Enter the title: ";
            cin.ignore();
            cin.getline(title, 256);
            cout << "Enter the Price: ";
            cin >> price;
            cout << "Enter the Author: ";
            cin.ignore();
            cin.getline(author, 256);
            cout << "Enter the Edition Number: ";
            cin >> edition;
            cout << "Enter the ISBN: ";
            cin.ignore();
            cin.getline(isbn, 256);
            bType = 3;//default booktype
            addTBookCatalog(title,price,author,edition,isbn,bType);
            break;
    }
}

void addToCatalog(char *title, double price, int bType){
    //adds a new book to booklist from passed in values and local variables
    Book *book = NULL;
    BookNode *node;
    static int amount = 1;
        book = new Book(title,price,amount,bType);
        if((book != NULL) && (node != NULL)) {
            node->setNode(book);
            node->setNext(bookHead);
            bookHead = node;
            cout << endl << "Book added to Booklist! \n" << endl;
        }else {
            cout << endl << "Out of memory!" << endl;
        }
    }

void addMagCatalog(char *title, double price, int issue, int bType){
    //adds a new magazine to booklist from passed in values and local variables
    Book *mag = NULL;
    BookNode *node = NULL;
    static int amount = 1;

    mag = new Magazine(title,price,amount,issue, bType);
    node = new BookNode();
    if((mag != NULL) && (node != NULL)) {
        node->setNode(mag);
        node->setNext(bookHead);
        bookHead = node;
        cout << endl << "Magazine added to Booklist! \n" << endl;
    }else {
		cout << endl << "Out of memory!" << endl;
	}
}

void addFictCatalog(char *title, double price, char *author, int bType){
    //adds a new fiction to booklist from passed in values and local variables
    Book *fict = NULL;
    BookNode *node = NULL;
    static int amount = 1;

    fict = new Fiction(title,price,amount,bType,author);
    node = new BookNode();
    if((fict != NULL) && (node != NULL)) {
        node->setNode(fict);
        node->setNext(bookHead);
        bookHead = node;
        cout << endl << "Fiction Book added to Booklist! \n" << endl;
    }else {
		cout << endl << "Out of memory!" << endl;
	}
}

void addTBookCatalog(char *title, double price, char *author, int edition, char *isbn, int bType){
    //adds a new textbook to booklist from passed in values and local variables
    Book *tBook = NULL;
    BookNode *node = NULL;
    static int amount = 1;

    tBook = new Textbook(title,price,amount,bType,author,edition,isbn);
    node = new BookNode();
    if((tBook != NULL) && (node != NULL)) {
        node->setNode(tBook);
        node->setNext(bookHead);
        bookHead = node;
        cout << endl << "Textbook added to Booklist! \n" << endl;
    }else {
        cout << endl << "Out of memory!" << endl;
    }
}

void removeFromCart(BookNode* b){
    //removes booknode passed in from cartlist by bookid
    BookNode *prev, *temp;
	Book *book, *lBook;
	int id;
    temp = cartHead;
    lBook = b->getNode();
    id = lBook->getBookId();
    while (temp != NULL){
        book = temp->getNode();
        if (id != book->getBookId()){
            prev = temp;
            temp = temp->getNext();
        }
        else{
            if(temp != cartHead)
                prev->setNext(temp->getNext());
            else
                cartHead = cartHead->getNext();
            delete book;
            book = NULL;
            delete temp;
            temp = NULL;
            return;
        }
    }
}

void removeFromList(BookNode* b){
    //removes booknode passed in from booklist by bookid
	BookNode *prev, *temp;
	Book *book, *lBook;
	int id;
    temp = bookHead;
    lBook = b->getNode();
    id = lBook->getBookId();
    while (temp != NULL){
        book = temp->getNode();
        if (id != book->getBookId()){
            prev = temp;
            temp = temp->getNext();
        }
        else{
            if(temp != bookHead)
                prev->setNext(temp->getNext());
            else
                bookHead = bookHead->getNext();
            delete book;
            book = NULL;
            delete temp;
            temp = NULL;
            return;
        }
    }
}

void addToCart(BookNode* b){
    //adds booknode passed in to cartlist
    Book *book, *cart = NULL;
    BookNode *node = NULL;
    int amount, bType;

    node = new BookNode();
    cout << "\nEnter amount of books to add to cart: ";
    cin >> amount;
    book = b->getNode();
    cart = new Book(book->getTitle(),book->getPrice(),book->getAmount(),book->getType());
    //cart is a new book for the cartlist
    if (book->getAmount() >= amount){ //checks if entered amount is lees than books amount
        if ( amount > 0){
            book->setAmount(book->getAmount()-amount); //subtracts given amount from current amount of books on booklist
            cart->setAmount(amount); //sets cart to given amount
            if((cart != NULL) && (node != NULL)) {
                node->setNode(cart);
                node->setNext(cartHead);
                cartHead = node;
                cout << endl << "Book(s) added to Shopping Cart! \n" << endl;
                display_cart_all();
            }
            else
                cout << endl << "Out of memory!" << endl;
            if (book->getAmount() == 0)  //if all the books are added to cart book is removed from booklist and added to most popular list
                //mostPopular(b);
                removeFromList(b);
            }
        else
            cout << endl << "Unable to add to Cart - Out of Stock\n" << endl;
        }
        else
            cout << endl << "Amount entered exceeds the stock!" << endl;
}

void emptyCart(){
    BookNode *node = NULL;
	node = cartHead;
	 do{
		removeFromCart(node);
		node = node->getNext();
	}while(node != NULL);
}

double checkOut(){
    //adds up all the book prices in the cartlist
    Book    *book;
    BookNode *node = cartHead;
    double total = 0.00;

    book = node->getNode();
    while (node != NULL){
        total+=(book->getAmount() * book->getPrice());
        node = node->getNext();
    }
    return total;
}

void mostPopular(BookNode* b){
    Book *book = b->getNode(), *pop;
    BookNode *node = popHead;
    pop = new Book(book->getTitle(),book->getPrice(),book->getAmount(),book->getType());
    if((pop != NULL) && (node != NULL)) {
        node->setNode(pop);
        node->setNext(popHead);
        popHead = node;
        }
}

BookNode* searchByTitle(char* title){
    Book    *book = NULL;
    BookNode *node = NULL;
    char key = title[3];
    char* nKey;

    node = bookHead;
    book = node->getNode();
    while (book != NULL){
        nKey = book->getTitle();
        if (key == nKey[3] ){
            cout << "\nItem Found with Title: " << title << endl;
            book->display();
            return node;
        }
        else
        node = node->getNext();
        book = node->getNode();
    }
    return NULL;
}

BookNode* searchBook(int bookID){
    //returns the booknode of the bookid passed in if found
    Book    *book = NULL;
    BookNode *node = NULL;
    int s;
    node = bookHead;
    book = node->getNode();
    while (book != NULL){
        s = book->getBookId();
        if (s == bookID){
            cout << "\nItem Found at BookID: " << s << endl;
            book->display();
            return node;
        }
        else
        node = node->getNext();
        book = node->getNode();
    }
    return NULL;
}
void displayPopList() {	// Display contents of all nodes in the most popular linked list
	BookNode *node = NULL;
	int node_count = 0;
	cout << endl << "Most Popular Books...............\n";
	node = popHead;
	while(node != NULL) {
		display_node(node->getNode(), ++node_count);
		node = node->getNext();
	}
	cout << endl << "No more records." << endl;
}

void display_book_all() {	// Display contents of all nodes in the book catalog linked list
	BookNode *node = NULL;
	int node_count = 0;
	cout << endl << "Displaying Booklist...............\n";
	node = bookHead;
	while(node != NULL) {
		display_node(node->getNode(), ++node_count);
		node = node->getNext();
	}
	cout << endl << "No more records." << endl;
}

void display_cart_all() {	// Display contents of all nodes in the shopping cart linked list
	BookNode *node = NULL;
	int node_count = 0;
	cout << endl << "Displaying Shopping Cart...............\n";
	node = cartHead;
	while(node != NULL) {
		display_node(node->getNode(), ++node_count);
		node = node->getNext();
	}
	cout << endl << "No more records." << endl;
}

void display_node(Book *book, int index) {// Display contents of node
	cout << endl << "Record " << index << ":" << endl;
	book->display();// Polymorphic call. Depending on the object pointed to
}				// by node, a different display function will be invoked.

