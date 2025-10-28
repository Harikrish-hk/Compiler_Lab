%{
#include<stdio.h>
int sl=1,line=1;    
%}
WS [ \t]
ALPHA [a-zA-Z]
DIGIT [0-9]
%%
{WS}+ {}
"\n" {line++;}
";" {printf("%d\t%d\t%s\tSemicolon\n",sl,line,yytext);sl++;}
"+"|"-"|"*"|"/" {printf("%d\t%d\t%s\tArith_Op\n",sl,line,yytext);sl++;}
"=="|">="|"<="|">"|"<"|"!=" {printf("%d\t%d\t%s\tRelation_Op\n",sl,line,yytext);sl++;}
"=" {printf("%d\t%d\t%s\tAssign_Op\n",sl,line,yytext);sl++;}
"{"|"("|"[" {printf("%d\t%d\t%s\tOpening_Bracket\n",sl,line,yytext);sl++;}
")"|"]"|"}" {printf("%d\t%d\t%s\tClosing_Bracket\n",sl,line,yytext);sl++;}
","|"."|"&" {printf("%d\t%d\t%s\tSpecial_Char\n",sl,line,yytext);sl++;}
"int"|"void"|"printf"|"if"|"else"|"include"|"scanf" {printf("%d\t%d\t%s\tKeyword\n",sl,line,yytext);sl++;}
{ALPHA}({ALPHA}|{DIGIT})* {printf("%d\t%d\t%s\tIdentifier\n",sl,line,yytext);sl++;}
{DIGIT}+"."{DIGIT}+ {printf("%d\t%d\t%s\tFloating_Point\n",sl,line,yytext);sl++;}
{DIGIT}+ {printf("%d\t%d\t%s\tNumber\n",sl,line,yytext);sl++;}
. {printf("%d\t%d\t%s\tUnrecog\n",sl,line,yytext);sl++;}
%%
int main(int argc, char *argv[])
{
    yyin=fopen(argv[1],"r");
    printf("Sl.No\tLine.No\tLexeme\tToken\n");
    yylex();
}
int yywrap()
{
    return 1;
}

/*

-->lex Lexical_Analyzer.l
-->gcc lex.yy.c
-->./a.out input.txt

------input.txt------

#include<stdio.h>
int main()
{
    int a=2.31;
    int b=a+10;
    if(a==b)
     printf("Error");
}


------output------

Sl.No   Line.No Lexeme  Token
1       1       #       Unrecog
2       1       include Keyword
3       1       <       Relation_Op
4       1       stdio   Identifier
5       1       .       Special_Char
6       1       h       Identifier
7       1       >       Relation_Op
8       2       int     Keyword
9       2       main    Identifier
10      2       (       Opening_Bracket
11      2       )       Closing_Bracket
12      3       {       Opening_Bracket
13      4       int     Keyword
14      4       a       Identifier
15      4       =       Assign_Op
16      4       2.31    Floating_Point
17      4       ;       Semicolon
18      5       int     Keyword
19      5       b       Identifier
20      5       =       Assign_Op
21      5       a       Identifier
22      5       +       Arith_Op
23      5       10      Number
24      5       ;       Semicolon
25      6       if      Keyword
26      6       (       Opening_Bracket
27      6       a       Identifier
28      6       ==      Relation_Op
29      6       b       Identifier
30      6       )       Closing_Bracket
31      7       printf  Keyword
32      7       (       Opening_Bracket
33      7       "       Unrecog
34      7       Error   Identifier
35      7       "       Unrecog
36      7       )       Closing_Bracket
37      7       ;       Semicolon
38      8       }       Closing_Bracket


*/
