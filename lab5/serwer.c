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
	// TEST DATA
	
	database[0].ID = 1;
	database[0].surname = "Katarzyna";
	
	database[1].ID = 2;
	database[1].surname = "Pawel";
	
	database[2].ID = 3;
	database[2].surname = "Maciek";
}

int main()
{
	//TO DO
	
	// [x] - database
	// [] - create client message
	// [] - parsing client message 
	// [] - create fifo files
	
	DATA_ENTRY database[DATABASE_SIZE] ;
	
	createData(database, DATABASE_SIZE);
	
	
	return 0;
}
