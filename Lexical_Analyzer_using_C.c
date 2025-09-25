#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("usage: %s <input file> <output file>\n",argv[0]);
        exit(0);
    }
    FILE *fp1,*fp2;
    fp1=fopen(argv[1],"r");
    fp2=fopen(argv[2],"w");
    int sl=1,line=1,flag=0,i;
    char lex[50],ch,ch1;
    char key[5][20]={"main","printf","scanf","if","else"};
    fprintf(fp2,"sl.no\tLine.no\tLexeme\tToken\n");
    while((ch=fgetc(fp1))!=EOF)
    {
        if(ch==' '||ch=='\t');
        else if(ch=='\n')
         line++;
        else if(ch=='{'||ch=='['||ch=='(')
        {
            fprintf(fp2,"%d\t%d\t%c\tOp_Brak\n",sl,line,ch);
            sl++;
        }
        else if(ch=='}'||ch==']'||ch==')')
        {
            fprintf(fp2,"%d\t%d\t%c\tCl_Brak\n",sl,line,ch);
            sl++;
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
        {
            fprintf(fp2,"%d\t%d\t%c\tAriop\n",sl,line,ch);
            sl++;
        }
        else if(ch==';')
        {
            fprintf(fp2,"%d\t%d\t%c\tSemicolon\n",sl,line,ch);
            sl++;
        }
        else if(ch=='&')
        {
            ch1=fgetc(fp1);
            if(ch1=='&')
            {
                fprintf(fp2,"%d\t%d\t%c%c\tRelop\n",sl,line,ch,ch1);
                sl++;
            }
            else
            {
                fprintf(fp2,"%d\t%d\t%c\tSpeop\n",sl,line,ch);
                sl++;
                ungetc(ch,fp1);
            }
        }
        else if(ch=='=')
        {
            ch1=fgetc(fp1);
            if(ch1=='=')
            {
                fprintf(fp2,"%d\t%d\t%c%c\tRelop\n",sl,line,ch,ch1);
                sl++;
            }
            else
            {
                fprintf(fp2,"%d\t%d\t%c\tAssop\n",sl,line,ch);
                sl++;
                ungetc(ch,fp1);
            }
        }
        else if(isdigit(ch))
        {
            i=0;
            lex[i++]=ch;
            do
            {
                ch1=fgetc(fp1);
                lex[i++]=ch1;
                if(ch1=='.')
                 flag=1;
            }while(ch1=='.'||isdigit(ch1));
            lex[--i]='\0';
            ungetc(ch1,fp1);
            if(flag==1)
            {
                fprintf(fp2,"%d\t%d\t%s\tFloat\n",sl,line,lex);
                sl++;
            }
            else
            {
                fprintf(fp2,"%d\t%d\t%s\tDigit\n",sl,line,lex);
                sl++;
            }
            flag=0;
            i=0;
        }
        
        else if(isalpha(ch))
        {
            i=0;
            lex[i++]=ch;
            do
            {
                ch1=fgetc(fp1);
                lex[i++]=ch1;
            }while(isdigit(ch1)||isalpha(ch1));
            lex[--i]='\0';
            ungetc(ch1,fp1);
            for(int j=0;j<5;j++)
            {
                if(strcmp(key[j],lex)==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                fprintf(fp2,"%d\t%d\t%s\tKeywrd\n",sl,line,lex);
                sl++;
            }
            else
                {
                    fprintf(fp2,"%d\t%d\t%s\tIdentifier\n",sl,line,lex);
                    sl++;
                }
        }
        else
        {
            fprintf(fp2,"%d\t%d\t%c\tUnrecg\n",sl,line,ch);
                    sl++;
        }
    }
    fclose(fp1);
    fclose(fp2);
}
