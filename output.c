/* $Id: output.c,v 1.19 2009/02/22 00:06:43 tom Exp $ */

#include "defs.h"

static int nvectors;
static int nentries;
static short **froms;
static short **tos;
static short *tally;
static short *width;
static short *state_count;
static short *order;
static short *base;
static short *pos;
static int maxtable;
static short *table;
static short *check;
static int lowzero;
static int high;

static void
write_char(FILE * out, int c)
{
    if (c == '\n')
	++outline;
    putc(c, out);
}

static void
write_code_lineno(FILE * out)
{
    if (!lflag)
	fprintf(out, line_format, (outline++) + 1, code_file_name);
}

static void
write_input_lineno(FILE * out)
{
    if (!lflag)
    {
	++outline;
	fprintf(out, line_format, lineno, input_file_name);
    }
}

static void
define_prefixed(const char *name)
{
    ++outline;
    fprintf(code_file, "#define %-10s %s%s\n", name, symbol_prefix, name + 2);
}

static void
output_prefix(void)
{
    if (symbol_prefix == NULL)
	symbol_prefix = "yy";
    else
    {
	define_prefixed("yyparse");
	define_prefixed("yylex");
	define_prefixed("yyerror");
	define_prefixed("yychar");
	define_prefixed("yyval");
	define_prefixed("yylval");
	define_prefixed("yydebug");
	define_prefixed("yynerrs");
	define_prefixed("yyerrflag");
	define_prefixed("yyss");
	define_prefixed("yyssp");
	define_prefixed("yyvs");
	define_prefixed("yyvsp");
	define_prefixed("yylhs");
	define_prefixed("yylen");
	define_prefixed("yydefred");
	define_prefixed("yydgoto");
	define_prefixed("yysindex");
	define_prefixed("yyrindex");
	define_prefixed("yygindex");
	define_prefixed("yytable");
	define_prefixed("yycheck");
	define_prefixed("yyname");
	define_prefixed("yyrule");
    }
    ++outline;
    fprintf(code_file, "#define YYPREFIX \"%s\"\n", symbol_prefix);
}

static void
output_newline(void)
{
    if (!rflag)
	++outline;
    putc('\n', output_file);
}

static void
output_line(const char *value)
{
    fputs(value, output_file);
    output_newline();
}

static void
output_int(int value)
{
    fprintf(output_file, "%5d,", value);
}

static void
start_int_table(const char *name, int value)
{
    int need = 34 - (int)(strlen(symbol_prefix) + strlen(name));

    if (need < 6)
	need = 6;
    fprintf(output_file,
	    "static const short %s%s[] = {%*d,",
	    symbol_prefix, name, need, value);
}

static void
start_str_table(const char *name)
{
    fprintf(output_file,
	    "static const char *%s%s[] = {",
	    symbol_prefix, name);
    output_newline();
}

static void
end_table(void)
{
    output_newline();
    output_line("};");
}

static void
output_rule_data(void)
{
    int i;
    int j;

    start_int_table("lhs", symbol_value[start_symbol]);

    j = 10;
    for (i = 3; i < nrules; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(symbol_value[rlhs[i]]);
    }
    end_table();

    start_int_table("len", 2);

    j = 10;
    for (i = 3; i < nrules; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    j++;

	output_int(rrhs[i + 1] - rrhs[i] - 1);
    }
    end_table();
}

static void
output_yydefred(void)
{
    int i, j;

    start_int_table("defred", (defred[0] ? defred[0] - 2 : 0));

    j = 10;
    for (i = 1; i < nstates; i++)
    {
	if (j < 10)
	    ++j;
	else
	{
	    output_newline();
	    j = 1;
	}

	output_int((defred[i] ? defred[i] - 2 : 0));
    }

    end_table();
}

