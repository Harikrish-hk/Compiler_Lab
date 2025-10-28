%{
#include<stdio.h>
#include<math.h>
#include<stdio.h>
int flag=0,a;    
%}
DIGIT [0-9]
%%
"+" {flag=1;}
"-" {flag=2;}
"*" {flag=3;}
"/" {flag=4;}
"^" {flag=5;}
{DIGIT}+ {if(flag==0)a=atoi(yytext);
else if(flag==1)a=a+atoi(yytext);
else if(flag==2)a=a-atoi(yytext);
else if(flag==3)a=a*atoi(yytext);
else if(flag==4)a=a/atoi(yytext);
else if(flag==5)a=pow(a,atoi(yytext));}
"\n" {printf("Result: %d\n",a);exit(0);}
. {printf("Unknown Operator '%s'\n",yytext); exit(0);}
%%
int main()
{
    printf("Enter the Expression:\t");
    yyin=stdin;
    yylex();
}
int yywrap()
{
    return 1;
}
