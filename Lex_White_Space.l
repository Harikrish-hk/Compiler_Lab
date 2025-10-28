%{
#include<stdio.h>
int flag=0;
FILE *fp;    
%}
WS [ \t]
%%
{WS}+ {}
"//" {flag=1;}
"\n" {if(flag==1)flag=0;}
"/*" {flag=2;}
"*/" {if(flag==2)flag=0;else if(flag==0)fprintf(fp,"%s",yytext);}
. {if(flag!=1&&flag!=2)fprintf(fp,"%s",yytext);}
%%
int main(int argc, char *argv[])
{
    yyin=fopen(argv[1],"r");
    fp=fopen(argv[2],"w");
    yylex();
    printf("Output can be viewed on file 'output.txt'\n");
}
int yywrap()
{
    return 1;
}

/*
-->lex Lex_White_Space.l
-->gcc lex.yy.c
-->./a.out input.txt output.txt


------input.txt------

#include<stdio.h>
int main()
{
    int a=0;  // initialize a
    int c=a+10; /* Add 10 to a and store it in c *
}

------output.txt------

#include<stdio.h>intmain(){inta=0;intc=a+10;}


*/
