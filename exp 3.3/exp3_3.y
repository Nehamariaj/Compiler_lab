%{
/* Definition section */
	#include<stdio.h>
	int flag=0;
	void yyerror();
	int yylex(void);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

/* Rule Section */
%%
ArithmeticExpression: exp{
	printf("\nResult=%d\n", $$);
	return 0;
};
exp:exp'+'exp {$$=$1+$3;}
|exp'-'exp{$$=$1-$3;}
|exp'*'exp {$$=$1*$3;}
|exp'/'exp {$$=$1/$3;}
|exp'%'exp {$$=$1%$3;}
|'('exp')' {$$=$2;}
| NUMBER {$$=$1;}
;
%%

//driver code
void main() {
	printf("\nEnter Any Arithmetic Expression :\n");
	yyparse();
	if(flag==0)
		printf("\nEntered arithmetic expression is Valid\n\n");
}

void yyerror() {
	printf("\nEntered arithmetic expression is Invalid\n\n");
	flag=1;
}
