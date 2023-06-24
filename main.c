#include <stdio.h>
#include <stdlib.h>

void Output(int Ans[][105], int PageFault[], int n, int pFrame)
{
	int i, j;
	printf("--- Page Replacement algorithm ---\n");
	for ( i = 0; i <= pFrame ; i++)
	{
		for (j = 0; j < n ; ++j)
		{
			if (Ans[i][j] == -1)
				printf("  ");
			else
				printf("%d ", Ans[i][j]);
		}
		printf("\n");
	}	
	for (i = 0; i < n ; ++i)
	{
		if (PageFault[i] == 1)
			printf("  ");
		else
			printf("* ");
	}
	printf("\n");
}

void FIFO(int a[], int PageFault[], int Ans[][105], int n, int pFrame)
{
	int i, tmp = 1, c = 0, k = 1;
	Ans[1][0] = Ans[0][0];
	for ( i = 1; i < n ; i++)
	{
		int j;
		c = 0;
		for (j = 1; j <= tmp ; ++j)
		{
			Ans[j][i] = Ans[j][i-1];
			if (a[i] == Ans[j][i])
			{
				PageFault[i] = 1;
				c = 1;
			}
			//printf("%d", tmp);
		}
		if (c == 0)
		{
			//printf("%d %d\n", tmp, a[i]);
			PageFault[i] = 0;
			if (tmp < pFrame)
			{
				tmp++;
				Ans[tmp][i] = a[i];		
			}
			else
			{	//printf("--%d ", k);
				Ans[k][i] = a[i];
				if (k == pFrame)
					k = 1;
                else
				    k++;
			}
		}
	}
}
void OPT(int a[], int PageFault[], int Ans[][105], int n, int pFrame)
{
	int i, tmp = 1, c = 0, k = 1;
    int check[105];
	Ans[1][0] = Ans[0][0];
	for ( i = 1; i < n ; i++)
	{
		int j;
		c = 0;
        int t; 
        for (j = 1; j <= tmp ; j++)
        {                        
            Ans[j][i] = Ans[j][i-1];
			if (a[i] == Ans[j][i])
			{
				PageFault[i] = 1;
				c = 1;
			}
        }
            //printf("%d\t",c);
            if (c == 0)
            {
                //printf("%d %d\n", tmp, a[i]);
                PageFault[i] = 0;
                if (tmp < pFrame)
                {
                    tmp++;
                    Ans[tmp][i] = a[i];	
                    //printf("%d  %d  %d\n", tmp, i, a[i]);	
                }
                else
                {	
                    int p, q, r = 0;
                    k = 1;
                    for (p = 0 ; p <= pFrame; p++)
                        check[p] = 0;
                    for (p = i + 1; p < n ; p++ )
                    {
                        for (q = 1; q <= pFrame ; q++)
                        {                        
                            if (a[p] == Ans[q][i] && check[q] == 0)
                            {
                                check[q] = 1;
                                if (r < p)
                                {
                                    r = p;
                                    k = q;
                                }
                                //break;
                            }
                        }
                    }
                    for (q = 1; q <= pFrame ; ++q)
                        if (check[q] == 0)
                        {
                            k = q;
                            break;
                        }
                    //printf("%d--%d\n", i, k);
                    Ans[k][i] = a[i];
                }
            
            }
        
	}
}

void LRU(int a[], int PageFault[], int Ans[][105], int n, int pFrame)
{
	int i, tmp = 1, c = 0, k = 1;
    int check[105];
	Ans[1][0] = Ans[0][0];
	for ( i = 1; i < n ; i++)
	{
		int j;
		c = 0;
        int t; 
        for (j = 1; j <= tmp ; j++)
        {                        
            Ans[j][i] = Ans[j][i-1];
			if (a[i] == Ans[j][i])
			{
				PageFault[i] = 1;
				c = 1;
			}
        }
            //printf("%d\t",c);
            if (c == 0)
            {
                //printf("%d %d\n", tmp, a[i]);
                PageFault[i] = 0;
                if (tmp < pFrame)
                {
                    tmp++;
                    Ans[tmp][i] = a[i];	
                    //printf("%d  %d  %d\n", tmp, i, a[i]);	
                }
                else
                {	
                    int p, q, r = n;
                    k = 1;
                    for (p = 0 ; p <= pFrame; p++)
                        check[p] = 0;
                    for (p = i - 1; p >= 0 ; p-- )
                    {
                        for (q = 1; q <= pFrame ; q++)
                        {                        
                            if (a[p] == Ans[q][i] && check[q] == 0)
                            {
                                check[q] = 1;
                                if (r > p)
                                {
                                    r = p;
                                    k = q;
                                }
                                //printf("%d  %d  %d  %d\n", p, a[p], k, r);
                                //break;
                            }
                        }
                    }
                    for (q = 1; q <= pFrame ; ++q)
                        if (check[q] == 0)
                        {
                            k = q;
                            break;
                        }
                    //printf("%d--%d\n", i, k);
                    Ans[k][i] = a[i];
                }
            
            }
	}
}

int main()
{
	int x, n = 0, PageFault[105], Ans[105][105];
    int a[105] = {2,1,5,2,2,1,4,5,0,0,7};
	int y;
	printf("--- Page Replacement algorithm ---\n");
	printf("1. Default referenced sequence\n");
	printf("2. Manual input sequence\n");
	scanf("%d", &x);
	if (x == 1)
	{
		n = 11;
		//break;
	}
	else if (x == 2)
	{
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        int i, y;
        printf("Enter the array: ");
		for (i = 0 ; i < n; i++)
		{
            scanf("%d", &y);
			a[i] = y;
		}
		//break;	
	}
	int i;
	for (i = 0 ; i < n ; i++)
	{
		Ans[0][i] = a[i];
	}

	int PageFrame;
	printf("--- Page Replacement algorithm ---\n");
	printf("Input page frames: ");
	scanf("%d", &PageFrame);
	for ( i = 1; i <= PageFrame ; i++)
	{
		int j;
		for (j = 0; j < n ; ++j)
			Ans[i][j] = -1;
	}

	int Algorithm; 
	printf("--- Page Replacement algorithm ---\n");
	printf("1. FIFO algorithm\n");
	printf("2. OPT algorithm\n");
	printf("3. LRU algorithm\n");
	scanf("%d", &Algorithm);
	if (Algorithm == 1)
		FIFO(a, PageFault, Ans, n, PageFrame);
		//break;
	else if (Algorithm == 2)
		OPT(a, PageFault, Ans, n, PageFrame);
		//break;	
	else if (Algorithm == 3)
		LRU(a, PageFault, Ans, n, PageFrame);
		//break;
	Output(Ans, PageFault, n, PageFrame);
	return 0;
}
