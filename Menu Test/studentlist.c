/*******************************************************************************
48430 Introduction to C Programming - Assignment 2
Name: Omar Salam
Student ID: 12002376
Date of submission: 8/09/17
A brief statement on what you could achieve (less than 50 words):


- Functional Menu
- Filtering invalid input and responding
- Adding Students with a maximum class size
- Deleting last student
- Storing Student list in DB
- Displaying student list

A brief statement on what you could NOT achieve (less than 50 words):

- Print the name with spaces


*******************************************************************************/

/*******************************************************************************
List of header files - do NOT use any other header files. Note that stdlib and
cstring are included in case you want to use any of the functions in there.
However the task can be achieved with stdio only.
*******************************************************************************/

#include <stdio.h> 		  /* Essential Functions   */
#include <stdlib.h>		 /*  Mainly for exit()    */
#include <string.h>		/*   Manipulating String */

/*******************************************************************************
List preprocessing directives - you may define your own.
*******************************************************************************/
/*Max students in a class*/
#define MAX_CLASS_SIZE 5
#define MAX_NAME_SIZE 11
#define DB_FILE_NAME "database"


struct student {
	struct date {
		/* structure of birthday*/
		unsigned int day;
		unsigned int month;
		unsigned int year;
		}birthday;
	/* Declaration of Char Name*/
	char name[MAX_NAME_SIZE];
       /*Declaration of float GPA */
	float gpa;

};

void printMenu(void);

int IsDayValid(int storDay);
int IsMonthValid(int storMonth);
int IsYearValid(int storYear);
int sign_In(char user[30], char pass[30]);
/*******************************************************************************
Main - Contains Menu with appropriate functions
*******************************************************************************/
int main(void) {



char user[30], pass[30];

    printf("\nUser:");
    scanf("%s",user);
    printf("\nPassword:");
    scanf("%s",pass);

    sign_In(user, pass);
return 0;
}

/*******************************************************************************
printMenu
This function prints the initial menu with all instructions on how to use this
program.
Inputs:
- Name
- Date of birth (day, month, year)
- GPA
Outputs:
- Add student to the list
- Delete last student in the list
- Display list of Student(s)
- Create a database txt file
- Read student list from the database
- Exit program
*******************************************************************************/
void printMenu(void)	{
	printf("\n\n"
	"1. add student\n"
	"2. delete last student\n"
	"3. display student list\n"
	"4. save the student list to the database\n"
	"5. read the student list from the database\n"
	"6. exit the program\n"
	"Enter your choice>");
}



/*			 Function checks if day is between the values of 1-31			  */
int IsDayValid(int storDay) 	{

	if (storDay<1)	{
		printf("Invalid day. \n");
		return 0;
	}
	else if(storDay>31) 	{
		printf("Invalid day. \n");
		return 0;
	}
	else	{
		return 1;
	}
}

/******************************************************************************
	Data Validation Functions to make sure data is within desired parameters
*******************************************************************************/

/* 				Function checks if month is between 1-12					  */
int IsMonthValid(int storMonth) 	{
	if (storMonth<1)	{
		printf("Invalid month. \n");
		return 0;
	}
	else if(storMonth>12)	{
		printf("Invalid month. \n");
		return 0;
	}
	else	{
	        return 1;
	}
}

/* 				Checks if the year is between the values of 1800-2017		  */
int IsYearValid(int storYear)	{
	if (storYear<1800)	{
		printf("Invalid year. \n");
	        return 0;
	}
	else if(storYear>2017)	{
		printf("Invalid year. \n");
	        return 0;
	}
	else	{
	        return 1;
	}
}


