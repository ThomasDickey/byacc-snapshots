#!/bin/sh
# $Id: run_test.sh,v 1.1 2004/03/28 19:30:50 tom Exp $
#
echo '** '`date`
for i in *.y
do
	case $i in
	test*)
		echo "?? ignored $i"
		;;
	*)
		root=`basename $i .y`
		ROOT="test-$root"
		../yacc -v -d -b $ROOT $i
		for type in .output .tab.c .tab.h
		do
			REF=${root}${type}
			CMP=${ROOT}${type}
			if test ! -f $CMP ; then
				echo "...not found $CMP"
				continue
			fi
			sed -s s/$CMP/$REF/ $CMP >temp$$ \
				&& mv temp$$ $CMP
			if ( cmp -s $REF $CMP )
			then
				echo "...ok $REF"
				rm -f $CMP
			else
				echo "...diff $REF"
			fi
		done
		;;
	esac
done
