//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
#include<string>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>
#include<iostream> 
#include<fstream>     // for basic math functions such as cos, sin, sqrt
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 
 * */
void SetCanvasSize(int width, int height) {
    glViewport(0,0,(GLsizei)width,(GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */

int gridX,gridY;
int width = 80, height = 80;

int foodX,foodY;
int pos_food_x1,pos_food_y1;
int pos_food_x2,pos_food_y2;
int pos_food_x3,pos_food_y3;
int pos_food_x4,pos_food_y4;
int pos_food_x5,pos_food_y5;
int BigFood_X,BigFood_Y;

bool food1=true;
bool food2=true;
bool food3=true;
bool food4=true;
bool food5=true;
bool Big_Food=false;

int pos_hardle_1_x,pos_hardle_1_y;
int pos_hardle_2_x,pos_hardle_2_y;
bool hardle=true;

int length_snake=5;
int pos_x[500]={34,36,37,38},pos_y[500]={40,40,40,40};
string direction="LEFT";

int score=0;
int highScores[20];
int page=0;
bool read_s=false;

void drawsnake();
void drawfood();
void unit(int,int);
void grid();
void init();
void initGrid(int x,int y){
	gridX=x;
	gridY=y;
}	
void change(int value);
void DrawHardle();
bool Digonal(int ,int ,int ,int);
bool Checkforsamerow(int ,int);
void death();
bool IsOverlapWithSnake(int x, int y);
void HardleChange(int value1);
void BigFoodChange(int value1);
bool isOverlap(int x, int y);
void ReadHighScores();
void ReadHighScores();
void WriteHighScore(int score);
void BigFood();
void MainPage();

void Display() { // This is dispaly function in which I call a lot of function which i wnat to display
    
    	if(page==1){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);  
	grid();
 	drawsnake();
 	drawfood();
	DrawHardle();
	BigFood();
	DrawLine( 0 , 0 , 0 , 30, 50 , colors[MISTY_ROSE] );
	DrawLine( 0 , 50 , 0 , 76, 20 , colors[MISTY_ROSE] );
	DrawLine(0 , 76 ,30  , 76 , 5 , colors[MISTY_ROSE] );
	DrawLine(50 , 76 ,80  , 76 , 5 , colors[MISTY_ROSE] );
	DrawLine( 80 , 76 , 80, 50 , 20 , colors[MISTY_ROSE] );
	DrawLine( 80 , 0 , 80, 30 , 50 , colors[MISTY_ROSE] );
	DrawLine( 0 , 0 , 30 ,0 , 50 , colors[MISTY_ROSE] );
	DrawLine( 50 , 0 , 80 ,0 , 1000 , colors[MISTY_ROSE] );
	
	DrawString( 5,78 , "Score :", colors[MISTY_ROSE]);
	
	stringstream ss;
        ss << score;
        
	DrawString( 12,78 , ss.str(), colors[MISTY_ROSE]);
	death();
	}
	MainPage();
	if(read_s){
		ReadHighScores();
	
		for (int i = 0,j=0; i < 5; i++) {
		
           	 stringstream ss;
               	ss << "High Score " << i + 1 << ": " << highScores[i];
            	DrawString(33, 28-j, ss.str(), colors[MISTY_ROSE]);
            	 j=j+3;
        }
	}	
	
	
    glutSwapBuffers();
}


void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT && direction != "RIGHT") {
        direction = "LEFT";
    } else if (key == GLUT_KEY_RIGHT && direction != "LEFT") {
        direction = "RIGHT";
    } else if (key == GLUT_KEY_UP && direction != "DOWN") {
        direction = "UP";
    } else if (key == GLUT_KEY_DOWN && direction != "UP") {
        direction = "DOWN";
    }

    glutPostRedisplay();
}


void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC) {
        exit(1); 
    }
    
    if(key=='S' || key=='s'){
    	page=1;
	pos_x[0]=34,pos_y[0]=40;
	pos_x[1]=36,pos_y[1]=40;
	pos_x[2]=37,pos_y[2]=40;
	food1=true;
	food2=true;
	food3=true;
	food4=true;
	food5=true;
	Big_Food=false;
	hardle=true;

	length_snake=5;
	direction="LEFT";
    	score=0;
    }
    if(key=='R' || key=='r'){
    	page=1;
    }
    if(key=='P' || key=='p'){
    	page=3;
    }	
    if(key=='H' || key=='h'){
    	read_s=true;
    }	
    else if (int(key) == 13)
    {  
	}
    	
    glutPostRedisplay();
}

// use timer
void Timer(int m) {

	glutPostRedisplay();
    glutTimerFunc(500.0 / FPS, Timer, 60);
    
}

