/*
 *
 * Solution to mazelog challenge Crossroad
 * http://www.mazelog.com/show?TD
 * Author: Nimalan M, mark1626
 * cc -o mazelog-sprice mazelog-sprice.c -O3 -std=c99 -pedantic
 */
#include <stdio.h>
#include <stdlib.h>

#define W 6
#define H 6
#define PATH_LEN 40

/* Describes arrows */
enum {NN, NE, EE, SE, SS, SW, WW, NW };

static const char grid[] = {
	EE, SS, WW, SW, NW, WW,
	SE, NE, NE, EE, WW, NE,
	WW, NN, SS, NE, NN, WW,
	SE, SW, NN, NN, NE, EE,
	EE, SW, WW, SE, NW, EE,
	NN, SS, NN, WW, NE, 00
};



static const int moves[] = {
	+0, -1, // NN
	+1, -1, // NE
	+1, +0, // EE
	+1, +1, // SE
	+0, +1, // SS
	-1, +1, // SW
	-1, +0, // WW
	-1, -1  // NW
};



static int solve(int *path, int step, int bestn)
{
	// Can be simplified as step % 2 ? -1 : +1;
	// Keeping this generic as it's also used in another puzzle
	int dir = step % 2 < 1 ? +1 : -1;

	// Reached the right bottom corner
	if (path[step] == W*H - 1)
	{
		for (int i=0; i <= step; i++)
		{
			printf("%d%c", path[i] + 1, " \n"[i == step]);
		}
		bestn = step;
	}
	else if (step < bestn-1)
	{
		div_t d = div(path[step], W);
		// Current position
		int x = d.rem;
		int y = d.quot;

		// Current arrow
		int arrow = grid[path[step]];

		for (int d = 1; ;d++)
		{

			int xx = x + d * moves[arrow*2 + 0] * dir;
			int yy = y + d * moves[arrow*2 + 1] * dir;
			// Check if within boundary
			if (xx >= 0 && xx < W && yy >= 0 && yy < H)
			{
				path[step+1] = yy * W + xx;
				bestn = solve(path, step+1, bestn);
			}
			else
			{
				break;
			}
		}
	}
	return bestn;
}



int main() {
	int path[PATH_LEN] = {0};

	solve(path, 0, PATH_LEN);
}
