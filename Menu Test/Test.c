#include <stdio.h>
#include <string.h>

int sign_In(char user[30], char pass[30]){
    FILE *p;
    char user2[30], pass2[30];

    p= fopen("users.txt", "r");


    fscanf(p,"User: %s Password: %s",user2,pass2);

    if( (strcmp(user,user2)==0) && (strcmp(pass,pass2)==0) )
        printf("\nUser and password correct!!!");


    else
        printf("\nUser or password incorrect!\n\n");

    printf("\n\n");

    fclose(p);
    return 0;
}

int main(){
    char user[30], pass[30];

    printf("\nUser:");
    scanf("%s",user);
    printf("\nPassword:");
    scanf("%s",pass);

    sign_In(user, pass);
return 0;
}

