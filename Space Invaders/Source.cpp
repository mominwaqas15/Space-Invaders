#include<iostream>
#include "mygraphics.h"
#include "myconsole.h"
#include<fstream>
//#include<cstdlib>
using namespace std;
struct coordinates {
	int x1;
	int y1;
	int x2;
	int y2;
};

int main()
{

	char space[] = "space";
	char game[] = "Space Invader";
	char out[] = "GAME OVER";
	char ingame[] = "Lifes Remaining: ";
	char score[] = "Score: ";
	char win[] = "You Win";
	char conti[] = "To resume game press 'y'";
	char newgame[] = "For new game press 'n' ";
	char save[] = "To save press 's'";
	char resume[] = "To resume press 'r'";
	char highest[] = "HIGH SCORES :";
	char luck[] = "Better luck Next Time";
	char currentscore[] = "Your score :";
	int x = 0, y = 0;
	int ball_x, ball_y;
	bool flag = false;
	bool kill[5][10];
	bool dir = false;
	bool yes = false;
	int check = false;
	bool clear1 = false;
	bool pause = false;
	int rect_x = 0;
	int	rect_y = 50;
	int rows = 50, columns = 0;
	int liney;
	char lives[5];
	int life = 3;
	int scorebeg = 0;
	char scoreend[100];
	int k = 0;
	int high[5];
	char tscore[5][10];
	int count = 0;
	int z1 = 0, z2 = 0;
	int temp1, temp2;




	GetWindowDimensions(x, y);
	ball_x = x / 2;
	ball_y = y - 50;
	int line_x = 0, line_y = 0;

	SetWindowTitle(game);

	for (int i = 0; 5 > i; i++) {
		high[i] = 0;
	}

	for (int i = 0; 5 > i; i++) {
		for (int j = 0; 10 > j; j++) {
			kill[i][j] = false;
		}
	}
	myRect(0, 0, x, y, RGB(12, 12, 12), RGB(120, 12, 12)); //red color screen
	myDrawTextWithFont(x - 900, y / 3, 40, newgame, RGB(255, 255, 255), RGB(120, 12, 12)); // new game
	myDrawTextWithFont(x - 400, y / 2, 40, conti, RGB(255, 255, 255), RGB(120, 12, 12)); // resume
	myDrawTextWithFont(x - 570, 0, 40, game, RGB(0, 255, 0), RGB(120, 12, 12)); // game name

	while (!flag) {




		int c = CheckKeyPressed1();
		if (c == 121) { //lower y for resume
			ifstream outaliens("aliens.txt");
			outaliens >> rect_x >> rect_y >> dir;
			outaliens.close();

			ifstream outball("ball.txt");
			outball >> ball_x >> ball_y;
			outball.close();

			ifstream outkill("kill.txt");
			for (int i = 0; 5 > i; i++) {
				for (int j = 0; 10 > j; j++) {
					outkill >> kill[i][j];
				}
			}
			outkill.close();

			ifstream outlife1("lifes.txt");
			outlife1 >> z1;
			outlife1.close();

			ifstream outscore1("score.txt");
			outscore1 >> z2;
			outscore1.close();
			life = z1;
			scorebeg = z2;
			flag = true;
		}
		else if (c == 110) // n lower case new game
			flag = true;

	}

	myRect(0, 0, x, y, RGB(12, 12, 12), RGB(12, 12, 12));



	while (flag) {



		ofstream inlife("lifes.txt"); // create lifes text
		inlife << life;
		inlife.close();
		ofstream inscore("score.txt"); // create score file
		inscore << scorebeg;
		inscore.close();


		//life start
		myDrawTextWithFont(0, 20, 30, ingame, RGB(0, 255, 250), RGB(0, 0, 0));// lifes remaining
		ifstream outlife("lifes.txt");
		outlife >> lives;
		outlife.close();
		myDrawTextWithFont(170, 20, 30, lives, RGB(0, 255, 250), RGB(0, 0, 0)); // life value
		//life end



		//score start
		myDrawTextWithFont(x - 120, 20, 30, score, RGB(0, 255, 250), RGB(0, 0, 0));// score print
		ifstream outscore("score.txt");
		outscore >> scoreend;
		outscore.close();
		myDrawTextWithFont(x - 50, 20, 30, scoreend, RGB(0, 255, 250), RGB(0, 0, 0));// print value of score
		//score end




		myDrawTextWithFont(x - 570, 0, 40, game, RGB(0, 255, 0), RGB(20, 20, 20));// print game name


		myLine(0, 50, 0, y, RGB(255, 255, 255));
		myLine(0, 50, x, 50, RGB(255, 255, 255));
		myLine(0, y, x, y, RGB(255, 255, 255));
		myLine(x, 50, x, y, RGB(255, 255, 255));




		//ball movement start
		myEllipse(ball_x, ball_y, ball_x + 30, ball_y + 30, RGB(100, 100, 50), RGB(0, 255, 0));
		int a = CheckKeyPressed();
		if (a == UPKEY) {
			myEllipse(ball_x, ball_y, ball_x + 30, ball_y + 30, RGB(12, 12, 12), RGB(12, 12, 12));
			ball_y -= 30;
			if (ball_y <= 50)
				ball_y = 50;
		}
		else if (a == DOWNKEY) {
			myEllipse(ball_x, ball_y, ball_x + 30, ball_y + 30, RGB(12, 12, 12), RGB(12, 12, 12));
			ball_y += 30;
			if (ball_y >= y - 30)
				ball_y = y - 30;
		}
		else if (a == LEFTKEY) {
			myEllipse(ball_x, ball_y, ball_x + 30, ball_y + 30, RGB(12, 12, 12), RGB(12, 12, 12));
			ball_x -= 30;
			if (ball_x <= 0)
				ball_x = 0;
		}
		else if (a == RIGHTKEY) {
			myEllipse(ball_x, ball_y, ball_x + 30, ball_y + 30, RGB(12, 12, 12), RGB(12, 12, 12));
			ball_x += 30;
			if (ball_x >= x - 30)
				ball_x = x - 30;
		}

		//ball movement end

		if (a == 27) { // escape key
			flag = false;
			yes = true;
		}


		//shooting start
		liney = line_y;
		if (a == 32) {
			if (line_y < 50) {
				line_x = ball_x + 15;
				line_y = ball_y;

				check = false;
			}
		}
		myLine(line_x, line_y, line_x, line_y - 10, RGB(12, 12, 12));
		liney = line_y;
		line_y -= 10;
		myLine(line_x, line_y, line_x, line_y - 10, RGB(255, 255, 255));
		//shooting end



		//printing aliens start
		columns = rect_x;
		rows = rect_y;
		for (int i = 0; 5 > i; i++) {
			for (int j = 0; 10 > j; j++) {

				coordinates alien[5][10];
				alien[i][j].x1 = rect_x;
				alien[i][j].y1 = rect_y;
				alien[i][j].x2 = rect_x + 40;
				alien[i][j].y2 = rect_y + 20;

				if (!kill[i][j])
					myRect(rect_x, rect_y, rect_x + 40, rect_y + 20, RGB(12, 12, 12), RGB(12, 12, 12));
				rect_x += 50;

			}
			rect_y += 30;
			rect_x = columns;
		}
		rect_y = rows;




		//aliens movement start 
		rect_x += 10 - dir * 20;
		if (rect_x <= 0 || rect_x + 500 >= x) {
			dir = !dir;
			rect_y += 20;
		}
		//alien movement end




		columns = rect_x;
		rows = rect_y;
		for (int i = 0; 5 > i; i++) {
			for (int j = 0; 10 > j; j++) {

				coordinates alien[5][10];
				alien[i][j].x1 = rect_x;
				alien[i][j].y1 = rect_y;
				alien[i][j].x2 = rect_x + 40;
				alien[i][j].y2 = rect_y + 20;

				//ball matches aliens start
				if ((ball_x >= alien[i][j].x1 && ball_x + 30 <= alien[i][j].x2 &&
					ball_y <= alien[i][j].y1 && ball_y + 30 >= alien[i][j].y2 &&
					kill[i][j] == false) || ((alien[i][j].y2 > y || alien[i][j].y1 > y) &&
						kill[i][j] == false)) {
					columns = 50;
					rows = 50;
					clear1 = true;
					myRect(0, 0, x, y, RGB(12, 12, 12), RGB(12, 12, 12));
					ball_x = x / 2;
					ball_y = y - 50;
					life--;
					break;
				}
				if (life == 0) {
					flag = false;
				}
				//ball matches aliens end


				if (kill[i][j]) {
					myRect(rect_x, rect_y, rect_x + 40, rect_y + 20, RGB(12, 12, 12), RGB(12, 12, 12));
				}
				else
					myRect(rect_x, rect_y, rect_x + 40, rect_y + 20, RGB(255, 0, 0), RGB(255, 0, 0));
				rect_x += 50;

			}
			rect_y += 30;
			rect_x = columns;
		}
		rect_y = rows;
		//printing aliens end



		//alien killing start
		if (!check) {
			while (liney > 50) {

				coordinates bullet;
				bullet.x1 = line_x;
				bullet.y1 = line_y;
				bullet.x2 = line_x;
				bullet.y2 = line_y - 10;

				columns = rect_x;
				rows = rect_y;

				for (int i = 0; 5 > i; i++) {
					for (int j = 0; 10 > j; j++) {
						coordinates alien[5][10];
						alien[i][j].x1 = rect_x;
						alien[i][j].y1 = rect_y;
						alien[i][j].x2 = rect_x + 40;
						alien[i][j].y2 = rect_y + 20;
						if (kill[i][j] == false) {
							if (bullet.x1 >= alien[i][j].x1 && bullet.x1 <= alien[i][j].x2 &&
								bullet.y1 <= alien[i][j].y2 && bullet.y2 >= alien[i][j].y1) {
								kill[i][j] = true;
								myRect(0, 0, x, y, RGB(12, 12, 12), RGB(12, 12, 12));
								check = true;
								scorebeg = scorebeg + 10;
								line_y = 0;
							}
						}
						rect_x += 50;
						liney -= 20;
					}
					rect_y += 30;
					rect_x = columns;
				}
				rect_y = rows;
			}
		}
		//alien killing end



		if (clear1) {
			ClearScreen();
			clear1 = false;
		}


		//to ckeck win start
		k = 0;
		for (int i = 0; 5 > i; i++) {
			for (int j = 0; 10 > j; j++) {
				if (kill[i][j]) {
					k++;
				}
				if (k == 50) {
					flag = false;
				}
			}
		}
		//check win end


		//pause start
		int e = CheckKeyPressed1();
		if (e == 112) { // p lower case
			pause = true;
			while (pause == true) {
				Sleep(100);


				//pause end
				myRect(0, 0, x, y, RGB(12, 12, 12), RGB(120, 12, 12));
				myDrawTextWithFont(x - 570, 0, 40, game, RGB(0, 255, 0), RGB(120, 12, 12));
				myDrawTextWithFont(x - 800, y / 3, 40, save, RGB(255, 255, 255), RGB(120, 12, 12));
				myDrawTextWithFont(x - 400, y / 2, 40, resume, RGB(255, 255, 255), RGB(120, 12, 12));

				//saving start
				ofstream inkill("kill.txt");
				inkill << " ";
				inkill.close();
				int b = CheckKeyPressed1();
				if (b == 115) { // s lower case
					myRect(0, 0, x, y, RGB(12, 12, 12), RGB(12, 12, 12));
					ofstream inaliens("aliens.txt");
					inaliens << rect_x << " " << rect_y << " " << dir;
					inaliens.close();
					ofstream inball("ball.txt");
					inball << ball_x << " " << ball_y << " ";
					inball.close();
					for (int i = 0; 5 > i; i++) {
						for (int j = 0; 10 > j; j++) {
							ofstream inkill("kill.txt", ios::app);
							inkill << kill[i][j] << " ";
							inkill.close();
						}
					}
					flag = false;
					yes = true;
					break;
				}
				else if (b == 114) { // r lower case resume
					myRect(0, 0, x, y, RGB(12, 12, 12), RGB(12, 12, 12));
					pause = false;
				}
			}

		}
		//saving end





	}
	myRect(0, 0, x, y, RGB(12, 12, 12), RGB(120, 12, 12));
	if (flag == false && life == 0) { // life safing
		ofstream inlife("lifes.txt");
		inlife << life;
		inlife.close();
	}
	if (!yes) {
		ofstream outtotal("total.txt", ios::app);
		outtotal << " " << scorebeg;
		outtotal.close();
		ifstream intotal("total.txt");
		for (int i = 0; 5 > i; i++) {

			intotal >> high[i];
		}
		intotal.close();
		for (int i = 0; 5 > i; i++) {
			for (int j = 0; 4 > j; j++) {
				if (high[i] > high[j]) {
					temp1 = high[i];
					temp2 = high[j];
					high[i] = temp2;
					high[j] = temp1;
				}
			}
		}
		ofstream outtotal1("total.txt");
		if (scorebeg > high[4])
			high[4] = scorebeg;
		if (high[4] == high[0] && high[3] == 0) {
			high[4] = 0;
		}
		for (int i = 0; 5 > i; i++) {
			if (high[4] > high[i]) {
				temp1 = high[i];
				temp2 = high[4];
				high[i] = temp2;
				high[4] = temp1;
			}
			outtotal1 << high[i] << " ";
		}
		outtotal1.close();
	}
	ifstream intotal1("total.txt");
	for (int i = 0; 5 > i; i++) {
		intotal1 >> tscore[i];
	}
	intotal1.close();
	int size = y - 150;
	for (int i = 0; 5 > i; i++) {
		myDrawTextWithFont(x - 200, size, 30, highest, RGB(50, 255, 255), RGB(120, 12, 12));
		myDrawTextWithFont(x - 60, size, 30, tscore[i], RGB(50, 100, 255), RGB(120, 12, 12));
		size += 30;
	}


	if (flag == false && life == 0) { // print score till 490
		myDrawTextWithFont(x - 600, y - 150, 50, currentscore, RGB(50, 255, 255), RGB(120, 12, 12));
		myDrawTextWithFont(x - 390, y - 150, 50, scoreend, RGB(50, 255, 255), RGB(120, 12, 12));
	}
	if (k == 50)
		myDrawTextWithFont(x - 670, y / 3, 100, win, RGB(255, 255, 255), RGB(120, 12, 12));
	else {
		myDrawTextWithFont(x - 670, y / 3, 100, out, RGB(255, 255, 255), RGB(120, 12, 12));
		myDrawTextWithFont(x - 590, y - 210, 30, luck, RGB(255, 255, 255), RGB(120, 12, 12));
	}
}