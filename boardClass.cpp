//Lorenzo Toscano || Tabamon
#include "headers/boardClass.hpp"
#include "headers/squareClass.hpp"
#include <iostream>
#include <fstream>

Board::Board(){
  unsigned int i;
  unsigned int j;
  bool color;
  for (i =0; i<8; i++){
    color = (i)%2;
    for (j=0; j<8; j++){
      if ((j+color)%2){
	squares[i][j].SetSquareColor(SQ_WHITE);
      }else{
	squares[i][j].SetSquareColor(SQ_BLACK);
      }
    }
}
turnNumber=0;
blackChips=12;
redChips=12;
}

//Board Class Member Functions
//Setters

void Board::SetRedPlayerName(string name){
  redPlayer=name;
}

void Board::SetBlackPlayerName(string name){
  blackPlayer=name;
}

void Board::SetTurnNumber(int turnNumber){
  this->turnNumber=turnNumber;
}

void Board::SetBlackChips(int blackChips){
  this->blackChips=blackChips;
}

void Board::SetRedChips(int redChips){
  this->redChips=redChips;
}

//Getters

string Board::GetRedPlayerName(){
  return redPlayer;
}

string Board::GetBlackPlayerName(){
  return blackPlayer;
}

int Board::GetTurn(){
  return turnNumber;
}

int Board::GetBlackChips(){
  return blackChips;
}

int Board::GetRedChips(){
  return redChips;
}

//Setup

bool Board::SetupFromFile(char fileName[]){
  Board fromFile;
  int r,c;
  int color,rank;
  ifstream setupFile;
  setupFile.open(fileName);
    if (!setupFile.is_open()){
        cout<<"ERROR, Setup File."<<endl;
        return 1;
    }
    for(unsigned int i=0; i<64; i++){
	  setupFile >> r >> c >> color >> rank;
	  squares[r][c].SetChipColor(color);
	  squares[r][c].SetChipRank(rank);
    if (color == BLACK) blackChips++;
    if (color == RED) redChips++;
	}
    setupFile >> blackPlayer;
    setupFile >> redPlayer;
    setupFile >> turnNumber;
	return 0;
}

char Board::DisplayChecker(int row,int col){

    if (squares[row][col].isEmpty())
         return ' ';
    else{
      if (squares[row][col].GetChipColor() == RED){
          if (squares[row][col].GetChipRank()==NOTKING)
            return 'r';
          else 
            return 'R';
      } 
      else{
          if (squares[row][col].GetChipRank()==NOTKING)
            return 'b';
          else 
            return 'B';
      }
    }
}

void Board::DisplayBoard(){

   std::string dashes = "+-----";      //characters for square top and bottom bounds
   std::string whiteSquareFill = "|*****";      //fill for white squares
   std::string blackSquareFill = "|     ";       // fill for black squares
   std::string line = "";
   std::string filler;
   int i,j,color;
   char chipState;

   
    std::cout << std::endl;
    
    std::cout << "x  ";
    for (i=0; i < 8; i++){     //display board top index
        std::cout << "  " << i+1 << "   ";
    }
    
    std::cout << std::endl;
    std::cout << "y";

    for (i=0; i < 8; i++){   //repeat 8 times, once for each row of squares
        std::cout << " ";
        if (i==0) line="";
        else line = " ";
        
        for (j=0; j < 8; j++){     //build line of cells for boundary  ( +---+ )
            line = line + dashes;
        }
        std::cout << line << "+" << std::endl;

        color = (i+1) % 2;          // Mod 2 - needed to distinguish rows starting with white or black squares
                                    // color = 1 ->row starts with white square, color = 0 -> start with black square
        std::cout << " ";
        line=" ";
        for (j=0; j < 8; j++){           //build first line for row of square
            if ( (j + color) % 2 ){
                filler = whiteSquareFill;        // fill stars for white squares    ( |*****|)
            }
            else{
                filler = blackSquareFill;        // fill spaces for black squares     ( |    |)
            }
            line = line + filler;
        }

        std::cout << line << "|" << std::endl;

        std::cout << i+1;
        line=" ";
        for (j=0; j < 8; j++){          //build second line for row of square ( |  x  | )
            if ((j + color) % 2 ){
               filler = whiteSquareFill;        // fill with stars for white squares    ( |*****|)
            }
            else{
               filler = "|  ";                  // fill spaces for blacksquares
//               filler += board[i][j].displayChipColor();   // display color of checker
               chipState = DisplayChecker(i, j);   // get color of checker
               filler += chipState;                // add color of checker to line
               filler += "  ";
          }
          line = line + filler;
        }

        std::cout << line << "|" << std::endl;
        std::cout << " ";
        line=" ";
        for (j=0; j < 8; j++){           //build third line for row of square
           if ( (j + color) %2 ){
                filler = whiteSquareFill;        // fill with stars for white squares   ( |*****| )
            }
            else{
                filler = blackSquareFill;        // fill with spaces for black squares   ( |     | )
            }
            line = line + filler;
        }
        std::cout << line << "|" << std::endl;
   }

        std::cout << " ";
        line=" ";
        for (j=0; j < 8; j++){     //build line of cells for boundary on bottom of board   ( +---+ )
            line = line + dashes;
        }
        std::cout << line << "+" << std::endl;

        std::cout << std::endl;

}

void Board::SaveGame(char file[]){
  ofstream outputFile;
  outputFile.open(file);
  outputFile.clear();
  for (unsigned int r=0;r<8;++r){
    for (unsigned int c=0; c<8;++c){
      outputFile << r << " " << c << " " << squares[r][c].GetChipColor() << " " << squares[r][c].GetChipRank() << "\n";
    }
  }
  outputFile<<blackPlayer<<endl;
  outputFile<<redPlayer<<endl;
  outputFile<<turnNumber;
  outputFile.close();
}

