#define screenwidth 800
#define screenHight 800
#define brickNumber 100
#define yAxismarjin 50
#include <iostream>
#include "iGraphics.h"
// #define totalBricks 100
// #include<cstdio>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
struct buttonCordinate
{
	int p;
	int q;
} bCordinate[4];
struct cuttonCordinate
{
	int g;
	int h;
} bLevel[3];
FILE *hs;
char button[10][15] = {"bp\\play.bmp", "bp\\play.bmp", "bp\\in.bmp", "bp\\high.bmp"};
char cutton[10][15] = {"bp\\easy.bmp", "bp\\normal.bmp", "bp\\hard.bmp"};
char homemenu[15] = "bp\\main2.bmp";
char play[15] = "bp\\3.bmp";
char high[25] = "bp\\rins.bmp";
char over[15] = "bp\\game.bmp";
char lev[15] = "bp\\level.bmp";
char stop[15] = "bp\\p.bmp";
char wait[15] = "bp\\res.bmp";
char front[15] = "bp\\main1.bmp";
char s[15] = "bp\\board.bmp";
char HighscoreFile[30] = "bp\\HIGH_SCORES";
char yep[15] = "bp\\yes.bmp";
char nope[15] = "bp\\no.bmp";
char onSound[15] = "bp\\on.bmp";
char offSound[15] = "bp\\off.bmp";
char life3[15] = "bp\\life3.bmp";
char life2[15] = "bp\\life2.bmp";
char life1[15] = "bp\\life.bmp";
char inp[15] = "bp\\hs.bmp";
char chan[15] = "bp\\change.bmp";
char welcome[15] = "bp\\welcome.bmp";
char welcome2[25] = "bp\\welcome2.bmp";
char wood[25] = "bp\\high_back.bmp";
char sp[15] = "bp\\splash.bmp";
char cloud[15] = "bp\\cloud.bmp";
char leader[25] = "bp\\leader.bmp";
int thirdIn, firstIn, secondIn;
void change();
void change2();
void defineBricks();
void defineBricks2();
void lev_change();
int b = 0;

struct brickStructure
{
	int a;
	int b;
	int dx = 80;
	int dy = 20;
	bool show = true;
	// bool show2=true;
	int red;
	int green;
	int blue;
};
// char bp[4][20]={"bp\\4.bmp"};
int x = 300, y = 300, r = 8;

