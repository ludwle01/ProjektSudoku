#include "sudoku.h"

int validate(int **sudoku)
{ 
    int here;
    for(int i = 0; i<SIZE; i++){
        for(int j= 0; i<SIZE; i++){
          here = sudoku[i][j];
          if(!validate_cell(i,j,here,sudoku)) return 0;
        }
    }
    return 1;
}
