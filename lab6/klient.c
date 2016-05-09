#include <stdio.h>
#include <stdlib.h>
#include <linux/msg.h>
#include <linux/ipc.h>
#include <string.h>

typedef struct _MESSAGE
{
      	long typ;
     	char dane[256];
}MESSAGE;

main(int argc, char * argv[])
{
	if(argc > 1)
	{
      		MESSAGE message;
      		int input, output, *p;
      		long ident = getpid();
		int key = 2005;
		int key2 = 2608;
      
      		input = msgget(key, 0777);
		output = msgget(key2, 0777);

		int length = strlen(argv[1]);
      		strcpy(message.dane, argv[1]);
		message.dane[strlen(argv[1])] = '\0';

      		message.typ = ident;
      		msgsnd(input, &message, 255, 0);
      		printf("klient %5ld wyslalem %s\n", ident, message.dane);
      		msgrcv(output, &message, 255, ident, 0);
      		printf("klient %5ld otrzymalem %s\n", ident, message.dane);
		
		return 0;
	}
	else
	{
		printf("nie podales slowa");
		return 1;
	}
   }      
