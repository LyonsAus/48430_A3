/*

test comment for github desktop

*/

/*
Group 10:
Alex Lyons 99126827
Godwin Huang 12458004
Hasan Rahman 12457988
Minh Van 11104332
Omar Salam 12002376
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Definiteions for limiting array sizes
*/


/**** TEST COMMMENT ****/

#define MAX_NUM_DRIVERS 50
#define MAX_NAME_SIZE 11

/*
driver struct:

Address -
post code is limited to 1000-2999 for NSW codes
*/

struct driver{
  char first_name[MAX_NAME_SIZE];
  char last_name[MAX_NAME_SIZE];
};

struct dob{
  int day;
  int month;
  int year;
};

struct address{
  int st_num;
  char st_name[MAX_NAME_SIZE];
  int p_code;
};

struct licence{
  int exp_month;
  int exp_year;
  char type;
  int lic_num;
};



/*
Functions:

Add Driver - Add a driver to the list. The list must be in a decrypted state to add a driver.
Delete Driver - Delete that last driver entered.
Delete List - Delete all entered drivers.
Print List - Print the list of drivers (encrypted or decrypted).
Search List - Display results based on a search term. Limited to search by licence type.
Encrypt List - After drivers are added the list is encrypted and a decryption passcode is set.
Compress List - Compress the list of drivers.
Decrypt List - The program requests a decryption passcode and decrypts the list upon authentication.
Decompress List - Decompress the list of drivers after compression.
*/

void printMenu();
void addDriver();
void deleteDriver();
void deleteList();
void printList();
void searchList();
void encryptList();
void compressList();
void decryptList();
void decompressList();


int main(void) {
  /* code */
  return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
/** THIS IS THE END OF THE PROGRAM **/

=======
void printMenu(){

}

void addDriver(){

}

void deleteDriver(){

}

void deleteList(){

}

void printList(){


 exit(0);
 
}

void searchList(){

}

void encryptList(){

}

void compressList(){

}

void decryptList(){

}

void decompressList(){

}
>>>>>>> Alex
=======
/** THIS IS THE END OF THE PROGRAM **/

>>>>>>> Omar
