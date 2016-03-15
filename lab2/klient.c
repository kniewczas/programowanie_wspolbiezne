#include <fcntl.h> 
#include <unistd.h> 
#include <stdio.h>
#define BLOCK_SIZE 512

void openConnection()
{	
	while (open("lockfile",O_CREAT|O_EXCL, 0711)==-1)
    {
       printf("Serwer zajety, prosze czekac\n\n");	
       sleep(4);
    }
}

void sendMessage()
{
	int dane;
	char buffer[BLOCK_SIZE] ={0x00,};
	char sign[1] = {0x00,};
	int counter = 0;
	
	char username[100] = {0x00,};
	getlogin_r(username, 100);
	char output[1024] = {0x00,};
	
	while((dane = open("dane.txt", O_RDWR|O_CREAT|O_APPEND, 0711)) < 0)
	{
		
	}
	
	if(dane > 0)
	{
			printf("\n%s:\n", username);
			while(1)
			{
				read(0,sign,1);
				if(sign[0] == 27)
                {
					counter = sprintf(output, "%s:\n%s" , username, buffer);
					write(dane, output, counter);
					break;
				}
				buffer[counter] = sign[0];
				counter++;
				
			}
	}
}

void getMessage()
{
	int wyniki;
	char buffer[BLOCK_SIZE] ={0x00,};

	while((wyniki = open("wyniki.txt", O_RDWR)) < 0)
	{
	}
		
	if(wyniki > 0)
	{
		while(read(wyniki,buffer,512) < 1)
		{
		}
		printf("Serwer:\n%s", buffer);
		close(wyniki);
	}
}

void closeConnection()
{
	remove("wyniki.txt");
}

///////////////////////////////////////////////////////////
//
//  compile with pattern below:
//  ./klient.c server_name

int main(int argc, char *argv[]) 
{
	char username[100] = {0x00,};
	getlogin_r(username, 100);
	
	///////////////////////////////////////////////////
	// If I can ./../
	///////////////////////////////////////////////////
	char path[200];
	getcwd(path, 200);
	printf("pwd -> %s\n", path);	
		
	
	printf("==============================\n");
	printf("KOMUNIKATOR (Konto:%s)\n" , username);
	printf("==============================\n\n");

		openConnection();
		
		sendMessage();
		
		getMessage();

		closeConnection();

	getchar();
    return 0;
}
		