static void
token_actions(void)
{
    int i, j;
    int shiftcount, reducecount;
    int max, min;
    short *actionrow, *r, *s;
    action *p;

    actionrow = NEW2(2 * ntokens, short);
    for (i = 0; i < nstates; ++i)
    {
	if (parser[i])
	{
	    for (j = 0; j < 2 * ntokens; ++j)
		actionrow[j] = 0;

	    shiftcount = 0;
	    reducecount = 0;
	    for (p = parser[i]; p; p = p->next)
	    {
		if (p->suppressed == 0)
		{
		    if (p->action_code == SHIFT)
		    {
			++shiftcount;
			actionrow[p->symbol] = p->number;
		    }
		    else if (p->action_code == REDUCE && p->number != defred[i])
		    {
			++reducecount;
			actionrow[p->symbol + ntokens] = p->number;
		    }
		}
	    }

	    tally[i] = shiftcount;
	    tally[nstates + i] = reducecount;
	    width[i] = 0;
	    width[nstates + i] = 0;
	    if (shiftcount > 0)
	    {
		froms[i] = r = NEW2(shiftcount, short);
		tos[i] = s = NEW2(shiftcount, short);
		min = MAXSHORT;
		max = 0;
		for (j = 0; j < ntokens; ++j)
		{
		    if (actionrow[j])
		    {
			if (min > symbol_value[j])
			    min = symbol_value[j];
			if (max < symbol_value[j])
			    max = symbol_value[j];
			*r++ = symbol_value[j];
			*s++ = actionrow[j];
		    }
		}
		width[i] = max - min + 1;
	    }
	    if (reducecount > 0)
	    {
		froms[nstates + i] = r = NEW2(reducecount, short);
		tos[nstates + i] = s = NEW2(reducecount, short);
		min = MAXSHORT;
		max = 0;
		for (j = 0; j < ntokens; ++j)
		{
		    if (actionrow[ntokens + j])
		    {
			if (min > symbol_value[j])
			    min = symbol_value[j];
			if (max < symbol_value[j])
			    max = symbol_value[j];
			*r++ = symbol_value[j];
			*s++ = actionrow[ntokens + j] - 2;
		    }
		}
		width[nstates + i] = max - min + 1;
	    }
	}
    }
    FREE(actionrow);
}

static int
default_goto(int symbol)
{
    int i;
    int m;
    int n;
    int default_state;
    int max;

    m = goto_map[symbol];
    n = goto_map[symbol + 1];

    if (m == n)
	return (0);

    for (i = 0; i < nstates; i++)
	state_count[i] = 0;

    for (i = m; i < n; i++)
	state_count[to_state[i]]++;

    max = 0;
    default_state = 0;
    for (i = 0; i < nstates; i++)
    {
	if (state_count[i] > max)
	{
	    max = state_count[i];
	    default_state = i;
	}
    }

    return (default_state);
}

static void
save_column(int symbol, int default_state)
{
    int i;
    int m;
    int n;
    short *sp;
    short *sp1;
    short *sp2;
    int count;
    int symno;

    m = goto_map[symbol];
    n = goto_map[symbol + 1];

    count = 0;
    for (i = m; i < n; i++)
    {
	if (to_state[i] != default_state)
	    ++count;
    }
    if (count == 0)
	return;

    symno = symbol_value[symbol] + 2 * nstates;

    froms[symno] = sp1 = sp = NEW2(count, short);
    tos[symno] = sp2 = NEW2(count, short);

    for (i = m; i < n; i++)
    {
	if (to_state[i] != default_state)
	{
	    *sp1++ = from_state[i];
	    *sp2++ = to_state[i];
	}
    }

    tally[symno] = count;
    width[symno] = sp1[-1] - sp[0] + 1;
}

static void
goto_actions(void)
{
    int i, j, k;

    state_count = NEW2(nstates, short);

    k = default_goto(start_symbol + 1);
    start_int_table("dgoto", k);
    save_column(start_symbol + 1, k);

    j = 10;
    for (i = start_symbol + 2; i < nsyms; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	k = default_goto(i);
	output_int(k);
	save_column(i, k);
    }

    end_table();
    FREE(state_count);
}

