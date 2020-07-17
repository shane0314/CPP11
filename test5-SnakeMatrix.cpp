#include "SnakeMatrix.h"

using namespace std;

void Solution(int m, int n, int** A)
{
 int num = 1;
 int i = 0, j = 0;
 int flag = 0; //0 leftdown; 1 rightup
 while (i < m && j < n)
 {
  A[i][j] = num++;
  if (0==flag)
  {
   if (0 ==j  && (m-1)==i)
   {
    j++;
    flag = 1;
   }
   else if (0 == j)
   {
    i++;
    flag = 1;
   }
   else if ((m - 1) == i)
   {
    j++;
    flag = 1;
   }
   else
   {
    i++;
    j--;
   }
  }
  else if (1==flag)
  {
   if (0==i && (n-1)==j)
   {
    i++;
    flag = 0;
   }
   else if (0==i)
   {
    j++;
    flag = 0;
   }
   else if ((n-1)==j)
   {
    i++;
    flag = 0;
   }
   else
   {
    i--;
    j++;
   }
  }
 }
}

