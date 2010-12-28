#include "ticTacToe.h"

void changeSetPriority(board *gameBoard, int set, int priority)
{
	int start, step, max, j;
	switch(set)
	{
		case 0:
			start = 0;
			max = 3;
			step = 1;
			break;

		case 1:
			start = 3;
			max = 6;
			step = 1;
			break;

		case 2:
			start = 6;
			max = 9;
			step = 1;
			break;

		case 3:
			start = 0;
			max = 7;
			step = 3;
			break;

		case 4:
			start = 1;
			max = 8;
			step = 3;
			break;

		case 5:
			start = 2;
			max = 9;
			step = 3;
			break;

		case 6:
			start = 0;
			max = 9;
			step = 4;
			break;

		case 7:
			start = 2;
			max = 7;
			step = 2;
			break;
	}

	//	printf("\n\nRunning for loop for set %i with parameters:\nstart = %i\nmax = %i\nstep = %i\n", i, start, max, step);
	for(j = start; j < max; j += step)
	{
		//	printf("Now checking gameBoard[%i].priority = %i\n", j, gameBoard[j].priority);
		if(gameBoard->squares[j].player == NULL)
			gameBoard->squares[j].priority = priority;

	}
	return;
}

void calcBlockWin(board *gameBoard, int *temp, int priority)
{
	int i;

	for(i = 0; i < 8; i++)
	{
		if(temp[i] > 1)
			changeSetPriority(gameBoard, i, priority);
	}
	return;
}

