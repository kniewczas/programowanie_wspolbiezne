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
        int id = -1;

	if(arg != NULL)
        {
                sscanf(arg, "%d", &id);
        }
        else
        {
                printf("Nie podales id!\n");
        }
	return id;
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
	int bytes = 0;

	fsync(server);
	read(server, &length, sizeof(int));
	if((bytes=read(server, surname, length)) > 0)
	{
		//for(j=0;j<8;j++)
	}
	printf("%s", surname);
}

int main(int argc, char * argv[])
{
	MESSAGE_INFO data;
	
	data.id = getID(argv[1]);
	data.homepath = getenv("HOME");
	data.length = sizeof(int) + strlen(data.homepath);
	
	if(data.id < 0)
	{
		return 1;
	}

	int client = open("clientFifo", O_WRONLY);
	int server = open("serverFifo", O_RDONLY);

	sendMessage(client, &data);
	getServerData(server);
}