static void
sort_actions(void)
{
    int i;
    int j;
    int k;
    int t;
    int w;

    order = NEW2(nvectors, short);
    nentries = 0;

    for (i = 0; i < nvectors; i++)
    {
	if (tally[i] > 0)
	{
	    t = tally[i];
	    w = width[i];
	    j = nentries - 1;

	    while (j >= 0 && (width[order[j]] < w))
		j--;

	    while (j >= 0 && (width[order[j]] == w) && (tally[order[j]] < t))
		j--;

	    for (k = nentries - 1; k > j; k--)
		order[k + 1] = order[k];

	    order[j + 1] = i;
	    nentries++;
	}
    }
}

/*  The function matching_vector determines if the vector specified by	*/
/*  the input parameter matches a previously considered	vector.  The	*/
/*  test at the start of the function checks if the vector represents	*/
/*  a row of shifts over terminal symbols or a row of reductions, or a	*/
/*  column of shifts over a nonterminal symbol.  Berkeley Yacc does not	*/
/*  check if a column of shifts over a nonterminal symbols matches a	*/
/*  previously considered vector.  Because of the nature of LR parsing	*/
/*  tables, no two columns can match.  Therefore, the only possible	*/
/*  match would be between a row and a column.  Such matches are	*/
/*  unlikely.  Therefore, to save time, no attempt is made to see if a	*/
/*  column matches a previously considered vector.			*/
/*									*/
/*  Matching_vector is poorly designed.  The test could easily be made	*/
/*  faster.  Also, it depends on the vectors being in a specific	*/
/*  order.								*/

static int
matching_vector(int vector)
{
    int i;
    int j;
    int k;
    int t;
    int w;
    int match;
    int prev;

    i = order[vector];
    if (i >= 2 * nstates)
	return (-1);

    t = tally[i];
    w = width[i];

    for (prev = vector - 1; prev >= 0; prev--)
    {
	j = order[prev];
	if (width[j] != w || tally[j] != t)
	    return (-1);

	match = 1;
	for (k = 0; match && k < t; k++)
	{
	    if (tos[j][k] != tos[i][k] || froms[j][k] != froms[i][k])
		match = 0;
	}

	if (match)
	    return (j);
    }

    return (-1);
}

static int
pack_vector(int vector)
{
    int i, j, k, l;
    int t;
    int loc;
    int ok;
    short *from;
    short *to;
    int newmax;

    i = order[vector];
    t = tally[i];
    assert(t);

    from = froms[i];
    to = tos[i];

    j = lowzero - from[0];
    for (k = 1; k < t; ++k)
	if (lowzero - from[k] > j)
	    j = lowzero - from[k];
    for (;; ++j)
    {
	if (j == 0)
	    continue;
	ok = 1;
	for (k = 0; ok && k < t; k++)
	{
	    loc = j + from[k];
	    if (loc >= maxtable - 1)
	    {
		if (loc >= MAXTABLE - 1)
		    fatal("maximum table size exceeded");

		newmax = maxtable;
		do
		{
		    newmax += 200;
		}
		while (newmax <= loc);
		table = (short *)REALLOC(table, newmax * sizeof(short));
		if (table == 0)
		    no_space();
		check = (short *)REALLOC(check, newmax * sizeof(short));
		if (check == 0)
		    no_space();
		for (l = maxtable; l < newmax; ++l)
		{
		    table[l] = 0;
		    check[l] = -1;
		}
		maxtable = newmax;
	    }

	    if (check[loc] != -1)
		ok = 0;
	}
	for (k = 0; ok && k < vector; k++)
	{
	    if (pos[k] == j)
		ok = 0;
	}
	if (ok)
	{
	    for (k = 0; k < t; k++)
	    {
		loc = j + from[k];
		table[loc] = to[k];
		check[loc] = from[k];
		if (loc > high)
		    high = loc;
	    }

	    while (check[lowzero] != -1)
		++lowzero;

	    return (j);
	}
    }
}

