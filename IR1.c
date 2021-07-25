#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

const char regs[4][8]={"AREG","BREG","CREG","DREG"};
const char impers[11][8]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
const char assd[5][8]={"START","END","EQU","LTORG","ORIGIN"};
const char cond[6][8]={"LT","LE","EQ","GE","GT","ANY"};
const char dec[2][8]={"DC","DS"};

struct node
{
	char symbol[10];
	int df,uf,address,ef;
	struct node *next;
};

struct node *root=NULL;

int imparative(char s[])
{
	int i;
	for(i=0;i<11;i++)
	{
		if(strcmp(s,impers[i])==0)
			return i;
	}
	return -1;
}

int declarative(char s[])
{
	int i;
	for(i=0;i<2;i++)
	{
		if(strcmp(s,dec[i])==0)
			return i+1;
	}
	return 0;
}

int ass_dir(char s[])
{
	int i;
	for(i=0;i<5;i++)
	{
		if(strcmp(s,assd[i])==0)
			return i+1;
	}
	return 0;
}

int cond_code(char s[])
{
	int i;
	for(i=0;i<6;i++)
	{
		if(strcmp(s,cond[i])==0)
			return i+1;
	}
	return 0;
}

int reg_code(char s[])
{
	int i;
	for(i=0;i<4;i++)
	{
		if(strcmp(s,regs[i])==0)
			return i+1;
	}
	return 0;
}

int isnum(char s[])
{
	int i;
	for(i=0;s[i]!='\0';i++)
		if(!isdigit(s[i]))
			return 0;
	return 1;
}

void insert(char t[],int LC,int f)
{
	struct node *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	strcpy(temp->symbol,t);
	if(f==1)
	{temp->df=1;temp->uf=0;temp->address=LC;temp->ef=0;}
	else if(f==-1)
	{temp->df=0;temp->uf=1;temp->address=0;temp->ef=0;}
	temp->next=NULL;

	if(root==NULL)
		root=temp;
	else
	{
		struct node *p;
		p=root;
		while(p->next!=NULL)
		{	p=p->next;	}
		p->next=temp;
	}
}

void display()
{
	struct node *t;
	printf("\nSymbol Table\n");
	printf("\nSymbol\tAddress\tUsed\tDefined");
	for(t=root;t!=NULL;t=t->next)
	{
		printf("\n%s\t%d\t%d\t%d",t->symbol,t->address,t->uf,t->df);
	}
}

int search(char s[])
{
	struct node *temp;
	int pos;
	for(temp=root,pos=1 ; temp!=NULL; temp=temp->next,pos++)
	{
		if(strcmp(temp->symbol,s)==0)
		{
			return pos;
		}
	}
	return -1;
}

void errors()
{
	int n=1;
	struct node *t;
		for(t=root;t!=NULL;t=t->next)
	{
		if(t->uf==1 && t->df==0)
		{
			printf("\n%d. Symbol %s is used but not defined",n++,t->symbol);
		}
		if(t->df==1 && t->ef==1)
		{
			printf("\n%d. Re-declaration of the Symbol %s",n++,t->symbol);
		}
	}
        for(t=root;t!=NULL;t=t->next)
        {
                if(t->df==1 && t->uf==0)
                {
                        printf("\n%d. Symbol %s is defined but not used",n++,t->symbol);
                }
	}
}
struct IC
{
	int address;
	char sclass[3];
	int code;
	char reg;
	char op;
	int cons;
	struct IC *next;
};
struct IC *head = NULL;

void insert_IC(int address, char sc[], int code, char reg, char op, int cons)
{
	struct IC *temp;
	temp = (struct IC*)malloc(sizeof(struct IC));
	temp->address=address;
	strcpy(temp->sclass,sc);	temp->code=code;
	temp->reg=reg;
	temp->op=op;	temp->cons=cons;
	temp->next=NULL;

	if(head==NULL)
		head=temp;
	else
	{
		struct IC *p;
		p=head;
		while(p->next!=NULL)
		{	p=p->next;	}
		p->next=temp;
	}
}
char* check_class(char[]);
int check_reg(char[]);
void display_IC();

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("\nPlease enter the valid arguments!\n");
		exit(0);
	}
	FILE *fp;
	int n,LC=0,f,i;
	char instr[50],str[50];
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("\nFile could not open!\n");
		exit(0);
	}
	struct node* temp;

	while(fgets(instr,50,fp)!=NULL)
	{
		n=0;
		char *s=instr;
		char *str1;
		char t1[10]={ },t2[10]={ },t3[10]={ },t4[10]={ };

		while((str1=strtok_r(s,"\n ,\t",&s)))
		{	
			n++;
			switch(n)
			{
				case 1: strcpy(t1,str1);
					break;
				case 2: strcpy(t2,str1);
					break;
				case 3: strcpy(t3,str1);
					break;
				case 4: strcpy(t4,str1);
					break;
				default:printf("\nInvalid Statement!\n");
					break;
			}
		}
		if(LC==0)
		{
			LC=atoi(t2);
			f=0;
		}
		else if(f==0)
			f=1;
		else if(f!=2)
			LC++;
		else
			f=1;


		if(f==0)
			printf("\t %s \t %s \t %s \t %s\n",t1,t2,t3,t4);
		else
			printf("%d\t %s \t %s \t %s \t %s\n",LC,t1,t2,t3,t4);

	if(imparative(t1)==-1 && declarative(t1)==0 && ass_dir(t1)==0 && cond_code(t1)==0 && reg_code(t1)==0 && isnum(t1)==0)
		{
			if(search(t1)==-1 && strcmp(t1,"")!=0)
				insert(t1,LC,1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcmp(temp->symbol,t1)==0)
					{
						if(temp->address==0)
						{
							temp->address=LC;
							temp->df=1;
						}
						else
							temp->ef=1;
						break;
					}
				}
			}
		}

	if(imparative(t2)==-1 && declarative(t2)==0 && ass_dir(t2)==0 && cond_code(t2)==0 && reg_code(t2)==0 && isnum(t2)==0)
		{
			if(search(t2)==-1 && strcmp(t2,"")!=0)
				insert(t2,0,-1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcmp(temp->symbol,t2)==0)
					{
						temp->uf=1;
						break;
					}
				}
			}
		}

		if(declarative(t2))
		{
			if(search(t1)==-1)
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcmp(temp->symbol,t1)==0 && temp->address==0)
					{
						temp->address=LC;
						temp->df=1;
						break;
					}
					
				}
			}
			if(strcmp(t2,"DS")==0)
			{
				LC+=atoi(t3);
			}
			else
			{
				char *con = strtok(t3,"'");
				LC++;
			}				
			f=2;
		}
	if(declarative(t2)==0)
	{
	if(imparative(t3)==-1 && declarative(t3)==0 && ass_dir(t3)==0 && cond_code(t3)==0 && reg_code(t3)==0 && isnum(t3)==0)
		{
			if(search(t3)==-1 && strcmp(t3,"")!=0)
				insert(t3,0,-1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcmp(temp->symbol,t3)==0)
					{
						temp->uf=1;
						break;
					}
				}
			}
		}
	}
	
