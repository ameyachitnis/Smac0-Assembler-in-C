#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char mnem[][6]={"STOP","ADD","SUB","MUL","MOVER","MOVEM","COMP","DIV","BC","READ","PRINT"};
char reg[][6]={"AREG","BREG","CREG","DREG"};
char asmdr[][10]={"STOP","START","END","EQU","ORIGN","LTORG"};
char cond[][5]={"LT","LE","EQ","GT","GE","ANY"};


int isMnem(char *t)
{
	int i;
	for(i=0;i<11;i++)
	{
		if(strcmp(mnem[i],t)==0)
		return 1;
	}
	return 0;
}

int isAsm(char *t)
{
	int i;
	for(i=0;i<7;i++)
	{
		if(strcmp(asmdr[i],t)==0)
		return 1;
	}
	return 0;
}

int isReg(char *t)
{
	int i;
	for(i=0;i<4;i++)
	{
		if(strcmp(reg[i],t)==0)
		return 1;
	}
	return 0;
}

int isCond(char *t)
{
	int i;
	for(i=0;i<6;i++)
	{
		if(strcmp(cond[i],t)==0)
		return 1;
	}
	return 0;
}
 
int i=0;

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("\n Invalid arguments:");
		exit(0);
	}
	
	FILE *fp;
	
	char t1[10]={},t2[10]={},t3[10]={},t4[10]={},tmp[20];
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("\n Cannot open the file!!");
		exit(0);
	}
	else
	{
		char line[50];
		int c,i,f=0,k=0,lno=0,l=0,num;
	while(fgets(line,50,fp)!=NULL)
	{
		strcpy(t1," ");
		strcpy(t2," ");
		strcpy(t3," ");
		strcpy(t4," ");
		lno++;
		c=sscanf(line,"%s %s %s %s",t1,t2,t3,t4);
		switch(c)
		{
			case 1: printf("\n\nLine:%d\t%s",lno,t1);
				if(strcasecmp(t1,"STOP")==0 ||strcasecmp(t1,"LTORG")==0 || strcasecmp(t1,"END")==0)
					f=1;
				if(f==0)
				{
					printf("\n Invalid mnemomic instruction.......\n");
				}
			break;

			case 4: printf("\n\nLine:%d\t %s\t%s\t%s\t%s",lno,t1,t2,t3,t4);	
				if(isMnem(t1)==1||isReg(t1)==1||isCond(t1)==1||isAsm(t1)==1)
					printf("\n Invalid Symbolic name.....");
				if(isMnem(t2)==0)
					printf("\n Invalid menmoic name.....");
				if(strcmp(t2,"BC")==0)
				{
					if(isCond(t3)==1)
						printf("\n Invalid condition code .....");
				}
				k=strlen(t3)-1;
				if(t3[k]!=',')
					printf("\n Invalid Register operand.....");
				else
				{
					for(i=0;i<k;i++)
						tmp[i]=t3[i];
						tmp[i]='\0';
					if(isReg(tmp)==0)
						printf("\n Invalid Register operand.....");
				}
				if(isMnem(t4)==1||isReg(t4)==1||isCond(t4)==1||isAsm(t4)==1)
					printf("\n Invalid Memory operand.....");
			break;

			case 3:	printf("\n\nLine:%d\t %s\t%s\t%s",lno,t1,t2,t3);
				if(isMnem(t1)==1)
				{
					if(strcmp(t1,"BC")==0)
					{
						if(isCond(t2)==0)
							printf("\n Invalid condition code .....");
						if(isMnem(t3)==1||isReg(t3)==1||isCond(t3)==1||isAsm(t3)==1)
							printf("\n Invalid label name.....");
					}
			
					else if(strcmp(t1,"ADD") || strcmp(t1,"SUB") || strcmp(t1,"DIV") || strcmp(t1,"MULT") )
					{
						k=strlen(t2)-1;
						if(t2[k]!=',')
							printf("\n Invalid Register operand.....");
						else
						{
							for(i=0;i<k;i++)
								tmp[i]=t2[i];
							tmp[i]='\0';
						if(isReg(tmp)==0)
							printf("\n Invalid Register operand.....");
						}
						if(isMnem(t3)==1||isReg(t3)==1||isCond(t3)==1||isAsm(t3)==1)
							printf("\n Invalid Memory operand.....");
			
					}
					else
					{
						k=strlen(t2)-1;
						if(t2[k]!=',')
							printf("\n Invalid Register operand.....");
						else
						{
							for(i=0;i<k;i++)
								tmp[i]=t2[i];
							tmp[i]='\0';
						if(isReg(tmp)==0)
							printf("\n Invalid Register operand.....");
						}
						if(isMnem(t3)==1||isReg(t3)==1||isCond(t3)==1||isAsm(t3)==1)
							printf("\n Invalid Memory operand.....");
			
					}
				}	
				else
				{
					if(isMnem(t1)==1||isReg(t1)==1||isCond(t1)==1||isAsm(t1)==1)
					printf("\n Invalid label name.....");
					
					if(strcmp(t2,"DC")==0 || strcmp(t2,"DS")==0)
					{
						if(isMnem(t3)==1||isReg(t3)==1||isCond(t3)==1||isAsm(t3)==1)
							printf("\n Invalid Symbolic name.....");
					}
					else if(strcmp(t2,"EQU")==0)
					{
						if(isMnem(t3)==1||isReg(t3)==1||isCond(t3)==1||isAsm(t3)==1)
							printf("\n Invalid Address specifier.....");
					}
					else
					{
						if(isMnem(t2)==0)
							printf("\n Invalid menmoic name.....");
						else
						{
							if(isMnem(t3)==1||isReg(t3)==1||isCond(t3)==1||isAsm(t3)==1)
							printf("\n Invalid Memory operand.....");
						}
					}
				}
			break;

			case 2: printf("\n\nLine:%d\t %s\t%s",lno,t1,t2);

					if(strcmp(t1,"ORIGIN")==0)
					{
						if(isMnem(t2)==1||isReg(t2)==1||isCond(t2)==1||isAsm(t2)==1)
							printf("\n Invalid label name.....");
					} 
					else
					{
						if(strcasecmp(t1,"READ")==0|| strcasecmp(t1,"PRINT")==0)
						{
							if(isMnem(t2)==1||isReg(t2)==1||isCond(t2)==1||isAsm(t2)==1)
								printf("\n Invalid Memory operand.....");
						}
						else if(strcasecmp(t1,"START")==0)
						{
							num=atoi(t2);
							if(num<0 || num >999)
								printf("\nInvalid location operand.....\n");
						}
						else
						{
						if(isMnem(t1)==0||isReg(t1)==0||isCond(t1)==0||isAsm(t1)==0)
								printf("\n Invalid label name.....");
							
								if(isMnem(t2)==1||isReg(t2)==1||isCond(t2)==1||isAsm(t2)==1)
								printf("\n Invalid Menmonic operand.....");
						}
		
					}
			break;
			}
	}
	fclose(fp);
}
}				

		
