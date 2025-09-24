#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 20

int top=-1;
char stack[MAX];

void push(char c)
{
    if(top>=MAX-1)
    {
        printf("Overflow.\n");
        exit(0);
    }
    else
     stack[++top]=c;
}

char pop()
{
    if(top<=-1)
    {
        printf("Underflow.\n");
        exit(0);
    }
    else 
     return stack[top--];
}

int priority(char c)
{
    if(c=='(') return 0;
    else if(c=='+'||c=='-') return 1;
    else if(c=='*'||c=='/') return 2;
    else if(c=='^') return 3;
    else return 0;
}

int main()
{
    int i=0,j=0;
    char postfix[MAX],infix[MAX];
    printf("Enter the Infix Expression:\t");
    scanf("%s",infix);

    while(infix[i]!='\0')
    {
        char ch=infix[i];
        if(isalnum(ch))
        {
            postfix[j++]=ch;
        }
        else if(ch=='(')
        {
            push(ch);
        }
        else if(ch==')')
        {
            char x;
            while((x=pop())!='(')
            {
                postfix[j++]=x;
            }
        }
        else
        {
            while(top!=-1&&priority(stack[top])>=priority(infix[i]))
            {
                postfix[j++]=pop();
            }
            push(ch);
        }
        i++;
    }
    while(top!=-1)
    {
        postfix[j++] = pop();
    }  
    postfix[j]='\0';
    printf("Postfix Expression is: %s\n",postfix);
}
