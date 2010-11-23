#define DREG 257
#define VREG 258
#define CONST 259
#define UMINUS 260
#if !(defined(YYSTYPE) || defined(YYSTYPE_IS_DECLARED))
typedef union
{
	int ival;
	double dval;
	INTERVAL vval;
} YYSTYPE;
#endif /* !(YYSTYPE || YYSTYPE_IS_DECLARED) */
extern YYSTYPE calc1_lval;