void HardleChange(int value1){
	hardle=true;
	glutTimerFunc( 30000, HardleChange, 1);
}


void change(int value) {
	food1 = true;
    	food2 = true;
    	food3 = true;
   	food4 = true;
   	food5 = true;
    glutTimerFunc( 15000, change, 1);
}

void changeBigFood1(int value1) {
	BigFood_X = rand() % 70+90;
        BigFood_Y = rand() % 70+90;
    glutTimerFunc( 20000, changeBigFood1, 4);
}

void changeBigFood(int value1) {
	Big_Food=true;
    glutTimerFunc( 60000, changeBigFood, 3);
}


// MAIN FUNCTION IN WHICH FUNCTION CALL
int main(int argc, char*argv[]) {
    
    InitRandomizer(); 
    glutInit(&argc, argv); 

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowPosition(50, 50); 
    glutInitWindowSize(900, 900); 
    glutCreateWindow("PF's Snake Game"); 
    SetCanvasSize(width, height); 
    glutTimerFunc( 15000, change, 2);
    glutTimerFunc( 30000, HardleChange, 1);
    glutTimerFunc( 60000, changeBigFood, 3);
    glutTimerFunc( 20000, changeBigFood1, 4);
    init();

    glutDisplayFunc(Display); 
    glutSpecialFunc(NonPrintableKeys); 
    glutKeyboardFunc(PrintableKeys); 
    glutTimerFunc(5.0 / FPS, Timer, 0);

    glutMainLoop();
    return 1;
}

void drawsnake() {
    // Update the position of the snake's body segments
    for (int i = length_snake; i > 0; i--) {
        pos_x[i] = pos_x[i - 1];
        pos_y[i] = pos_y[i - 1];
    }

    // Update the position of the snake's head based on the direction
    if (direction == "UP") {
        pos_y[0] ++;
    } else if (direction == "DOWN") {
        pos_y[0] --;
    } else if (direction == "RIGHT") {
        pos_x[0] ++;
    } else if (direction == "LEFT") {
        pos_x[0] --;
    }
	// in or out
	if (pos_x[0] >= 80 ) {
        pos_x[0] = 0;
   	 }
    	if (pos_y[0] >= 76.5 ) {
        pos_y[0] = 1;
   	 }
   	 if (pos_x[0] <= 0 ) {
        pos_x[0] = 80;
   	 }
    	if (pos_y[0] <= 0 ) {
        pos_y[0] = 76;
   	 }
	
	
    // Draw the snake
    for (int i = 0; i < length_snake; i++) {
        if (i == 0)
            DrawCircle(pos_x[i]+0.5, pos_y[i]+0.5, 0.5, colors[83]);  // Head
        else if(i%2==1)
            DrawSquare(pos_x[i], pos_y[i], 2, colors[9]); // Body
        else
            DrawSquare(pos_x[i], pos_y[i], 2, colors[1]); 
    }
	//check food eats
	if(pos_x[0]==pos_food_x1 && pos_y[0]==pos_food_y1){
		length_snake++;
		score += 5;
		food1=true;
	}
	
	if(pos_x[0]==pos_food_x2 && pos_y[0]==pos_food_y2){
		length_snake++;
		score += 5;
		food2=true;
	}
	
	if(pos_x[0]==pos_food_x3 && pos_y[0]==pos_food_y3){
		length_snake++;
		score += 5;
		food3=true;
	}
	
	if(pos_x[0]==pos_food_x4 && pos_y[0]==pos_food_y4){
		length_snake++;
		score += 5;
		food4=true;
	}
	
	if(pos_x[0]==pos_food_x5 && pos_y[0]==pos_food_y5){
		length_snake++;
		score += 5;
		food5=true;
	}
	// Bonus point or food
	if((pos_x[0]==BigFood_X && pos_y[0]==BigFood_Y) || (pos_x[0]==BigFood_X && pos_y[0]==BigFood_Y+1) || (pos_x[0]==BigFood_X-1 && pos_y[0]==BigFood_Y-1)){
		length_snake+=2;
		score += 20;
		BigFood_X = rand() % 70+90;
                BigFood_Y = rand() % 70+90;
	}		
		
}



void init(){
	glClearColor(0,0,0,1);
	initGrid(width,height);
}	

void grid(){
	for(int x=0;x<gridX;x++){
		for(int y=0;y<gridY;y++){
		
			unit(x,y);
		}
	}
}

void unit(int x,int y){		

	glLineWidth(2.0);
	glColor3f(0,0,0);
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
		glVertex2f(x+1,y);
		glVertex2f(x+1,y+1);
		glVertex2f(x,y+1);
	glEnd();	


}	

