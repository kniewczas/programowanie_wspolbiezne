#include <fcntl.h> 
#include <unistd.h> 
#include <stdio.h>
#define BLOCK_SIZE 512


void getMessage()
{
   int dane = 0;
   char buffer[BLOCK_SIZE] ={0x00,};
 
   
	
   while((dane = open("dane.txt", O_RDWR)) < 0)
   {
	   
   }
	
   if(dane > 0)
   {
		while(read(dane,buffer,512) < 1)
		{
		}	
		printf("%s" , buffer);
   }
}

void sendMessage()
{
	int wyniki;
	char buffer[BLOCK_SIZE] ={0x00,};
	char sign[1] = {0x00,};
	int counter = 0;
	
	while((wyniki = open("wyniki.txt", O_RDWR|O_CREAT|O_EXCL, 0711)) < 0)
	{
		
	}
	
	if(wyniki > 0)
	{
		printf("Serwer:\n");
		while(1)
		{
			read(0,sign,1);
			
			if(sign[0] == (char)27)
			{
				write(wyniki, buffer, counter);
				close(wyniki);
				break;
			}
			
			buffer[counter] = sign[0];
			counter++;
		}
	}
}

void closeConnection()
{
		remove("lockfile");
		remove("dane.txt");
}

int main()
{
	printf("==============================\n");
	printf("KOMUNIKATOR  (Konto: serwer)\n");
	printf("==============================\n");
	
	while(1)
	{

		
		getMessage();
		
		sendMessage();
		
		closeConnection();
		
		printf("\n\n");
	}
		
	return 0;
}




