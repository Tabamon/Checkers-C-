//Lorenzo Toscano Lab05 boardClass
#ifndef CLASSES
#define CLASSES 10
#include "squareClass.hpp"

class Board{
public:
  Board();
  bool SetupFromFile(char fileName[]);
  void DisplayBoard();
  void SaveGame(char file[]);
  bool ProcessMove(int fromY, int fromX, int toY, int toX);
  chipColor CheckWinner();
  void SetRedPlayerName(string name);
  void SetBlackPlayerName(string name);
  string GetRedPlayerName();
  string GetBlackPlayerName();
  int GetTurn();
  int GetBlackChips();
  int GetRedChips();
  void SetTurnNumber(int turnNumber);
  void SetBlackChips(int blackChips);
  void SetRedChips(int redChips);
private:
  //variables
  Square squares[8][8];
  string redPlayer;
  string blackPlayer;
  int turnNumber;
  int blackChips;
  int redChips;
  //functions
  char DisplayChecker(int row,int col);
  bool IsMoveOnBoard(int fromRow, int fromCol, int toRow, int toCol);
  bool IsRightColor(int fromRow, int fromCol);
  bool LegalMove(int fromY, int fromX, int toY, int toX);
  void RemoveChip(int Y, int X);
  bool IsValidJump(int fromY, int fromX, int toY, int toX);
  void MakeKing(int Y, int X);
  bool KingValidMove(int fromY, int fromX, int toY, int toX);

};

#endif
