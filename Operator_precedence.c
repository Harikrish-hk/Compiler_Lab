#include<stdio.h>
#include <stdlib.h>

#define MAX 20
int ter,top=-1;
char term[MAX],op[MAX][MAX],string[MAX],stack[MAX];

void push(char c)
{
    if(top>=MAX-1)
    {
        printf("Stack Overflow.\n");
        exit(0);
    }
    else
     stack[++top]=c;
}

char pop()
{
    if(top<=-1)
    {
        printf("Stack Underflow.\n");
        exit(0);
    }
    else 
     return stack[top--];
}

int find_index(char c)
{
    for(int i=0;i<ter;i++)
    {
        if(term[i]==c)
         return i;
    }
    return -1;
}

int main()
{
    printf("Enter the Number of Symbols:\t");
    scanf("%d",&ter);
    printf("Enter the Symbols:\n");
    for(int i=0;i<ter;i++)
    {
        scanf(" %c",&term[i]);
    }
    for(int i=0;i<ter;i++)
    {
        for(int j=0;j<ter;j++)
        {
            printf("%c and %c:\t",term[i],term[j]);
            scanf(" %c",&op[i][j]);
        }
    }
    while(1)
    {
        printf("Enter the string:\t");
        scanf("%s",string);

        int j=0;
        push(string[j]);
        j++;
        while(1)
        {
            char a=stack[top];
            char b=string[j];
            
            int p=find_index(a);
            int q=find_index(b);

            char rel=op[p][q];
            char rel1;

            if(rel=='-')
            {
                printf("Rejected: Invalid precedence between '%c' and '%c'\n", a, b);
                return 1;
            }
            else if(rel=='='||rel=='<')
            {
                push(b);
                j++;
            }
            else if(rel=='>')
            {
                char x,y;
                do{
                    x=pop();
                    y=stack[top];

                    int m=find_index(y);
                    int n=find_index(x);

                    rel1=op[m][n];
                }while(rel1=='>');
            }
            if(string[j]=='$'&&stack[top]=='$')
                {
                    printf("Accepted.");
                    break;
                }
        }
    }
}
