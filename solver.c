
#define DELAY 100000
#define CLRSCR() printf("\e[2J\e[H")

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

enum halfcat {
	orange_front,
	orange_back,
	grey_front,
	grey_back,
	brown_front,
	brown_back,
	black_front,
	black_back,
};

struct piece {
	char id;
	enum halfcat top;
	enum halfcat bottom;
	enum halfcat left;
	enum halfcat right;
};

struct piece pieces[9] = {
	{'A', grey_back, orange_front, brown_back, black_front},
	{'B', orange_front, grey_back, grey_front, brown_front},
	{'C', grey_front, orange_front, black_back, black_back},
	{'D', black_back, grey_back, brown_front, orange_front},
	{'E', black_front, orange_front, grey_back, brown_front},
	{'F', grey_front, black_front, brown_back, orange_back},
	{'G', black_back, grey_front, orange_front, brown_front},
	{'H', brown_back, brown_back, orange_back, black_front},
	{'I', brown_back, orange_back, grey_back, black_front},
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

int matches(enum halfcat a, enum halfcat b) {

	if ((a == orange_front && b == orange_back) || (a == orange_back && b == orange_front))
		return 1;

	if ((a == grey_front && b == grey_back) || (a == grey_back && b == grey_front))
		return 1;

	if ((a == brown_front && b == brown_back) || (a == brown_back && b == brown_front))
		return 1;

	if ((a == black_front && b == black_back) || (a == black_back && b == black_front))
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

void print_with_color(enum halfcat c) {

	switch(c) {
		case orange_front:	printf("\e[48;5;208mF\e[0m"); break;
		case orange_back:	printf("\e[48;5;208mB\e[0m"); break;
		case grey_front:	printf("\e[48;5;249mF\e[0m"); break;
		case grey_back:		printf("\e[48;5;249mB\e[0m"); break;
		case brown_front:	printf("\e[48;5;94mF\e[0m"); break;
		case brown_back:	printf("\e[48;5;94mB\e[0m"); break;
		case black_front:	printf("\e[48;5;232mF\e[0m"); break;
		case black_back:	printf("\e[48;5;232mB\e[0m"); break;
		case 'A' ... 'I':	printf("\e[48;5;196m%c\e[0m", c); break;
		case 'Y':			printf("\e[48;5;2m \e[0m"); break;
//		case 'Z':			printf("\e[48;5;231m \e[0m"); break;
		case 'Z':			printf("\e[0m "); break;
	}

}

void print_board(struct piece *current, int depth) {

	char buffer[13*13];
	int i, j;

	int offsets[9] = {0, 4, 8, 52, 56, 60, 104, 108, 112};

	memset(buffer, 'Z', 13*13*sizeof(char));

	for (i=0; i<13; i++) {
		for (j=0; j<13; j++) {
			if (i % 4 == 0 || j % 4 == 0) {
				buffer[(i*13)+j] = 'Y';
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
		print_with_color((enum halfcat)buffer[i]);
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

