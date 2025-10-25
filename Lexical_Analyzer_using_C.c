#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s <input_file>\n",argv[0]);
        exit(0);
    }
    FILE *fp1,*fp2;
    fp1=fopen(argv[1],"r");
    int sl=1,line=1,i=0,flag=0;
    char lex[50],ch,ch1;
    char key[15][50]={"void","main","printf","include","scanf","if","else","int"};
    printf("sl.no\tline.no\tlexeme\ttoken\n");
    while((ch=fgetc(fp1))!=EOF)
    {
        if(ch==' '||ch=='\t');
        else if(ch=='\n')
         line++;
        else if(ch=='{'||ch=='('||ch=='[')
        {
            printf("%d\t%d\t%c\tOpen_brack\n",sl,line,ch);
            sl++;
        }
        else if(ch=='}'||ch==')'||ch==']')
        {
            printf("%d\t%d\t%c\tClose_brack\n",sl,line,ch);
            sl++;
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
        {
            printf("%d\t%d\t%c\tAssign_op\n",sl,line,ch);
            sl++;
        }
        else if(ch==';')
        {
            printf("%d\t%d\t%c\tSemicolon\n",sl,line,ch);
            sl++;
        }
        else if(ch==',')
        {
            printf("%d\t%d\t%c\tSpl_char\n",sl,line,ch);
            sl++;
        }
        else if(ch=='&')
        {
            ch1=fgetc(fp1);
            if(ch1=='&')
            {
                printf("%d\t%d\t%c%c\tLogical_op\n",sl,line,ch,ch1);
                sl++;
            }
            else
            {
                printf("%d\t%d\t%c\tSpl_char\n",sl,line,ch);
                sl++;
                ungetc(ch1,fp1);
            }
        }
        else if(ch=='=')
        {
            ch1=fgetc(fp1);
            if(ch1=='=')
            {
                printf("%d\t%d\t%c%c\tRel_op\n",sl,line,ch,ch1);
                sl++;
            }
            else
            {
                printf("%d\t%d\t%c\tAss_op\n",sl,line,ch);
                sl++;
                ungetc(ch1,fp1);
            }
        }
        else if(isdigit(ch))
        {
            i=0;
            lex[i++]=ch;
            do{
                ch=fgetc(fp1);
                lex[i++]=ch;
                if(ch=='.')
                 flag=1;
            }while(isdigit(ch)||ch=='.');
            lex[--i]='\0';
            ungetc(ch,fp1);
            if(flag==0)
            {
                printf("%d\t%d\t%s\tDigit\n",sl,line,lex);
                sl++;
            }
            else if(flag==1)
            {
                printf("%d\t%d\t%s\tFloat_point\n",sl,line,lex);
                sl++;
            }
            flag=0;
        }
        else if(isalpha(ch))
        {
            i=0;
            lex[i++]=ch;
            do{
                ch=fgetc(fp1);
                lex[i++]=ch;
            }while(isalpha(ch)||isdigit(ch));
            lex[--i]='\0';
            ungetc(ch,fp1);

            for(i=0;i<8;i++)
            {
                if(strcmp(key[i],lex)==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                printf("%d\t%d\t%s\tKeyword\n",sl,line,lex);
                sl++;
            }
            else if(flag==0)
            {
                printf("%d\t%d\t%s\tIdentifier\n",sl,line,lex);
                sl++;
            }
            flag=0;
        }
        else
        {
            printf("%d\t%d\t%c\tUnrecog_char\n",sl,line,ch);
            sl++;
        }
    }
}


/*

--------------------input.txt-------------------

#include<stdio.h>
int main()
{
    int a=2.31;
    int b=a+10;
    if(a==b)
     printf("Error");
} 
     
*/
