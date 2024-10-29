
#include <stdio.h>			/*printf*/

#include "knight_tour.h"	/*typedef, function declarations*/

#define TIME_LIMIT 300
#define BACK_TRACK 0
#define HEURISTIC 1

static void RunKnightsTourHeuristicTest(void);
static void RunKnightsTourBackTrackTest(void);
static void PrintSolution(position_t path[PATH_LENGTH]);


int main(void)
{
	RunKnightsTourHeuristicTest();
	RunKnightsTourBackTrackTest();
	
	return 0;
}


/********************************************/
/*				  Test Functions			*/
/********************************************/


void RunKnightsTourHeuristicTest(void)
{
	position_t path[PATH_LENGTH] = {0};
	position_t starting_position = BuildPosition(2, 4);
	
	knights_tour_status_e status = RunKnightsTour(path, starting_position, HEURISTIC, TIME_LIMIT);
	
	if (SUCCESS == status)
	{
		printf("Heuristic Knight Tour Succeed!\n");
	}
	else if (BAD_PATH == status)
	{
		printf("Heuristic Knight Tour Failed! (Bad Path)\n");
	}
	else
	{
		printf("Back Track Knight Tour Failed! (Time Exeeded)\n");
	}
	
	PrintSolution(path);
}

void RunKnightsTourBackTrackTest(void)
{
	position_t path[PATH_LENGTH] = {0};
	position_t starting_position = BuildPosition(0, 0);
	
	knights_tour_status_e status = RunKnightsTour(path, starting_position, BACK_TRACK, TIME_LIMIT);
	
	if (SUCCESS == status)
	{
		printf("Back Track Knight Tour Succeed!\n");
	}
	else if (BAD_PATH == status)
	{
		printf("Back Track Knight Tour Failed! (Bad Path)\n");
	}
	else
	{
		printf("Back Track Knight Tour Failed! (Time Exeeded)\n");
	}
	
	PrintSolution(path);
}


/********************************************/
/*				  Help Functions			*/
/********************************************/


int Row(position_t x)
{
    return x&0x0F;   
}                                

int Col(position_t y)
{
 	y>>=4;
 	
	return y; 
} 

void PrintSolution(position_t path[PATH_LENGTH]) 
{
    int col_index = 0;
    int row_index = 0;
    
    for (col_index = 0; col_index < NUM_OF_ROWS; ++col_index)
     {
        for (row_index = 0; row_index < NUM_OF_ROWS; ++row_index)
         {
            printf("| %d%c |", Row(path[col_index * NUM_OF_ROWS + row_index]) + 1, 
            					Col(path[col_index * NUM_OF_ROWS + row_index]) + 97);
        }
        printf("\n");
    }
}


