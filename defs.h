/* $Id: defs.h,v 1.5 2004/03/28 20:27:20 tom Exp $ */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>


/*  machine-dependent definitions			*/
/*  the following definitions are for the Tahoe		*/
/*  they might have to be changed for other machines	*/

/*  MAXCHAR is the largest unsigned character value	*/
/*  MAXSHORT is the largest value of a C short		*/
/*  MINSHORT is the most negative value of a C short	*/
/*  MAXTABLE is the maximum table size			*/
/*  BITS_PER_WORD is the number of bits in a C unsigned	*/
/*  WORDSIZE computes the number of words needed to	*/
/*	store n bits					*/
/*  BIT returns the value of the n-th bit starting	*/
/*	from r (0-indexed)				*/
/*  SETBIT sets the n-th bit starting from r		*/

#define	MAXCHAR		255
#define	MAXSHORT	32767
#define MINSHORT	-32768
#define MAXTABLE	32500
#define BITS_PER_WORD	32
#define	WORDSIZE(n)	(((n)+(BITS_PER_WORD-1))/BITS_PER_WORD)
#define	BIT(r, n)	((((r)[(n)>>5])>>((n)&31))&1)
#define	SETBIT(r, n)	((r)[(n)>>5]|=((unsigned)1<<((n)&31)))


/*  character names  */

#define	NUL		'\0'    /*  the null character  */
#define	NEWLINE		'\n'    /*  line feed  */
#define	SP		' '     /*  space  */
#define	BS		'\b'    /*  backspace  */
#define	HT		'\t'    /*  horizontal tab  */
#define	VT		'\013'  /*  vertical tab  */
#define	CR		'\r'    /*  carriage return  */
#define	FF		'\f'    /*  form feed  */
#define	QUOTE		'\''    /*  single quote  */
#define	DOUBLE_QUOTE	'\"'    /*  double quote  */
#define	BACKSLASH	'\\'    /*  backslash  */


/* defines for constructing filenames */

#if defined(VMS)
#define CODE_SUFFIX	"_code.c"
#define	DEFINES_SUFFIX	"_tab.h"
#define	OUTPUT_SUFFIX	"_tab.c"
#define	VERBOSE_SUFFIX	".output"
#else
#define CODE_SUFFIX	".code.c"
#define	DEFINES_SUFFIX	".tab.h"
#define	OUTPUT_SUFFIX	".tab.c"
#define	VERBOSE_SUFFIX	".output"
#endif


/* keyword codes */

#define TOKEN 0
#define LEFT 1
#define RIGHT 2
#define NONASSOC 3
#define MARK 4
#define TEXT 5
#define TYPE 6
#define START 7
#define UNION 8
#define IDENT 9


/*  symbol classes  */

#define UNKNOWN 0
#define TERM 1
#define NONTERM 2


/*  the undefined value  */

#define UNDEFINED (-1)


/*  action codes  */

#define SHIFT 1
#define REDUCE 2


/*  character macros  */

#define IS_IDENT(c)	(isalnum(c) || (c) == '_' || (c) == '.' || (c) == '$')
#define	IS_OCTAL(c)	((c) >= '0' && (c) <= '7')
#define	NUMERIC_VALUE(c)	((c) - '0')


/*  symbol macros  */

#define ISTOKEN(s)	((s) < start_symbol)
#define ISVAR(s)	((s) >= start_symbol)


/*  storage allocation macros  */

#define CALLOC(k,n)	(calloc((unsigned)(k),(unsigned)(n)))
#define	FREE(x)		(free((char*)(x)))
#define MALLOC(n)	(malloc((unsigned)(n)))
#define	NEW(t)		((t*)allocate(sizeof(t)))
#define	NEW2(n,t)	((t*)allocate((unsigned)((n)*sizeof(t))))
#define REALLOC(p,n)	(realloc((char*)(p),(unsigned)(n)))


/*  the structure of a symbol table entry  */

typedef struct bucket bucket;
struct bucket
{
    struct bucket *link;
    struct bucket *next;
    char *name;
    char *tag;
    short value;
    short index;
    short prec;
    char class;
    char assoc;
};


/*  the structure of the LR(0) state machine  */

typedef struct core core;
struct core
{
    struct core *next;
    struct core *link;
    short number;
    short accessing_symbol;
    short nitems;
    short items[1];
};


/*  the structure used to record shifts  */

typedef struct shifts shifts;
struct shifts
{
    struct shifts *next;
    short number;
    short nshifts;
    short shift[1];
};


