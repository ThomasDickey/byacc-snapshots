#!/bin/sh
# $Id: run_test.sh,v 1.13 2014/03/29 11:38:48 tom Exp $
# vi:ts=4 sw=4:

if test $# = 1
then
	PROG_DIR=`pwd`
	TEST_DIR=$1
	PROG_DIR=`echo "$PROG_DIR" | sed -e 's/ /\\\\ /g'`
	TEST_DIR=`echo "$TEST_DIR" | sed -e 's/ /\\\\ /g'`
else
	PROG_DIR=..
	TEST_DIR=.
fi

YACC=$PROG_DIR/yacc

tmpfile=temp$$

ifBTYACC=`fgrep -l 'define YYBTYACC' config.h > /dev/null; test $? != 0; echo $?`

if test $ifBTYACC = 0; then
	REF_DIR=${TEST_DIR}/yacc
else
	REF_DIR=${TEST_DIR}/btyacc
fi

rm -f ${REF_DIR}/test-*

echo '** '`date`
for input in ${TEST_DIR}/*.y
do
	case $input in
	test-*)
		echo "?? ignored $input"
		;;
	*)
		root=`basename $input .y`
		ROOT="test-$root"
		prefix=${root}_

		OPTS=
		OPT2=
		TYPE=".error .output .tab.c .tab.h"
		case $input in
		${TEST_DIR}/btyacc_*)
			if test $ifBTYACC = 0; then continue; fi
			OPTS="$OPTS -B"
			prefix=`echo "$prefix" | sed -e 's/^btyacc_//'`
			;;
		${TEST_DIR}/grammar*)
			OPTS="$OPTS -g"
			TYPE="$TYPE .dot"
			;;
		${TEST_DIR}/code_*)
			OPTS="$OPTS -r"
			TYPE="$TYPE .code.c"
			prefix=`echo "$prefix" | sed -e 's/^code_//'`
			;;
		${TEST_DIR}/pure_*)
			OPTS="$OPTS -P"
			prefix=`echo "$prefix" | sed -e 's/^pure_//'`
			;;
		${TEST_DIR}/quote_*)
			OPT2="-s"
			;;
		${TEST_DIR}/inherit*|\
		${TEST_DIR}/err_inherit*)
			if test $ifBTYACC = 0; then continue; fi
			;;
		esac

		for opt2 in "" $OPT2
		do
			$YACC $OPTS $opt2 -v -d -p $prefix -b $ROOT${opt2} $input 2>&1 | sed -e "s%$YACC%YACC%" >${ROOT}${opt2}.error
			for type in $TYPE
			do
				REF=${REF_DIR}/${root}${opt2}${type}
				NEW=${ROOT}${opt2}${type}
				mv -f $NEW ${REF_DIR}
				CMP=${REF_DIR}/${NEW}
				if test ! -f $CMP
				then
					echo "...not found $CMP"
				else
					sed	-e s,$NEW,$REF, \
						-e /YYPATCH/d \
						-e 's,#line \([1-9][0-9]*\) "'$REF_DIR'/,#line \1 ",' \
						-e 's,#line \([1-9][0-9]*\) "'$TEST_DIR'/,#line \1 ",' \
						< $CMP >$tmpfile \
						&& mv $tmpfile $CMP
					if test ! -f $REF
					then
						mv $CMP $REF
						echo "...saved $REF"
					elif ( cmp -s $REF $CMP )
					then
						echo "...ok $REF"
						rm -f $CMP
					else
						echo "...diff $REF"
						diff -u $REF $CMP
					fi
				fi
			done
		done
		;;
	esac
done