int totalBricks = 100;
brickStructure bricks[1500];
// brickStructure bricks2[1500];
int red = 0;
int green = 0;
int blue = 0;
int x_ball = screenwidth / 2;
int y_ball = yAxismarjin;
int z = 0;
int rx = x_ball - 50, ry = y_ball - 20, dx_board = 100, dy_board = 10;
int count = 0;
int radius_ball = 10;
int HighScore[5] = {0};
int ShowHighscore = 0;
int fx;
int life = 2;
int dx = 5;
int dy = 7;
int j = 0;
bool isStarted = false;
bool pause = false;
char name_inp[100];
bool musicOn = true;
int game_state = -2;
int game_lev = 0;
int bpIndex = 0;
long long score = 0;
char scoreText[100];
char highScoreText[100];
int high_s = 0;
char level[100];
char line[5][25];
char str_score[4];
char quit[1000] = "Do you want to continue this game??";
int ex = 265;
int ey = 65;
int exx = 10;
char load[1000] = "...L o a d i n g...";
int scores[1000];
char file_name[1000] = "score.txt";
char d[100][20];
int p = 1, player = 0, first, second, third;
void restart();
void defineBricks();
void defineBricks2();
void leaderboard()
{
	FILE *file = fopen(file_name, "r+");
	char s[100];
	player = 0;
	while (fscanf(file, "%s %d", d[player], &scores[player]) != EOF)
	{
		printf("\n%s %d\n", d[player], scores[player]);
		player++;
	}
	fclose(file);

	third = first = second = INT_MIN;
	for (int i = 0; i < player; i++)
	{
		if (scores[i] > first)
		{
			third = second;
			thirdIn = secondIn;
			second = first;
			secondIn = firstIn;
			first = scores[i];
			firstIn = i;
		}
		else if (scores[i] > second && scores[i] != first)
		{
			third = second;
			thirdIn = secondIn;
			second = scores[i];
			secondIn = i;
		}
		else if (scores[i] > third && scores[i] != second && scores[i] != first)
		{
			third = scores[i];
			thirdIn = i;
		}
	}
}
int getHighscore(void)
{
	FILE *fp = fopen("highScore.txt", "r");
	if (!fp)
		return 0;
	else
	{
		int high_s;
		fscanf(fp, "%d", &high_s);
		fclose(fp);
		return high_s;
	}
}
void setHighScore(int score)
{
	FILE *fp = fopen("highScore.txt", "w");
	fprintf(fp, "%d", score);
	fclose(fp);
}
void iDraw()
{
	// place your drawing codes here
	iClear();
	if (game_state == -2)
	{
		iShowBMP(0, 0, front);
		iSetColor(255, 2, 255);
		iRectangle(265, 65, 200, 10);
		iSetColor(255, 255, 255);
		iFilledRectangle(ex, ey, exx, 10);

		iSetColor(0, 0, 0);
		iText(265 + 50, 90, load, GLUT_BITMAP_TIMES_ROMAN_24);

		// change2();
	}
	if (game_state == -1)
	{
		iShowBMP(0, 0, homemenu);
		iShowBMP(600, 20, chan);
		for (int i = 1; i < 4; i++)
		{
			iShowBMP2(bCordinate[i].p, bCordinate[i].q, button[i], 255);
		}
		if (p == 1)
		{
			if (musicOn)
			{
				iShowBMP2(700, 700, onSound, 0);
			}
		}
		else if (p == 2)
		{
			iShowBMP(700, 700, offSound);
		}
		// isStarted=false;
	}
	if (game_state == 0)
	{
		iShowBMP(0, 0, play);
		iShowBMP2(0, 670, cloud, 0);
		iShowBMP(50, screenHight - 50, stop);

		iSetColor(255, 0, 0);
		iFilledCircle(x_ball, y_ball, radius_ball, 1000);
		iSetColor(255, 255, 255);
		iFilledRectangle(rx, ry, dx_board, dy_board);
		// defineBricks();
		for (int i = 0; i < totalBricks; i++)
		{
			if (bricks[i].show)
			{
				red = rand() % 255;
				green = rand() % 255;
				blue = rand() % 255;
				iSetColor(bricks[i].red, bricks[i].green, bricks[i].blue);
				iFilledRectangle(bricks[i].a, bricks[i].b, bricks[i].dx, bricks[i].dy);
			}
			// change();
		}
		if (life == 2)
		{
			iShowBMP2(550, 740, life3, 0);
		}
		else if (life == 1)
		{
			iShowBMP2(550, 740, life2, 0);
		}
		else if (life == 0)
		{
			iShowBMP2(550, 740, life1, 0);
		}
		sprintf(scoreText, "Score: %i", score);
		iSetColor(0, 0, 0);
		iText(100, screenHight - 50, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 0, 0);
		// sprintf(level, "Game=%d", game_lev);
		iText(40, 40, level, GLUT_BITMAP_TIMES_ROMAN_24);

		if (pause == 1)
		{
			iShowBMP(0, 0, wait);
			iSetColor(0, 0, 0);
			iText(200, 120, quit, GLUT_BITMAP_TIMES_ROMAN_24);
			iShowBMP(250, 56, yep);
			iShowBMP(413, 56, nope);
		}
	}
	else if (game_state == 1)
	{
		iShowBMP(0, 0, lev);
		for (int i = 0; i < 3; i++)
		{
			iShowBMP2(bLevel[i].g, bLevel[i].h, cutton[i], 255);
		}
	}
	else if (game_state == 2)
	{
		iShowBMP(0, 0, high);
	}
	else if (game_state == 3)
	{
		iShowBMP(0, 0, s);
		iShowBMP2(150, 500, leader, 0);
		iShowBMP2(90, 90, wood, 0);
		iSetColor(0, 0, 0);
		iRectangle(90, 90, 100, 25);

		iSetColor(255, 255, 255);
		// iText(660,565,itoa(score,str_score,10),GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(400, 0, sp, 0);
		iSetColor(0, 0, 0);
		iText(430, 60, "***PRESS 1 TO CONTINUE***", GLUT_BITMAP_HELVETICA_18);
		char s2[100];
		iSetColor(0, 0, 0);
		iText(250, 360, d[firstIn], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(250, 280, d[secondIn], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(250, 200, d[thirdIn], GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(s2, "%d", scores[firstIn]);
		iText(490, 360, s2, GLUT_BITMAP_TIMES_ROMAN_24);
		char s3[100];
		char s4[100];
		sprintf(s3, "%d", scores[secondIn]);
		iText(490, 280, s3, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(s4, "%d", scores[thirdIn]);
		iText(490, 200, s4, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (game_state == 10)
	{
		iShowBMP(0, 0, over);
		sprintf(scoreText, "Score: %i", score);
		iSetColor(255, 255, 255);
		iText(screenwidth / 2 - 100, screenHight / 2, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(highScoreText, "High Score: %i", getHighscore());
		iSetColor(255, 255, 255);
		iText(screenwidth / 2 - 100, screenHight / 2 - 50, highScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 0, 0);
		iText(430, 60, "***PRESS 1 TO CONTINUE***", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	else if (game_state == -3)
	{

		iShowBMP(0, 0, over);
		iShowBMP(0, 0, welcome);
		iShowBMP2(100, 80, welcome2, 0);
		iShowBMP(330, 290, inp);
		iSetColor(0, 0, 0);
		iText(250, 370, "***Enter your name here***", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 0, 0);
		iRectangle(330, 290, 200, 38);
		iSetColor(0, 0, 0);
		iText(250, 300, "Name:", GLUT_BITMAP_TIMES_ROMAN_24);
		if (z == 1)
		{
			iSetColor(0, 0, 0);
			iText(340, 297, name_inp, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}

void iMouseMove(int mx, int my)
{
	// printf("x = %d, y= %d\n",mx,my);
	// place your codes here
}

void restart2();
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (game_state == -1)
		{ //
			for (int i = 1; i < 4; i++)
			{
				if (mx >= bCordinate[i].p && mx <= bCordinate[i].q + 300 && my >= bCordinate[i].q && my <= bCordinate[i].q + 80)
				{
					game_state = i;
					// printf("%d", game_state);
					if (game_state == 3)
						leaderboard();
					if (game_state == 0)
					{

						restart2();
						score = 0;
						life = 2;
						for (int i = 0; i < totalBricks; i++)
						{
							bricks[i].show = true;
						}
					}
				}
				else if (mx >= 600 && mx <= 600 + 150 && my >= 20 && my <= 20 + 46)
				{
					game_state = -3;
					FILE *file = fopen(file_name, "a");
					fprintf(file, "%s %d\n", name_inp, score);
					fclose(file);
					for (int i = 0; i < j; i++)
					{
						name_inp[i] = 0;
					}
					j = 0;
				}
			}

			// else if(game_state == -2){

			//}
			if (mx > 700 && mx < 700 + 71 && my > 700 && my < 700 + 77)
			{
				if (musicOn)
				{
					musicOn = false;
					PlaySound(0, 0, 0);
					p = 2;
				}
				else
				{
					musicOn = true;
					PlaySound("music\\sample-15s.wav", NULL, SND_LOOP | SND_ASYNC);
					p = 1;
				}
			}
		}

		else if (game_state == -3)
		{

			if (mx >= 330 && mx <= 330 + 200 && my >= 290 && my <= 290 + 38)
			{
				z = 1;
			}
		}
		else if (game_state == 0)
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			{

				if (mx > 50 && mx < 50 + 40 && my > screenHight - 50 && my < screenHight - 50 + 38)
				{
					pause = true;
				}
				if (pause)
				{

					if (mx > 250 && mx < 250 + 110 && my > 56 && my < 56 + 37)
					{
						game_state = 0;
						pause = 0;
						isStarted = true;
					}
					else if (mx > 413 && mx < 413 + 110 && my > 56 && my < 56 + 37)
					{
						game_state = -1;
						iResumeTimer(2);
						iResumeTimer(3);
						iResumeTimer(4);

						pause = 0;
					}
				}
			}
		}
		else if (game_state == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				if (mx >= bLevel[i].g && mx <= bLevel[i].h + 300 && my >= bLevel[i].h && my <= bLevel[i].h + 88)
				{
					game_state = 0;
					game_lev = i;
					if (game_lev == 0)
					{
						restart2();
						score = 0;
						life = 2;
						for (int i = 0; i < brickNumber; i++)
							bricks[i].show = true;
						// b=100;
						// iPauseTimer(2);
						iPauseTimer(3);
						iPauseTimer(4);
					}
					if (game_lev == 1)
					{
						restart2();
						score = 0;
						life = 2;
						for (int i = 0; i < brickNumber; i++)
							bricks[i].show = true;
						b = 50;
						iPauseTimer(2);
						iPauseTimer(4);

						// iResumeTimer(4);
					}
					if (game_lev == 2)
					{
						restart2();
						life = 2;
						score = 0;
						for (int i = 0; i < brickNumber; i++)
							bricks[i].show = true;
						b = 10;
						iPauseTimer(2);
						iPauseTimer(3);

						// iResumeTimer(5);
					}
				}
			}
		}
		else if (game_state == 3)
		{
			leaderboard();
		}
	}

	/*if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		x -= 10;
		y -= 10;
	}*/
}

void iKeyboard(unsigned char key)
{
	if (game_state == 10)
	{
		if (key == '1')
		{
			FILE *file = fopen(file_name, "a");
			fprintf(file, "%s %d\n", name_inp, score);
			fclose(file);
			for (int i = 0; i < j; i++)
			{
				name_inp[i] = 0;
			}
			j = 0;
		}
	}
	if (key == 'esc')
	{
		exit(0);
	}
	if (key == '1')
	{
		game_state = -1;
		isStarted = false;
		iResumeTimer(2);
		iResumeTimer(3);
		iResumeTimer(4);
	}
	if (game_state == 0)
	{
		if (key == ' ' && isStarted == false)
		{
			if (!isStarted)
			{
				isStarted = true;
			}
		}
		else if (isStarted = true && key == 'b')
		{
			pause = true;
		}
		else if (key == 'p' && pause == 1)
		{
			game_state = 0;
			pause = 0;
			isStarted = true;
		}
	}

	if (game_state == -3 && z == 1)
	{
		if (key != '\r')
		{
			if (key != '\b')
			{
				name_inp[j] = key;
				j++;
			}
			else
			{
				if (j >= 0)
				{
					name_inp[j - 1] = 0;
					j--;
				}
				else
				{
					j = 0;
				}
			}
		}
		else
		{
			game_state = -1;
		}
	}
	// place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_UP)
	{
	}

	else if (key == GLUT_KEY_DOWN)
	{
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (rx >= 0)
		{
			rx -= 10;
			if (!isStarted)
			{
				x_ball -= 10;
			}
		}
	}
	else if (key == GLUT_KEY_RIGHT)
	{

		if (rx < screenwidth - dx_board)
		{
			rx += 10;
			if (!isStarted)
			{
				x_ball += 10;
			}
		}
	}
}

void change()
{
	if (!pause)
	{
		if (isStarted)
		{
			x_ball += dx;
			y_ball += dy;
			if (x_ball >= screenwidth || x_ball <= 0)
				dx *= (-1);
			if (y_ball >= screenHight)
				dy *= (-1);
			for (int i = 0; i < totalBricks; i++)
			{
				if (bricks[i].show)
				{
					if (x_ball >= bricks[i].a && x_ball <= bricks[i].a + bricks[i].dx)
					{
						if (y_ball >= bricks[i].b && y_ball <= bricks[i].b + bricks[i].dy)
						{
							dy *= -1;
							bricks[i].show = false;
							score += 20;
							if (score > getHighscore())
								setHighScore(score);
							/*if(score>=200){
							 game_state=10;
						  restart2();
							 }*/
						}
						else if (y_ball >= bricks[i].b && y_ball <= bricks[i].b + bricks[i].dy)
						{
							if (x_ball >= bricks[i].a && x_ball <= bricks[i].a + bricks[i].dx)
							{
								dx *= (-1);
								bricks[i].show = false;
								score += 20;
								if (score > getHighscore())
									setHighScore(score);
								/*if(score>=200){
							   game_state=10;
							restart2();
							  }*/
							}
						}
					}
				}
			}
			if (x_ball >= rx && x_ball <= rx + dx_board && y_ball >= ry && y_ball <= ry + dy_board)
			{
				dy *= -1;
			}
			else
			{
				if (y_ball < ry)
				{
					if (life == 0)
					{
						game_state = 10;
					}
					else
						restart();
				}
			}
		}
	}
}

void change2()
{
	if (exx < 200)
		exx += 10;
}
void change3()
{
	if (game_state == -2)
	{
		game_state = -3;
	}
}

void defineBricks()
{
	int sumx = 100;
	int sumy = 450;
	for (int i = 0; i < totalBricks; i++)
	{
		bricks[i].red = rand() % 255;
		bricks[i].green = rand() % 255;
		bricks[i].blue = rand() % 255;
		bricks[i].a = sumx;
		bricks[i].b = sumy;
		sumx += 100;
		if (sumx > 800)
		{
			sumx = 100;
			sumy += 20;
		}
	}
}

void restart()
{
	x_ball = screenwidth / 2;
	y_ball = yAxismarjin;

	rx = x_ball - 50, ry = y_ball - 20, dx_board = 100, dy_board = 10;
	dx = 5;
	dy = 7;
	isStarted = false;
	life = life - 1;
}
void restart2()
{
	x_ball = screenwidth / 2;
	y_ball = yAxismarjin;

	rx = x_ball - 50, ry = y_ball - 20, dx_board = 100, dy_board = 10;
	dx = 5;
	dy = 7;
	isStarted = false;
}

int main()
{

	defineBricks();

	int sum = 100;
	for (int i = 3; i >= 0; i--)
	{
		bCordinate[i].p = 250;
		bCordinate[i].q = sum;
		sum += 150;
	}
	int sum1 = 100;
	for (int i = 3; i >= 0; i--)
	{
		bLevel[i].g = 250;
		bLevel[i].h = sum1;
		sum1 += 150;
	}
	// if(game_state==0)

	// place your own initialization codes here.
	iSetTimer(2500, change3);

	iSetTimer(100, change2);
	iSetTimer(100, change);
	// iSetTimer(50, change);
	iSetTimer(30, change);
	iSetTimer(1, change);

	if (musicOn)
		PlaySound("music\\sample-15s.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(screenwidth, screenHight, "MBBG");
	return 0;
}