/*  the structure used to store reductions  */

typedef struct reductions reductions;
struct reductions
{
    struct reductions *next;
    short number;
    short nreds;
    short rules[1];
};


/*  the structure used to represent parser actions  */

typedef struct action action;
struct action
{
    struct action *next;
    short symbol;
    short number;
    short prec;
    char action_code;
    char assoc;
    char suppressed;
};


/* global variables */

extern char dflag;
extern char lflag;
extern char rflag;
extern char tflag;
extern char vflag;
extern char *symbol_prefix;

extern char *myname;
extern char *cptr;
extern char *line;
extern int lineno;
extern int outline;

extern char *banner[];
extern char *tables[];
extern char *header[];
extern char *body[];
extern char *trailer[];

extern char *code_file_name;
extern char *defines_file_name;
extern char *input_file_name;
extern char *output_file_name;
extern char *verbose_file_name;

extern FILE *action_file;
extern FILE *code_file;
extern FILE *defines_file;
extern FILE *input_file;
extern FILE *output_file;
extern FILE *text_file;
extern FILE *union_file;
extern FILE *verbose_file;

extern int nitems;
extern int nrules;
extern int nsyms;
extern int ntokens;
extern int nvars;
extern int ntags;

extern char unionized;
extern char line_format[];

extern int   start_symbol;
extern char  **symbol_name;
extern short *symbol_value;
extern short *symbol_prec;
extern char  *symbol_assoc;

extern short *ritem;
extern short *rlhs;
extern short *rrhs;
extern short *rprec;
extern char  *rassoc;

extern short **derives;
extern char *nullable;

extern bucket *first_symbol;
extern bucket *last_symbol;

extern int nstates;
extern core *first_state;
extern shifts *first_shift;
extern reductions *first_reduction;
extern short *accessing_symbol;
extern core **state_table;
extern shifts **shift_table;
extern reductions **reduction_table;
extern unsigned *LA;
extern short *LAruleno;
extern short *lookaheads;
extern short *goto_map;
extern short *from_state;
extern short *to_state;

extern action **parser;
extern int SRtotal;
extern int RRtotal;
extern short *SRconflicts;
extern short *RRconflicts;
extern short *defred;
extern short *rules_used;
extern short nunused;
extern short final_state;

/* global functions */

extern bucket *lookup(char *);
extern bucket *make_bucket(char *);

#ifndef GCC_NORETURN
#define GCC_NORETURN /* nothing */
#endif

/* closure.c */
extern void closure(short *nucleus, int n);
extern void finalize_closure(void);
extern void set_EFF(void);
extern void set_first_derives(void);

/* error.c */
extern void default_action_warning(void);
extern void dollar_error(int a_lineno, char *a_line, char *a_cptr);
extern void dollar_warning(int a_lineno, int i);
extern void fatal(char *msg);
extern void illegal_character(char *c_cptr);
extern void illegal_tag(int t_lineno, char *t_line, char *t_cptr);
extern void no_grammar(void);
extern void no_space(void);
extern void open_error(char *filename);
extern void over_unionized(char *u_cptr);
extern void prec_redeclared(void);
extern void print_pos(char *st_line, char *st_cptr);
extern void reprec_warning(char *s);
extern void restarted_warning(void);
extern void retyped_warning(char *s);
extern void revalued_warning(char *s);
extern void syntax_error(int st_lineno, char *st_line, char *st_cptr) GCC_NORETURN;
extern void terminal_lhs(int s_lineno);
extern void terminal_start(char *s);
extern void tokenized_start(char *s);
extern void undefined_goal(char *s);
extern void undefined_symbol_warning(char *s);
extern void unexpected_EOF(void);
extern void unknown_rhs(int i);
extern void unterminated_action(int a_lineno, char *a_line, char *a_cptr);
extern void unterminated_comment(int c_lineno, char *c_line, char *c_cptr);
extern void unterminated_string(int s_lineno, char *s_line, char *s_cptr);
extern void unterminated_text(int t_lineno, char *t_line, char *t_cptr);
extern void unterminated_union(int u_lineno, char *u_line, char *u_cptr);
extern void untyped_lhs(void);
extern void untyped_rhs(int i, char *s);
extern void used_reserved(char *s);

/* lalr.c */
extern int hash(char *name);
extern void create_symbol_table(void);
extern void free_symbol_table(void);
extern void free_symbols(void);