void originalPriority(board *gameBoard)
{
	int i, j, set = 0;

	for(i = 0; i < 8; i++)
	{
		gameBoard->block[i] = 0;
		gameBoard->win[i] = 0;
	}

	for(i = 0; i < 9; i++)
		gameBoard->squares[i].priority = 0;

	for(i = 0; i < 8; i += 3)
	{
		for(j = 0; j < 3; j++)
		{
			if(gameBoard->squares[i + j].player == gameBoard->human)
				gameBoard->block[set]++;
			if(gameBoard->squares[i + j].player == gameBoard->computer)
				gameBoard->win[set]++;
		}
		//		printf("block[%i] = %i\t\twin[%i] = %i\n", set, block[set], set, win[set]);
		//		sleep(2);

		if(gameBoard->squares[i].player != gameBoard->human && gameBoard->squares[i + 1].player != gameBoard->human && gameBoard->squares[i + 2].player != gameBoard->human)
		{
			gameBoard->squares[i].priority++;
			gameBoard->squares[i + 1].priority++;
			gameBoard->squares[i + 2].priority++;
		}
		set++;
	}

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 8; j += 3)
		{
			if(gameBoard->squares[i + j].player == gameBoard->human)
				gameBoard->block[set]++;
			if(gameBoard->squares[i + j].player == gameBoard->computer)
				gameBoard->win[set]++;
		}

		if(gameBoard->squares[i].player != gameBoard->human && gameBoard->squares[i + 3].player != gameBoard->human && gameBoard->squares[i + 6].player != gameBoard->human)
		{
			gameBoard->squares[i].priority++;
			gameBoard->squares[i + 3].priority++;
			gameBoard->squares[i + 6].priority++;
		}
		set++;
	}

	if(gameBoard->squares[0].player != gameBoard->human && gameBoard->squares[4].player != gameBoard->human && gameBoard->squares[8].player != gameBoard->human)
	{
		gameBoard->squares[0].priority++;
		gameBoard->squares[4].priority++;
		gameBoard->squares[8].priority++;
	}

	for(j = 0; j < 9; j += 4)
	{
		if(gameBoard->squares[j].player == gameBoard->human)
			gameBoard->block[set]++;
		if(gameBoard->squares[j].player == gameBoard->computer)
			gameBoard->win[set]++;
	}
	set++;

	if(gameBoard->squares[2].player != gameBoard->human && gameBoard->squares[4].player != gameBoard->human && gameBoard->squares[6].player != gameBoard->human)
	{
		gameBoard->squares[2].priority++;
		gameBoard->squares[4].priority++;
		gameBoard->squares[6].priority++;
	}

	for(j = 2; j < 7; j += 2)
	{
		if(gameBoard->squares[j].player == gameBoard->human)
			gameBoard->block[set]++;
		if(gameBoard->squares[j].player == gameBoard->computer)
			gameBoard->win[set]++;
	}

	for(i = 0; i < 8; i++)
	{
		//		printf("block[%i] = %i and win[%i] = %i", i, block[i], i, win[i]);
		//		getchar();
		if(gameBoard->block[i] + gameBoard->win[i] == 2 && gameBoard->block[i] < 2 && gameBoard->win[i] < 2)
			changeSetPriority(gameBoard, i, 5);
	}

	for(i = 0; i < 9; i++)
	{
		switch(i)
		{
			case 0:
				if((gameBoard->win[0] == 1 && gameBoard->block[0] == 0 && gameBoard->win[3] == 1 && gameBoard->block[1] == 0) || (gameBoard->win[0] == 1 && gameBoard->block[0] == 0 && gameBoard->win[6] == 1 && gameBoard->block[6] == 0) || (gameBoard->win[3] == 1 && gameBoard->block[3] == 0 && gameBoard->win[6] == 1 && gameBoard->block[6] == 0))
					gameBoard->squares[0].priority = 7;
				else if((gameBoard->win[0] == 0 && gameBoard->block[0] == 1 && gameBoard->win[3] == 0 && gameBoard->block[1] == 1) || (gameBoard->win[0] == 0 && gameBoard->block[0] == 1 && gameBoard->win[6] == 0 && gameBoard->block[6] == 1) || (gameBoard->win[3] == 0 && gameBoard->block[3] == 1 && gameBoard->win[6] == 0 && gameBoard->block[6] == 1))
					gameBoard->squares[0].priority = 6;
				break;

			case 1:
				if(gameBoard->win[0] == 1 && gameBoard->block[0] == 0 && gameBoard->win[4] == 1 && gameBoard->block[4] == 0)
					gameBoard->squares[1].priority = 7;
				else if(gameBoard->win[0] == 0 && gameBoard->block[0] == 1 && gameBoard->win[4] == 0 && gameBoard->block[4] == 1)
					gameBoard->squares[1].priority = 6;
				break;

			case 2:
				if((gameBoard->win[0] == 1 && gameBoard->block[0] == 0 && gameBoard->win[5] == 1 && gameBoard->block[5] == 0) || (gameBoard->win[0] == 1 && gameBoard->block[0] == 0 && gameBoard->win[7] == 1 && gameBoard->block[7] == 0) || (gameBoard->win[5] == 1 && gameBoard->block[5] == 0 && gameBoard->win[7] == 1 && gameBoard->block[7] == 0))
					gameBoard->squares[2].priority = 7;
				else if((gameBoard->win[0] == 0 && gameBoard->block[0] == 1 && gameBoard->win[5] == 0 && gameBoard->block[5] == 1) || (gameBoard->win[0] == 0 && gameBoard->block[0] == 1 && gameBoard->win[7] == 0 && gameBoard->block[7] == 1) || (gameBoard->win[5] == 0 && gameBoard->block[5] == 1 && gameBoard->win[7] == 0 && gameBoard->block[7] == 1))
					gameBoard->squares[2].priority = 6;
				break;

			case 3:
				if(gameBoard->win[1] == 1 && gameBoard->block[1] == 0 && gameBoard->win[3] == 1 && gameBoard->block[3] == 0)
					gameBoard->squares[3].priority = 7;
				else if(gameBoard->win[1] == 0 && gameBoard->block[1] == 1 && gameBoard->win[3] == 0 && gameBoard->block[3] == 1)
					gameBoard->squares[3].priority = 6;
				break;

			case 4:
				if((gameBoard->win[1] == 1 && gameBoard->block[1] == 0 && gameBoard->win[4] == 1 && gameBoard->block[4] == 0) || (gameBoard->win[1] == 1 && gameBoard->block[1] == 0 && gameBoard->win[6] == 1 && gameBoard->block[6] == 0) || (gameBoard->win[1] == 1 && gameBoard->block[1] == 0 && gameBoard->win[7] == 1 && gameBoard->block[7] == 0) || (gameBoard->win[4] == 1 && gameBoard->block[4] == 0 && gameBoard->win[6] == 1 && gameBoard->block[6] == 0) || (gameBoard->win[4] == 1 && gameBoard->block[4] == 0 && gameBoard->win[7] == 1 && gameBoard->block[7] == 0) || (gameBoard->win[6] == 1 && gameBoard->block[6] == 0 && gameBoard->win[7] == 1 && gameBoard->block[7] == 0))
					gameBoard->squares[4].priority = 7;
				else if((gameBoard->win[1] == 0 && gameBoard->block[1] == 1 && gameBoard->win[4] == 0 && gameBoard->block[4] == 1) || (gameBoard->win[1] == 0 && gameBoard->block[1] == 1 && gameBoard->win[6] == 0 && gameBoard->block[6] == 1) || (gameBoard->win[1] == 0 && gameBoard->block[1] == 1 && gameBoard->win[7] == 0 && gameBoard->block[7] == 1) || (gameBoard->win[4] == 0 && gameBoard->block[4] == 1 && gameBoard->win[6] == 0 && gameBoard->block[6] == 1) || (gameBoard->win[4] == 0 && gameBoard->block[4] == 1 && gameBoard->win[7] == 0 && gameBoard->block[7] == 1) || (gameBoard->win[6] == 0 && gameBoard->block[6] == 1 && gameBoard->win[7] == 0 && gameBoard->block[7] == 1))
					gameBoard->squares[4].priority = 6;
				break;

			case 5:
				if(gameBoard->win[1] == 1 && gameBoard->block[1] == 0 && gameBoard->win[5] == 1 && gameBoard->block[5] == 0)
					gameBoard->squares[5].priority = 7;
				else if(gameBoard->win[1] == 0 && gameBoard->block[1] == 1 && gameBoard->win[5] == 0 && gameBoard->block[5] == 1)
					gameBoard->squares[5].priority = 6;
				break;

			case 6:
				if((gameBoard->win[2] == 1 && gameBoard->block[2] == 0 && gameBoard->win[3] == 1 && gameBoard->block[3] == 0) || (gameBoard->win[2] == 1 && gameBoard->block[2] == 0 && gameBoard->win[7] == 1 && gameBoard->block[7] == 0) || (gameBoard->win[3] == 1 && gameBoard->block[3] == 0 && gameBoard->win[7] == 1 && gameBoard->block[7] == 0))
					gameBoard->squares[6].priority = 7;
				else if((gameBoard->win[2] == 0 && gameBoard->block[2] == 1 && gameBoard->win[3] == 0 && gameBoard->block[3] == 1) || (gameBoard->win[2] == 0 && gameBoard->block[2] == 1 && gameBoard->win[7] == 0 && gameBoard->block[7] == 1) || (gameBoard->win[3] == 0 && gameBoard->block[3] == 1 && gameBoard->win[7] == 0 && gameBoard->block[7] == 1))
					gameBoard->squares[6].priority = 6;
				break;

			case 7:
				if(gameBoard->win[2] == 1 && gameBoard->block[2] == 0 && gameBoard->win[4] == 1 && gameBoard->block[4] == 0)
					gameBoard->squares[7].priority = 7;
				else if(gameBoard->win[2] == 1 && gameBoard->block[2] == 0 && gameBoard->win[4] == 1 && gameBoard->block[4] == 0)
					gameBoard->squares[7].priority = 6;
				break;

			case 8:
				if((gameBoard->win[2] == 1 && gameBoard->block[2] == 0 && gameBoard->win[5] == 1 && gameBoard->block[5] == 0) || (gameBoard->win[2] == 1 && gameBoard->block[2] == 0 && gameBoard->win[6] == 1 && gameBoard->block[6] == 0) || (gameBoard->win[5] == 1 && gameBoard->block[5] == 0 && gameBoard->win[6] == 1 && gameBoard->block[6] == 0))
					gameBoard->squares[8].priority = 7;
				else if((gameBoard->win[2] == 0 && gameBoard->block[2] == 1 && gameBoard->win[5] == 0 && gameBoard->block[5] == 1) || (gameBoard->win[2] == 0 && gameBoard->block[2] == 1 && gameBoard->win[6] == 0 && gameBoard->block[6] == 1) || (gameBoard->win[5] == 0 && gameBoard->block[5] == 1 && gameBoard->win[6] == 0 && gameBoard->block[6] == 1))
					gameBoard->squares[8].priority = 6;
				break;
		}
	}

	calcBlockWin(gameBoard, gameBoard->block, 8);
	calcBlockWin(gameBoard, gameBoard->win, 9);

/*	if(gameBoard->squares[0].player == gameBoard->human)
	{
		gameBoard->squares[6].priority--;
		gameBoard->squares[4].priority--;
	}
*/
//	if(gameBoard->squares[2].player == gameBoard->human)
//		gameBoard


	for(i = 0; i < 9; i++)
		if(gameBoard->squares[i].player != NULL)
			gameBoard->squares[i].priority = 0;
	//	for(i = 0; i < 8; i++)
	//	{
	//		printf("Number of taken spots in set %i is %i.\n",i, block[i] + win[i]);
	//		printf("Number of enemy squares in set %i is %i\n",i, block[i]);
	//		printf("Number of player squares in set %i is %i\n",i, win[i]);
	//	}

	return;
}
