#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define DB_SIZE 10
#define MAX_LINE 70

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
        char buf[MAX_LINE];
        int i = 0;

        if(fp = fopen("data", "r"))
        {
                while((fgets(buf, sizeof(buf), fp) != NULL) && (i<DB_SIZE))
                {
                        ((CLIENT_DATA *)data)[i].surname = (char *) malloc(MAX_LINE);
                        sscanf(buf, "%d %20s", &((CLIENT_DATA *)data)[i].id, ((CLIENT_DATA *)data)[i].surname);
                        i++;
                }
                fclose(fp);
        }
        else
        {
		printf("nie moge otwrozy cpliku");
                return 1;
        }
        return 0;
}

char * getSurnameByID(void * data, int id)
{
        int i;

	printf("my id: %d", id);
        for(i = 0; i < DB_SIZE; i++)
        {
                if(((CLIENT_DATA *)data)[i].id == id)
                {
			printf("inside: %s", ((CLIENT_DATA *)data)[i].surname);
                        return ((CLIENT_DATA *)data)[i].surname;
                }
        }
        return "User don't exists.";
}


MESSAGE_DATA getClientData(int client, int size)
{
        MESSAGE_DATA data = {0,""};
        unsigned char * message;

        message = (char *) malloc(size);
        read(client, message, size);
        memcpy(&data.id, message, sizeof(int));
        data.homepath = (char *) malloc(size - sizeof(int));
        memcpy(data.homepath, (message + sizeof(int)), size - sizeof(int));
        free(message);
        return data;
}

void sendMessage(int server, void * db, void * data)
{
 
	unsigned char * message;
        unsigned char * surname = getSurnameByID(db, ((MESSAGE_DATA *)data)->id);
	int length;

	printf("surname:\n %s\n", surname);
        message = (char *) malloc(strlen(surname) + sizeof(int) + 1);
        length = strlen(surname);
	printf("length :\n %d\n" , length);
        
        memcpy(message, &length , sizeof(int));
        memcpy(message+sizeof(int), surname, length);
	length += sizeof(int);

	//int i =0;
	//for(i = 0; i< length; i++)
	//{
	//	printf(" %d " , message[i]); 
	//}
        write(server, message, length);
	free(message);
}

int main()
{
	CLIENT_DATA dbdata[DB_SIZE] = {{0,""},};
	MESSAGE_DATA data;
	initiallizeDatabase(dbdata);

	mkfifo("clientFifo", 0666);
	mkfifo("serverFifo", 0666);

	int client = open("clientFifo", O_RDONLY);
	int server = open("serverFifo", O_WRONLY);

	int x = 0;
	int i = 0;

	while(1)
	     if((i = read(client, &x, sizeof(int))) > 0)
             {
		printf("Received: [%d]\n bits: %d\n", x,i);
		data = getClientData(client, x);
		sendMessage(server, &dbdata, &data);
             }

	close(client);
	close(server);

	unlink("clientFifo");
	unlink("serverFifo");
}
