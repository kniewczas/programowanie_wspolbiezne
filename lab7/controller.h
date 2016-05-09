
void initiallize(int * board)
{
        int i;
        for(i = 0; i < BOARD_SIZE; i++)
        board[i] = EMPTY;
}

void printBoard(int ** buffer)
{
        int i,j;
        printf("\n");

        for(i = 0; i < COL_SIZE; i++)
        {
                for(j = 0; j < ROW_SIZE; j++)
                {
                        if(buffer[i][j] == EMPTY) printf(" ");
                        else if(buffer[i][j] == KOLKO) printf("O");
                        else printf("X");
                        printf("|");
                }
                printf("\n");
        }
}

int userTurn(int ** buffer, int col, int row, FIELD sign)
{
        if((col < COL_SIZE) && (row < ROW_SIZE) && (buffer[col][row] == EMPTY))
        {
                buffer[col][row] = sign;
		return 0;
        }
        else
        {
                printf("Niedozwony ruch\n");
		return -1;
        }
}

int check(int ** buffer, FIELD sign)
{
        int i, j;
	int result = 0; 
	FIELD data = sign;

/*	for(j = 0; j < 3; j++)
	{	for(i = 0; i < 3; i++)
		{
			if(buffer[j][i] != sign)
			{
				printf("%d", buffer[j][i]);
				break;
			}
			return 2;
		}
	}

	for(j = 0; j < 3; j++)
	{
		for(i = 0; i < 3; i++)
		{
			if(buffer[i][j] != sign)
			{
				break;
			}
			return 2;
		}
	}

*/
	for(i = 0; i < 3; i++)
		for(j = 0; j<3 ; j++)
		if(buffer[i][j] == EMPTY)
		{
			return 1;
		}

        return -1;
}


