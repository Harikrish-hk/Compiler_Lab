#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 20

int top=-1;
char stack[MAX];
int i=0,j=0;
char postfix[MAX],infix[MAX];

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

void intopo()
{
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

void tac()
{
    int sl=1;
    top=-1,i=0;
    char ch,ch1,ch2;
    printf("\nTHREE ADDRESS CODE\n");
    while(postfix[i]!='\0')
    {
        ch=postfix[i];
        if(isalpha(ch))
         push(ch);
        else
        {
            ch2=pop();
            ch1=pop();
            if(isalpha(ch1)&&isalpha(ch2))
             printf("t%d=%c%c%c\n",sl,ch1,ch,ch2);
            else if(isalpha(ch1)&&isdigit(ch2))
             printf("t%d=%c%ct%c",sl,ch1,ch,ch2);
            else if(isalpha(ch2)&&isdigit(ch1))
             printf("t%d=t%c%c%c",sl,ch1,ch,ch2);
            else if(isdigit(ch1)&&isdigit(ch2))
             printf("t%d=t%c%ct%c",sl,ch1,ch,ch2);

             push(sl+'0');
             sl++;
        }
        i++;
    }
}

void quad()
{
    char ch,ch1,ch2;
    top=-1;
    i=0;
    int sl=1;
    printf("\nQuadruple CODE\n");
    printf("OP\tARG1\tARG2\tRESULT\n");
    while(postfix[i]!='\0')
    {
        ch=postfix[i];
        if(isalpha(ch))
         push(ch);
        else
        {
            ch2=pop();
            ch1=pop();

            if(isalpha(ch1)&&isalpha(ch2))
             printf("%c\t%c\t%c\tt%d\n",ch,ch1,ch2,sl);
            else if(isalpha(ch1)&&isdigit(ch2))
             printf("%c\t%c\tt%c\tt%d\n",ch,ch1,ch2,sl);
            else if(isalpha(ch2)&&isdigit(ch1))
             printf("%c\tt%c\t%c\t%d\n",ch,ch1,ch2,sl);
            else if(isdigit(ch1)&&isdigit(ch2))
             printf("%c\tt%c\t%c\tt%d\n",ch,ch1,ch2,sl);

            push(sl+'0');
            sl++;
        }
        i++;
    }
}

void trip()
{
    top=-1;
    i=0;
    int sl=1;
    char ch,ch1,ch2;
    printf("\nTriple CODE\n");
    printf("\tOP\tARG1\tARG2\n");
    while(postfix[i]!='\0')
    {
        ch=postfix[i];
        if(isalpha(ch))
         push(ch);
        else
        {
            ch2=pop();
            ch1=pop();

            if(isalpha(ch1)&&isalpha(ch2))
             printf("(%d)\t%c\t%c\t%c\n",sl-1,ch,ch1,ch2);
            else if(isalpha(ch1)&&isdigit(ch2))
             printf("(%d)\t%c\t%c\t(%c)\n",sl-1,ch,ch1,ch2-1);
            else if(isalpha(ch2)&&isdigit(ch1))
             printf("(%d)\tt%c\t(%c)\t%c\n",sl-1,ch,ch1-1,ch2);
            else if(isdigit(ch1)&&isdigit(ch2))
             printf("(%d)\tt%c\t(%c)\t(%c)\n",sl-1,ch,ch1-1,ch2-1);

            push(sl+'0');
            sl++;
        }
        i++;
    }
}

int main()
{
    printf("Enter the Infix Expression:\t");
    scanf("%s",infix);
    intopo();
    tac();
    quad();
    trip();
}
