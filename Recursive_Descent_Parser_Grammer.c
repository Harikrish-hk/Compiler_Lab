/* A->iB,
B-> *iC| /iC| C, 
C-> +iD| -iD| D, 
D-> epsilon */

#include<stdio.h>
char input[20];
int j=0;
int A();
int B();
int C();
int D();

int main()
{
    printf("Enter the String:\t");
    scanf("%s",input);
    if(A()==1&&input[j]=='\0')
     printf("Accept.");
    else
     printf("Reject.");
}

int A()
{
    if(input[j]=='i')
    {
        printf("Expanding A-> iB\n");
        printf("Consuming i\n");
        j++;
        if(B()==1)
         return 1;
        else 
         return 0;
    }
    else
     return 0;
}

int B()
{
    if(input[j]=='*')
    {
        printf("Expanding B-> *iC\n");
        printf("Consuming *\n");
        j++;
        if(input[j]=='i')
        {
            printf("Consuming i\n");
            j++;
            if(C()==1)
             return 1;
            else
             return 0;
        }
        else
         return 0;
    }
    else if(input[j]=='/')
    {
        printf("Expanding B-> /iC\n");
        printf("Consuming /\n");
        j++;
        if(input[j]=='i')
        {
            printf("Consuming i\n");
            j++;
            if(C()==1)
             return 1;
            else
             return 0;
        }
        else
         return 0;
    }
    else if(C()==1)
     return 1;
    else
     return 0;
}

int C()
{
    if(input[j]=='+')
    {
        printf("Expanding C-> +iD\n");
        printf("Consuming +\n");
        j++;
        if(input[j]=='i')
        {
            printf("Consuming i\n");
            j++;
            if(D()==1)
             return 1;
            else
             return 0;
        }
        else
         return 0;
    }
    else if(input[j]=='-')
    {
        printf("Expanding C-> -iD\n");
        printf("Consuming -\n");
        j++;
        if(input[j]=='i')
        {
            printf("Consuming i\n");
            j++;
            if(D()==1)
             return 1;
            else
             return 0;
        }
        else
         return 0;
    }
    else if(D()==1)
     return 1;
    else
     return 0;
}

int D()
{
    printf("Expanding D-> epsilon\n");
    return 1;
}
