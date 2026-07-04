#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h" 

int main() {
    int** test = read();
    int valid = validate_matrix(test);
    if(valid == 0){
        printf("Die matrix ist valide!");
    }else if(valid == 1){
        printf("Die matrix ist invalide, der Test ist erfolgreich!");
    }else{
        printf("Irgendwas ist schief gelaufen, int != 0 || 1");
    }
    output(test);

    for (int i = 0; i < 9; i++) {
        free(test[i]);
    }
    free(test);
}
