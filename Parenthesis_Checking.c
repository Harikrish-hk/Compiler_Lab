#include<stdio.h>
int top=-1,line=1;
char stack[200];
void push(char c)
{
    stack[++top]=c;
}
char pop()
{
    return stack[top--];
}
int main(int argc, char *argv[])
{
    FILE *fp;
    fp=fopen(argv[1],"r");
    char ch;
    int er=0;
    while((ch=fgetc(fp))!=EOF)
    {
        switch(ch)
        {
            case ' ':
            case '\t':
             break;
            case '\n':
             line++;
             break;
            case '{':
            case '(':
            case '[':
             push(ch);
             break;
            case '}':
             if(top==-1)
            {
                printf("Error %d: Opening parenthesis missing for }\n",line);
                er=1;
            }
            else
            {
                char c=pop();
                if(c!='{')
                {
                    printf("Error %d: Parethesis Mismatch for }, found %c\n",line,c);
                    er=1;
                }
            }
            break;
            case ')':
             if(top==-1)
            {
                printf("Error %d: Opening parenthesis missing for )\n",line);
                er=1;
            }
            else
            {
                char c=pop();
                if(c!='(')
                {
                    printf("Error %d: Parethesis Mismatch for ), found %c\n",line,c);
                    er=1;
                }
            }
            break;
            case ']':
             if(top==-1)
            {
                printf("Error %d: Opening parenthesis missing for ]\n",line);
                er=1;
            }
            else
            {
                char c=pop();
                if(c!='[')
                {
                    printf("Error %d: Parethesis Mismatch for ], found %c\n",line,c);
                    er=1;
                }
            }
            break;
            default:
             break;
        }
    }
    if(top!=-1)
    {
        while(top!=-1)
         printf("Error %d: Closing Parenthesis missing for %c\n",line,stack[top--]);
    }
     if(er==0)
     printf("Correct\n");
}