static void
pack_table(void)
{
    int i;
    int place;
    int state;

    base = NEW2(nvectors, short);
    pos = NEW2(nentries, short);

    maxtable = 1000;
    table = NEW2(maxtable, short);
    check = NEW2(maxtable, short);

    lowzero = 0;
    high = 0;

    for (i = 0; i < maxtable; i++)
	check[i] = -1;

    for (i = 0; i < nentries; i++)
    {
	state = matching_vector(i);

	if (state < 0)
	    place = pack_vector(i);
	else
	    place = base[state];

	pos[i] = place;
	base[order[i]] = place;
    }

    for (i = 0; i < nvectors; i++)
    {
	if (froms[i])
	    FREE(froms[i]);
	if (tos[i])
	    FREE(tos[i]);
    }

    FREE(froms);
    FREE(tos);
    FREE(pos);
}

static void
output_base(void)
{
    int i, j;

    start_int_table("sindex", base[0]);

    j = 10;
    for (i = 1; i < nstates; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(base[i]);
    }

    end_table();

    start_int_table("rindex", base[nstates]);

    j = 10;
    for (i = nstates + 1; i < 2 * nstates; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(base[i]);
    }

    end_table();

    start_int_table("gindex", base[2 * nstates]);

    j = 10;
    for (i = 2 * nstates + 1; i < nvectors - 1; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(base[i]);
    }

    end_table();
    FREE(base);
}

static void
output_table(void)
{
    int i;
    int j;

    ++outline;
    fprintf(code_file, "#define YYTABLESIZE %d\n", high);
    start_int_table("table", table[0]);

    j = 10;
    for (i = 1; i <= high; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(table[i]);
    }

    end_table();
    FREE(table);
}

static void
output_check(void)
{
    int i;
    int j;

    start_int_table("check", check[0]);

    j = 10;
    for (i = 1; i <= high; i++)
    {
	if (j >= 10)
	{
	    output_newline();
	    j = 1;
	}
	else
	    ++j;

	output_int(check[i]);
    }

    end_table();
    FREE(check);
}

static void
output_actions(void)
{
    nvectors = 2 * nstates + nvars;

    froms = NEW2(nvectors, short *);
    tos = NEW2(nvectors, short *);
    tally = NEW2(nvectors, short);
    width = NEW2(nvectors, short);

    token_actions();
    FREE(lookaheads);
    FREE(LA);
    FREE(LAruleno);
    FREE(accessing_symbol);

    goto_actions();
    FREE(goto_map + ntokens);
    FREE(from_state);
    FREE(to_state);

    sort_actions();
    pack_table();
    output_base();
    output_table();
    output_check();
}

static int
is_C_identifier(char *name)
{
    char *s;
    int c;

    s = name;
    c = *s;
    if (c == '"')
    {
	c = *++s;
	if (!isalpha(c) && c != '_' && c != '$')
	    return (0);
	while ((c = *++s) != '"')
	{
	    if (!isalnum(c) && c != '_' && c != '$')
		return (0);
	}
	return (1);
    }

    if (!isalpha(c) && c != '_' && c != '$')
	return (0);
    while ((c = *++s) != 0)
    {
	if (!isalnum(c) && c != '_' && c != '$')
	    return (0);
    }
    return (1);
}

static void
output_defines(void)
{
    int c, i;
    char *s;

    for (i = 2; i < ntokens; ++i)
    {
	s = symbol_name[i];
	if (is_C_identifier(s))
	{
	    fprintf(code_file, "#define ");
	    if (dflag)
		fprintf(defines_file, "#define ");
	    c = *s;
	    if (c == '"')
	    {
		while ((c = *++s) != '"')
		{
		    putc(c, code_file);
		    if (dflag)
			putc(c, defines_file);
		}
	    }
	    else
	    {
		do
		{
		    putc(c, code_file);
		    if (dflag)
			putc(c, defines_file);
		}
		while ((c = *++s) != 0);
	    }
	    ++outline;
	    fprintf(code_file, " %d\n", symbol_value[i]);
	    if (dflag)
		fprintf(defines_file, " %d\n", symbol_value[i]);
	}
    }

    ++outline;
    fprintf(code_file, "#define YYERRCODE %d\n", symbol_value[1]);

    if (dflag && unionized)
    {
	rewind(union_file);
	while ((c = getc(union_file)) != EOF)
	    putc(c, defines_file);
	fprintf(defines_file, " YYSTYPE;\nextern YYSTYPE %slval;\n",
		symbol_prefix);
    }
}

