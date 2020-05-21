%{
#include <stdio.h>
int vsz = 0;
%}
szj	[0-9]
%%
{szj}*(\.{szj}+)?	{++vsz; 
    printf("[valosszam=%s %f]", yytext, atof(yytext));}
%%
int
main ()
{
 yylex ();
 printf("A bemenetre erkezett valos szamok szama: %d\n", vsz);
 return 0;
}
