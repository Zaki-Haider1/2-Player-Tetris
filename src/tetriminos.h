#pragma once

class Tetrimino
{

public:

    Tetrimino(int tetrimino[4][4], int x, int y, int state);

    int structure[4][4];
    int x;
    int y;
    int state;
    

   /* Tetrimino(int tetrimino[4][4] )
    {

        x = 3;
        y = 0;
        state = 0;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                structure[i][j] = tetrimino[i][j];
    }*/

    
};

Tetrimino::Tetrimino(int tetrimino[4][4], int x, int y, int state)
{

    this->x = x;
    this->y = y;
    this->state = state;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            structure[i][j] = tetrimino[i][j];
}


int tetrimino1[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};



int tetrimino2[4][4] = {
    {0, 0, 0, 0},
    {2, 2, 2, 2},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};



int tetrimino3[4][4] = {
    {0, 3, 0, 0},
    {3, 3, 3, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};



int tetrimino4[4][4] = {
    {0, 0, 4, 0},
    {4, 4, 4, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};



int tetrimino5[4][4] = {
    {5, 0, 0, 0},
    {5, 5, 5, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};



int tetrimino6[4][4] = {
    {0, 6, 6, 0},
    {6, 6, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};



int tetrimino7[4][4] = {
    {7, 7, 0, 0},
    {0, 7, 7, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

Tetrimino Otetrimino(tetrimino1, 3 , -1, 0);
Tetrimino Itetrimino(tetrimino2, 3, -1 , 0);
Tetrimino Ttetrimino(tetrimino3 , 3 , 0, 0);
Tetrimino Ltetrimino(tetrimino4 , 3 , 0, 0);
Tetrimino Jtetrimino(tetrimino5 ,3 , 0 , 0);
Tetrimino Stetrimino(tetrimino6 , 3 , 0 , 0);
Tetrimino Ztetrimino(tetrimino7, 3, 0 , 0);

/*Tetrimino Otetrimino(tetrimino1);
Tetrimino Itetrimino(tetrimino2);
Tetrimino Ttetrimino(tetrimino3);
Tetrimino Ltetrimino(tetrimino4);
Tetrimino Jtetrimino(tetrimino5);
Tetrimino Stetrimino(tetrimino6);
Tetrimino Ztetrimino(tetrimino7);
*/