//Lorenzo Toscano Lab04
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "headers/squareClass.hpp"
#include "headers/boardClass.hpp"
#include "headers/enums.hpp"
using namespace std;

//main test function
int main(void){
  Board checkersBoard;
  string buffer;
  char newBoard[30] = "newboard.txt";

  char menu;
  char fileName[30];
  bool menuFlag=0;
  do {
    cout << "Do you want to start a new game or resumme?[N/R] ";
    cin >> menu;
    menu = toupper(menu);

    if (menu == 'N'){
      if (checkersBoard.SetupFromFile(newBoard)!=0){
        cout << "ERROR, missing newboard.txt File";
        exit(1);
      }
      checkersBoard.DisplayBoard();
      cout << "Player1: ";
      cin >> buffer;
      checkersBoard.SetBlackPlayerName(buffer);
      cout << "Player2: ";
      cin >> buffer;
      checkersBoard.SetRedPlayerName(buffer);
      cout << "Save the game in file: ";
      cin >> fileName;
      menuFlag=1;
    }else if (menu == 'R'){
      cout << "Insert file name for saved game: ";
      cin >> fileName;
      if (checkersBoard.SetupFromFile(fileName)!=0){
        cout << "ERROR, missing newboard.txt File"<<endl;
        menuFlag=0;
      }else{
      checkersBoard.DisplayBoard();
      menuFlag=1;
      }
    }else{
      menuFlag=0;
      cout << "ERROR, Wrong input" << endl;
    }
  }while(menuFlag!=1);
  
  int fromX,fromY,toX,toY;
  string turn;
  while (checkersBoard.CheckWinner()==EMPTY){

    if (checkersBoard.GetTurn()%2==0){
      turn=checkersBoard.GetBlackPlayerName();
    }else{
      turn = checkersBoard.GetRedPlayerName();
    }
    cout << turn <<" insert your move"<< endl;
    cin >> fromX>>fromY>>toX>>toY;
    checkersBoard.ProcessMove(fromY-1,fromX-1,toY-1,toX-1);
    checkersBoard.DisplayBoard();
    checkersBoard.SaveGame(fileName);
  }
}


