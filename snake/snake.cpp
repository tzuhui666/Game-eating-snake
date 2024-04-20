#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;


// 遊戲變數宣告 
bool gameover;
const int width = 25;
const int height = 15;
int x, y, coinX, coinY, score;
int nTail;
int tailX[150], tailY[150];
int direction;
const int Stop = 0, Left = 1, Right = 2, Down = 3, Up = 4;


// 函數 
void Clear()
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = 0;
	scrn.Y = 0;
	SetConsoleCursorPosition(hOuput, scrn);
	return;
}

//遊戲初始化
void SetUp() {
	gameover = false;
	direction = Stop;
	x = width / 2;
	y = height / 2;
	score = 0;
	nTail = 0;
}




void Draw() {
	Sleep(100); // 暫停0.1秒
	Clear();
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) { // 修正此處迴圈條件
			if (j == 0) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "*";
			}
			else if (i == coinY && j == coinX) {
				cout << "$";
			}
			else {
				bool printSnake = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "*";
						printSnake = true;
					}
				}
				if (!printSnake) {
					cout << " ";
				}
			}
			if (j == width - 1) {
				cout << "#";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score:" << score << endl;
	return;
}




void Input() {
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case 'a':
			direction = Left;
			break;
		case 'd':
			direction = Right;
			break;
		case 'w':
			direction = Down;
			break;
		case 's':
			direction = Up;
			break;
		case 'p':
			direction = Stop;
			break;
		}
	}
}



void Algorithm() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;

	}
	switch(direction)
	{
		case Left:
			x--;
			break;
		case Right:
			x++;
			break;
		case Down:
			y--;
			break;
		case Up:
			y++;
			break;
	}

	if (x >= width)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = width - 1;
	}
	if (y >= height)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = height - 1;
	}

	// 檢查蛇是否撞到邊界
	if (x >= width || x < 0 || y >= height || y < 0) {
		gameover = true;
		cout << "\a";
		return;
	}
	// 檢查蛇是否撞到自身
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameover = true;
			cout << "\a";
			return;
		}
	}


	if (x == coinX && y == coinY)
	{
		score += 20;
		coinX = rand() % (width - 1) + 1;
		coinY = rand() % (height - 1) + 1;
		nTail++;
	}
	return;
}


int main()
{
	//隨機亂數
	srand(time(NULL));
	SetUp();
	while(!gameover) 
	{
		Draw();
		Input();
		Algorithm();
	}
	return 0;
}