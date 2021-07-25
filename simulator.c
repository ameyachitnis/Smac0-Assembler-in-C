#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int symbolc=0;
FILE *fp;
char fil[100];
int flag=0;
int mem[1000],reg1[4];
int t1,t2,lc=0,pc=0;
char s[1000];
void load(),print(),exe();
int main()
{
	int c;
	
	do
	{
		printf("\nMENU:\n1-Load\n2-Print\n3-Execute\n4-Exit\nEnter your choice: ");
		scanf("%d",&c);
		switch(c)
		{
			case 1:load();
				flag=1;
				break;
				
			case 2:if(flag==0)
					printf("\nload first");	
				else
					print();
				break;
			case 3:if(flag==0)
					printf("\nload first");
				else
					exe();
				break;
			case 4:exit(0);
		}
	}while(c<=4 && c>0);
}

void load()
{
	int n;
	printf("\n Enter File to be loaded:");
	scanf("%s",fil);
	fp=fopen(fil,"r");
	if(fp==NULL)
	{
		printf("\n File Does Not Exist!");
		exit(1);
	}
	while(fgets(s,1000,fp)!=NULL)
	{
		n=sscanf(s,"%d %d",&t1,&t2);
		if(t1==-1)
			break;
		else
		{
			mem[t1]=t2;
			pc=t1;
			if(lc==0)
				lc=t1;
		}
	}
	printf("\nLoaded into memory!!!");
}

void print()
{
	int i,n;
	for(i=lc;i<=pc;i++)
		printf("\n%d\t%d",i,mem[i]);
	printf("\n-1\t%d",lc);
}

void exe()
{
	int a,i,add=0,op=0,opcode=0,reg=0,sym=0,flag=0;
	for(i=lc;i<=pc;i++)
	{
		a=mem[i];
		add=a%1000;
		op=a/1000;
		opcode=op/10;
		reg=op%10;
		switch(opcode)
		{
			case 1:reg1[reg]=reg1[reg]+mem[add];
				break;
			case 2:reg1[reg]=reg1[reg]-mem[add];
				break;
			case 3:reg1[reg]=reg1[reg]*mem[add];
				break;
			case 4:reg1[reg]=mem[add];
				break;
			case 5:mem[add]=reg1[reg];
				break;
			case 6:flag=reg1[reg]-mem[add];
				break;
			case 7:if(reg==1)
				{
					if(flag<0)
					{
						i=add-1;
						flag=0;
					}
				}
				if(reg==2)
				{
					if(flag<=0)
					{
						i=add-1;
						flag=0;
					}
				}
				if(reg==3)
				{
					if(flag==0)
					{
						i=add-1;
						flag=0;
					}
				}
				if(reg==4)
				{
					if(flag>0)
					{
						i=add-1;
						flag=0;
					}
				}
				if(reg==5)
				{
					if(flag>=0)
					{
						i=add-1;
						flag=0;
					}
				}
				if(reg==6)
				{
						i=add-1;
						flag=0;	
				}
				break;		
			case 8:reg1[reg]=reg1[reg]/mem[add];
				break;
			case 9:printf("\nEnter Value of Symbol: ");
				scanf("%d",&sym);
				mem[add]=sym;
				break;
			case 10:printf("\nAnswer is:%d ",mem[add]);
				break;
		}
	}
}
