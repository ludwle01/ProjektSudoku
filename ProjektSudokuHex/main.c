#include "sudoku.h" 

int main() {
  printf("Hi friendly user!\nI am Mister Masterbrain, your personal assistant for solving Hexa-Sudoku puzzles!\n");
  int **puzzle = read();
  int solved = solve(0,0,puzzle);
  if(solved){
    printf("Mister Masterbrain hat dein Sudoku gelöst:\n");
    printMatrix(puzzle);
  }
}
