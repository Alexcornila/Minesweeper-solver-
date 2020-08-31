// /*    This program solves a minesweeper game.
// PLEASE FILL IN THESE FIELDS:
// Your Name:Ciprian Alex Cornila
// Date: 10/03/2018
//  */
#include "minefield.h"
void open_squares(int r, int c, int opened [8][8]);
void flag_all(int r, int c, int opened [8][8]);
int Neighbor_notopen(int ab, int r, int c, int opened[8][8]);
int Neighbor_flag(int adjacent_bombs, int r, int c, int opened[8][8]);
void Guessing();
int adjacent_bombs;
int r, c;
int opened[8][8];
int i,j;
int a;
void solver(int mn)
{
	int not_opened = 0;
	int flaged = 0;

	int can_flag = 0;
	int can_open = 0;

	int action_taken = 0;

//create a matrix of 9's = unopened squares
	for(i = 0; i < 8; i++)
	{
			for(j = 0; j < 8; j++)
		{
				opened[i][j] = 9;//unopen = 9
				printf("%4d", opened[i][j]);
		}
				printf("\n");
	}
//loop untill back end takes control
	while( 1)
	{
		can_flag = 0;
		can_open = 0;
		action_taken = 0;
//loop through the array and pass every r,c to functions Neighbor_ to check for possible moves
		for(int r = 0; r<8; r++)
		{
			for(int c= 0; c <8; c++)//iterate column0s
			{
				adjacent_bombs = opened[r][c];
				not_opened =	Neighbor_notopen(adjacent_bombs, r, c, opened);//checks for number of unopened squares around particular rc
				flaged =	Neighbor_flag(adjacent_bombs, r, c, opened);////checks for number of flaged squares around particular rc
				can_flag = (adjacent_bombs == (not_opened + flaged));
				can_open = (adjacent_bombs == flaged)||(adjacent_bombs == 0);

				if(not_opened!=0)
				{
					if(can_flag)
					{
						//helper_flag_all(r,c);
						flag_all(r, c, opened);
						action_taken = 1;
					}
					else if(can_open)
					{
						open_squares(r, c, opened);
						action_taken = 1;
					}
				}


			}
	}
			if(action_taken==0)
   		{
		 		Guessing();
	 		}

		}

}
//opens squares around a particular square determined by rc passed to Neighbor_
void open_squares(int r, int c, int opened [8][8])

{
	int r_start = r-1;
	int r_end = r+1;
	int c_start = c-1;
	int c_end = c+1;
	if(r_start < 0)
	r_start = r;
	if(r_end > 7)
	r_end = r;
	if(c_start < 0)
	c_start = c;
	if(c_end > 7)
	c_end = c;

	for(int i= r_start; i <= r_end; i++)
	{
			for(int j= c_start; j <= c_end; j++)
			{
				//if((i!=r)||(j!=c))
				if(!(i==r&&j==c))
				{
					if (opened[i][j] == 9)
					{
						opened[i][j]= open(i,j);
					}

				}
			}

	}

}
//opens squares around a particular square determined by rc passed to Neighbor_
void flag_all(int r, int c, int opened [8][8])

{
	int r_start = r-1;
	int r_end = r+1;
	int c_start = c-1;
	int c_end = c+1;
	if(r_start < 0)
	r_start = r;
	if(r_end > 7)
	r_end = r;
	if(c_start < 0)
	c_start = c;
	if(c_end > 7)
	c_end = c;

	for(int i= r_start; i <= r_end; i++)
	{
			for(int j= c_start; j <= c_end; j++)
			{
				//if((i!=r)||(j!=c))
				if(!(i==r&&j==c))
				{
					if (opened[i][j] == 9)
					{
						flag(i,j);
						opened[i][j]= -1;
					}

				}
			}

	 }

}
//if we cannot open or flag we guess the next available==9 square
void Guessing()
{

	for (int x=0; x<=7; x++)
	{
		for(int y=0; y<=7; y++)
		{
			if(opened[x][y]==9)
			   {
					 opened[x][y]= guess(x,y);
					 display_field_discovered_so_far();
					 return;
				 }
		 }
	 }

}
//determines number of not open squares around a particular rc
int Neighbor_notopen(int adjacent_bombs, int r, int c, int opened[8][8])
{
int not_opened = 0;
//int flaged = 0;
int r_start = r-1;
int r_end = r+1;
int c_start = c-1;
int c_end = c+1;
if(r_start < 0)
r_start = r;
if(r_end > 7)
r_end = r;
if(c_start < 0)
c_start = c;
if(c_end > 7)
c_end = c;

for(int i= r_start; i <= r_end; i++)
{
		for(int j= c_start; j <= c_end; j++)
		{
			if((i!=r)||(j!=c))
			//if(!(i==r&&j==c))
		{
			if (opened[i][j] == 9)
			{
				not_opened = not_opened + 1;
			}

		}
	}

}
return not_opened;
}
//determines number of flagged squares around a particular rc
int Neighbor_flag(int adjacent_bombs, int r, int c, int opened[8][8])
{
int flaged = 0;
int r_start = r-1;
int r_end = r+1;
int c_start = c-1;
int c_end = c+1;
if(r_start < 0)
r_start = r;
if(r_end > 7)
r_end = r;
if(c_start < 0)
c_start = c;
if(c_end > 7)
c_end = c;

	for(int i= r_start; i <= r_end; i++)
	{
		for(int j= c_start; j <= c_end; j++)
		{
			//if((i!=r)||(j!=c))
			if(!(i==r&&j==c))
			{
	 		if(opened[i][j] == -1)
	 		{
	 			flaged = flaged + 1;
	 		}

		}
	}
}
	return flaged;
}
