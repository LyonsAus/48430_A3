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


/* Omar */
void printMenu(int mode){
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
/* Hasan */
void addDriver(){
  /* From A2 - sList variable is a counter of the number of students in the array
  if(sList == MAX_CLASS_SIZE){
		printf("Class is full\n");
	}
	else{
		char newName;
		int newDay = -1;
		int newMonth = -1;
		int newYear = -1;
		float newGPA = -1.0f;

		printf("Enter name>");
		scanf("%s", &newName);
		strcpy(studentlist[sList].name, &newName);


		while(newDay <= 0 || newDay > 31){
			printf("Enter birthday: day>");
			scanf("%d", &newDay);
				if(newDay <= 0 || newDay > 31){
				printf("Invalid day. ");
				}
			}
			studentlist[sList].bday.day = newDay;

		while(newMonth <= 0 || newMonth > 12){
			printf("Enter birthday: month>");
			scanf("%d", &newMonth);
				if(newMonth <= 0 || newMonth > 12){
				printf("Invalid month. ");
				}
			}
			studentlist[sList].bday.month = newMonth;

		while(newYear < 1800 || newYear > 2017){
			printf("Enter birthday: year>");
			scanf("%d", &newYear);
				if(newYear < 1800 || newYear > 2017){
					printf("Invalid year. ");
				}
			}
			studentlist[sList].bday.year = newYear;

		while(newGPA < 0 || newGPA > 4){
			printf("Enter GPA>");
			scanf("%f", &newGPA);
				if(newGPA < 0 || newGPA > 4){
					printf("Invalid gpa. ");
				}
			}
			studentlist[sList].GPA = newGPA;

			sList++;
		}
  */
}
/* Alex/Hasan */
void deleteDriver(){

}
/* Alex/Hasan */
void deleteList(){

}
/* Hasan */
void printList(){

}
/* Alex/Hasan */
void searchList(){

}
/* Hasan */
void encryptList(){

}
/* Godwin/Minh */
void compressList(){

}
/* Hasan */
void decryptList(){

}
/* Godwin/Minh */
void decompressList(){

}
/* Godwin/Minh */
/* Huffman tree coding
 
typedef struct node_t {
	struct node_t *left, *right;
	int freq;
	char c;
} *node;
 
struct node_t pool[256] = {{0}};
node qqq[255], *q = qqq - 1;
int n_nodes = 0, qend = 1;
char *code[128] = {0}, buf[1024];
 
node new_node(int freq, char c, node a, node b)
{
	node n = pool + n_nodes++;
	if (freq) n->c = c, n->freq = freq;
	else {
		n->left = a, n->right = b;
		n->freq = a->freq + b->freq;
	}
	return n;
}
 
/* priority queue /*
void qinsert(node n)
{
	int j, i = qend++;
	while ((j = i / 2)) {
		if (q[j]->freq <= n->freq) break;
		q[i] = q[j], i = j;
	}
	q[i] = n;
}
 
node qremove()
{
	int i, l;
	node n = q[i = 1];
 
	if (qend < 2) return 0;
	qend--;
	while ((l = i * 2) < qend) {
		if (l + 1 < qend && q[l + 1]->freq < q[l]->freq) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[qend];
	return n;
}
 
/* walk the tree and put 0s and 1s /*
void build_code(node n, char *s, int len)
{
	static char *out = buf;
	if (n->c) {
		s[len] = 0;
		strcpy(out, s);
		code[n->c] = out;
		out += len + 1;
		return;
	}
 
	s[len] = '0'; build_code(n->left,  s, len + 1);
	s[len] = '1'; build_code(n->right, s, len + 1);
}
 
void init(const char *s)
{
	int i, freq[128] = {0};
	char c[16];
 
	while (*s) freq[(int)*s++]++;
 
	for (i = 0; i < 128; i++)
		if (freq[i]) qinsert(new_node(freq[i], i, 0, 0));
 
	while (qend > 2) 
		qinsert(new_node(0, 0, qremove(), qremove()));
 
	build_code(q[1], c, 0);
}

void encode(const char *s, char *out)
{
	while (*s) {
		strcpy(out, code[*s]);
		out += strlen(code[*s++]);
	}
}
 
void decode(const char *s, node t)
{
	node n = t;
	while (*s) {
		if (*s++ == '0') n = n->left;
		else n = n->right;
 
		if (n->c) putchar(n->c), n = t;
	}
 
	putchar('\n');
	if (t != n) printf("garbage input\n");
}