/* lalr.c */
extern int map_goto(int state, int symbol);
extern short ** transpose(short **R, int n);
extern void add_lookback_edge(int stateno, int ruleno, int gotono);
extern void build_relations(void);
extern void compute_FOLLOWS(void);
extern void compute_lookaheads(void);
extern void digraph(short **relation);
extern void initialize_F(void);
extern void initialize_LA(void);
extern void lalr(void);
extern void set_accessing_symbol(void);
extern void set_goto_map(void);
extern void set_maxrhs(void);
extern void set_reduction_table(void);
extern void set_shift_table(void);
extern void set_state_table(void);
extern void traverse(int i);

/* lr0.c */
extern core * new_state(int symbol);
extern int get_state(int symbol);
extern void allocate_itemsets(void);
extern void allocate_storage(void);
extern void append_states(void);
extern void free_derives(void);
extern void free_nullable(void);
extern void free_storage(void);
extern void generate_states(void);
extern void initialize_states(void);
extern void lr0(void);
extern void new_itemsets(void);
extern void save_reductions(void);
extern void save_shifts(void);
extern void set_derives(void);
extern void set_nullable(void);
extern void show_cores(void);
extern void show_ritems(void);
extern void show_rrhs(void);
extern void show_shifts(void);

/* main.c */
extern char *allocate(unsigned n);
extern void create_file_names(void);
extern void done(int k) GCC_NORETURN;
extern void getargs(int argc, char *argv[]);
extern void onintr(int sig);
extern void open_files(void);
extern void set_signals(void);
extern void usage(void);

/* mkpar.c */
extern action * add_reduce(action *actions, int ruleno, int symbol);
extern action * add_reductions(int stateno, action *actions);
extern action * get_shifts(int stateno);
extern action * parse_actions(int stateno);
extern int sole_reduction(int stateno);
extern void defreds(void);
extern void find_final_state(void);
extern void free_action_row(action *p);
extern void free_parser(void);
extern void make_parser(void);
extern void remove_conflicts(void);
extern void total_conflicts(void);
extern void unused_rules(void);

/* output.c */
extern int default_goto(int symbol);
extern int is_C_identifier(char *name);
extern int matching_vector(int vector);
extern int pack_vector(int vector);
extern void free_itemsets(void);
extern void free_reductions(void);
extern void free_shifts(void);
extern void goto_actions(void);
extern void output(void);
extern void output_actions(void);
extern void output_base(void);
extern void output_check(void);
extern void output_debug(void);
extern void output_defines(void);
extern void output_prefix(void);
extern void output_rule_data(void);
extern void output_semantic_actions(void);
extern void output_stored_text(void);
extern void output_stype(void);
extern void output_table(void);
extern void output_trailing_text(void);
extern void output_yydefred(void);
extern void pack_table(void);
extern void save_column(int symbol, int default_state);
extern void sort_actions(void);
extern void token_actions(void);

/* reader.c */
extern bucket * get_literal(void);
extern bucket * get_name(void);
extern char * dup_line(void);
extern char * get_tag(void);
extern int get_number(void);
extern int hexval(int c);
extern int is_reserved(char *name);
extern int keyword(void);
extern int mark_symbol(void);
extern int nextc(void);
extern void add_symbol(void);
extern void advance_to_start(void);
extern void cachec(int c);
extern void check_symbols(void);
extern void copy_action(void);
extern void copy_ident(void);
extern void copy_text(void);
extern void copy_union(void);
extern void declare_start(void);
extern void declare_tokens(int assoc);
extern void declare_types(void);
extern void end_rule(void);
extern void expand_items(void);
extern void expand_rules(void);
extern void free_tags(void);
extern void get_line(void);
extern void initialize_grammar(void);
extern void insert_empty_rule(void);
extern void pack_grammar(void);
extern void pack_names(void);
extern void pack_symbols(void);
extern void print_grammar(void);
extern void read_declarations(void);
extern void read_grammar(void);
extern void reader(void);
extern void skip_comment(void);
extern void start_rule(bucket *bp, int s_lineno);

/* skeleton.c */
extern void write_section(char *section[]);

/* verbose.c */
extern void log_conflicts(void);
extern void log_unused(void);
extern void print_actions(int stateno);
extern void print_conflicts(int state);
extern void print_core(int state);
extern void print_gotos(int stateno);
extern void print_nulls(int state);
extern void print_reductions(action *p, int defred2);
extern void print_shifts(action *p);
extern void print_state(int state);
extern void verbose(void);

/* warshall.c */
extern void reflexive_transitive_closure(unsigned *R, int n);
extern void transitive_closure(unsigned *R, int n);
