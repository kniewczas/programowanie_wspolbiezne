#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define DB_SIZE 10
#define MAX_LINE 70
#define DB_DATA_FILE "data"

typedef struct _CLIENT_DATA
{
	int id;
	char * surname;
}CLIENT_DATA;

typedef struct _MESSAGE_DATA
{
	int id;
	char * homepath;
}MESSAGE_DATA;

int initiallizeDatabase(void * data)
{
        FILE * fp;

        char buffer[MAX_LINE];
        int i = 0;

        if(fp = fopen(DB_DATA_FILE, "r"))
        {
                while((fgets(buffer, sizeof(buffer), fp) != NULL) && (i<DB_SIZE))
                {
                        ((CLIENT_DATA *)data)[i].surname = (char *) malloc(MAX_LINE);
                        sscanf(buffer, "%d %20s", &((CLIENT_DATA *)data)[i].id, ((CLIENT_DATA *)data)[i].surname);
                        i++;
                }
                fclose(fp);
        }
        else
        {
		printf("Nie moge otworzyc pliku");
                return 1;
        }
        return 0;
}

char * getSurnameByID(void * data, int id)
{
        int i;

        for(i = 0; i < DB_SIZE; i++)
        {
                if(((CLIENT_DATA *)data)[i].id == id)
                {
                        return ((CLIENT_DATA *)data)[i].surname;
                }
        }
        return "User don't exists.";
}


MESSAGE_DATA getClientData(int client, int size)
{
        MESSAGE_DATA data;

        unsigned char * buffer = (char *) malloc(size);

        read(client, buffer, size);

        memcpy(&data.id, buffer, sizeof(int));
        data.homepath = (char *) malloc(size - sizeof(int));
        memcpy(data.homepath, (buffer + sizeof(int)), size - sizeof(int));
        
	free(buffer);
	return data;
}

void sendMessage(int server, void * db, void * data)
{
 
	int length = 0;
	unsigned char * message;
        unsigned char * surname = getSurnameByID(db, ((MESSAGE_DATA *)data)->id);

        message = (char *) malloc(strlen(surname) + sizeof(int) + 1);
        length = strlen(surname);
        memcpy(message, &length , sizeof(int));
        memcpy(message + sizeof(int), surname, length);

        write(server, message, length + sizeof(int));

	free(message);
}

int main()
{
	CLIENT_DATA dbdata[DB_SIZE];
	MESSAGE_DATA data;

	initiallizeDatabase(dbdata);

	mkfifo("clientFifo", 0666);
	mkfifo("serverFifo", 0666);

	int client = open("clientFifo", O_RDONLY);
	int server = open("serverFifo", O_WRONLY);

	int messageLength = 0;
	int bytes = 0;

	while(1)
	{
	     if((bytes = read(client, &messageLength, sizeof(int))) > 0)
             {
		data = getClientData(client, messageLength);
		sendMessage(server, &dbdata, &data);
             }
	}

	close(client);
	close(server);

	unlink("clientFifo");
	unlink("serverFifo");
}
