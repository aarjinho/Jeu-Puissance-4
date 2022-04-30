#include "jeu.h"

}

int main(void){
    char tableau[7][7];

    srand(time(0));
    initialize(tableau);
    print_tableau(tableau);

    game(tableau);

    return 0;
}
