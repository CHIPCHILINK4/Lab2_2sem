#include <stdio.h>
#include <stdlib.h>
#include <time.h>


short int printi(int** Dptr, size_t rows, size_t columns) {
   if (Dptr&& *Dptr)
   {
       if(rows>0 && columns>0)
       {
           //printf("A[%zu][%zu] = \n", rows, columns);
           for (size_t i = 0; i < rows; i++)
           {
               if (Dptr[i])
               {
                   for (size_t j = 0; j < columns; j++)
                   {
                       printf("%3d ", Dptr[i][j]);
                   }
               }
               else
               {
                   printf("NULL");
               }
               printf("\n");;
           }
           printf("\n");
           printf("\n");
           return 0;
       }
   }
   else
   {
       return 1;
   }
}

void free_matrix(int*** Dptr, size_t rows) {
   if (Dptr /*&& *Dptr*/)
   {
       int** Dptr1 = *Dptr;
       for (size_t i = 0; i < rows; i++)
       {
           if (Dptr1[i])
           {
               free(Dptr1[i]);
               Dptr1[i] = NULL;
               //printf("%p\n", **Dptr);
           }
       }
       free(*Dptr);
       *Dptr = NULL;
   }

   //return NULL;
}

int** set_matrix(size_t rows, size_t columns, int rangeA, int rangeB) {

   if (rows>0 && columns>0)
   {
       if (rangeA > rangeB) {
           int tmp = rangeA;
           rangeA = rangeB;
           rangeB = tmp;
       }
       int** Dptr = (int**)calloc(rows, sizeof(int*));
       if (Dptr) {
           for (size_t i = 0; i < rows; i++) {
               Dptr[i] = (int*)calloc(columns, sizeof(int));
               if (Dptr[i]) {
                   for (size_t j = 0; j < columns; j++) {
                       Dptr[i][j] = rand() % (rangeB + 1 - rangeA) + rangeA;
                       //Dptr[i][j] = j;
                       //Dptr[i][j] = i;
                   }
               }
               else
               {
                   free_matrix(&Dptr, rows);
                   return NULL;
               }
           }
           return Dptr;
       }
   }
   return NULL;
}

int** matrix_transpositions(int** Mx, size_t rows, size_t columns) {
   int** transpositionMx = NULL;
   if (Mx)
   {
       transpositionMx = set_matrix(columns, rows, 0, 0);
       if (transpositionMx)
       {
           int* tmp = NULL;

           for (size_t i = 0; i < rows; i++)
           {
               if (Mx[i])
               {
                   tmp = Mx[i];//по другому  был калок

                   for (size_t j = 0; j < columns; j++)
                   {
                       transpositionMx[j][i] = tmp[j];
                   }
               }
               //else
               //{
               //    for (size_t j = 0; j < columns; j++)
               //    {
               //        transpositionMx[j][i] = NULL;
               //    }
               //}
           }
       }
   }
   return transpositionMx;
}


int** sum_of_sparse_matrices(int** Mx1, int** Mx2, size_t rows, size_t columns) {
   if (Mx1 && Mx2)
   {
       if ((rows == columns) && rows > 0)
       {
           int** resSum = NULL;
           resSum = set_matrix(rows, columns, 0, 0);
           //int* tmp = NULL;// я пробовал
           for (size_t i = 0; i < rows; i++)
           {
               if ((Mx1[i] == NULL) && (Mx2[i] == NULL))
               {
                   free(resSum[i]);
                   resSum[i] = NULL;
               }
               else if ((Mx1[i]) && (Mx2[i] == NULL))
               {
                   for (size_t j = 0; j < columns; j++)//иначе никак тогда при удалении матрицы у нас меняются значения в дптр1 и дптр2
                   {
                       resSum[i][j] = Mx1[i][j];
                   }


               }
               else if ((Mx1[i] == NULL) && (Mx2[i]))
               {
                   for (size_t j = 0; j < columns; j++)//иначе никак тогда при удалении матрицы у нас меняются значения в дптр1 и дптр2
                   {
                       resSum[i][j] = Mx2[i][j];
                   }
               }
               else
               {
                   for (size_t j = 0; j < columns; j++)
                   {
                       resSum[i][j] = Mx1[i][j] + Mx2[i][j];
                   }
               }
           }
           return resSum;
       }
   }
   return NULL;
}




