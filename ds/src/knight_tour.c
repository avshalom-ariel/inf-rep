/*
Name: Avshalom Ariel
Reveiwer: Yarnden
Date: 09/07/2024
status: Approved
*/

#include <stddef.h>			/*size_t*/
#include <assert.h>			/*assert*/
#include <time.h>			/*time*/

#include "knight_tour.h"	/*typedef, function declarations*/

#define IVALID_POSITION (unsigned char)(-1)
#define MAX_POSSIBLE_MOVES 8
#define VALID_DIRECTION 2
#define ROW_MASK 0x70 		/*01110000*/
#define COL_MASK 7 			/*00000111*/
#define ROW_INDEX 0
#define COL_INDEX 1
#define MAX_ROW_POSSIBLE 7
#define MAX_COL_POSSIBLE 7
#define HALF_BYTE 4
#define FULL_BITMAP (size_t)(-1)

static knights_tour_status_e BackTrackKnightTour(position_t curr, size_t index, size_t bit_map,
						position_t path[PATH_LENGTH], unsigned int time_limit);
static knights_tour_status_e HeuristicKnightTour(position_t path[PATH_LENGTH], size_t bit_map,
                                     position_t starting_position, unsigned int time_limit);
static position_t AddMove(position_t position, size_t index, size_t bit_map);
static size_t Row(position_t position);
static size_t Col(position_t position);
static size_t SetBit(position_t position, size_t bit_map);
static int CheckBit(position_t position, size_t bit_map);
static position_t NextHeuristic(position_t position, size_t bit_map);

static char g_moves_lut[MAX_POSSIBLE_MOVES][VALID_DIRECTION] = 
											{{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, 
											{-2, -1}, {-1, -2}, {1, -2}, {2, -1}};


/********************************************/
/*			   API Functions				*/
/********************************************/


knights_tour_status_e RunKnightsTour(position_t path[PATH_LENGTH], 
                                     position_t starting_position, 
                                     int use_heuristic, 
                                     unsigned int time_limit)
{
	knights_tour_status_e status = SUCCESS;
	size_t bit_map = 0;
	
	if (0 == use_heuristic)
	{
		status = BackTrackKnightTour(starting_position, 0, bit_map, path, time(NULL) + time_limit);
	}
	else if (1 == use_heuristic)
	{
		status = HeuristicKnightTour(path, bit_map, starting_position, time(NULL) + time_limit);
	}
	
	return status;
}

position_t BuildPosition(unsigned char row, unsigned char col)
{
	position_t position = 0;
	
	assert(NUM_OF_ROWS > row);
	assert(NUM_OF_ROWS > col);
	
	position |= row;
	position <<= HALF_BYTE;
	position |= col;
	
	return position;
}


/********************************************/
/*			  Recursion Functions			*/
/********************************************/


knights_tour_status_e BackTrackKnightTour(position_t curr, size_t index, size_t bit_map,
								  position_t path[PATH_LENGTH], unsigned int time_limit)
{
	knights_tour_status_e status = BAD_PATH;
	size_t i = 0;

	bit_map = SetBit(curr, bit_map);
	path[index] = curr;

	if (FULL_BITMAP == bit_map)
	{
		return SUCCESS;
	}
	
	if (time(NULL) > time_limit)
	{
		return TIME_EXCEEDED;
	}

	for (; i < MAX_POSSIBLE_MOVES; ++i)
	{
		if (IVALID_POSITION != AddMove(curr, i, bit_map))
		{
			status = BackTrackKnightTour(AddMove(curr, i, bit_map), index + 1, 
												   bit_map, path, time_limit);
			if (SUCCESS == status)
			{
				return SUCCESS;
			}
		}
	}
	
	return status;
}

knights_tour_status_e HeuristicKnightTour(position_t path[PATH_LENGTH], size_t bit_map,
								 position_t starting_position, unsigned int time_limit)
{
	size_t count = 0;
	position_t curr = starting_position;
	
	while (count < PATH_LENGTH && IVALID_POSITION != curr)
	{	
		if (time(NULL) > time_limit)
		{
			return TIME_EXCEEDED;
		}

		bit_map = SetBit(curr, bit_map);
		path[count] = curr;
		curr = NextHeuristic(curr, bit_map);
		++count;		
	}

	if (count != PATH_LENGTH)
	{
		return BAD_PATH;
	}
	
	return SUCCESS;
}


/********************************************/
/*			   Help Functions				*/
/********************************************/


size_t PositionDegree(position_t position, size_t bit_map)
{
	size_t count = 0;
	size_t i = 0;
	
	for (; i < MAX_POSSIBLE_MOVES; ++i)
	{
		if (0 == CheckBit(AddMove(position, i, bit_map), bit_map) && 
					IVALID_POSITION != AddMove(position, i, bit_map))
		{
			++count;
		}
	}
	
	return count;
}

position_t NextHeuristic(position_t position, size_t bit_map)
{
	size_t min_possible_moves = MAX_POSSIBLE_MOVES;
	size_t min_index = 0;
	size_t i = 0;
	
	for (; i < MAX_POSSIBLE_MOVES; ++i)
	{
		if (IVALID_POSITION != AddMove(position, i, bit_map))
		{
			if (min_possible_moves >= PositionDegree(AddMove(position, i, bit_map), bit_map))
			{
				min_possible_moves = PositionDegree(AddMove(position, i, bit_map), bit_map);
				min_index = i;
			}
		}
	}
	
	return AddMove(position, min_index, bit_map);
}

position_t AddMove(position_t position, size_t index, size_t bit_map)
{
	position_t next = 0;
	char row = Row(position);
	char col = Col(position);
	
	row += g_moves_lut[index][ROW_INDEX];
	col += g_moves_lut[index][COL_INDEX];
	
	if (0 > row || MAX_ROW_POSSIBLE < row)
	{
		return IVALID_POSITION;
	}
	else if (0 > col || MAX_COL_POSSIBLE < col)
	{
		return IVALID_POSITION;
	}
	
	next = BuildPosition(row, col);
	
	if (1 == CheckBit(next, bit_map))
	{
		return IVALID_POSITION;
	}

	return next;
}

size_t Row(position_t position)
{
	return (position) >> HALF_BYTE;
}

size_t Col(position_t position)
{
	return position & COL_MASK;
}

size_t SetBit(position_t position, size_t bit_map)
{

	bit_map |= ((size_t)1 << (Row(position) + (NUM_OF_ROWS * Col(position))));
	
	return bit_map;
}

int CheckBit(position_t position, size_t bit_map)
{
	if (bit_map & ((size_t)1 << (Row(position) + NUM_OF_ROWS * Col(position))))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


