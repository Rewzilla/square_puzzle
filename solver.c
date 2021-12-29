
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define aA_COLOR		208
#define aB_COLOR		208
#define bA_COLOR		249
#define bB_COLOR		249
#define cA_COLOR		94
#define cB_COLOR		94
#define dA_COLOR		232
#define dB_COLOR		232
#define center_COLOR	196
#define border_COLOR	2

enum halfobj {
	aA,
	aB,
	bA,
	bB,
	cA,
	cB,
	dA,
	dB,
};

struct piece {
	char id;
	enum halfobj top;
	enum halfobj bottom;
	enum halfobj left;
	enum halfobj right;
};

struct piece pieces[9] = {
	{'A', bB, aA, cB, dA},
	{'B', aA, bB, bA, cA},
	{'C', bA, aA, dB, dB},
	{'D', dB, bB, cA, aA},
	{'E', dA, aA, bB, cA},
	{'F', bA, dA, cB, aB},
	{'G', dB, bA, aA, cA},
	{'H', cB, cB, aB, dA},
	{'I', cB, aB, bB, dA},
};

int solutions = 0;

struct piece rotate(struct piece p, int amount) {

	struct piece tmp;

	tmp.id = p.id;

	switch(amount) {
		case 0:
			tmp = p;
			break;
		case 1:
			tmp.top = p.left;
			tmp.right = p.top;
			tmp.bottom = p.right;
			tmp.left = p.bottom;
			break;
		case 2:
			tmp.top = p.bottom;
			tmp.right = p.left;
			tmp.bottom = p.top;
			tmp.left = p.right;
			break;
		case 3:
			tmp.top = p.right;
			tmp.right = p.bottom;
			tmp.bottom = p.left;
			tmp.left = p.top;
			break;
	}

	return tmp;

}

int matches(enum halfobj a, enum halfobj b) {

	if ((a == aA && b == aB) || (a == aB && b == aA))
		return 1;

	if ((a == bA && b == bB) || (a == bB && b == bA))
		return 1;

	if ((a == cA && b == cB) || (a == cB && b == cA))
		return 1;

	if ((a == dA && b == dB) || (a == dB && b == dA))
		return 1;

	return 0;

}

int valid(struct piece *current, int depth) {

	if (depth == 0 || depth == 1) {
		return 1;
	} else if (depth == 2) {
		if(matches(current[0].right, current[1].left)) {
			return 1;
		}
	} else if (depth == 3) {
		if (matches(current[0].right, current[1].left)
		&& matches(current[1].right, current[2].left)) {
			return 1;
		}
	} else if (depth == 4) {
		if (matches(current[0].right, current[1].left)
		&& matches(current[1].right, current[2].left)
		&& matches(current[0].bottom, current[3].top)) {
			return 1;
		}
	} else if (depth == 5) {
		if (matches(current[0].right, current[1].left)
		&& matches(current[1].right, current[2].left)
		&& matches(current[0].bottom, current[3].top)
		&& matches(current[3].right, current[4].left)
		&& matches(current[4].top, current[1].bottom)) {
			return 1;
		}
	} else if (depth == 6) {
		if (matches(current[0].right, current[1].left)
		&& matches(current[1].right, current[2].left)
		&& matches(current[0].bottom, current[3].top)
		&& matches(current[3].right, current[4].left)
		&& matches(current[4].top, current[1].bottom)
		&& matches(current[4].right, current[5].left)
		&& matches(current[5].top, current[2].bottom)) {
			return 1;
		}
	} else if (depth == 7) {
		if (matches(current[0].right, current[1].left)
		&& matches(current[1].right, current[2].left)
		&& matches(current[0].bottom, current[3].top)
		&& matches(current[3].right, current[4].left)
		&& matches(current[4].top, current[1].bottom)
		&& matches(current[4].right, current[5].left)
		&& matches(current[5].top, current[2].bottom)
		&& matches(current[6].top, current[3].bottom)) {
			return 1;
		}
	} else if (depth == 8) {
		if (matches(current[0].right, current[1].left)
		&& matches(current[1].right, current[2].left)
		&& matches(current[0].bottom, current[3].top)
		&& matches(current[3].right, current[4].left)
		&& matches(current[4].top, current[1].bottom)
		&& matches(current[4].right, current[5].left)
		&& matches(current[5].top, current[2].bottom)
		&& matches(current[6].top, current[3].bottom)
		&& matches(current[6].right, current[7].left)
		&& matches(current[7].top, current[4].bottom)) {
			return 1;
		}
	} else if (depth == 9) {
		if (matches(current[0].right, current[1].left)
		&& matches(current[1].right, current[2].left)
		&& matches(current[0].bottom, current[3].top)
		&& matches(current[3].right, current[4].left)
		&& matches(current[4].top, current[1].bottom)
		&& matches(current[4].right, current[5].left)
		&& matches(current[5].top, current[2].bottom)
		&& matches(current[6].top, current[3].bottom)
		&& matches(current[6].right, current[7].left)
		&& matches(current[7].top, current[4].bottom)
		&& matches(current[7].right, current[8].left)
		&& matches(current[5].bottom, current[8].top)) {
			return 1;
		}
	} else {
		return 0;
	}

}