static void
output_stored_text(void)
{
    int c;
    FILE *in, *out;

    rewind(text_file);
    if (text_file == NULL)
	open_error("text_file");
    in = text_file;
    if ((c = getc(in)) == EOF)
	return;
    out = code_file;
    write_char(out, c);
    while ((c = getc(in)) != EOF)
    {
	write_char(out, c);
    }
    write_code_lineno(out);
}

static void
output_debug(void)
{
    int i, j, k, max;
    const char **symnam;
    const char *s;

    ++outline;
    fprintf(code_file, "#define YYFINAL %d\n", final_state);

    outline += 3;
    fprintf(code_file, "#ifndef YYDEBUG\n#define YYDEBUG %d\n#endif\n", tflag);

    if (rflag)
    {
	fprintf(output_file, "#ifndef YYDEBUG\n");
	fprintf(output_file, "#define YYDEBUG %d\n", tflag);
	fprintf(output_file, "#endif\n");
    }

    max = 0;
    for (i = 2; i < ntokens; ++i)
	if (symbol_value[i] > max)
	    max = symbol_value[i];

    ++outline;
    fprintf(code_file, "#define YYMAXTOKEN %d\n", max);

    symnam = (const char **)MALLOC((max + 1) * sizeof(char *));
    if (symnam == 0)
	no_space();

    /* Note that it is  not necessary to initialize the element         */
    /* symnam[max].                                                     */
    for (i = 0; i < max; ++i)
	symnam[i] = 0;
    for (i = ntokens - 1; i >= 2; --i)
	symnam[symbol_value[i]] = symbol_name[i];
    symnam[0] = "end-of-file";

    output_line("#if YYDEBUG");

    start_str_table("name");
    j = 80;
    for (i = 0; i <= max; ++i)
    {
	if ((s = symnam[i]) != 0)
	{
	    if (s[0] == '"')
	    {
		k = 7;
		while (*++s != '"')
		{
		    ++k;
		    if (*s == '\\')
		    {
			k += 2;
			if (*++s == '\\')
			    ++k;
		    }
		}
		j += k;
		if (j > 80)
		{
		    output_newline();
		    j = k;
		}
		fprintf(output_file, "\"\\\"");
		s = symnam[i];
		while (*++s != '"')
		{
		    if (*s == '\\')
		    {
			fprintf(output_file, "\\\\");
			if (*++s == '\\')
			    fprintf(output_file, "\\\\");
			else
			    putc(*s, output_file);
		    }
		    else
			putc(*s, output_file);
		}
		fprintf(output_file, "\\\"\",");
	    }
	    else if (s[0] == '\'')
	    {
		if (s[1] == '"')
		{
		    j += 7;
		    if (j > 80)
		    {
			output_newline();
			j = 7;
		    }
		    fprintf(output_file, "\"'\\\"'\",");
		}
		else
		{
		    k = 5;
		    while (*++s != '\'')
		    {
			++k;
			if (*s == '\\')
			{
			    k += 2;
			    if (*++s == '\\')
				++k;
			}
		    }
		    j += k;
		    if (j > 80)
		    {
			output_newline();
			j = k;
		    }
		    fprintf(output_file, "\"'");
		    s = symnam[i];
		    while (*++s != '\'')
		    {
			if (*s == '\\')
			{
			    fprintf(output_file, "\\\\");
			    if (*++s == '\\')
				fprintf(output_file, "\\\\");
			    else
				putc(*s, output_file);
			}
			else
			    putc(*s, output_file);
		    }
		    fprintf(output_file, "'\",");
		}
	    }
	    else
	    {
		k = strlen(s) + 3;
		j += k;
		if (j > 80)
		{
		    output_newline();
		    j = k;
		}
		putc('"', output_file);
		do
		{
		    putc(*s, output_file);
		}
		while (*++s);
		fprintf(output_file, "\",");
	    }
	}
	else
	{
	    j += 2;
	    if (j > 80)
	    {
		output_newline();
		j = 2;
	    }
	    fprintf(output_file, "0,");
	}
    }
    end_table();
    FREE(symnam);

    start_str_table("rule");
    for (i = 2; i < nrules; ++i)
    {
	fprintf(output_file, "\"%s :", symbol_name[rlhs[i]]);
	for (j = rrhs[i]; ritem[j] > 0; ++j)
	{
	    s = symbol_name[ritem[j]];
	    if (s[0] == '"')
	    {
		fprintf(output_file, " \\\"");
		while (*++s != '"')
		{
		    if (*s == '\\')
		    {
			if (s[1] == '\\')
			    fprintf(output_file, "\\\\\\\\");
			else
			    fprintf(output_file, "\\\\%c", s[1]);
			++s;
		    }
		    else
			putc(*s, output_file);
		}
		fprintf(output_file, "\\\"");
	    }
	    else if (s[0] == '\'')
	    {
		if (s[1] == '"')
		    fprintf(output_file, " '\\\"'");
		else if (s[1] == '\\')
		{
		    if (s[2] == '\\')
			fprintf(output_file, " '\\\\\\\\");
		    else
			fprintf(output_file, " '\\\\%c", s[2]);
		    s += 2;
		    while (*++s != '\'')
			putc(*s, output_file);
		    putc('\'', output_file);
		}
		else
		    fprintf(output_file, " '%c'", s[1]);
	    }
	    else
		fprintf(output_file, " %s", s);
	}
	fprintf(output_file, "\",");
	output_newline();
    }

    end_table();
    output_line("#endif");
}

