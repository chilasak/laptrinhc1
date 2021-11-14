#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
typedef struct node
{
	char data[10];
	struct node *next;
}Node;
typedef struct stack
{
	Node* top;
}Stack;
Node *CreateNode(char *x)
{
	Node *p = (Node*) malloc(sizeof(Node));
	strcpy(p->data,x);
	p->next = NULL;
}
void Push(Stack *s, Node *p)
{
	if (s->top==NULL)
		s->top =p;
	else
		{
			p->next= s->top;
			s->top =p; 
		}
}
char* Pop(Stack *s)
{
	char *str = (char*)malloc(10);
		

	if (s->top==NULL)
		strcpy(str,"");
	else
		{
			Node *p=s->top;
			strcpy(str,p->data);
			s->top = s->top->next;
			free(p);
		}
	return str;
}
char* Peek(Stack *s)
{
	char *str = (char*)malloc(10);
		

	if (s->top==NULL)
		strcpy(str,"");
	else
		{
			Node *p=s->top;
			strcpy(str,p->data);
		}
	return str;
}

void PrintStack(Stack s)
{
	Node *p= s.top;
	if (p==NULL)
		{
			printf("\nStack rong");
		}
	else
		while (p!=NULL)
		{
			printf("%s ",p->data);
			p=p->next;
		}	
}
void init(Stack *s)
{
	s->top =NULL;
}
typedef struct queue
{
	Node *head;
	Node *tail;
}Queue;
void initq(Queue *q)
{
	q->head=NULL;
	q->tail=NULL;
}
void enQueue(Queue *q,Node *p)
{
	if(q->head==NULL)
	{
		q->head=p;
		q->tail=p;
	}
	else{
		q->tail->next=p;
		q->tail=p;
	}
}
char* peekq(Queue *q){
	char *str = (char*)malloc(10);
	if(q->head==NULL){
		strcpy(str,"");
	}
	else
	{
		Node *p=q->head;
		strcpy(str,p->data);
		q->head = q->head->next;
		if(q->head==NULL){
			q->tail=NULL;
		}
		free(p);
	}
	return str;
}
float Tinh(char *dau,float a,float b)
{
	if(dau == "+")
		return a+b;
	if(dau == "-")
		return a-b;
	if(dau == "*")
		return a*b;
	if(dau == "/")
		return a/b;
	if(dau == "^");
		return pow(a,b);
}
int DoUuTien(char *o)
{ 

	if(o[0] == '^')
	  return 3;
	if(o[0] == '*' || o[0] == '/')
	  return 2;
	if(o[0] == '+' || o[0] == '-')
	  return 1;
}
int KiemTraPhanTu(char *Token)
{ 

 	if(Token[0] == '+'||Token[0] == '-'||Token[0] == '*'||Token[0] == '/'||Token[0] == '^')
  		return 1;
 	else
 	{
 		if(Token[0] == '('|| Token[0] == ')')
   			return -1;
  		else
   			return 0;
 	}
}
void PrintQueue(Queue q)
{
	Node *p= q.head;
	
	while(p!=NULL){
		printf("%s ",p->data);
		p=p->next;
	}
}
int KT(char *s)
{
	if(s[0]!='(')
		return 1;
	return 0;
}
void StringToStack(Stack *s,Queue *q,char *str)
{	
    char pt[3];
	char num[10];
	char ch[2];
	char p1[10],p2[10],p3[10];
	int KetQua;
	Node *p;
	int i,j;
	i=0;
	while (str[i]!='\0')
	{
		if(str[i]=='(')
		{
			pt[0]=str[i];
			pt[1]='\0';
			p=CreateNode(pt);
			Push(s,p);
		}
		if(str[i]>='0' && str[i]<='9')
		{
			pt[0]=str[i];
			pt[1]='\0';
			if(str[i+1]>='0' && str[i+1]<='9')
			{
				pt[1]=str[i+1];	
				pt[2]='\0';
				i++;
			}
			if(str[i+1]>='0' && str[i+1]<='9')
			{
				pt[2]=str[i+1];	
				pt[3]='\0';
				i++;
			}
			
			p=CreateNode(pt);
			enQueue(q,p);
		}
		if((str[i]=='+')||(str[i]=='-')||(str[i]=='*')||(str[i]=='/')||(str[i]=='^'))
			{
				while (KiemTraPhanTu(Peek(s))>0)
				{
					Node *t=s->top;
					if (DoUuTien(t->data)>=DoUuTien(&str[i]))
					{
						char cp[2];
						strcpy(cp,Pop(s));
						p=CreateNode(cp);
						enQueue(q,p);
					}
					else
						break;
				}
				pt[0]=str[i];
				pt[1]='\0';
				p=CreateNode(pt);
				Push(s,p);
			}
		if (str[i]==')')
		   	{

				while(s->top!=NULL)
				{
					char t[2];
					strcpy(t,Pop(s));
					if(t[0]!='(')
					{
						p=CreateNode(t);
						enQueue(q,p);
					}
					else
					break;
				}
			}
		i++;
	}

}

int main()
{
	Stack s;
	Queue q;
	init(&s);
	initq(&q);
	char str[]="((98+((4/2)*5)-2))";
	printf("Bieu thuc trung to %s \n",str);
	StringToStack(&s,&q,str);
	printf("Bieu thuc hau to la  : ");
	PrintQueue(q);
//	PrintStack(s);
}
