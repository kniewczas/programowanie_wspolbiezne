#include "controller.h"
#include <signal.h>
//HELP: moba x term



void printTest()
{
	int i,j;
		
	for(j = 0; j < COL_SIZE; j++)
	{
		for(i = 0; i < ROW_SIZE; i++)
		{
			printf("%d ", board[j][i]);
		}
		printf("\n");
	}
}

void setSemafors(struct sembuf **p_op, struct sembuf **p_cl)
{
		if((sem = semget(key, 2, 0777|IPC_CREAT|IPC_EXCL)) > 0)
        {
			isFirst = 1;
        }	
        else
        {
			sem = semget(key, 2, 077|IPC_CREAT);
		}
		semctl(sem, 0, SETVAL, 0);
		semctl(sem, 1, SETVAL,1 );
		
		if(isFirst)
        {
             *p_op = &p1_op;
             *p_cl = &p1_cl;
        }
        else
        {
             *p_op = &p2_op;
             *p_cl = &p2_cl;
        }
}

void setMemory()
{
		int i ;
		signal(SIGTSTP, end);
	
		mem = shmget(key, BOARD_SIZE * sizeof(FIELD), 0777|IPC_CREAT);
		
		data = shmat(mem, 0, 0);
		
        board = malloc(BOARD_SIZE * sizeof(board[0]));
	    
	    for(i = 0; i < ROW_SIZE; i++)
	    {
			board[i] = data + i * ROW_SIZE;
			board[0][0] = EMPTY;
		}  
}

void start()
{
		if(isFirst)
        {
                initiallizeBoard();
                playerTurn(isFirst ? WOLF : SHEEP);
        }
}

void game(struct sembuf **p_op, struct sembuf **p_cl)
{
	    while(1)
        {
              printf("\nCzekam na ruch przeciwnika...\n");
                
              semop(sem, *p_op, 1);
			  playerTurn(isFirst ? WOLF : SHEEP);
              
              semop(sem, *p_cl, 1);              
        }
}

void end()
{
      semctl(sem,0,IPC_RMID,0);
      shmctl(mem,IPC_RMID,0);     
      free(board);
      
      exit(0);
}

int main()
{
        
        struct sembuf *p_op, *p_cl;

        setSemafors(&p_op, &p_cl);
              
        setMemory(); 
        
		start();	
		
		game(&p_op, &p_cl);		
        
        end();
        
        return 0;
}




