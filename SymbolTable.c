#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct symbol
{
	char name[20];
	int addr,value,length;
	int def,used;
	struct symbol *next;
}*newnode;

struct symbol *head=NULL;
char mnemonic[11][20]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ ","PRINT"};

int ismnemonic(char abc[10])
{
	int i,flag=1;
	for(i=0;i<11;i++)
	{
		if(strcmp(abc,mnemonic[i])==0)
		{
			flag=0;
			break;
		}
	}
	if(flag==0)
		return 0;
	else
		return 1;
}
void addsym(char nam[20],int j,char len[10],char val[10])
{
	struct symbol *temp;
	int l,valu,flag=0;
	for(temp=head;temp!=NULL;temp=temp->next)
	{
		if(strcmp(temp->name,nam)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{	
		if(j!=0)
		{
			if(temp->addr!=0)
				printf("Error:%S is being re-declared\n",temp->name);
			else
			{
				temp->addr=j;
				temp->def=1;
			}
		}
		else
			temp->used=1;
			if(strcmp(len,"")!=0)
			{
				l=atoi(len);
				temp->length=1;
			}
			if(strcmp(val,"")!=0)
			{
				valu=atoi(val);
				temp->value=valu;
			}
		}
		if(flag==0)
		{
			newnode=(struct symbol *)malloc(sizeof(struct symbol));
			newnode->next=NULL;
			strcpy(newnode->name,nam);
			if(j!=0)
			{
				newnode->addr=j;
				newnode->def=1;
			}
			else
				newnode->used=1;
				if(strcmp(len,"")!=0)
				{
					l=atoi(len);
					newnode->length=1;
				}
				if(strcmp(val,"")!=0)
				{
					valu=atoi(val);
					temp->value=valu;
				}
			
			if(head==NULL)
				head=newnode;
			else
			{
				temp=head;
				while(temp->next!=NULL)
				{
					temp=temp->next;
				}
				temp->next=newnode;
			}
		}
	}

	void disp()
	{
		struct symbol *temp;
		printf("\nSymbol\tAddress\tUsed\tDefined\n");
		for(temp=head;temp!=NULL;temp=temp->next)
		{
			printf("\n%s\t%d\t%d\t%d\n",temp->name,temp->addr,temp->used,temp->def);
		}
		printf("\n");
		for(temp=head;temp!=NULL;temp=temp->next)
		{	
			if(temp->used==1 && temp->def==0)
			{
				printf("\nError:%s is used but not defined\n",temp->name);
			}
			if(temp->def==1&& temp->used==0)
			{
				printf("\nwarning:%s is defined but not used\n",temp->name);
			}
		}
	}

void main(int argc,char *argv[])
{
	FILE *fp=NULL;
	if(argc!=2)
	{
		printf("Invalid no. of arguments\n");
		exit(0);
	}
	char statement[100],opcode[10],reg[10],label[10],mem[10];
	int n,x,lc=0,a;
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("\n Error in opening File\n");
		exit(0);
	}
	while(fgets(statement,1000,fp)!=NULL)
	{
			strcpy(label,"");
			strcpy(opcode,"");
			strcpy(reg,"");
			strcpy(mem,"");
			n=sscanf(statement,"%s%s%s%s",label,opcode,reg,mem);
			switch(n)
			{
				case 1: if(strcmp(label,"STOP")==0 || strcmp(label,"END")==0)
					{
						lc++;
					}
					if(strcmp(label,"START")==0)
					{
						lc=0;
					}
					break;

				case 2:if(strcmp(label,"START")==0)
					{
						lc=atoi(opcode);
					}
					if(strcmp(label,"READ")==0 || strcmp(label,"PRINT")==0)
					{
						lc++;
						addsym(opcode,0,"","");
					}
					if(strcmp(opcode,"STOP")==0)
					{
						addsym(label,lc,"","");
						lc++;
					}
					if(strcmp(label,"END")==0)
					{
						addsym(opcode,lc,"","");
						lc++;
					}
					break;

				case 3: if(strcmp(opcode,"DS")==0)
					{
						addsym(label,lc,reg,"");
						x=atoi(reg);
						lc=lc+x;
					}
					if(strcmp(opcode,"DC")==0)
					{
						addsym(label,lc,"",reg);
						lc++;
					}
					a=ismnemonic(label);
					if(a==0)
					{
						addsym(reg,0,"","");
						lc++;
					}
					if(strcmp(opcode,"READ")==0 || strcmp(opcode,"PRINT")==0)
					{
						addsym(label,lc,"","");
						lc++;
					}

					break;
					
					
				case 4:addsym(label,lc,"","");
					addsym(mem,0,"","");
					lc++;

				break;
		}
	}
	disp();
}



	
		