void drawfood() {
	srand(time(0));
	
	if(food5){
	
        do { //food5
        
    		pos_food_x5=rand()%16+63;
    		pos_food_y5=rand()% 73 + 2;
    	
    	} while (isOverlap(pos_food_x5, pos_food_y5)) ;
    	
    		food5=false;
        }
    
        if(food4){
        
        do { // food4
    		pos_food_x4=rand()%16+49;
    		pos_food_y4=rand()%73 +2;
    	} while (isOverlap(pos_food_x4, pos_food_y4) || (Checkforsamerow(pos_food_y4,pos_food_y5)) ||   ( Digonal(pos_food_x4,pos_food_y4,pos_food_x5,pos_food_y5)));
    		food4=false;
    		
        }
    
        if(food3){ //food 3
        
        do {
    		pos_food_x3=rand()%21+30;
    		pos_food_y3=rand()% 73 +2;
    	} while (isOverlap(pos_food_x3, pos_food_y3) || (Checkforsamerow(pos_food_y3,pos_food_y4) || Checkforsamerow(pos_food_y3,pos_food_y4)) ||  (Digonal(pos_food_x3,pos_food_y3,pos_food_x4,pos_food_y4) || Digonal(pos_food_x3,pos_food_y3,pos_food_x5,pos_food_y5)));
    		food3=false;
    }
	
	
	if (food2 ) { //food 2
	
        do {
        
            pos_food_x2 = rand() % 15 + 16;
            pos_food_y2 = rand() % 73+2;
            
        } while (isOverlap(pos_food_x2, pos_food_y2) || (Checkforsamerow(pos_food_y2,pos_food_y3) || Checkforsamerow(pos_food_y2,pos_food_y4) || Checkforsamerow(pos_food_y2,pos_food_y5)) || (Digonal(pos_food_x2,pos_food_y2,pos_food_x3,pos_food_y3) || Digonal(pos_food_x2,pos_food_y2,pos_food_x4,pos_food_y4) ||
   	Digonal(pos_food_x2,pos_food_y2,pos_food_x5,pos_food_y5)));

       	 food2 = false;
        }
    
        if (food1 ) { //food1
         
        do {
          	 pos_food_x1 = rand() % 15 + 1;
          	 pos_food_y1 = rand() % 73+2;
        } while (isOverlap(pos_food_x1, pos_food_y1) || (Checkforsamerow(pos_food_y1,pos_food_y2) || Checkforsamerow(pos_food_y1,pos_food_y3) || Checkforsamerow(pos_food_y1,pos_food_y4) || Checkforsamerow(pos_food_y1,pos_food_y5)) || (Digonal(pos_food_x1,pos_food_y1,pos_food_x2,pos_food_y2) || Digonal(pos_food_x1,pos_food_y1,pos_food_x3,pos_food_y3) ||
   	Digonal(pos_food_x1,pos_food_y1,pos_food_x4,pos_food_y4) || Digonal(pos_food_x1,pos_food_y1,pos_food_x5,pos_food_y5)));

       		 food1 = false;
    }
    
   	 
 
    DrawSquare(pos_food_x1, pos_food_y1, 2, colors[60]); // FOod are prints
    DrawSquare(pos_food_x2, pos_food_y2, 2, colors[60]);
    DrawSquare(pos_food_x3, pos_food_y3, 2, colors[60]);
    DrawSquare(pos_food_x4, pos_food_y4, 2, colors[60]);
    DrawSquare(pos_food_x5, pos_food_y5, 2, colors[60]);
    
   
}	

bool Checkforsamerow(int y1,int y2){ // function to chreck reows
	return (y1==y2);
		
}
	
bool Digonal(int x1,int y1,int x2,int y2){ // Function to check digonal
 	return(abs(x1-x2)==abs(y1-y2));
 }		

void DrawHardle() {
    if (hardle) {   // hurdle positions until it does not overlap with the snake
        
        do {
            pos_hardle_1_x = rand() % 77+1;
            pos_hardle_1_y = rand() % 40+3;
            pos_hardle_2_x = rand() % 77+1;
            pos_hardle_2_y = rand() % 40 +22;
        } while (IsOverlapWithSnake(pos_hardle_1_x, pos_hardle_1_y) || IsOverlapWithSnake(pos_hardle_2_x, pos_hardle_2_y));

        hardle = false;
    }

    DrawLine(pos_hardle_1_x, pos_hardle_1_y, pos_hardle_1_x, pos_hardle_1_y + 10, 2, colors[MISTY_ROSE]);
    DrawLine(pos_hardle_2_x, pos_hardle_2_y, pos_hardle_2_x, pos_hardle_2_y + 10, 2, colors[MISTY_ROSE]);
}

