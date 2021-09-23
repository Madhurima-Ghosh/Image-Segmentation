#include<stdio.h>
#include<math.h>
#include<stdlib.h>

struct pixel 
{
	int val;
	int cluster;
};

struct pixel x[300][300];
int out[300][300];
int e=10;
int v[4]={50,100,150,200};

void main()
{
	int i,j,k, d,t=0, n=0;
	int v1[4];
	float diff=0, sum=0;
	FILE *fp, *fp1;
	fp=fopen("original_lena.txt","r");
	fp1=fopen("kmeans_lena.pgm","w");
	
	//read file
	for (i=1; i<=256;i++)
	{
		for(j=1;j<=256;j++)
		{
			fscanf(fp,"%d ",&d);
			x[i][j].val=d;
		}
	}
	
	for(t=0; t<50; t++)
	{
		printf("Iteration %d", t);
		for(i=0;i<4;i++)
		{
			v1[i]=v[i];
		}
		
		//cluster selection
		for(i=1; i<=256; i++)
		{
			for(j=1; j<=256; j++)
			{
				diff=abs(x[i][j].val - v[0]);
				d=0;
				for(k=1;k<4;k++)
				{
					if (abs(x[i][j].val - v[k])< diff)
					{
						diff = abs(x[i][j].val - v[k]);
						d=k;
					}
				}
				x[i][j].cluster = d;
			}
		}
		
		//mean of values
		for(k=0;k<4;k++)
		{
			sum=0;
			n=0;
			for(i=1; i<=256; i++)
			{
				for(j=1; j<=256; j++)
				{
					if(x[i][j].cluster==k)
					{
						sum=sum+x[i][j].val;
						n++;
					}
				}
			}
			v[k]=sum/n;
		}
		
		e=abs(v[0]-v1[0]);
		for(k=1;k<4;k++)
		{
			if(abs(v[k] - v1[k]) > e)
				e = abs(v[k] - v1[k]);
		}
		if(e==0)
			break;
	}
	
	printf("%d %d %d %d", v[0], v[1], v[2], v[3]);
	for(i=1; i<=256; i++)
		{
			for(j=1; j<=256; j++)
			{
				out[i][j] = v[x[i][j].cluster];
			}
		}
	
	//write file
	fprintf(fp1,"P2\n256 256\n255\n");
	for (i=1; i<=256;i++)
	{
		for(j=1;j<=256;j++)
		{
			fprintf(fp1,"%d ",out[i][j]);
		}
	}
}
