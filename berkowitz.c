#include<stdio.h>
#include<malloc.h>


int ** mat_mult(int m, int p,int q, int **a,int **b)
{
 int i,j,k,sum=0;
 int **multiply = (int **) malloc(m * sizeof(int*));
 for(i=0; i<m; i++)
    {
       multiply[i] = (int* ) malloc( sizeof(int)*q );
    }
 for (i=0 ; i<m ; i++)
    {
      for (j=0 ; j<q ; j++)
      {
        for (k = 0 ; k <p  ; k++)
        {
          sum = sum + a[i][k]*b[k][j];
        }
         multiply[i][j] = sum;
        sum = 0;
      }
    }
 return multiply;
}


int ** mat_power(int k,int n,int **a)
{
  int i;
  int **pow= (int **) malloc(n * sizeof(int*));
  for(i=0; i<n; i++)
    {
        pow[i] = (int* ) malloc( sizeof(int)*n );
    }
  pow=a;
 
  if(k==1)
    {
      return pow;
    }
  else
    {
      for(i=2;i<=k;i++)
      {
        pow=mat_mult(n,n,n,pow,a); 
      }
    }
return pow;
free(pow);
}


int** toep(int n,int t[n])
{
  int i,j; 
  int **toep = (int **) malloc((n+1) * sizeof(int*));
  for(i=0; i<(n+1); i++)
  {
    toep[i] = (int* ) malloc( sizeof(int)*n );
    for(j=0;j<n;j++)
      {
	toep[i][j]=0;
      }
  }
  
  for(i=0;i<n;i++)
  {
    toep[i][0]=t[i];
  }

  for(i=1;i<n;i++)
  {
    for(j=1;j<=i;j++)
    {
	toep[i][j]=toep[i-1][j-1];
    }
  }

  return toep;
}


void ber(int n ,int** m)
{
  int i,j;
  printf("\nThe matrix you entered is: \n");  
  for(i=0;i<n;i++)
  {
     for(j=0;j<n;j++)
     {
	printf("%d ",m[i][j]);
     }
     printf("\n");
  }

  int **vect = (int **) malloc((n+1) * sizeof(int*));
  for(i=0; i<=n; i++)
  {
     vect[i] = (int* ) malloc( sizeof(int)*1 );
  }

  vect[0][0]=1;
  vect[1][0]=-m[0][0];

  int r,k;
  for(r=1;r<n;r++)
  {
     int **R = (int **) malloc((1) * sizeof(int*));
     for(i=0; i<1; i++)
     {
        R[i] = (int* ) malloc( sizeof(int)*r );
     }

     int x; 
     for(x=0;x<r ;x++)
     {
	R[0][x]=m[r][x];  
     }

     int **S = (int **) malloc((r) * sizeof(int*));
     for(i=0; i<r; i++)
     {
        S[i] = (int* ) malloc( sizeof(int)*1 );
     }

     for(i=0;i<r ;i++)
     {
	S[i][0]=m[i][r];  
     }

     int **A = (int **) malloc(r * sizeof(int*));
     for(i=0; i<r; i++)
     {
        A[i] = (int* ) malloc( sizeof(int)*r );
        for(j=0; j<r; j++)
        {
           A[i][j]=m[i][j];
        }
     }

     int t[r+2];
     t[0]=1;
     t[1]=-m[r][r];

     int ** temp=mat_mult(1,r,1,R,S);
     t[2]=-temp[0][0];

     for(k=1;k<=r;k++)
     {
	int ** temp_pow=mat_power(k,r,A);
	int ** temp_mult=mat_mult(1,r,r,R,temp_pow);
	int ** p=mat_mult(1,r,1,temp_mult,S);

	t[k+2]=-(p[0][0]);
     }

     free(R);
     free(S);

     int ** temp_toep=toep((r+2),t);
     vect= mat_mult((r+2),(r+1),1,temp_toep,vect);
     free(temp_toep);
  }
  printf("\nThe characteristic vector is: \n");  
  for(i=0;i<=n;i++)
    {
      for(j=0;j<1;j++)
      {
	printf("%d",vect[i][j]);
      }
      printf("\n");
    }

}

void main()
{
  int n,i,j;
  
  printf("\nEnter the size of matrix: ");
  scanf("%d",&n); 
  
  int **mat1 = (int **) malloc(n * sizeof(int*));
  for(i=0; i<n; i++)
  {
     mat1[i] = (int* ) malloc( sizeof(int)*n );
     for(j=0; j<n; j++)
     {
        printf("\nEnter value for mat[%d][%d]: ",i,j);
        scanf(" %d", &mat1[i][j]);
     }
   }

  printf("\nApplying Berkowitz algorithm to compute characteristic polynomial vector:\n ");
  ber(n,mat1);

}

