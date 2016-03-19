#include <fcntl.h> 
#include <unistd.h> 
#include <stdio.h>
#define DATABASE_SIZE 3
#define MAX_SURNAME_LENGTH 20

typedef struct _DATA_ENTRY
{
	int ID;
	char *surname;	//max 20 signs with string + \0
}DATA_ENTRY;

void createData(DATA_ENTRY database[], int databaseSize)
{
	 FILE *fp;
	 char str[MAX_SURNAME_LENGTH];
	 int i = 0;
	  
	 fp = fopen("data.txt" , "r");
	 
	 if (fp != NULL)
	 {
		 while(fgets(str,MAX_SURNAME_LENGTH, fp) != NULL)
		 {
			//printf("%s" , str);
			database[i].ID = i;
			database[i].surname = "";
			strcpy(database[i].surname, str);
			i++;
		 }
	 }
	 else
	 {	
		 printf("blad bazy danych");
	 }
}

int main()
{
	DATA_ENTRY database[DATABASE_SIZE] ;
	createData(database, DATABASE_SIZE);
	printf("%d", database[0].ID);
	return 0;
}
