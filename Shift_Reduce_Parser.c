#include<stdio.h>
int top=0,j=0,sl=1;
char stack[20],input[20],ch;

void reduce();

int main()
{
    printf("Enter the String:\t");
    scanf("%s",input);
    printf("Sl.No\tStack\tInput\tAction\n");
    printf("%d\t$%s\t%s$\t-\n",sl,stack,input);
    sl++;
    while(input[j]!='\0')
    {
        ch=input[j];
        stack[top++]=ch;
        stack[top]='\0';
        input[j]=' ';
        j++;
        printf("%d\t$%s\t%s$\tShift %c\n",sl,stack,input,ch);
        sl++;
        reduce();
    }
    if(stack[0]=='E'&&stack[1]=='\0')
     printf("Accepted.");
    else
     printf("Rejected.");
}
void reduce()
{
    int z=0;
    for(z=0;z<top;z++)
    {
        if(stack[z]=='i')
        {
            stack[z]='E';
            printf("%d\t$%s\t%s$\tReduce E->i\n",sl,stack,input);
            sl++;
        }
    }
    for(z=0;z<top;z++)
    {
        if(stack[z]=='('&&stack[z+1]=='E'&&stack[z+2]==')')
        {
            stack[z]='E';
            stack[z+1]='\0';
            top-=2;
            printf("%d\t$%s\t%s$\tReduce E->(E)\n",sl,stack,input);
            sl++;
        }
    }
    for(z=0;z<top;z++)
    {
        if(stack[z]=='E'&&stack[z+1]=='+'&&stack[z+2]=='E')
        {
            stack[z]='E';
            stack[z+1]='\0';
            top-=2;
            printf("%d\t$%s\t%s$\tReduce E->E+E\n",sl,stack,input);
            sl++;
        }
    }
    for(z=0;z<top;z++)
    {
        if(stack[z]=='E'&&stack[z+1]=='*'&&stack[z+2]=='E')
        {
            stack[z]='E';
            stack[z+1]='\0';
            top-=2;
            printf("%d\t$%s\t%s$\tReduce E->E*E\n",sl,stack,input);
            sl++;
        }
    }
}
