#include <iostream>
#include <conio.h> //for _kbhit() & _getch()
#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>  // Required for std::chrono::seconds, milliseconds, etc.
#include <cstdlib> //for srand()

void updateBoard();
int input(); //take input for moving snake using canio.h
void logic();
void updateScoreNFruit(); //update score & fruit coordinates

const int SLEEP_TIME = 300; //milliseconds to wait before updating the board, increase it for bigger boards
const int ROW = 20;
const int COL = 50;
char playground[ROW][COL];

int snakex, snakey, fruitx, fruity, score;

enum Controls {
    UP, DOWN, RIGHT, LEFT, NOINPUT
};

int main() {
    //fill board with empty values
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            playground[i][j] = ' ';
        }
    }

    //generate random cords for fruit
    srand(time(0));
    fruity = (rand() % (ROW-2)) + 1; // board = [0, row-1] // playable board = [1, row-2] // fruitx = [0, row-3] + 1
    fruitx = (rand() % (COL-2)) + 1; // board = [0, col-1] // playable board = [1, col-2] // fruitx = [0, col-3] + 1

    //default starting position (center of board)
    snakex = COL/2;
    snakey = ROW/2;

    std::cout << "press any key to begin" << std::endl;
    logic();
    std::cout<< "game over :( your score: " << score << std::endl;
    return 0;
}

void logic() {
    while (snakex > 0 && snakex < COL-1 && snakey > 0 && snakey < ROW-1) {  
        switch (input())
        {
            case UP:
                while (!(_kbhit()) && snakex > 0 && snakex < COL-1 && snakey > 0 && snakey < ROW-1){
                    updateScoreNFruit();
                    snakey--;
                    updateBoard();
                }
                break;
            case DOWN:
                while (!(_kbhit()) && snakex > 0 && snakex < COL-1 && snakey > 0 && snakey < ROW-1){
                    updateScoreNFruit();
                    snakey++;
                    updateBoard();
                }
                break;
            case RIGHT:
                while (!(_kbhit()) && snakex > 0 && snakex < COL-1 && snakey > 0 && snakey < ROW-1){
                    updateScoreNFruit();
                    snakex++;
                    updateBoard();
                }
                break;
            case LEFT:
                while (!(_kbhit()) && snakex > 0 && snakex < COL-1 && snakey > 0 && snakey < ROW-1){
                    updateScoreNFruit();
                    snakex--;
                    updateBoard();
                }
                break;
            
            default:
                updateScoreNFruit();
                updateBoard();
                break;
        }
    }
} 

void updateBoard() {
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME)); //waits before updating the board

    //clear terminal
    #ifdef _WIN32
        system("cls"); //for windows
    #else
        system("clear"); //for linux
    #endif 

    std::cout << "snake x: " << snakex << " snake y: " << snakey << " score :"<< score << std::endl <<
                 "fruit x: " << fruitx << " fruit y: " << fruity << std::endl;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == snakey && j == snakex) std::cout << '@'; //snake
            else if (i == fruity && j == fruitx) std::cout << '&'; //fruit
            else if (i == 0 || i == ROW-1) std::cout << '#'; //border
            else if (j == 0 || j == COL-1) std::cout << '#'; //border
            else std::cout << playground[i][j];
        }
        std::cout << std::endl;
    }
}

int input() { //take input for moving snake using canio.h
    switch (_getch())
        {
            case 'w':
                return UP;
            case 's':
                return DOWN;
            case 'a':
                return LEFT;
            case 'd':
                return RIGHT;
            case 'q':
            
            default:
                return NOINPUT;
        }
}

void updateScoreNFruit() {
    if (snakex == fruitx && snakey == fruity) {
        score++;
        fruity = (rand() % (ROW-2)) + 1; 
        fruitx = (rand() % (COL-2)) + 1; 
    }
}