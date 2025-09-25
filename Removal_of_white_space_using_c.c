#include<stdio.h>
int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usasge %s <input file> <output file>",argv[0]);
        return 1;
    }
    FILE *fp1,*fp2;
    fp1=fopen(argv[1],"r");
    fp2=fopen(argv[2],"w"); //hello da

    char ch;
    while((ch=fgetc(fp1))!=EOF) /*happy journey*/
    {
        switch(ch)
        {
            case ' ':
            case '\n':
            case '\t':
                      break;
            case '/': 
                     ch=fgetc(fp1);
                     if(ch=='/')
                     {
                        while((ch=fgetc(fp1))!='\n');
                     }
                    else if(ch=='*')
                    {
                        char ch1=fgetc(fp1);
                        char ch2=fgetc(fp1);
                        while(ch1!='*'&&ch2!='/')
                        {
                            ch1=ch2;
                            ch2=fgetc(fp1);
                        }
                    }
                    else
                    {
                        fputc('/',fp2);
                        ungetc(ch,fp1);
                    }
                    break;
            default: fputc(ch,fp2);
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
}