//Movement
bool Board::IsMoveOnBoard(int fromRow, int fromCol, int toRow, int toCol){

    int valid=0;

    if (fromRow>=0&&fromRow<=7) ++valid;
    if (fromCol>=0&&fromCol<=7) ++valid;
    if (toRow>=0&&toRow<=7) ++valid;
    if (toCol>=0&&toCol<=7) ++valid;
    if (valid==4) return true;
    else{
      cout << "move not legal, not on board!" << endl;
      return false;

    }
}

bool Board::IsRightColor(int fromRow, int fromCol){

    if ((squares[fromRow][fromCol].GetChipColor()-1)!=(turnNumber%2)) return true;
    else{ 
      cout << "move not legal, wrong turn!" <<endl;
      return false; 
    }
}

bool Board::IsValidJump(int fromY, int fromX, int toY, int toX){
  if (fromY+2==toY && fromX+2==toX){
    if (!squares[fromY+1][fromX+1].isEmpty()&&!IsRightColor(fromY+1,fromX+1)){
      RemoveChip(fromY+1,fromX+1);
      return true;
    }
  }else if (fromY+2==toY && fromX-2==toX){
    if (!squares[fromY+1][fromX-1].isEmpty()&&!IsRightColor(fromY+1,fromX-1)){
      RemoveChip(fromY+1,fromX-1);
      return true;
    }
  }else if (fromY-2==toY && fromX+2==toX){
    if (!squares[fromY-1][fromX+1].isEmpty()&&!IsRightColor(fromY-1,fromX+1)){
      RemoveChip(fromY-1,fromX+1);
      return true;
    }
  }else if (fromY-2==toY && fromX-2==toX){
    if (!squares[fromY-1][fromX-1].isEmpty()&&!IsRightColor(fromY-1,fromX-1)){
      RemoveChip(fromY-1,fromX-1);
      return true;
    }
  } 
  return false;
}

bool Board::LegalMove(int fromY, int fromX, int toY, int toX){

if (squares[fromY][fromX].GetChipRank()==NOTKING){
  if ((fromY+1==toY||fromY-1==toY)&&(fromX+1==toX||fromX-1==toX)){
    return true;
  }else if (IsValidJump(fromY, fromX, toY, toX)){
    return true;
  }
}else if (squares[fromY][fromX].GetChipRank()==KING){
  if (squares[toY][toX].GetChipColor()==EMPTY){
	  if (IsValidJump(fromY,fromX,toY,toX)){
		  return true;
	  }
    if (KingValidMove(fromY, fromX, toY, toX)){
      return true;
    }else{ 
      cout << "Not a valid King Move" <<endl;
      return false;}
    }
    
  }
  cout << "move not legal, check squares!" << endl;
  return false;

}

void Board::RemoveChip(int Y, int X){
  if (squares[Y][X].GetChipColor()==BLACK) blackChips--;
  if (squares[Y][X].GetChipColor()==RED) redChips--;
  squares[Y][X].clear();
}

bool Board::ProcessMove(int fromY, int fromX, int toY, int toX){

  if (IsMoveOnBoard(fromY,fromX,toY,toX)){
    if (!squares[fromY][fromX].isEmpty()&&IsRightColor(fromY,fromX)){
      if (squares[toY][toX].isEmpty()){
        if (LegalMove(fromY, fromX, toY, toX)){
          squares[toY][toX]=squares[fromY][fromX];
          squares[fromY][fromX].clear();
          turnNumber++;
          MakeKing(toY,toX);
          cout << "move processed!"<<endl;
          return true;
        }
      }else cout << "not empty" << endl;
    }else cout << "no chip to move" <<endl;
  }
  return false;
}

void Board::MakeKing(int Y, int X){
  if (squares[Y][X].GetChipColor()==RED){
    if (Y==7){
      squares[Y][X].SetChipRank(KING);
    }
  }else if (squares[Y][X].GetChipColor()==BLACK){
    if (Y==0){
      squares[Y][X].SetChipRank(KING);
    }
  }else{
    //do nothing
  }
}

chipColor Board::CheckWinner(){
  if (blackChips==0){
    cout << redPlayer << " is the winner" <<endl;
    return RED;
  }else if (redChips==0){
    cout << blackPlayer << " is the winner"<<endl;
    return BLACK;
  }else{
    return EMPTY;
  }
}

bool Board::KingValidMove(int fromY, int fromX, int toY, int toX){
  if (fromY>toY){
    if (fromX>toX){
      for (unsigned int i = 1; i>=fromX-toX; i++){
        if (!squares[fromY-i][fromX-i].isEmpty()){
          cout<<"1";
          return false;
        }
      }
      return true;
    }
    if (fromX<toX){
      for (unsigned int i = 1; i<=toX-fromX; i++){
        if (!squares[fromY-i][fromX+i].isEmpty()){
          cout<<"2";
          return false;
        }
      }
      return true;
    }
  }else if (fromY<toY){
    if (fromX>toX){
      for (unsigned int i = 1; i>=fromX-toX; i++){
        if (!squares[fromY+i][fromX-i].isEmpty()){
          cout<<"3";
          return false;
        }
      }
      return true;
    }
    if (fromX<toX){
      for (unsigned int i = 1; i<=toX-fromX; i++){
        if (!squares[fromY+i][fromX+i].isEmpty()) {
          cout<<"4";
          return false;
        }
      }
      return true;
    }
  }else {return false;}
return false;
}