/******
Login
******/
int sign_In(char user[30], char pass[30]){
	int Menuchoice=0;
	FILE * fPointer;
	int arraycount=0;
	int count;
	struct student studentlist[MAX_CLASS_SIZE];
FILE *p;
    char user2[30], pass2[30];

    p= fopen("users.txt", "r");


    fscanf(p,"User: %s Password: %s",user2,pass2);

    if( (strcmp(user,user2)==0) && (strcmp(pass,pass2)==0) ){
       printMenu();

do {


    /*Captures input for menu selection*/
    scanf("%d",&Menuchoice);


	switch(Menuchoice)	{

		case 1:		{
			if (arraycount<MAX_CLASS_SIZE)	  {

                printf("Enter name>");
				scanf("%s",studentlist[arraycount].name);


			day:
		         printf("Enter birthday: day>");
		         char dy[100];

            	 scanf("%s", dy);

            	 	 int a=atoi(dy);
            	     if (IsDayValid(a)==0)	{
                	             goto day;
            	     }

            	     studentlist[arraycount].birthday.day=a;


	        month:

		          printf("Enter birthday: month>");
		          char mon[100];

		          scanf("%s",mon);
		          	  int b=atoi(mon);
		          	  if(IsMonthValid(b)==0)	{
		          		  	  	 goto month;
		          	  }

            	      studentlist[arraycount].birthday.month=b;


	          year:

                   printf("Enter birthday: year>");
                   char yr[100];

            	   scanf("%s",yr);/*Take the year input as a string*/
            	   	   int c=atoi(yr);/*convert the string into integer*/
            	       if(IsYearValid(c)==0)	{
            	    	   	   	   goto year;
            	       }

            	       studentlist[arraycount].birthday.year=c;

	           gpa:

			       printf("Enter GPA>");
			       char g[1000];

                   scanf("%s", g);
                   	  float e= atof(g);/*GPA string to Floating point (Double)*/

                   	  if(e<0 || e>4.0000)	{
			          printf("Invalid GPA. \n");
			          	  	  	goto gpa;
			        }

                   	studentlist[arraycount].gpa=e;

                   	arraycount++;

		}

		else	{

			 printf("Class is full \n");
			 }
				break;
		}


		case 2:		{   /* Wont delete if class is empty */
				if (arraycount==0)	{
					printf("Class is empty\n");
				}
				else if(arraycount>0)	{
                    /* Delete last line of the list */
				    studentlist[arraycount-1]=studentlist[arraycount];

                    /* List of student is decrease from bottom */
				    arraycount--;
			}
		    	 break;
		}

     	 case 3:	{
     		 	 	 /* Check if class has students */
		    	    if(arraycount==0)	{
		    		    printf("Class is empty\n");
				  }

				else	{
				        printf("Name       Birthday   GPA   \n");
			    	    printf("---------- ---------- ------\n");

			/*displays the studentlist until the end of it */

			    for (count=0;count<arraycount;count++) {
			    		printf("%-10.10s",studentlist[count].name);
                        printf(" %02d",studentlist[count].birthday.day);
			    		printf("-");
			    		printf("%02d",studentlist[count].birthday.month);
			    		printf("-");
			    		printf("%d",studentlist[count].birthday.year);
			    		printf(" %.4f",studentlist[count].gpa);
					printf("\n");
			    		}
					}
		    	break;
			 }

     	 case 4:	{
		        /*Write student list to txt*/
				fPointer = fopen("database.txt", "w");
                for (count=0;count<arraycount;count++)	{

                	fprintf(fPointer,"%-10.10s %d \t %d \t %d \t %.4f \n",
                           studentlist[count].name,
                           studentlist[count].birthday.day,
                           studentlist[count].birthday.month,
                           studentlist[count].birthday.year,
                           studentlist[count].gpa);
		    	    }
		    	    fclose(fPointer);

		    	 break;
			   }


     	 case 5:

		     	 /* Read student list from db */
		    	 fPointer = fopen("database.txt", "r");
		    	    arraycount=0;
		    	    if (fPointer!=NULL)	{
				   do	{
			     fscanf(fPointer,"%s %d %d %d %f\n",
                        studentlist[arraycount].name,
                        &studentlist[arraycount].birthday.day,
                        &studentlist[arraycount].birthday.month,
                        &studentlist[arraycount].birthday.year,
                        &studentlist[arraycount].gpa);

				    	arraycount++;
					}	while(!feof(fPointer));
		   		}
		   		fclose(fPointer);
		    	        break;

		 case 6:

		   		/*exiting the program*/
		   		exit(0);
		  		break;

		   default:

		    /*for any value outside the menu - careless users*/
		    printf("Invalid choice.\n");
		    	 break;

		        }
	     }
               while(Menuchoice!=6);


    }else{
        printf("\nUser or password incorrect!\n");
	}

    fclose(p);
    return 0;
}
