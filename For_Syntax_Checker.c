#include<stdio.h>
#include<ctype.h>
#include<string.h>
char lex[20][30],ch;
int i=0,j=0;
int main(int argc, char *argv[])
{
    FILE *fp;
    fp=fopen(argv[1],"r");
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch==' '||ch=='\n'||ch=='\t');
        else if(isalnum(ch))
        {
            do{
                lex[i][j]=ch;
                j++;
                ch=fgetc(fp);
            }while(isalnum(ch));
            lex[i][j]='\0';
            i++;
            j=0;
            ungetc(ch,fp);
        }
        else
        {
            lex[i][j]=ch;
            j++;
            lex[i][j]='\0';
            i++;
            j=0;
        }
    }
    int count=i,sem=0,f=0;
    printf("Lexeme Separation:\n");
    for(i=0;i<count;i++)
    {
        printf(" %s\n",lex[i]);
    }

    for(i=0;i<count;i++)
    {
        if(strcmp(lex[i],"for")==0)
        {
            f++;
            i++;
            if(i<count&&(strcmp(lex[i],"("))==0)
            {
                i++;
                while(i<count&&(strcmp(lex[i],")"))!=0)
                {
                    if(strcmp(lex[i],";")==0)
                     sem++;

                    i++;
                }
                if(strcmp(lex[i],")")==0)
                {
                    if(sem==2)
                     printf("Syntax correct\n");
                    else if(sem>2)
                     printf("More than 2 semicolon\n");
                    else if(sem<2)
                     printf("Less than 2 semicolon\n");
                }
                else
                 printf("Missing )\n");
            }
            else
             printf("Missing ( after for\n");
        }
    }
}
