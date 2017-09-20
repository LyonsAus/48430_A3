/*****************************************************************************
48430 Fundamentals of C Programming - Assignment 3

Name: Alex Lyons
Student ID: 99126827

Name: Godwin Huang
Student ID: 12458004

Name: Hasan Rahman
Student ID: 12457988

Name: Minh Van
Student ID: 11104332

Name: Omar Salam
Student ID: 12002376

Date of submission:
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_SIZE 11

/*****************************************************************************
Struct definitions
*****************************************************************************/
typedef struct driver{
  char firstName[MAX_NAME_SIZE];
  char surname[MAX_NAME_SIZE];
  int day;
  int month;
  int year;
  int st_num;
  char st_name[MAX_NAME_SIZE];
  char st_type[MAX_NAME_SIZE];
  int p_code;
  int exp_month;
  int exp_year;
  char lic_type;
  char lic_num[3];
  struct driver *next;
} driver_t;

/*****************************************************************************
Function prototypes
*****************************************************************************/
void printMenu();
driver_t *addDriver(driver_t *previous);
driver_t *deleteDriver(driver_t *start);
void deleteList();
void printList(driver_t *start);
void searchList();
void encryptList();
void compressList();
void decryptList();
void decompressList();
<<<<<<< HEAD


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

=======
void clr_stdin(void);

/*****************************************************************************
main
This is the main function of the program 
inputs:
- none
outputs:
- integer
*****************************************************************************/
int main(void) {
  char choice;
  driver_t *firstDriver = NULL;
  driver_t *latestDriver = NULL;
  driver_t *temp = NULL;

  while(choice != '0')
  {
	  printMenu();
	  scanf("%c", &choice);
	  clr_stdin();
	  switch(choice)
	  {
		  case '1':
			if(firstDriver == NULL){
				firstDriver = addDriver(NULL);
				latestDriver = firstDriver;
			}
			else{
				latestDriver = addDriver(latestDriver);
			}
			break;
		  case '2':
			temp = deleteDriver(firstDriver);
			if(temp == firstDriver){
				latestDriver = firstDriver;
				firstDriver = temp;
			}
			else{
				latestDriver = NULL;
			}
			break;
		  case '3':
			printList(firstDriver);
			break;
		  case '4':
			printf("Search list\n");
			break;
		  case '5':
			printf("Encrypt and compress\n");
			break;
		  case '6':
			printf("Decompress and decrypt\n");
			break;
		  case '7':
			printf("Erase stored content\n");
			break;
		  case '0':
			break;

		  default:
			printf("%s is an invalid input", &choice);
	  }
  }
  return 0;
}

/*****************************************************************************
printMenu
This function prints the main menu of the program 
inputs:
- none
outputs:
- none
*****************************************************************************/
void printMenu(){
	printf("\nMain Menu\n"
	       "1 = Add driver\n"
	       "2 = Remove driver\n"
	       "3 = Display driver list\n"
	       "4 = Search list\n"
	       "5 = Encrypt and compress\n"
	       "6 = Decompress and decrypt\n"
	       "7 = Erase stored content\n"
	       "0 = Exit program\n\n"
	       "Enter choice: ");
}

/*****************************************************************************
addDriver
This function adds a driver to the list 
inputs:
- driver_t pointer (points to last driver in the list)
outputs:
- driver_t pointer
*****************************************************************************/
driver_t *addDriver(driver_t *previous){
	printf("\nAdding new driver\n");
	driver_t *newDriver = malloc(sizeof(driver_t));
	printf("Enter firstname and surname seperated by a space\n> ");
	scanf("%s %s", newDriver->firstName, newDriver->surname);
	if(newDriver->firstName[0] > 96 && newDriver->firstName[0] < 123){
		newDriver->firstName[0] -= 32;
	}
	if(newDriver->surname[0] > 96 && newDriver->surname[0] < 123){
		newDriver->surname[0] -= 32;
	}

	while((newDriver->day < 1 || newDriver->day > 31) ||
	      (newDriver->month < 1 || newDriver->month > 12) ||
	      (newDriver->year < 1900 || newDriver->year > 2017)){
		printf("Enter date of birth in following format DD MM YYYY\n> ");
		scanf("%d %d %d", &newDriver->day, &newDriver->month, &newDriver->year);
		
		if(newDriver->day <= 0 || newDriver->day > 31){
			printf("Invalid day, please enter day between 1 and 31\n");
		}
		if(newDriver->month <= 0 || newDriver->month > 12){
			printf("Invalid month, please enter month between 1 and 12\n");
		}
		if(newDriver->year <= 1900 || newDriver->year > 2017){
			printf("Invalid year, please enter year between 1900 and 2017\n");
		}
	}

	printf("Enter street number and street name seperated by a space\n> ");
	scanf("%d %s %s", &newDriver->st_num, newDriver->st_name,
	newDriver->st_type);

	while(newDriver->p_code < 1000 || newDriver->p_code > 2999){
		printf("Enter postcode\n> ");
		scanf("%d", &newDriver-> p_code);
		if(newDriver->p_code < 1000 || newDriver->p_code > 2999){
			printf("Invalid postcode, please enter postcode between 1000 and 2999\n");
		}
	}
	
	while((newDriver->exp_month < 1 || newDriver->exp_month > 12) ||
		   (newDriver->exp_year < 2017 || newDriver->exp_year > 2022)){
			   printf("Enter expiry date in following format MM YYYY\n> ");
			   scanf("%d %d", &newDriver->exp_month, &newDriver->exp_year);
			   clr_stdin();
			   
			   if(newDriver->exp_month < 1 || newDriver->exp_month > 12){
				   printf("Invalid month, please enter month between 1 and 12\n");
			   }
			   if(newDriver->exp_year < 2017 || newDriver->exp_year > 2022){
				   printf("Invalid year, please enter year between 2017 and 2022\n");
			   }
	}

	while(newDriver->lic_type != 'C' && newDriver->lic_type != 'R' &&
	      newDriver->lic_type != 'L' && newDriver->lic_type != 'M' &&
	      newDriver->lic_type != 'H' && newDriver->lic_type != 'B'){
		printf("Choose licence type\n");
		printf("C = Car \t\t M = Medium rigid\n");
		printf("R = rider \t\t H = Heavy rigid\n");
		printf("L = Light rigid \t B = Multi combination\n> ");
		scanf("%c", &newDriver->lic_type);
		clr_stdin();
		
		if(newDriver->lic_type == 'c' || newDriver->lic_type == 'r' ||
		   newDriver->lic_type == 'l' || newDriver->lic_type == 'm' ||
		   newDriver->lic_type == 'h' || newDriver->lic_type == 'b'){
			newDriver->lic_type -= 32;
		}
		
		if(newDriver->lic_type != 'C' && newDriver->lic_type != 'c' &&
		   newDriver->lic_type != 'R' && newDriver->lic_type != 'r' &&
		   newDriver->lic_type != 'L' && newDriver->lic_type != 'l' &&
		   newDriver->lic_type != 'M' && newDriver->lic_type != 'm' &&
		   newDriver->lic_type != 'H' && newDriver->lic_type != 'h' &&
		   newDriver->lic_type != 'B' && newDriver->lic_type != 'b'){
			printf("\n\nInvalid license type, please choose from the list\n");
		}
	}
	
	newDriver->lic_num[0] = newDriver->lic_type;
	newDriver->lic_num[1] = newDriver->firstName[0];
	newDriver->lic_num[2] = newDriver->surname[0];
	newDriver->lic_num[3] = '\0';
	printf("Driver licence ID generated: %s", newDriver->lic_num);

	newDriver->next = NULL;
	if(previous != NULL){
		previous->next = newDriver;
	}
	return newDriver;
}

