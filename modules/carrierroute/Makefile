# $Id: Makefile,v 1.6 2003/05/23 15:43:43 andrei Exp $
#
# carrierroute Makefile
#
# WARNING: do not run this directly, it should be run by the master Makefile

include ../../Makefile.defs

auto_gen=
NAME=carrierroute.so

DEFS+=-DKAMAILIO_MOD_INTERFACE

SERLIBPATH=../../lib
SER_LIBS+=$(SERLIBPATH)/trie/trie $(SERLIBPATH)/srdb1/srdb1 $(SERLIBPATH)/kmi/kmi $(SERLIBPATH)/kcore/kcore

include ../../Makefile.modules
