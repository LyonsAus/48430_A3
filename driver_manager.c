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

Add Driver - Add a driver to the list. The list must be in a decrypted state to
            add a driver.
Delete Driver - Delete that last driver entered.
Delete List - Delete all entered drivers.
Print List - Print the list of drivers (encrypted or decrypted).
Search List - Display results based on a search term. Limited to search by
              licence type.
Encrypt List - After drivers are added the list is encrypted and a decryption
              passcode is set.
Compress List - Compress the list of drivers.
Decrypt List - The program requests a decryption passcode and decrypts the
              list upon authentication.
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
  /*
  menu:
    The menu uses a switch/break to select menu options. The menu choice
    integer is initialised at 0.
  */
  int menuChoice = 0;
  do{
    printMenu();
    if(scanf("%d", &menuChoice) <=0){
      printf("Invalid Choice");
    }
    else{
      switch (menuChoice){
        case 1:
          addDriver();
          break;
        case 2:
          deleteDriver();
          break;
        case 3:
          deleteList();
          break;
        case 4:
          printList();
          break;
        case 5:
          searchList();
          break;
        case 6:
          encryptList();
          break;
        case 7:
          compressList();
          break;
        case 8:
          decryptList();
          break;
        case 9:
          decompressList();
          break;
        case 10:
          exit(0);
        default:
          printf("Invalid Choice");
          break;
      }
    }
  }
  while(menuChoice != 10);

  return 1;
}

void printMenu(){
  printf("\n\n"
    "1. Add Driver\n"
    "2. Delete Last Driver\n"
    "3. Delete Driver List\n"
    "4. Print Driver List\n"
    "5. Search Driver List\n"
    "6. Encrypt Driver List\n"
    "7. Compress Driver List\n"
    "8. Decrypt Driver List\n"
    "9. Decompress Driver List\n"
    "10. Exit\n"
    "Enter Your Choice> ");
}

void addDriver(){

}

void deleteDriver(){

}

void deleteList(){

}

void printList(){

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
