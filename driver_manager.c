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


#define DB_FILE_NAME "database"
#define len(x) ((int)log10(x)+1
/*****************************************************************************
Struct definitions
*****************************************************************************/
typedef struct driver{
  char firstName[11];
  char surname[11];
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

struct node							/*new*/
{									/*new*/
    int value;						/*new*/
    char letter;					/*new*/
    struct node *left,*right;		/*new*/
};									/*new*/
typedef struct node Node;

/*****************************************************************************
Function prototypes
*****************************************************************************/
void printMenu();
driver_t *addDriver(driver_t *previous);
driver_t *deleteDriver(driver_t *start);
void deleteList();
void printList(driver_t *start);
void searchList();
void encrypt(driver_t* start);
void decryptList();
void clr_stdin(void);


void buildHuffmanTree(Node **tree);								/*new*/
void fillTable(int codeTable[], Node *tree, int Code);			/*new*/
void compressList(FILE *input, FILE *output, int codeTable[]);	/*new*/
void decompressList(FILE *input, FILE *output, Node *tree);	/*new*/
void invertCodes(int codeTable[],int codeTable2[]);

/*****************************************************************************
main
This is the main function of the program
inputs:
- none
outputs:
- integer
*****************************************************************************/
int main(void){
  char choice;
  driver_t *firstDriver = NULL;
  int compress;
  Node *tree;								/*new*/
  int codeTable[27], codeTable2[27];		/*new*/
  FILE *input, *output;

  while(choice != '0'){
	  printMenu();
	  scanf("%c", &choice);
	  clr_stdin();
	  switch(choice){
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
			while(tst){
				fprintf(fPointer, "%-10s %-10s %02d %02d %4d %-20s %d %02d %4d %c %s\n"
				/*"%s %s %d %d %d %s %d %d %d %c %s"*/,
				tst->firstName, tst->surname, tst->day, tst->month, tst->year,
				tst->address, tst->p_code, tst->exp_month, tst->exp_year,
				tst->lic_type, tst->lic_num);
				tst = tst->next;
			}
			fclose(fPointer);
			break;
		  case '6':;
			FILE *fPointers = fopen("database0.txt","r");
			firstDriver = NULL;
			fseek(fPointers, 0, SEEK_END);
			long fileSize = ftell(fPointers);
			rewind(fPointers);
			int nodeCount = (int)(fileSize) / ((sizeof(driver_t)) - 23);
			int loop = 0;
			for(loop = 0; loop < nodeCount; ++loop){
				fseek(fPointers, (((sizeof(driver_t)) - 23) * loop), SEEK_SET);
				if(firstDriver == NULL){
					firstDriver = malloc(sizeof(driver_t));
					fscanf(fPointers, "%s %s %d %d %d %s %d %d %d %c %s",
					firstDriver->firstName, firstDriver->surname,
					&firstDriver->day, &firstDriver->month, &firstDriver->year,
					firstDriver->address, &firstDriver->p_code,
					&firstDriver->exp_month, &firstDriver->exp_year,
					&firstDriver->lic_type, firstDriver->lic_num);
					firstDriver->next = NULL;
					firstDriver->prev = NULL;
				}
				else{
					driver_t *refDriver = firstDriver;
					driver_t *newDriver = malloc(sizeof(driver_t));
					while(refDriver->next != NULL){
						refDriver = refDriver->next;
					}
					fscanf(fPointers, "%s %s %d %d %d %s %d %d %d %c %s",
					newDriver->firstName, newDriver->surname,
					&newDriver->day, &newDriver->month, &newDriver->year,
					newDriver->address, &newDriver->p_code,
					&newDriver->exp_month, &newDriver->exp_year,
					&newDriver->lic_type, newDriver->lic_num);
					refDriver->next = newDriver;
					newDriver->next = NULL;
					newDriver->prev = refDriver;
				}
			}
			fclose(fPointers);
			break;
		  case '7':
			printf("Erase stored content\n");
			break;
		  case '8':
		  	buildHuffmanTree(&tree);
			fillTable(codeTable, tree, 0);
			invertCodes(codeTable,codeTable2);
		  	printf("Type 1 to compress and 2 to decompress:");
			scanf("%d",&compress);
      clr_stdin();

		  	if (compress==1)
			{
				input = fopen("database0.txt", "r");
				output = fopen("compressed.txt","w");
				compressList(input,output,codeTable2);
				fclose(output);
        fclose(input);
			}
			else
			{
			/*to change the file name for decompression*/
				if(rename("compressed.txt", "decompressed1.txt") == 0)
				{
					printf("File has been decompressed.\n");
				}
				else
				{
					printf("Error, database not encrypted.\n");
				}
				/*input = fopen("decompressed1.txt","r");
				output = fopen("database1.txt", "w");*/
				decompressList(input,output, tree);
				/*fclose(output);
        fclose(input);*/
			}

			break;

		  case '9':
        encrypt(firstDriver);


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
	       "8 = Compress Menu\n"
	       "9 = Encryption Menu\n"
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
void encrypt(driver_t* start)
{
            driver_t *encDriver = start;
            int key[5];
    printf("Enter four digit numeric pin: ");
    scanf("%1d%1d%1d%1d%1d", &key[0], &key[1], &key[2], &key[3], &key[4]);
	clr_stdin();

    /*char alphanum[13][5]={
        {'a','b','c','d','e'},1
        {'f','g','h','i','j'},2
        {'k','l','m','n','o'},3
        {'p','q','r','s','t'},4
        {'u','v','w','x','y'},5
        {'z','A','B','C','D'},6
        {'E','F','G','H','I'},7
        {'J','K','L','M','N'},8
        {'O','P','Q','R','S'},9
        {'T','U','V','W','X'},10
        {'Y','Z','-',' ','='},11
        {'1','2','3','4','5'},12
        {'6','7','8','9','0'},13
        };

    char secret[13][5]={
        {'U','5','V','W','X'},1
        {'T','b','c','d','e'},2
        {'Y','Z','-',' ','='},3
        {'k','l','v','n','o'},4
        {'f','g','h','8','j'},5
        {'3','m','w','x','y'},6
        {'E','q','r','R','t'},7
        {'6','7','i','9','0'},8
        {'p','F','G','H','I'},9
        {'z','A','B','1','D'},10
        {'J','K','L','M','N'},11
        {'O','P','Q','s','S'},12
        {'C','2','u','4','a'},13
        };*/

  char alphanum[8][8]={
        {'a','b','R','d','e','f','g','h'},
	{'i','j','k','l','m','n','o','p'},
	{'q','r','s','t','u','v','w','x'},
	{'y','z','A','B','C','D','E','F'},
	{'G','H','I','J','K','L','M','N'},
	{'O','P','Q','T','S','c','U','V'},
	{'W','X','Y','Z','1','2','3','4'},
	{'5','6','7','8','9','0',' ','='},
        };

    char secret[8][8]={
	{'k','f','B','l','J','m','I','y'},
	{'M','e','L','P','W','b','o','H'},
	{'j','V','A','c','z','w','T','x'},
	{'t','r','K','q','G','=','Z','1'},
	{'C','N','7','d','p','Y','4','Q'},
	{'g','U','8','v','n','D','a','X'},
	{'6','i',' ','O','0','3','s','9'},
	{'E','u','F','5','S','2','h','R'},
        };
/*15690*/


/*0V4hPj*/
    while(encDriver != NULL)
    {
    	int loop;
        /*for(loop=0;encDriver->surname[loop]!='\0';loop++)
        {
            int ax,ay,sx,sy;
            for (ay=0;ay<13;ay++)
                for (ax=0;ax<5;ax++)
                    if(encDriver->surname[loop] == alphanum[ay][ax])
                    {
                        sx=ax;
                        sy=ay;
                        break;
                    }
            encDriver->surname[loop]=secret[sy][sx];
        }*/

	for(loop=0; encDriver->surname[loop]!='\0'; loop++)
        {
            int ax,ay,sx,sy;
            for (ay=0;ay<8;ay++)
                for (ax=0;ax<8;ax++)
			if(encDriver->surname[loop] == alphanum[ay][ax]){
				if(loop >= 0 && loop < 2){
					sx = ax + key[0];
					while(sx >= 8){
						sx -= 8;
					}
		                	sy = ay + key[0];
					while(sy >= 8){
						sy -= 8;
					}
		                	break;
				}
				if(loop >= 2 && loop < 4){
					sx = ax + key[1];
					while(sx >= 8){
						sx -= 8;
					}
		                	sy = ay + key[1];
					while(sy >= 8){
						sy -= 8;
					}
		                	break;
				}
				if(loop >= 4 && loop < 6){
					sx = ax + key[2];
					while(sx >= 8){
						sx -= 8;
					}
		                	sy = ay + key[2];
					while(sy >= 8){
						sy -= 8;
					}
		                	break;
				}
				if(loop >= 6 && loop < 8){
					sx = ax + key[3];
					while(sx >= 8){
						sx -= 8;
					}
		                	sy = ay + key[3];
					while(sy >= 8){
						sy -= 8;
					}
		                	break;
				}
				if(loop >= 8 && loop < 10){
					sx = ax + key[4];
					while(sx >= 8){
						sx -= 8;
					}
		                	sy = ay + key[4];
					while(sy >= 8){
						sy -= 8;
					}
		                	break;
				}
		}
		encDriver->surname[loop]=secret[sy][sx];
	}
                    

        /*for(loop=0;encDriver->firstName[loop]!='\0';loop++)
        {
            int ax,ay,sx,sy;
            for (ay=0;ay<13;ay++)
                for (ax=0;ax<5;ax++)
                    if(encDriver->firstName[loop]==alphanum[ay][ax])
                    {
                        sx=ax;
                        sy=ay;
                        break;
                    }
            encDriver->firstName[loop]=secret[sy][sx];
        }

        for(loop=0; encDriver->address[loop] != '\0'; loop++)
        {
            int ax,ay,sx,sy;
            for (ay = 0; ay < 13; ay++)
                for (ax = 0; ax < 5; ax++)
                    if(encDriver->address[loop]==alphanum[ay][ax])
                    {
                        sx=ax;
                        sy=ay;
                        break;
                    }
            encDriver->address[loop]=secret[sy][sx];
        }*/

        /*for(loop=0;linkedlistp->storeddata.address[loop]!='\0';loop++)
        {
            int ax,ay,sx,sy;
            for (ay=0;ay<13;ay++)
                for (ax=0;ax<5;ax++)
                    if(linkedlistp->storeddata.address[loop]==alphanum[ay][ax])
                    {
                        sx=ax;
                        sy=ay;
                        break;
                    }
            linkedlistp->storeddata.address[loop]=secret[sy][sx];
        }

        for(loop=0;loop<3;loop++)
        {
            int ax,ay,sx,sy;
            for (ay=0;ay<13;ay++)
                for (ax=0;ax<5;ax++)
                    if(linkedlistp->storeddata.blood[loop]==alphanum[ay][ax])
                    {
                        sx=ax;
                        sy=ay;
                        break;
                    }
            linkedlistp->storeddata.blood[loop]=secret[sy][sx];
        }

        linkedlistp->storeddata.day+=(key[0]+key[1]+key[2]-key[3]);
        linkedlistp->storeddata.month+=(key[3]+key[2]+key[1]-key[0]);
        linkedlistp->storeddata.year+=(key[3]+key[1]+key[2]-key[4]);*/

        encDriver=encDriver->next;
    }
}


/***************************************************
BUilding the huff tree
****************************************************/

int englishLetterFrequencies [36] = {77,11,23,39,120,18,16,56,65,1,4,36,20,62,69,15,1,55,58,86,24,6,20,1,16,1,12,29,17,12,9,7,6,4,3,3};

/*finds and returns the small sub-tree in the forrest*/
int findSmaller (Node *array[], int differentFrom){
    int smaller;
    int i = 0;

    while (array[i]->value==-1)
        i++;
    smaller=i;
    if (i==differentFrom){
        i++;
        while (array[i]->value==-1)
            i++;
        smaller=i;
    }

    for (i=1;i<36;i++){
        if (array[i]->value==-1)
            continue;
        if (i==differentFrom)
            continue;
        if (array[i]->value<array[smaller]->value)
            smaller = i;
    }

    return smaller;
}

/*builds the huffman tree and returns its address by reference*/
void buildHuffmanTree(Node **tree){
    Node *temp;
    Node *array[36];
    int i, subTrees = 36;
    int smallOne,smallTwo;

    for (i=0;i<36;i++){
        array[i] = malloc(sizeof(Node));
        array[i]->value = englishLetterFrequencies[i];
        array[i]->letter = i;
        array[i]->left = NULL;
        array[i]->right = NULL;
    }

    while (subTrees>1){
        smallOne=findSmaller(array,-1);
        smallTwo=findSmaller(array,smallOne);
        temp = array[smallOne];
        array[smallOne] = malloc(sizeof(Node));
        array[smallOne]->value=temp->value+array[smallTwo]->value;
        array[smallOne]->letter=120;
        array[smallOne]->left=array[smallTwo];
        array[smallOne]->right=temp;
        array[smallTwo]->value=-1;
        subTrees--;
    }

    *tree = array[smallOne];

return;
}

/* builds the table with the bits for each letter. 1 stands for binary 0 and 2
for binary 1 (used to facilitate arithmetic)*/
void fillTable(int codeTable[], Node *tree, int Code){
    if (tree->letter<36)
        codeTable[(int)tree->letter] = Code;
    else{
        fillTable(codeTable, tree->left, Code*10+1);
        fillTable(codeTable, tree->right, Code*10+2);
    }

    return;
}




/*****************************************************************************

inputs:
-
outputs:
-
*****************************************************************************/
void compressList(FILE *input, FILE *output, int codeTable[]){
    char bit, c, x = 0;
    int n,length,bitsLeft = 8;
    int originalBits = 0, compressedBits = 0;

    while ((c=fgetc(input))!=10)
    {
        originalBits++;
        if (c==32)
        {
            length = len(codeTable[36]));
            n = codeTable[36];
        }
        else
        {
            length=len(codeTable[c-97]));
            n = codeTable[c-97];
        }

        while (length>0){
            compressedBits++;
            bit = n % 10 - 1;
            n /= 10;
            x = x | bit;
            bitsLeft--;
            length--;
            if (bitsLeft==0){
                fputc(x,output);
                x = 0;
                bitsLeft = 8;
            }
            x = x << 1;
        }
    }

    if (bitsLeft!=8){
        x = x << (bitsLeft-1);
        fputc(x,output);
    }

    /*print details of compression on the screen*/
    fprintf(stderr,"Original bits = %d\n",originalBits*8);
    fprintf(stderr,"Compressed bits = %d\n",compressedBits);
    fprintf(stderr,"Saved %.2f%% of memory\n",((float)compressedBits/
    (originalBits*8))*100);

    return;
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
void decompressList(FILE *input, FILE *output, Node *tree){
    Node *current = tree;
    char c,bit;
    char mask = 1 << 7;
    int i;


    while ((c=fgetc(input))!=EOF)
    {

        for (i=0;i<8;i++)
        {
            bit = c & mask;
            c = c << 1;
            if (bit==0)
            {
                current = current->left;
                if (current->letter!=120)
                {
                    if (current->letter==36)
                        fputc(32, output);
                    else
                        fputc(current->letter+97,output);
                    current = tree;
                }
            }

            else
            {
                current = current->right;
                if (current->letter!=120)
                {
                    if (current->letter==36)
                        fputc(32, output);
                    else
                        fputc(current->letter+97,output);
                    current = tree;
                }
            }
        }
    }

    return;
}


/*invert the codes in codeTable2 so they can be used with mod operator by compressFile function*/
void invertCodes(int codeTable[],int codeTable2[]){
    int i, n, copy;

    for (i=0;i<36;i++){
        n = codeTable[i];
        copy = 0;
        while (n>0){
            copy = copy * 10 + n %10;
            n /= 10;
        }
        codeTable2[i]=copy;
    }

return;
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
