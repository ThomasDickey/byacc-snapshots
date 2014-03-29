#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)


#ifndef yyparse
#define yyparse    inherit1_parse
#endif /* yyparse */

#ifndef yylex
#define yylex      inherit1_lex
#endif /* yylex */

#ifndef yyerror
#define yyerror    inherit1_error
#endif /* yyerror */

#ifndef yychar
#define yychar     inherit1_char
#endif /* yychar */

#ifndef yyval
#define yyval      inherit1_val
#endif /* yyval */

#ifndef yylval
#define yylval     inherit1_lval
#endif /* yylval */

#ifndef yydebug
#define yydebug    inherit1_debug
#endif /* yydebug */

#ifndef yynerrs
#define yynerrs    inherit1_nerrs
#endif /* yynerrs */

#ifndef yyerrflag
#define yyerrflag  inherit1_errflag
#endif /* yyerrflag */

#ifndef yylhs
#define yylhs      inherit1_lhs
#endif /* yylhs */

#ifndef yylen
#define yylen      inherit1_len
#endif /* yylen */

#ifndef yydefred
#define yydefred   inherit1_defred
#endif /* yydefred */

#ifndef yydgoto
#define yydgoto    inherit1_dgoto
#endif /* yydgoto */

#ifndef yysindex
#define yysindex   inherit1_sindex
#endif /* yysindex */

#ifndef yyrindex
#define yyrindex   inherit1_rindex
#endif /* yyrindex */

#ifndef yygindex
#define yygindex   inherit1_gindex
#endif /* yygindex */

#ifndef yytable
#define yytable    inherit1_table
#endif /* yytable */

#ifndef yycheck
#define yycheck    inherit1_check
#endif /* yycheck */

#ifndef yyname
#define yyname     inherit1_name
#endif /* yyname */

#ifndef yyrule
#define yyrule     inherit1_rule
#endif /* yyrule */
#define YYPREFIX "inherit1_"

#define YYPURE 0

#line 2 "inherit1.y"
#include <stdlib.h>

typedef enum {cGLOBAL, cLOCAL} class;
typedef enum {tREAL, tINTEGER} type;
typedef char * name;

struct symbol { class c; type t; name id; };
typedef struct symbol symbol;

struct namelist { symbol *s; struct namelist *next; };
typedef struct namelist namelist;

extern symbol *mksymbol(type t, class c, name id);

#ifdef YYBISON
#define YYLEX_DECL() yylex(void)
#define YYERROR_DECL() yyerror(const char *s)
extern int YYLEX_DECL();
extern void YYERROR_DECL();
#endif
#line 32 "inherit1.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
{
    class	cval;
    type	tval;
    namelist *	nlist;
    name	id;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 135 "inherit1.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define GLOBAL 257
#define LOCAL 258
#define REAL 259
#define INTEGER 260
#define NAME 261
#define YYERRCODE 256
static const short inherit1_lhs[] = {                    -1,
    0,    0,    3,    3,    4,    4,    1,    1,    5,    6,
    2,
};
static const short inherit1_len[] = {                     2,
    3,    2,    1,    1,    1,    1,    2,    1,    0,    0,
    3,
};
static const short inherit1_defred[] = {                  0,
    3,    4,    5,    6,    0,    0,    9,    0,    2,   10,
    8,    0,    0,    7,    0,
};
static const short inherit1_dgoto[] = {                   5,
   12,    9,    6,    7,   10,   13,
};
static const short inherit1_sindex[] = {               -257,
    0,    0,    0,    0,    0, -255,    0, -254,    0,    0,
    0, -253, -254,    0, -253,
};
static const short inherit1_rindex[] = {                  0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    6,    0,    0,    9,
};
static const short inherit1_gindex[] = {                  0,
   -3,    0,    0,    5,    0,    0,
};
#define YYTABLESIZE 11
static const short inherit1_table[] = {                   1,
    2,    3,    4,    3,    4,    1,   11,   14,   11,   15,
    8,
};
static const short inherit1_check[] = {                 257,
  258,  259,  260,  259,  260,    0,  261,  261,    0,   13,
    6,
};
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 261
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"GLOBAL","LOCAL","REAL","INTEGER",
"NAME","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : declaration",
"declaration : class type namelist",
"declaration : type locnamelist",
"class : GLOBAL",
"class : LOCAL",
"type : REAL",
"type : INTEGER",
"namelist : namelist NAME",
"namelist : NAME",
"$$1 :",
"$$2 :",
"locnamelist : $$1 $$2 namelist",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 74 "inherit1.y"

extern int YYLEX_DECL();
extern void YYERROR_DECL();
#line 280 "inherit1.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

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
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
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
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
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

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
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
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 44 "inherit1.y"
	{ yyval.nlist = yystack.l_mark[0].nlist; }
break;
case 2:
#line 46 "inherit1.y"
	{ yyval.nlist = yystack.l_mark[0].nlist; }
break;
case 3:
#line 49 "inherit1.y"
	{ yyval.cval = cGLOBAL; }
break;
case 4:
#line 50 "inherit1.y"
	{ yyval.cval = cLOCAL; }
break;
case 5:
#line 53 "inherit1.y"
	{ yyval.tval = tREAL; }
break;
case 6:
#line 54 "inherit1.y"
	{ yyval.tval = tINTEGER; }
break;
case 7:
#line 58 "inherit1.y"
	{ yyval.nlist->s = mksymbol(yystack.l_mark[-2].tval, yystack.l_mark[-3].cval, yystack.l_mark[0].id);
	      yyval.nlist->next = yystack.l_mark[-1].nlist;
	    }
break;
case 8:
#line 62 "inherit1.y"
	{ yyval.nlist->s = mksymbol(yystack.l_mark[-1].tval, yystack.l_mark[-2].cval, yystack.l_mark[0].id);
	      yyval.nlist->next = NULL;
	    }
break;
case 9:
#line 68 "inherit1.y"
	{ yyval.cval = cLOCAL; }
break;
case 10:
#line 69 "inherit1.y"
	{ yyval.tval = yystack.l_mark[-2].tval; }
break;
case 11:
#line 71 "inherit1.y"
	{ yyval.nlist = yystack.l_mark[0].nlist; }
break;
#line 530 "inherit1.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
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
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
