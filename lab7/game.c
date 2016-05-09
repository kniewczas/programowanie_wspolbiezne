#include "data.h"
#include "controller.h"

int mem, sem;

void start(FIELD * type)
{
	mem = shmget(key, BOARD_SIZE * sizeof(FIELD), 0777|IPC_CREAT);
	if((sem = semget(key, 2, 0777|IPC_CREAT|IPC_EXCL)) > 0)
	{
		(*type) = KRZYZYK;
	}
	else
	{
		sem = semget(key, 2, 077|IPC_CREAT);
		(*type) = KOLKO;
	}
	semctl(sem, 0, SETVAL, 0);
        semctl(sem, 1, SETVAL,1 );
}

void end()
{
      semctl(sem,0,IPC_RMID,0);
      shmctl(mem,IPC_RMID,0);
      exit(0);
}

int main()
{
	FIELD sign;
	FIELD *data,** board;
	struct sembuf *p_op, *p_cl;
	int a,b, i;

	start(&sign);

	if(sign == KRZYZYK)
	{
		p_op = &p1_op;
		p_cl = &p1_cl;
	}
	else
	{
		p_op = &p2_op;
		p_cl = &p2_cl;
	}

	data = shmat(mem, 0, 0);
        board = malloc(3 * sizeof(board[0]));
        for(i = 0; i < 3; i++)
        board[i] = data + i * 3;

	if(sign == KRZYZYK)
	{
		int j;
	        for(i = 0; i < 3; i ++)
                for(j = 0; j< 3; j++)
                board[i][j] = EMPTY;

		printBoard((int**)board);
		printf("Twoj ruch:\n");
		scanf("%d %d", &a, &b);

		if(a == 4)
		{
			end();
		}

		while(userTurn((int**)board, a, b, sign) <0)
		{}
		printBoard((int**)board);
	}

	while(1)
	{
		
		printf("Czekam na ruch przeciwnika:\n");
		semop(sem, p_op, 1);
		printf("Stan:\n");
		printBoard((int**)board);
		do
		{
		printf("Twoj ruch:\n");
		scanf("%d %d", &a, &b);

		if(a == 4)
		{
			end();
		}

		}while(userTurn((int**)board, a, b, sign) < 0);
		
		int gameresult;
		
		gameresult = check((int**)board, sign);
		if(gameresult < 0)
		{
			printf("Koniec gry");
			end();
		}
		
		printf("Twoj ruch:");
		printBoard((int**)board);
		semop(sem, p_cl, 1);
		//printBoard((int**)board);
	}
        free(board);
	end();
}
