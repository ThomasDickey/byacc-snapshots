#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "calc.y"
# include <stdio.h>
# include <ctype.h>

int regs[26];
int base;

#line 29 "calc.tab.c"
#define DIGIT 257
#define LETTER 258
#define UMINUS 259
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    0,    1,    1,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    3,    3,
};
short yylen[] = {                                         2,
    0,    3,    3,    1,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    2,    1,    1,    1,    2,
};
short yydefred[] = {                                      1,
    0,    0,   17,    0,    0,    0,    0,    0,    0,    3,
    0,   15,   14,    0,    2,    0,    0,    0,    0,    0,
    0,    0,   18,    0,    6,    0,    0,    0,    0,    9,
   10,   11,
};
short yydgoto[] = {                                       1,
    7,    8,    9,
};
short yysindex[] = {                                      0,
  -40,   -7,    0,  -55,  -38,  -38,    1,  -29, -247,    0,
  -38,    0,    0,   22,    0,  -38,  -38,  -38,  -38,  -38,
  -38,  -38,    0,  -29,    0,   51,   60,  -20,  -20,    0,
    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    2,    0,    0,    0,    9,   -9,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   10,    0,   -6,   14,    5,   13,    0,
    0,    0,
};
short yygindex[] = {                                      0,
    0,   65,    0,
};
#define YYTABLESIZE 220
short yytable[] = {                                       6,
   16,    6,   10,   13,    5,   11,    5,   22,   17,   23,
   15,   15,   20,   18,    7,   19,   22,   21,    4,    5,
    0,   20,    8,   12,    0,    0,   21,   16,   16,    0,
    0,   16,   16,   16,   13,   16,    0,   16,   15,   15,
    0,    0,    7,   15,   15,    7,   15,    7,   15,    7,
    8,   12,    0,    8,   12,    8,    0,    8,   22,   17,
    0,    0,   25,   20,   18,    0,   19,    0,   21,   13,
   14,    0,    0,    0,    0,   24,    0,    0,    0,    0,
   26,   27,   28,   29,   30,   31,   32,   22,   17,    0,
    0,    0,   20,   18,   16,   19,   22,   21,    0,    0,
    0,   20,   18,    0,   19,    0,   21,    0,    0,    0,
    0,    0,    0,    0,   16,    0,    0,   13,    0,    0,
    0,    0,    0,    0,    0,   15,    0,    0,    7,    0,
    0,    0,    0,    0,    0,    0,    8,   12,    0,    0,
    0,    0,    0,    0,    0,   16,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    3,    4,    3,   12,
};
short yycheck[] = {                                      40,
   10,   40,   10,   10,   45,   61,   45,   37,   38,  257,
   10,   10,   42,   43,   10,   45,   37,   47,   10,   10,
   -1,   42,   10,   10,   -1,   -1,   47,   37,   38,   -1,
   -1,   41,   42,   43,   41,   45,   -1,   47,   37,   38,
   -1,   -1,   38,   42,   43,   41,   45,   43,   47,   45,
   38,   38,   -1,   41,   41,   43,   -1,   45,   37,   38,
   -1,   -1,   41,   42,   43,   -1,   45,   -1,   47,    5,
    6,   -1,   -1,   -1,   -1,   11,   -1,   -1,   -1,   -1,
   16,   17,   18,   19,   20,   21,   22,   37,   38,   -1,
   -1,   -1,   42,   43,  124,   45,   37,   47,   -1,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   -1,   -1,  124,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,  124,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,  124,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  256,  257,  258,  257,  258,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 259
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,0,0,0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"DIGIT","LETTER","UMINUS",
};
char *yyrule[] = {
"$accept : list",
"list :",
"list : list stat '\\n'",
"list : list error '\\n'",
"stat : expr",
"stat : LETTER '=' expr",
"expr : '(' expr ')'",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '&' expr",
"expr : expr '|' expr",
"expr : '-' expr",
"expr : LETTER",
"expr : number",
"number : DIGIT",
"number : number DIGIT",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 63 "calc.y"
 /* start of programs */

main ()

{
    while(!feof(stdin)) {
      yyparse();
   }
}

yyerror(char *s)
{  
   fprintf(stderr, "%s\n", s);
}


yylex() {   /* lexical analysis routine */
            /* returns LETTER for a lower case letter, yylval = 0 through 25 */
            /* return DIGIT for a digit, yylval = 0 through 9 */
            /* all other characters are returned immediately */

      int c;

      while( (c=getchar()) == ' ' )   { /* skip blanks */ }

      /* c is now nonblank */

      if( islower( c )) {
         yylval = c - 'a';
         return ( LETTER );
         }
      if( isdigit( c )) {
         yylval = c - '0';
         return ( DIGIT );
         }
      return( c );
      }
#line 227 "calc.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 3:
#line 25 "calc.y"
{  yyerrok ; }
break;
case 4:
#line 29 "calc.y"
{  printf("%d\n",yyvsp[0]);}
break;
case 5:
#line 31 "calc.y"
{  regs[yyvsp[-2]] = yyvsp[0]; }
break;
case 6:
#line 35 "calc.y"
{  yyval = yyvsp[-1]; }
break;
case 7:
#line 37 "calc.y"
{  yyval = yyvsp[-2] + yyvsp[0]; }
break;
case 8:
#line 39 "calc.y"
{  yyval = yyvsp[-2] - yyvsp[0]; }
break;
case 9:
#line 41 "calc.y"
{  yyval = yyvsp[-2] * yyvsp[0]; }
break;
case 10:
#line 43 "calc.y"
{  yyval = yyvsp[-2] / yyvsp[0]; }
break;
case 11:
#line 45 "calc.y"
{  yyval = yyvsp[-2] % yyvsp[0]; }
break;
case 12:
#line 47 "calc.y"
{  yyval = yyvsp[-2] & yyvsp[0]; }
break;
case 13:
#line 49 "calc.y"
{  yyval = yyvsp[-2] | yyvsp[0]; }
break;
case 14:
#line 51 "calc.y"
{  yyval = - yyvsp[0]; }
break;
case 15:
#line 53 "calc.y"
{  yyval = regs[yyvsp[0]]; }
break;
case 17:
#line 58 "calc.y"
{  yyval = yyvsp[0]; base = (yyvsp[0]==0) ? 8 : 10; }
break;
case 18:
#line 60 "calc.y"
{  yyval = base * yyvsp[-1] + yyvsp[0]; }
break;
#line 465 "calc.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
