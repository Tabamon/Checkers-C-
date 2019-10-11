//Lorenzo Toscano squareClass
#include <stdlib.h>
#include <iostream>
#include "enums.hpp"
#ifndef SQUARE
#define SQUARE 10
using namespace std;

class Square{
public:
  Square(){
    rk = NOTKING;
    col = EMPTY;
  }
  int GetChipRank();
  int GetChipColor();
  void SetSquareColor(bool newColor);
  void SetChipColor(int newChipColor);
  void SetChipRank(int newChipRank);
  int GetSquareColor();
  bool isEmpty();
  void operator=(const Square originalSquare);
  void clear();
private:
  int rk;
  int col;
  int squareColor;
};

#endif