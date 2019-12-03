#include "myfunctions.h"

// глобальные переменные
// int m_posX, m_posY;

// глобльные объекты
// QPixmap pix0, pix1, pix1_5, pix2, pix3;

// глобальные методы
/*qreal multMatrix(Qmd3x3 C, Qmd3x3 H)
{
  qreal S,P,SH;

    P = 0.0; SH = 0.0;
    for (int i = 0; i < 3; i++){
         for (int j = 0; j < 3; j++){
              S = 0.0;
              for (int k = 0; k < 3; k++){
                   S = S+C[i][k] * H[k][j]; // C[i][j] - старые элементы, Hm[i][j] - сглаживающая маска
               } // k
               // S=S[i][j]
               P = P+S; // сумма всех новых элементов S[i][j]
               SH = SH + H[i][j];
         } // j
    } // i
    P = P/(3.0*SH); // усредненное значение C с весом Hm

    return P;
}*/