bool IsOverlapWithSnake(int x, int y) { // chack position overlap with snakee
    for (int i = 0; i < length_snake; i++) {
        if (x == pos_x[i] && (y= pos_y[i] || y+1 == pos_y[i] || y+2 == pos_y[i] || y+3 == pos_y[i] || y+4 == pos_y[i] || y+5 == pos_y[i] || y+7 == pos_y[i] || y+8 == pos_y[i]|| y+9 == pos_y[i] || y+10 == pos_y[i] )) {
            return true; // Position overlaps with snake
        }
    }
    return false; 
}

bool isOverlap(int x, int y) { // Check overlap with the snake
    
    for (int i = 0; i < length_snake; i++) {
        if (x == pos_x[i] && y == pos_y[i]) {
            return true; // Position overlaps with snake
        }
    }

    // Check overlap with hurdle 1
    if ((x >= pos_hardle_1_x && x <= pos_hardle_1_x) &&
        (y >= pos_hardle_1_y && y <= pos_hardle_1_y + 10)) {
        return true; // Position overlaps with hurdle
    }

    // Check overlap with hurdle 2
    if ((x >= pos_hardle_2_x && x <= pos_hardle_2_x) &&
        (y >= pos_hardle_2_y && y <= pos_hardle_2_y + 10)) {
        return true; // Position overlaps with hurdle
    }

    // Position does not overlap with snake or hurdles
    return false;
}

void death(){ //COndition in which the snake die and game over
    for(int i=1 ; i < length_snake; i++){
        if(pos_x[0]==pos_x[i] && pos_y[0]==pos_y[i]){
            page=2;
        }	
    }      
    if(pos_x[0]==pos_hardle_1_x && (pos_y[0]>=pos_hardle_1_y && pos_y[0]<=pos_hardle_1_y+10) ){
    page=2;
    }
    
    if(pos_x[0]==pos_hardle_2_x && (pos_y[0]>=pos_hardle_2_y && pos_y[0]<=pos_hardle_2_y+10) ){
    	page=2;
    } else if (pos_x[0]==0 && (pos_y[0]>=0 && pos_y[0]<=30)){
    	page=2;
    } else if (pos_x[0]==0 && (pos_y[0]>=50 && pos_y[0]<=80)){
    	page=2;
    }else if (pos_x[0]==79 && (pos_y[0]>=0 && pos_y[0]<=30)){
    	page=2;
    } else if (pos_x[0]==79 && (pos_y[0]>=50 && pos_y[0]<=80)){
    	page=2;
    } else if (pos_y[0]==75 && (pos_x[0]>=50 && pos_x[0]<=80)){
    	page=2;
    } else if (pos_y[0]==0 && (pos_x[0]>=0 && pos_x[0]<=30)){
    	page=2;
    } else if (pos_y[0]==0 && (pos_x[0]>=50 && pos_x[0]<=80)){
    	page=2;
    }else if (pos_y[0]==75 && (pos_x[0]>=0 && pos_x[0]<=30)){
    	page=2;
    } 
     
     
}

void MainPage(){ // Menu display
	if(page==0){
		DrawString( 33,40 , "Start New Game", colors[MISTY_ROSE]);
		DrawString( 33,37 , "History", colors[MISTY_ROSE]);
		DrawString( 33,31 , "Exit", colors[MISTY_ROSE]);
	}
	if (page==2){
		DrawString( 34,43 , "GAME OVER!", colors[MISTY_ROSE]);
		DrawString( 33,41 , "Your Score is :", colors[MISTY_ROSE]);
		stringstream ss;
       		ss << score;
       		DrawString( 46,41 , ss.str(), colors[MISTY_ROSE]);
       		ofstream outFile("highscores.txt", ios::app);
   		 if (outFile.is_open()) {
     		outFile << score << endl;
      		  outFile.close();
    }
       		
	}
	if (page==3){
		DrawString( 33,40 , "Start New Game", colors[MISTY_ROSE]);
		DrawString( 33,37 , "Resume Game", colors[MISTY_ROSE]);
		DrawString( 33,34 , "History", colors[MISTY_ROSE]);
		DrawString( 33,28 , "Exit", colors[MISTY_ROSE]);
	}
	
}
// Bonus food
void BigFood() {
    if (Big_Food) {
        do {
            BigFood_X = rand() % 70;
            BigFood_Y = rand() % 70;
        } while (isOverlap(BigFood_X, BigFood_Y));

        Big_Food = false;
    }
    	 DrawCircle(BigFood_X, BigFood_Y, 1, colors[80]);
}
void ReadHighScores() {
    ifstream inFile("highscores.txt");
    if (inFile.is_open()) {
        int i = 0;
        while (inFile >> highScores[i] && i < 20) {
            i++;
        }
        inFile.close();
    }
}



	
#endif /* Snake Game */
 
