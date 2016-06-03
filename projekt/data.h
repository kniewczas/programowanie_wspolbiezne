#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define BOARD_SIZE 64
#define ROW_SIZE 8
#define COL_SIZE 8

#define key 2006

int mem, sem;
uint8_t isFirst;

struct sembuf p1_op = {0,-1,0},
              p1_cl = {1,1,0},
              p2_op = {1,-1,0},
              p2_cl = {0,1,0};

typedef enum _FIELD
{
        EMPTY = 0,
        WOLF,
        SHEEP,
        FRAME
}FIELD;

FIELD *data;
FIELD ** board;



