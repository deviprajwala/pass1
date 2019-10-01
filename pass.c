#include<stdio.h>
#include<stdlib.h>
#include<string.h>




struct cell
{
 int loc;
 char label[10];
 char opcode[10];
 char operand[10];
 char objectcode[10];
 struct cell *link;
};
typedef struct cell *cell;

struct symtab
{
 char label[10];
 int locctr;
 struct symtab *link;
};
typedef struct symtab *symtab;
symtab root;

cell getcell();
cell input(cell head);
void print(head);
void generate();
symtab insert(char a[10],int b);

cell getcell()
{
 cell x;
 x=(cell)malloc(sizeof(struct cell));
 return x;
}

char str1[10],str2[10],str3[10],str4[10],str5[10];
char word1[10]="word";
char resw1[10]="resw";
char resb1[10]="resb";
char byte1[10]="byte";
cell input(cell head)
{
 cell cur,prev,x;
 x=getcell();
 prev=NULL;
 cur=head;
 if(cur==NULL)
 {
  head=x;
  goto label;
 }
 while(cur!=NULL)
 {
  prev=cur;
  cur=cur->link;
 }
 prev->link=x;
label:
 //printf("\nLabel: ");
 gets(str1);
 //printf("\nOpcode: ");
 gets(str2);
 //printf("\noperand: ");
 gets(str3);
 strcpy(x->label,str1);
 strcpy(x->opcode,str2);
 strcpy(x->operand,str3);
 return head;
}

symtab getsymtab()
{
 symtab x;
 x=(symtab)malloc(sizeof(struct symtab));
 return x;
}
 
void print(cell head)
{
cell cur,prev;
prev=NULL;
cur=head;
if(cur==NULL)
{
 return;
}
printf("%d     ",cur->loc);
printf("%s     ",cur->label);
printf("%s     ",cur->opcode);
printf("%s\n",cur->operand);
cur=cur->link;
print(cur);
}

void generate(cell head)
{
 int res,p,q,r,s;
 cell cur,prev;
 cur=head;

 strcpy(str2,cur->opcode);
 char str4[10]="start ";
 res=strcmp(str2,str4);
 if(res==0)
 {
  int starting_address=atoi(cur->operand);
  cur->loc=1000;//atoi(cur->operand);
  //printf("%d",starting_address);
  prev=cur;
  cur=cur->link;
  cur->loc=prev->loc;
  goto label;
 }

  strcpy(str2,cur->opcode);
  char str3[10]="end ";
  p=strcmp(str2,str3);
  while(p!=0)
  {
   strcpy(str2,cur->label);
   char str4[10]="*****";
   q=strcmp(str2,str4);
   if(q!=0)
   {
     root=insert(cur->label,prev->loc); 
   }
   strcpy(str2,cur->opcode);
   char str[10]="*****";
   r=strcmp(str2,str4);
   if(r!=0)
   {
    s=strcmp(str2,word1);
    if(s==0)
    {s=1;
     cur->loc=prev->loc+3;
     goto label;
    }
    s=strcmp(str2,resw1);
    if(s==0)
    {s=1;
     int x;
     x=atoi(cur->operand)*3;
     cur->loc=prev->loc+x;
     goto label;
    }
    s=strcmp(str2,resb1);
    if(s==0)
    {s=1;
     cur->loc=prev->loc+atoi(cur->operand);
     goto label;
    }
    s=strcmp(str2,byte1);
    if(s==0)
    {s=1;
     int len;
     strcpy(str3,cur->operand);
     len=strlen(str3);
     cur->loc=prev->loc+len-3;
     goto label;
    }
    cur->loc=prev->loc+3;
label:    
    prev=cur;
    cur=cur->link;
    strcpy(str2,cur->opcode);
    char str5[10]="end";
    p=strcmp(str2,str5);
   }
 }
// printf("Program length is %d",prev->loc-starting_address);
}
symtab insert(char a[25],int b)
{
 symtab x,cur,prev;
 x=getsymtab();
 strcpy(x->label,a);
 x->locctr=b;
 x->link=NULL;
 if(root==NULL)
 {
  root=x;
  return root;
 }
 prev=NULL;
 cur=root;
 while(cur!=NULL)
 {
   prev=cur;
   cur=cur->link;
 }
 prev->link=x;
 return root;
}
int main()
{
int n,i;
cell head;
printf("Enter the number of lines: ");
scanf("%d  ",&n);
for(i=1;i<=n;i++)
{
 if(i==1)
 {
  head=NULL;
 }
 head=input(head);
}
printf("\n");
printf("LOC  LABEL   OPCODE    OPERAND   \n");
generate(head);
print(head);
}