static void
output_stype(void)
{
    if (!unionized && ntags == 0)
    {
	outline += 3;
	fprintf(code_file, "#ifndef YYSTYPE\ntypedef int YYSTYPE;\n#endif\n");
    }
}

static void
output_trailing_text(void)
{
    int c, last;
    FILE *in, *out;

    if (line == 0)
	return;

    in = input_file;
    out = code_file;
    c = *cptr;
    if (c == '\n')
    {
	++lineno;
	if ((c = getc(in)) == EOF)
	    return;
	write_input_lineno(out);
	write_char(out, c);
	last = c;
    }
    else
    {
	write_input_lineno(out);
	do
	{
	    putc(c, out);
	}
	while ((c = *++cptr) != '\n');
	write_char(out, c);
	last = '\n';
    }

    while ((c = getc(in)) != EOF)
    {
	write_char(out, c);
	last = c;
    }

    if (last != '\n')
    {
	write_char(out, '\n');
    }
    write_code_lineno(out);
}

static void
output_semantic_actions(void)
{
    int c, last;
    FILE *out;

    rewind(action_file);
    if ((c = getc(action_file)) == EOF)
	return;

    out = code_file;
    last = c;
    write_char(out, c);
    while ((c = getc(action_file)) != EOF)
    {
	write_char(out, c);
	last = c;
    }

    if (last != '\n')
    {
	write_char(out, '\n');
    }

    write_code_lineno(out);
}

static void
free_itemsets(void)
{
    core *cp, *next;

    FREE(state_table);
    for (cp = first_state; cp; cp = next)
    {
	next = cp->next;
	FREE(cp);
    }
}

static void
free_shifts(void)
{
    shifts *sp, *next;

    FREE(shift_table);
    for (sp = first_shift; sp; sp = next)
    {
	next = sp->next;
	FREE(sp);
    }
}

static void
free_reductions(void)
{
    reductions *rp, *next;

    FREE(reduction_table);
    for (rp = first_reduction; rp; rp = next)
    {
	next = rp->next;
	FREE(rp);
    }
}

void
output(void)
{
    free_itemsets();
    free_shifts();
    free_reductions();
    output_prefix();
    output_stored_text();
    output_defines();
    output_rule_data();
    output_yydefred();
    output_actions();
    free_parser();
    output_debug();
    output_stype();
    if (rflag)
	write_section(tables);
    write_section(header);
    output_trailing_text();
    write_section(body);
    output_semantic_actions();
    write_section(trailer);
}

#ifdef NO_LEAKS
void
output_leaks(void)
{
    DO_FREE(tally);
    DO_FREE(width);
    DO_FREE(order);
}
#endif
