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

/*****************************************************************************
Struct definitions
*****************************************************************************/
typedef struct driver{
  char firstName[10];
  char surname[10];
  int day;
  int month;
  int year;
  char address[20];
  int p_code;
  int exp_month;
  int exp_year;
  char lic_type;
  char lic_num[4];
  struct driver *next;
  struct driver *prev;
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

  while(choice != '0')
  {
	  printMenu();
	  scanf("%c", &choice);
	  clr_stdin();
	  switch(choice)
	  {
		  case '1':
				firstDriver = addDriver(firstDriver);
			break;
		  case '2':
				firstDriver = deleteDriver(firstDriver);
			break;
		  case '3':
			printList(firstDriver);
			break;
		  case '4':
			printf("Search list\n");
			break;
		  case '5':;
			driver_t *tst = firstDriver;
			FILE *fPointer = fopen("database0.txt","w");
			while(tst) 
			{
				fprintf(fPointer, /*"|%-10s| |%-10s| |%02d-%02d-%4d| |%-20s| |%d| |%02d-%4d| |%c| |%s|\n"*/
				"%s %s %d %d %d %s %d %d %d %c %s",
				tst->firstName, tst->surname, tst->day, tst->month, tst->year,
				tst->address, tst->p_code, tst->exp_month, tst->exp_year,
				tst->lic_type, tst->lic_num);
				tst = tst->next;
			}
			fclose(fPointer);
			break;
		  case '6':;
			FILE *fPointers = fopen("database0.txt","r");
			/*fseek(fPointers, 0, SEEK_END);
			long fileSize = ftell(fPointers);
			rewind(fPointers);
			int count = (int)(fileSize);
			int boo = (sizeof(driver_t)) + 10;
			printf("%d %d\n", count, boo);*/
			driver_t *tmpDriver = malloc(sizeof(driver_t));
			fscanf(fPointers, "%s %s %d %d %d %s %d %d %d %c %s",
			tmpDriver->firstName, tmpDriver->surname, &tmpDriver->day, &tmpDriver->month, &tmpDriver->year,
			tmpDriver->address, &tmpDriver->p_code, &tmpDriver->exp_month, &tmpDriver->exp_year,
			&tmpDriver->lic_type, tmpDriver->lic_num);
			tmpDriver->next = NULL;
			printf("%s\n", tmpDriver->firstName);
			fclose(fPointers);
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
	       "5 = Save list\n"
	       "6 = Load list\n"
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
driver_t *addDriver(driver_t *start){
	driver_t *newDriver = malloc(sizeof(driver_t));
	driver_t *latestDriver = start;
	
	if(start != NULL){
		while(latestDriver->next != NULL){
			latestDriver = latestDriver->next;
		}
	}
	else{
		latestDriver = NULL;
	}
	
	newDriver->next = NULL;
	newDriver->prev = NULL;
	if(latestDriver != NULL){
		latestDriver->next = newDriver;
		newDriver->prev = latestDriver;
	}
	
	printf("\nAdding new driver\n");
	printf("Enter firstname and surname seperated by a space\n> ");
	scanf("%s %s", newDriver->firstName, newDriver->surname);
	clr_stdin();
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
		scanf("%d %d %d", &newDriver->day, &newDriver->month,
		&newDriver->year);
		clr_stdin();
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

	printf("Enter street address\n> ");
	fgets(newDriver->address, 20, stdin);
	strtok(newDriver->address, "\n");
	/*clr_stdin();*/

	while(newDriver->p_code < 1000 || newDriver->p_code > 2999){
		printf("Enter postcode\n> ");
		scanf("%d", &newDriver-> p_code);
		clr_stdin();
		if(newDriver->p_code < 1000 || newDriver->p_code > 2999){
			printf(
			"Invalid postcode, please enter postcode between 1000 and 2999\n");
		}
	}
	
	while((newDriver->exp_month < 1 || newDriver->exp_month > 12) ||
		   (newDriver->exp_year < 2017 || newDriver->exp_year > 2022)){
			   printf("Enter expiry date in following format MM YYYY\n> ");
			   scanf("%d %d", &newDriver->exp_month, &newDriver->exp_year);
			   clr_stdin();
			   
			   if(newDriver->exp_month < 1 || newDriver->exp_month > 12){
				   printf(
				   "Invalid month, please enter month between 1 and 12\n");
			   }
			   if(newDriver->exp_year < 2017 || newDriver->exp_year > 2022){
				   printf(
				   "Invalid year, please enter year between 2017 and 2022\n");
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
	printf("Driver licence ID generated: %s\n\n", newDriver->lic_num);
	
	if(start == NULL){
		return newDriver;
	}
	else{
		return start;
	}
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
	char input[4];
	driver_t *delete = start;
	
	if(delete == NULL){
		printf("No data in list\n");
		return NULL;
	}
	
	printf("Enter the licence ID to delete\n> ");
	scanf("%s", input);
	clr_stdin();
	
	while(delete != NULL){
		if(strcmp(input, delete->lic_num) == 0){
			break;
		}
		delete = delete->next;
	}
	if(delete == NULL){
		printf("ID '%s' does not exist\n", input);
		return start;
	}
	
	if(delete == start && delete != NULL){
		if(delete->next != NULL){
			start->next->prev = NULL;
			start = start->next;
		}
		else{
			start = NULL;
		}
	}
	else{
		if(delete != NULL){
			if(delete->prev != NULL){
				delete->prev->next = delete->next;
			}
			if(delete->next != NULL){
				delete->next->prev = delete->prev;
			}
		}
	}
	delete = NULL;
	free(delete);
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
	/*driver_t *ahead = NULL;
	driver_t *behind = NULL;*/
	if(currentDriver == NULL){
		printf("No data in list\n");
		return;
	}
	
	printf("\n");
	while(currentDriver != NULL){
		/*ahead = currentDriver->next;
		behind = currentDriver->prev;
		printf("ID:%s Ahead:%s Behind:%s\n",
			currentDriver->lic_num,
			(ahead == NULL) ? "None" : ahead->lic_num,
			(behind == NULL) ? "None" : behind->lic_num);
			currentDriver = currentDriver->next;
			ahead = NULL;
			behind = NULL;*/
		printf("(%s)--------------------------------------------\n",
		currentDriver->lic_num);
		int tmp;
		int nameLen = strlen(currentDriver->firstName)
		+ strlen(currentDriver->surname) + 1;
		printf("Name:    %s %s", currentDriver->firstName,
		currentDriver->surname);
		for(tmp = nameLen; tmp < 20; tmp++){
			printf(" ");
		}
		printf("D.O.B:    %02d-%02d-%4d\n", currentDriver->day,
		currentDriver->month, currentDriver->year);

		int addressLen = strlen(currentDriver->address);
		printf("Address: %s", currentDriver->address);
		for(tmp = addressLen; tmp < 20; tmp++){
			printf(" ");
		}
		printf("Postcode: %d\n", currentDriver->p_code);

		printf("Type:    %c", currentDriver->lic_type);
		printf("                   ");
		printf("EXP:      %02d-%4d\n\n",currentDriver->exp_month,
		currentDriver->exp_year);

		currentDriver = currentDriver->next;
		count++;
	}
	printf("-------------------------------------------------\n");
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
}