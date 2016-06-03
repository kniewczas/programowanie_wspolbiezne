#include "data.h"

//START STATE

void start();
void game();
void end();

void cleanBoard()
{
        int i, j;
        for(i = 0; i < 8; i ++)
            for(j = 0; j< 8; j++)
                board[i][j] = EMPTY;
}

void setFrameFields()
{
	}

void setSheepFields()
{
        board[0][1] = SHEEP;
        board[0][3] = SHEEP;
        board[0][5] = SHEEP;
        board[0][7] = SHEEP;
}

//do zmiany: user wybiera ktora krawedz

void setWolfFields()
{
	board[7][0] = WOLF;
} 

void initiallizeBoard()
{
	cleanBoard();
	setSheepFields();
	setWolfFields();
}

//CYCLE STATE

// a)board view 

void printBoard()
{
       int i,j;

       for(i = 0; i < 8; i++)
       {
                for(j = 0; j < 8; j++)
                {
                        if(board[i][j] == EMPTY)
                        {
							 printf(" ");
						 }
                        else if(board[i][j] == WOLF)
                        {
							 printf("W");
						}
                        else if(board[i][j] == SHEEP)
                        {
							printf("S");
						}
                        printf("|");
                }
                printf("\n");
        }
        printf("\n");
}

//b) movement control

int userTurn(int col, int row, FIELD sign)
{
        if((col < ROW_SIZE) && (row < ROW_SIZE) && (board[col][row] == EMPTY))
        {
                board[col][row] = sign;
                return 0;
        }
        else
        {
                return -1;
        }
}

void move(FIELD type)
{
	int x, y;
	
    do
    {
		printf("Wprowadz indeksy kolumn po spacji\n");
		scanf("%d %d", &x, &y);
		
	}while(userTurn(x, y, type) < 0);
}

void playerTurn(FIELD type)
{
	//message
	printf("Twoj ruch\n");
	
	//print 
	printBoard(board);
	
	//turn
	move(type);
	
	//print
	printBoard(board);		
}

int check(int ** buffer, FIELD sign)
{
        return 0;
}






