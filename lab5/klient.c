#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

typedef struct _MESSAGE_INFO
{
        unsigned int length;
        int id;
        char * homepath;

}MESSAGE_INFO;

int getID(char * arg)
{
        if(arg != NULL)
        {
                int id = 0;
                sscanf(arg, "%d", &id);
                return id;
        }
        else
        {
                printf("Nie podales id!\n");
                return -1;
        }
}

void sendMessage(int client, void * data)
{
        unsigned char * buffer;
        buffer = (char *) malloc(sizeof(int) + ((MESSAGE_INFO *)data)->length);
        memcpy(buffer, &((MESSAGE_INFO *)data)->length, sizeof(int));
        memcpy(buffer + sizeof(int), &((MESSAGE_INFO *)data)->id, sizeof(int));
        memcpy(buffer + (2 * sizeof(int)), ((MESSAGE_INFO *)data)->homepath, ((MESSAGE_INFO *)data)->length - sizeof(int));

        write(client, buffer, ((MESSAGE_INFO *)data)->length + sizeof(int));
        free(buffer);
}

void getServerData(int server)
{
        unsigned char * surname = malloc(13);;
        int length = 0;
	int i,j;

	fsync(server);
	read(server, &i, sizeof(int));
	if((i=read(server, surname, i)) > 0)
	{
		for(j=0;j<8;j++)
		printf(" %d " , surname[j]);
	//printf("%s", surname);
	}
	printf("%s", surname);
//	if((i = read(server, &length, sizeof(int))) > 0)
//	printf("%d \n\n received[%d]", length, i);
//	surname = malloc(8);
	//read(server, surname,8);
	//int j;
	//for(j = 0; j< 8; j++)
	//printf("%d\n", surname[j]);
//        if((i = read(server, &length, sizeof(int))) > 0)
//	{
	   //read(server, &length, sizeof(int));
           //surname = (char *) malloc(length);
           //read(server, surname, length);
           //printf("%s   \n   ", surname);
//	}
        //free(surname);
}

int main(int argc, char * argv[])
{
	MESSAGE_INFO data;
	
	data.id = getID(argv[1]);
	data.homepath = getenv("HOME");
	data.length = sizeof(int) + strlen(data.homepath);
	
	if(data.id < 0)
	return 1;

	int client = open("clientFifo", O_WRONLY);
	int server = open("serverFifo", O_RDONLY);

	sendMessage(client, &data);
	getServerData(server);

	//int a =5;
	//int b = 10;
	//write(client, &a, sizeof(int));
	//write(client, &b, sizeof(int));
}