void print_with_color(enum halfobj c) {

	switch(c) {
		case aA:			printf("\e[48;5;%dmA\e[0m", aA_COLOR); break;
		case aB:			printf("\e[48;5;%dmB\e[0m", aB_COLOR); break;
		case bA:			printf("\e[48;5;%dmA\e[0m", bA_COLOR); break;
		case bB:			printf("\e[48;5;%dmB\e[0m", bB_COLOR); break;
		case cA:			printf("\e[48;5;%dmA\e[0m", cA_COLOR); break;
		case cB:			printf("\e[48;5;%dmB\e[0m", cB_COLOR); break;
		case dA:			printf("\e[48;5;%dmA\e[0m", dA_COLOR); break;
		case dB:			printf("\e[48;5;%dmB\e[0m", dB_COLOR); break;
		case 'A' ... 'I':	printf("\e[48;5;%dm%c\e[0m", center_COLOR, c); break;
		case 'Z':			printf("\e[48;5;%dm \e[0m", border_COLOR); break;
		default:			printf("\e[0m "); break;
	}

}

void print_board(struct piece *current, int depth) {

	char buffer[13*13];
	int i, j;

	int offsets[9] = {0, 4, 8, 52, 56, 60, 104, 108, 112};

	memset(buffer, '\xff', 13*13*sizeof(char));

	for (i=0; i<13; i++) {
		for (j=0; j<13; j++) {
			if (i % 4 == 0 || j % 4 == 0) {
				buffer[(i*13)+j] = 'Z';
			}
		}
	}

	for (i=0; i<depth; i++) {
		buffer[15 + offsets[i]] = (char)current[i].top;
		buffer[27 + offsets[i]] = (char)current[i].left;
		buffer[29 + offsets[i]] = (char)current[i].right;
		buffer[41 + offsets[i]] = (char)current[i].bottom;
	}

	int centers[9] = {28, 32, 36, 80, 84, 88, 132, 136, 140};

	for (i=0; i<depth; i++) {
		buffer[centers[i]] = current[i].id;
	}

	for (i=0; i<13*13; i++) {
		print_with_color((enum halfobj)buffer[i]);
		if(i%13 == 12)
			printf("\n");
	}

}

void solve(struct piece *current, struct piece *remaining, int depth) {

	int r, p;
	struct piece tmp;
	struct piece swapped[9];

	if (depth == 9) {

		printf("Solution #%d!\n", ++solutions);
		print_board(current, depth);
		printf("\n\n");

	} else {

		for (p = depth; p<9; p++) {

			for (r=0; r<4; r++) {

				memcpy(swapped, remaining, 9 * sizeof(struct piece));

				current[depth] = rotate(remaining[p], r);

				if (valid(current, depth + 1)) {

					tmp = swapped[depth];
					swapped[depth] = swapped[p];
					swapped[p] = tmp;

					solve(current, swapped, depth + 1);

				}

			}

		}

	}

}

int main() {

	struct piece *init = calloc(9, sizeof(struct piece));

	solve(init, pieces, 0);

}

