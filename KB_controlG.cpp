#include <iostream>
#include <conio.h>
#include<fstream>
#include<Windows.h>

using namespace std;

const int N=100, width = 50, height = 20;// 78 22
int x, y, Fx, Fy, score, tailN = 1, BS;
bool gameOver;
int tailX[N], tailY[N];

void Setup()
{
	x = rand() % width-2;
	y = rand() % height-2;
	Fx = rand() % width;
	Fy = rand() % height;
	for (int i = 0; i < N; i++) {	tailX[i] = 0; tailY[i] = 0;	}
}

void Draw()
{
	system("cls");
	for (int i = 0; i <= width; i++)  cout << "+";
	cout << " Best score " << BS << endl;

	for (int i = 0; i <= height; i++) { 
		for (int j = 0; j <= width; j++) {
				if ((j == 0) || (j == width)) { cout << "+"; 
				if (i == 0 && j == width) cout << " Score " << score;
					if (i==1 && j==width) cout << " Double X - Exit";}
				else if (x == j && y == i) cout << "O";
				else if (Fx == j && Fy == i) cout << "F";
				else {
					bool as = 0;
					for (int k = 0; k < tailN; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							cout << "o";
							as = 1;
						}
					}
					if (!as) cout << " ";
				}
		}
		cout << endl;
	}

	for (int i = 0; i <= width; i++) { cout << "+"; }
}

void Control()
{
	char last = 'x';
		switch (_getch())
		{
		case 'w':if (last != 's') { y--; last = 'w'; } break;
		case 'a':if (last != 'd') { x--; last = 'a'; } break;
		case 's':if (last != 'w') { y++; last = 's'; } break;
		case 'd':if (last != 'a') { x++; last = 'd'; } break;
		case 'x':gameOver = 1;
		}		
}

void Logic()
{
	ifstream SC;
	SC.open("score.txt", fstream::out);
	if (SC.is_open()) SC>>BS;
	else BS = 0;
	SC.close();

	int  lastX = tailX[0], lastY = tailY[0];
	int last2x, last2y;
	tailX[0] = x; tailY[0] = y;
	for (int i = 1; i < tailN; i++) {
		last2x = tailX[i];		last2y = tailY[i];
		tailX[i] = lastX;		tailY[i] = lastY;
		lastX = last2x;	lastY = last2y;
	}

	if (x == Fx && y == Fy) {
		score+=10;
		Fx = rand() % width;
		Fy = rand() % height;
		tailN++;
	}
	for (int i = 1; i < tailN; i++)
		if (tailX[i] == x && tailY[i] == y) gameOver = 1;
	if (x == 0 || y == 0-1 || x == width || y == height+1) gameOver = 1;

	if (gameOver==1 && score>BS) {
		ofstream SC;
		SC.open("score.txt");
		SC << score;
		SC.close();
	}
}

int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		Control();
		Logic();
	}
	return 0;
}