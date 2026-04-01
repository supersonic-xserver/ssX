#!/bin/sh
#
# $XFree86: xc/programs/Xserver/hw/xfree86/doc/sgml/add.sh,v 1.5 2006/04/23 17:03:51 dawes Exp $
#

sgmlfile=index.sgml
pdfprefix=../PDF/

while [ $# -gt 1 ]; do
	case $1 in
	-f)
		shift
		sgmlfile="$1"
		;;
	-p)
		shift
		pdfprefix="$1"
		;;
	esac
	shift
done

name=`basename $1 .sgml`
sgmlfmt -f index $1 | \
	sed -e 's,<title>,<item><htmlurl name=",' \
	    -e 's,</title>," url="'$name.html'"> <htmlurl name="[PDF]" url="'$pdfprefix$name.pdf'">,' \
	    -e 's,<author>,<!-- ,' \
	    -e 's,</author>, -->,' \
	    -e 's,<date>,<!-- ,' \
	    -e 's,</date>, -->,' >> $sgmlfile
exit 0
