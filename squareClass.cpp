#include "headers/squareClass.hpp"
#include <iostream>


//setters
void Square::SetChipColor(int newChipColor){
  col=newChipColor;
}

void Square::SetChipRank(int newChipRank){
  rk=newChipRank;
}

void Square::SetSquareColor(bool newColor){
  squareColor = newColor;
}

//getters
int Square::GetSquareColor(){
  return squareColor;
}

int Square::GetChipRank(void){
  return rk;
}

int Square::GetChipColor(void){
  return col;
}

//functions
bool Square::isEmpty(){
    if(col == EMPTY)
        return true;
    else
        return false;
}

void Square::operator=(const Square originalSquare){
  rk=originalSquare.rk;
  col=originalSquare.col;
}

void Square::clear(){
  SetChipColor(EMPTY);
  SetChipRank(NOTKING);
}