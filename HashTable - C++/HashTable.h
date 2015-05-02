/******************************************************************
//	Assignment 5
//	Name:	Justin P JAckson
//	Description:	header file for hashtable functions
//
//  h = hi(zipCode) + i*h2(zipCode)
//  h1 = zipCode % tableSize
//  h2 = 1 + (zipCode % floor(tableSize/3))
//
//  Hash Analysis:
//        I choose my hash functions form starting with the examples for
//        the  notes. Except that I changed the primes of both h1 and h2.
//        For h1 I picked the size of the table to be the prime moding the
//        zipcode key. In h2 I use the floor fuction of the tableSize divided
//        by 3 to find a large prime smaller than the tablesize. These two
//        functions are the results of reducing the amount of collision. I
//        changed the primes indivaully until realizing that the tableSize
//        provided a better number for any table entered to be hashed. This
//        did decrease the totall amount of collision but still dosent fully
//        effective.
//
//****************************************************************/

#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

struct Address{
    string zipCode;
    string city;
    string state;
    int collision;
};  //struct for hashtable data

Address* hashTable; //pointer for hashtable
string* zipCodeTable; // pointer for zipcodes inputed from file

int h(string, int, int); // key, i value and tableSize  hash function
int h1(string, int);    // hash function
int h2(string, int);    // hash function
void insertElement(Address* , int);     //Inserts address form inputTable to hashTable
void searchElement(Address* , int);     //Searches hashTable for zipcodes from zipcodeTable
void display(Address*,int);     //Displays the entire table passed in

int h(string zipCode,int iValue, int tableSize){
//    hash function
    return (h1(zipCode, tableSize) + (iValue * h2(zipCode,tableSize)));
}

int h1(string zipCode, int tableSize){
    //    hash function
    return atoi(zipCode.c_str()) % tableSize;
}

int h2(string zipCode, int tableSize){
//    hash function
    return 1 + (atoi(zipCode.c_str()) % (int)(floor(((double)tableSize)/3)));
}

void insertElement(Address* hTable, int tableSize){
    int key,i,j,c=0;
    hashTable = new Address[tableSize]; //new hashtable of table size
    do{ // full new table with "None"'s
        hashTable[c].zipCode = "None";
        hashTable[c].city = "None";
        hashTable[c].state = "None";
        hashTable[c].collision = 0;
        c++;
    }while(c != tableSize );
    j = 0; i = 0;
    do{                 //Insertion code form pseudo code in notes
        key = h(hTable[i].zipCode, j,tableSize);
        if (hashTable[key].zipCode == "None"){
            hashTable[key] = hTable[i];
            i++; j = 0;
        }else{
            hTable[i].collision++;
            j++;
        }
    }while(i != tableSize);
}

void searchElement(Address* hTable, int tableSize){
    int j = 0,i = 0;
    cout << "\nSearching.....\n";

    do{             //Search code form pseudo code in notes
        if(hTable[j].zipCode.compare(zipCodeTable[i])){
            cout << hTable[j].zipCode << " is for the city of ";
            cout << hTable[j].city << " in " << hTable[j].state << endl;
            i++; j++;
        }else{
            j++;
        }
        cout << zipCodeTable[i] << " not found" << endl;
    }while((j != tableSize) && (!zipCodeTable[i].empty()) );

}

void display(Address* hTable, int tableSize){
    int i = 0;
    cout << "\nIndex\tZipCode\tCity\t\tState/Province\t\tCollision\n\n";
    do{         //Displays entire table
        cout << i;
        cout << "\t" << hTable[i].zipCode;
        cout << "\t" << hTable[i].city;
        cout << "\t\t" << hTable[i].state;
        cout << "\t\t" << hTable[i].collision << endl;
        i++;
    }while(i != tableSize);
}
