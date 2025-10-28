%{
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
%}
%token NUMBER
%%
L:E'\n' {printf("Result is :%d\n",$1);exit(0);}
;
E:E'+'T {$$=$1+$3;}
| T {$$=$1;}
;
T:T'*'F {$$=$1*$3;}
| F {$$=$1;}
;
F:NUMBER {$$=$1;}
;
%%
int main()
{
  printf("\nEnter the Expression:\t");
  yyparse();
}
yylex()
{
  char ch;
  ch=getchar();
  if(isdigit(ch))
  {
    ungetc(ch,stdin);
    scanf("%d",&yylval);
    return NUMBER;
  }
  else
   return ch;
}
yyerror()
{
  printf("Invalid Expression.\n");
  exit(0);
}

/*

-->lex Simple_Calculator.y
-->yacc Simple_Calculator.y
-->gcc y.tab.c
-->./a.out

*/
