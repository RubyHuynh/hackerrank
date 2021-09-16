/******************************************************************************

16/09/2021 https://www.ics.uci.edu/~eppstein/161/960229.html

*******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool
max (int a, int b)
{
  return a > b ? true : false;
}


/*dp*/

int **L;
int lcs_length2 (char *A, char *B)
{

  int i = 0, j;
  int m = strlen (A);
  int n = strlen (B);
  L = (int **) malloc (m * sizeof (int *));
  for (i = m; i >= 0; i--)
    {
      L[i] = (int *) malloc (n * sizeof (int));

      for (j = n; j >= 0; j--)
	{
	  if (A[i] == '\0' || B[j] == '\0')
	    L[i][j] = 0;
	  else if (A[i] == B[j])
	    L[i][j] = 1 + L[i + 1][j + 1];
	  else
	    L[i][j] = max (L[i + 1][j], L[i][j + 1]);
	}
    }
  return L[0][0];
}

/*memoizing, time O(mn), space O(mn) */
char *A;
char *B;

int
subproblem (int i, int j)
{
  if (L[i][j] < 0)
    {
      if (A[i] == '\0' || B[j] == '\0')
	L[i][j] = 0;
      else if (A[i] == B[j])
	L[i][j] = 1 + subproblem (i + 1, j + 1);
      else
	L[i][j] = max (subproblem (i + 1, j), subproblem (i, j + 1));
    }
  return L[i][j];
}

int
lcs_length1 (char *AA, char *BB)
{

  int i = 0, j;
  int m = strlen (AA);
  int n = strlen (BB);
  A = AA;
  B = BB;
  L = (int **) malloc (m * sizeof (int *));

  /*allocate storage for L; */
  for (i = 0; i <= m; i++)
    {
      L[i] = (int *) malloc (n * sizeof (int));

      for (j = 0; j <= m; j++)
	{

	  L[i][j] = -1;
	}
    }
  return subproblem (0, 0);
}


/*typical 2^n*/
int
lcs_length (char *A, char *B)
{
  if (*A == '\0' || *B == '\0')
    return 0;
  else if (*A == *B)
    return 1 + lcs_length (A + 1, B + 1);
  else
    return max (lcs_length (A + 1, B), lcs_length (A, B + 1));
}

int
main ()
{
  printf ("Longest Common Subsequence\n");
  char *a = "ematode knowledge";
  char *b = "empty bottle";
  printf ("rs = %d\n", lcs_length (a, b));
  printf ("rs1 = %d\n", lcs_length1 (a, b));
  printf ("rs2 = %d\n", lcs_length2 (a, b));
  return 0;
}
