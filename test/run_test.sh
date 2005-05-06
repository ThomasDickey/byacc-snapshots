#!/bin/sh
# $Id: run_test.sh,v 1.2 2005/05/04 23:01:44 tom Exp $
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
			sed	-e s/$CMP/$REF/ \
				-e /YYPATCH/d \
				< $CMP >temp$$ \
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
