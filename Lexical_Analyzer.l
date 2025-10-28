%{
#include<stdio.h>   
int line=1,sl=1; 
%}
ALPHA [a-zA-Z]
DIGIT [0-9]
WS [ \t]
%%
{WS}+ {}
"\n" {line++;}
";" {printf("%d\t%d\t%s\tSemicolon\n",sl,line,yytext);sl++;}
"+"|"-"|"*"|"/" {printf("%d\t%d\t%s\tArith_Op\n",sl,line,yytext);sl++;}
"("|"["|"{" {printf("%d\t%d\t%s\tOpen_brack\n",sl,line,yytext);sl++;}
")"|"]"|"}" {printf("%d\t%d\t%s\tClose_brack\n",sl,line,yytext);sl++;}
","|"." {printf("%d\t%d\t%s\tSpcl_Char\n",sl,line,yytext);sl++;}
"int"|"void"|"printf"|"if"|"else"|"include"|"scanf" {printf("%d\t%d\t%s\tKeyword\n",sl,line,yytext);sl++;}
{ALPHA}({ALPHA}|{DIGIT})* {printf("%d\t%d\t%s\tIdentifier\n",sl,line,yytext);sl++;}
{DIGIT}+"."{DIGIT}+ {printf("%d\t%d\t%s\tFloat_Point\n",sl,line,yytext);sl++;}
{DIGIT}+ {printf("%d\t%d\t%s\tNumber\n",sl,line,yytext);sl++;}
. {printf("%d\t%d\t%s\tUnrecog_Char\n",sl,line,yytext);sl++;}
%%
int main(int argc,char *argv[])
{
    yyin=fopen(argv[1],"r");
    printf("sl\tline\tlexeme\ttoken\n");
    yylex();
}
int yywrap()
{
    return 1;
}
