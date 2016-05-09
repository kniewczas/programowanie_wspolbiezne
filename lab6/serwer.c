#include <stdio.h>
#include <stdlib.h>
#include <linux/msg.h>
#include <linux/ipc.h>
#include <string.h>
#define DB_SIZE 6

typedef struct _MESSAGE
{
	long typ;
      	char dane[256];
}MESSAGE;

typedef struct _DICTIONARY
{
	char * plWord;
	char * engWord;
}DICTIONARY;

void initiallizeDatabase(void * db)
{
	((DICTIONARY *) db)[0].plWord = "drzwi";
	((DICTIONARY *) db)[0].engWord = "drzwi";
	((DICTIONARY *) db)[1].plWord = "wskaznik";
	((DICTIONARY *) db)[1].engWord = "pointer";
	((DICTIONARY *) db)[2].plWord = "okno";
	((DICTIONARY *) db)[2].engWord = "window";
	((DICTIONARY *) db)[3].plWord = "biurko";
	((DICTIONARY *) db)[3].engWord = "desk";
	((DICTIONARY *) db)[4].plWord = "torba";
	((DICTIONARY *) db)[4].engWord = "bag";
	((DICTIONARY *) db)[5].plWord = "kurtka";
	((DICTIONARY *) db)[5].engWord = "jacket";
}

int compare(void * db, int length, const char * word)
{
//	printf("czesc");
	int i;
	char temp[256];
	strcpy(temp, word);
	temp[strlen(word)] = '\0';

//	printf("powornuje %s" , temp);
	for(i = 0; i < length; i++)
	{
		if(strcmp(((DICTIONARY *) db)[i].plWord, temp) == 0)
		{
			printf("%s", ((DICTIONARY *) db)[i].engWord);
			return i;
		}
	}
//	printf("Nie znaleziono");
	return 0;
}

main()
{
      	MESSAGE message;
	DICTIONARY dictionary[DB_SIZE];

	initiallizeDatabase(dictionary);

      	int input, output, *p;
	int key = 2005;
	int key2 = 2608;

      	input = msgget(key, 0777|IPC_CREAT);
	output = msgget(key2, 0777|IPC_CREAT);
	
	while(1)
	{
      		if(msgrcv(input, &message, 255, 0, 0) > 0)
		{
			//printf("serwer: otrzymalem %s od %5ld\n", message.dane, message.typ);

				int result = compare(dictionary, DB_SIZE, message.dane);
				memset(message.dane, 0x00, 256);
				if(result > 0)
				{
					strcpy(message.dane, dictionary[result].engWord);
        			}
				else
				{
					strcpy(message.dane, "Nie znaleziono");
				}
				//printf("serwer: odsylam %s do %5ld\n", dictionary[result].engWord, message.typ);
      				msgsnd(output, &message, 255, 0);
		}
	}
	msgctl(input, IPC_RMID, 0);
	msgctl(output, IPC_RMID, 0);
   }   
