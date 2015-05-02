/********************************************************************
//  CSE310 Assignment 5
//  Date: 3/11/2014
//  Programmer: Justin P. Jackson <justin.p.jackson@asu.edu>
//
//************************************************************************/

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

Address* inputTable; //pointer for input table

int main();     //main
int readData(string);   //reads from file given as parameter returns tableSize

int main(){
    int m,r;
    string fileName;
    bool inputFlag = false;

    do{ // Do-While Menu Loop
        cout << "\n HashTable Assignment 5\n\tMenu:";
        cout << "\n\t\t ***Choice 1 must be ran before 2 ***";
        cout << "\n\t\t1 to Enter File.";
        cout << "\n\t\t2 to Display Search Results.";
        cout << "\n\t\t0 to Exit.";
        cout << "\n\t\tChoice: ";
        cin >> r;

        switch (r){
            case 1:
                cout << "Include suffix -- input.[1-5].txt: ";
                cin >> fileName;
                m = readData(fileName);
                inputFlag = true;
            break;
            case 2:
                if(inputFlag){
                    searchElement(hashTable,m);
                }else{
                    cout << "\n\tError please input file first" << endl;
                }
            break;
            case 0:
            break;
        }
    }while(r != 0);

    return 0;
}

int readData(string fileName){
//    Local Variables
    int tableSize, firstComma,secondComma, m, n;
    char comma = ',';
    string line, skipLine;
    Address* temp = new Address;
    zipCodeTable = new string[20];

    fstream myfile; //variable for input file
    myfile.open(fileName.c_str(),ios::in); //open input file in read mode
    if (myfile.is_open()){
        myfile >> tableSize;
        inputTable = new Address[tableSize]; // new array of address of size form file
        myfile.ignore();
        getline(myfile, line);
        m = 0; n = 0;
        while(getline(myfile, line)){
            if (line.size() > 6){ //lines with Zipcode, City , and State
                firstComma = line.find(comma); //find first comma in input line
                temp->zipCode.insert(0,line,0,firstComma); //inserts zipcode form input line to temp address
                secondComma = line.rfind(comma); //finds last comma starting at the end
                temp->city.insert(0,line,firstComma+1,secondComma-6); //inserts city form input line between the two commas
                temp->state.insert(0,line,secondComma+1,line.size()); //inserts state form input line from last comma to end of string
                temp->collision = 0;
                inputTable[m] = *temp; // temp address added to inputTable
                m++;
                temp->zipCode = ""; //Clear temp for next line of data
                temp->city = "";
                temp->state = "";
            }else{ //lines with only zipcodes
                zipCodeTable[n] = line;
                n++;
            }
        }
        if ( m < tableSize){ // if entries are less than tableSize full rest of table with "None"'s
            do{
                inputTable[m].zipCode = "None";
                inputTable[m].city = "None";
                inputTable[m].state = "None";
                inputTable[m].collision = 0;
                m++;
            }while( m != tableSize);
        }
        insertElement(&inputTable[0],tableSize); //call to insert addresss form input table to hashtable
        cout << endl << endl;
        display(&hashTable[0], tableSize); //call to display hashed table
    }else cout << "Unable to open file";
    myfile.close(); //close input file
    return tableSize;
}