if(imparative(t4)==-1 && declarative(t4)==0 && ass_dir(t4)==0 && cond_code(t4)==0 && reg_code(t4)==0 && isnum(t4)==0)
		{
			if(search(t4)==-1 && strcmp(t4,"")!=0)
				insert(t4,0,-1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcmp(temp->symbol,t4)==0)
					{
						temp->uf=1;
						break;
					}
				}
			}
		}	
	}
	display();
	errors();
	printf("\n");

	rewind(fp);
	LC=0;	
	while(fgets(instr,50,fp)!=NULL)
	{
		n=0;
		char *s=instr;
		char *str1;
		char t[4][10]={"\0"};

		while((str1=strtok_r(s,"\n ,\t\0",&s)))
		{	
			switch(n)
			{
				case 0: strcpy(t[n++],str1);
					break;
				case 1: strcpy(t[n++],str1);
					break;
				case 2: strcpy(t[n++],str1);
					break;
				case 3: strcpy(t[n++],str1);
					break;
				default:printf("\nInvalid Statement!\n");
					break;
			}
		}
		if(LC==0)
		{
			LC=atoi(t[1]);
			f=0;
		}
		else if(f==0)
			f=1;
		else if(f!=2)
			LC++;
		else
			f=1;
	
		char sclass[3]={ };
		int code=0;
		char reg=0;
		char op=' ';
		int no=0;
		int f1=0;
		for(i=0;i<n;i++)
		{
			if(imparative(t[i])!=-1 || declarative(t[i])!=0 || ass_dir(t[i])!=0)
			{
				strcpy(sclass,check_class(t[i]));
				if(strcmp(sclass,"IS")==0)
				{
					code=imparative(t[i]);
				}
				else if(strcmp(sclass,"DL")==0)
				{
					code=declarative(t[i]);
				}
				else if(strcmp(sclass,"AD")==0)
				{
					code=ass_dir(t[i]);
				}
			}
			else if(cond_code(t[i])!=0 || reg_code(t[i])!=0)
				reg = check_reg(t[i]);
			else if(search(t[i])!=-1 && f1==0)
			{
				op='S';
				no=search(t[i]);
				f1=1;
			}
			else if(isnum(t[i]) && f1==0 && strcmp(t[i],"")!=0)
			{
				op='C';
				no = atoi(t[i]);
				f1=1;
			}
		}
		if(declarative(t[1]))
		{
			op='C';
			if(strcmp(t[1],"DC")==0)
			{
				char *z = strtok(t[2],"\'");
				no = atoi(z);
			}
			else
				no = atoi(t[2]);
		}
		insert_IC(LC,sclass,code,reg,op,no);

		if(declarative(t[1]))
		{
			if(strcmp(t[1],"DC")==0)
				LC++;
			else
				LC+=atoi(t[2]);
			f=2;	
		}
	}
	display_IC();
}

char *check_class(char s[])
{
	if(imparative(s)!=-1)
		return"IS";
	else if(declarative(s)!=0)
		return "DL";
	else if(ass_dir(s)!=0)
		return "AD";
	else
		return"";
}

int check_reg(char s[])
{
	int n=cond_code(s);
	if(n!=0)
		return n;
	n = reg_code(s);
		return n;
}

void display_IC()
{
	struct IC *t;
	printf("\nIntermediate Code\n\n");
	for(t=head;t!=NULL;t=t->next)
	{
		if(t->reg!=0 && t->op!=' ')
		{
			printf("%d \t <%s,%d> %d <%c,%d>\n",t->address,t->sclass,t->code,t->reg,t->op,t->cons);
		}
		
		else if(t->code==0)
		{
			
			printf("%d \t <%s,%d> \n",t->address,t->sclass,t->code);
		}
		else if(t->reg==0 && t->op!=' ')
		{
			printf("%d \t <%s,%d> <%c,%d>\n",t->address,t->sclass,t->code,t->op,t->cons);
		}
	
		
		else if(t->reg==0 && t->op==' ')
		{
			printf("%d \t <%s,%d>\n",t->address,t->sclass,t->code);
		}
	}
}