//двойной указатель
int main() {
   clock_t t;

   int** Dptr1 = NULL;
   int** Dptr2 = NULL;

   //int* some = 0;
   //printi(&some, 3, 3);

   size_t row = 0, col = 0;
   int rangeA = 0, rangeB = 0;

   printf("rows, columns, rangeA, rangeB\n");
   //short int check = scanf_s("%zu %zu %d %d", &row, &col, &rangeA, &rangeB);
   int check = 4;
   row = 3; col = 3; rangeA = 1; rangeB = 100;

   printf("\n");

   t = clock();
   if (check == 4)
   {
       //srand(time(0));
       srand(1);
       Dptr1 = set_matrix(row, col, rangeA, rangeB);
       Dptr2 = set_matrix(row, col, rangeA, rangeB);


       printf("start AAAAAAAAAAAAAAAA\n");
       printi(Dptr1, row, col);

       printf("start BBBBBBBBBBBBBBBB\n");
       printi(Dptr2, row, col);



       //
       free(Dptr1[0]); Dptr1[0] = NULL; free(Dptr1[2]); Dptr1[2] = NULL; free(Dptr2[2]); Dptr2[2] = NULL;

       //for (size_t i = 0; i < row; i++){free(Dptr1[i]); Dptr1[i] = NULL;}

       //for (size_t i = 0; i < row; i++){free(Dptr2[i]); Dptr2[i] = NULL;}

       //for (size_t i = 0; i < row; i++){free(Dptr1[i]); Dptr1[i] = NULL;free(Dptr2[i]); Dptr2[i] = NULL;}



       //


       if (Dptr1 && Dptr2) {
           printf("AAAAAAAAAAAAAAAA\n");
           printi(Dptr1, row, col);
           printf("BBBBBBBBBBBBBBBB\n");
           printi(Dptr2, row, col);
           int** MxRes = NULL;
           MxRes = sum_of_sparse_matrices(Dptr1, Dptr2, row, col);


           if (MxRes)
           {
               printf("Summ Summ Summ\n");
               printi(MxRes, row, col);
               free_matrix(&MxRes, row);
           }
       }


       if (Dptr1)
       {
           int** tMx = NULL;
           tMx = matrix_transpositions(Dptr1, row, col);
           if (tMx)
           {
               printf("TMx TMx TMx TMx\n");
               printi(tMx, col, row);


               free_matrix(&tMx, col);
           }
       }


       if (Dptr1 && Dptr2)
       {

           /*Dptr1 =*/ free_matrix(&Dptr1, row);
           /*Dptr2 =*/ free_matrix(&Dptr2, row);
           //printf("%p\n", Dptr1);
           if (!(Dptr1) && !(Dptr2)) {
               printf("program is done\n");
           }
           else
           {
               printf("programm ERR2\n");
           }
       }
       else
       {
           printf("programm ERR1\n");
       }
   }
   else
   {
       printf("err0: incurrent values\n");
   }
   t = clock() - t;
   double time_taken = ((double)t) / CLOCKS_PER_SEC;//
   printf("%f\n", time_taken);//
   return 0;
}
//
////Индивидуальные задания.
////Реализовать следующие функции :
////
////a)Функция сложения двух разреженных  матриц;
////
////b)Функция транспонирования разреженной матрицы;
//
//
//////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
////printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
////printf("AAAAAAAAAAAAAAAA\n");
////printi(Dptr1, row, col);
////printf("BBBBBBBBBBBBBBBB\n");
////printi(Dptr2, row, col);
//////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
////