/*****************************************************************************
deleteDriver
This function removes nth driver from the list
inputs:
- driver_t pointer
outputs:
- driver_t pointer
*****************************************************************************/
driver_t *deleteDriver(driver_t *start){
	char input[3];
	driver_t *first = start;
	driver_t *preDelete = start;
	driver_t *delete = NULL;
	
	printf("Enter the licence ID to delete\n> ");
	scanf("%s", input);
	clr_stdin();
	while(first != NULL){
		if(strcmp(input, first->lic_num) == 0){
			delete = first;
			break;
		}
		first = first->next;
	}
	while(preDelete != NULL && preDelete->next != delete){
		preDelete = preDelete->next;
	}
	
	if(start != NULL && delete == start){
		if(delete->next != NULL){
			start = delete->next;
		}
		else{
			start = NULL;
		}
	}
	else{
		if(delete != NULL){
			if(preDelete != NULL && delete->next != NULL){
				preDelete->next = delete->next;
			}
			else if(preDelete != NULL && delete->next == NULL){
				preDelete->next = NULL;
			}
		}
	}
	
	if(delete != NULL){
		delete = NULL;
		free(delete);
	}
	return start;
}

/*****************************************************************************
deleteList
inputs:
- 
outputs:
- 
*****************************************************************************/
void deleteList(){

}

/*****************************************************************************
printList
inputs:
- driver_t pointer (points to first driver in the list)
outputs:
- none
*****************************************************************************/
void printList(driver_t *start){
	driver_t *currentDriver = start;
	int count = 0;
	while(currentDriver != NULL){
		printf("(%c%c%c)----------------------------------------\n",
		currentDriver->lic_num[0],
		currentDriver->lic_num[1],
		currentDriver->lic_num[2]);

		printf("Name: %s %s", currentDriver->firstName,
		currentDriver->surname);
		printf("\t D.O.B: %02d-%02d-%4d\n", currentDriver->day,
		currentDriver->month, currentDriver->year);

		printf("Address: %d %s %s", currentDriver->st_num,
		currentDriver->st_name,
		currentDriver->st_type);
		printf("\t Postcode: %d\n", currentDriver->p_code);

		printf("Licence type: %c", currentDriver->lic_type);
		printf("\t Expiry date: %02d-%4d\n\n",currentDriver->exp_month,
		currentDriver->exp_year);

		currentDriver = currentDriver->next;
		count++;
	}
	printf("---------------------------------------------\n");
	printf("Total driver(s): %d\n\n", count);
}

/*****************************************************************************

inputs:
- 
outputs:
- 
*****************************************************************************/
void searchList(){

}

/*****************************************************************************

inputs:
- 
outputs:
- 
*****************************************************************************/
void encryptList(){

}

/*****************************************************************************

inputs:
- 
outputs:
- 
*****************************************************************************/
void compressList(){

}

/*****************************************************************************

inputs:
- 
outputs:
- 
*****************************************************************************/
void decryptList(){

}

/*****************************************************************************

inputs:
- 
outputs:
- 
*****************************************************************************/
void decompressList(){

}

/*****************************************************************************
clr_stdin
This function clears stdin buffer, in most cases the '\n' that is left out by
the scanf function.
inputs:
- 
outputs:
- 
*****************************************************************************/void clr_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
>>>>>>> Hasan
}
>>>>>>> Alex
=======
/** THIS IS THE END OF THE PROGRAM **/

>>>>>>> Omar
