#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

typedef struct _CLIENT_DATA
{
	int messageLength;
	int ID;
	char * homePath;
}CLIENT_DATA;

 int getHomePath(CLIENT_DATA *data)
{
	data->homePath = getenv("HOME");
	
	if(data->homePath != NULL)
	{
	   return 0;
	}
	return 1;
}

int main()
{
	//int result;
	
	CLIENT_DATA data;
	CLIENT_DATA *data2 = &data;
	CLIENT_DATA *data3 = &data; 
	int length = 0;
	unsigned char * message = malloc(sizeof(CLIENT_DATA));


	data2->ID = 1;
	data2->homePath = getenv("HOME");
	length = sizeof(int) + strlen(data2->homePath);
	data2->messageLength = length;
	
	memcpy(message, data2, sizeof(*data2));
	printf("%c" , message[0]);
	
	//przekazac message przez kolejke fifo
	//dopisac parser wiadomosci po stronie serwera
	
	//memcpy(data3, message, strlen(message));
	
	/*if(result == 1)
	{
		printf("Writing name failed");
		return 1;
	}
	else
	{
		printf("%s", data2->homePath);	
	}*/
	
	printf("%s" , data3->homePath);	
		
	return 0;
}
