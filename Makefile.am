# Process this file with automake to produce Makefile.in (in this,
# and all subdirectories).
# Makefile for the top-level directory of GNU shill.
#
# Copyright 1997, 1998, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2013,
# 2014 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Find gnulib headers.
ACLOCAL_AMFLAGS = -I m4 --install

AM_CPPFLAGS = -Ilib -I$(top_srcdir)/lib -Isrc -I$(top_srcdir)/src

# Additional files to distribute.
EXTRA_DIST = \
	README-dev \
	ChangeLog.O \
	m4/gnulib-cache.m4 \
	man/shill.x \
	contrib/de_franconian_po.txt \
	contrib/evolution.txt

# Subdirectories to descend into.
SUBDIRS = po

MODULES_SOURCES = \
  src/argument/argument.c \
  src/argument/argument.h \
  src/command/command.c \
  src/command/command.h \
  src/configuration/configuration.c \
  src/configuration/configuration.h \
  src/service/service.c \
  src/service/service.h \
  src/service/repository.c \
  src/service/repository.h \
  src/error/error.c \
  src/error/error.h \
  src/type/string.c \
  src/type/string.h \
  src/model/timestamp.h \
  src/model/user.c \
  src/model/user.h \
  src/model/post.c \
  src/model/post.h \
  src/model/post_collection.c \
  src/model/post_collection.h


bin_PROGRAMS = shill
shill_SOURCES = \
  src/main.c \
  $(MODULES_SOURCES)

shill_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@

shill_LDADD = \
	$(LIBINTL) $(top_builddir)/lib/lib$(PACKAGE).a \
  @CURL_LIBS@ \
  @JANSSON_LIBS@

localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

CLEANFILES =

if !GIT_CROSS_COMPILING
man_MANS = shill.1
EXTRA_DIST += $(man_MANS)
endif

if BUILD_FROM_GIT
shill.1: shill
	$(HELP2MAN) --include=$(top_srcdir)/man/shill.x $(top_builddir)/shill -o $@-t
	chmod a=r $@-t
	mv -f $@-t $@

CLEANFILES += $(man_MANS)
endif

noinst_LIBRARIES =
MOSTLYCLEANFILES =
MOSTLYCLEANDIRS =
BUILT_SOURCES =
SUFFIXES =

TESTS = \
  string_type_cunit_test \
  configuration_cunit_test \
  repository_cunit_test \
  post_model_cunit_test \
  user_model_cunit_test \
  post_collection_model_cunit_test

check_PROGRAMS = \
  $(TESTS)

string_type_cunit_test_SOURCES = \
  test/string_type_cunit_test.c \
  $(MODULES_SOURCES)

configuration_cunit_test_SOURCES = \
  test/configuration_cunit_test.c \
  $(MODULES_SOURCES)

repository_cunit_test_SOURCES = \
  test/repository_cunit_test.c \
  $(MODULES_SOURCES)

user_model_cunit_test_SOURCES = \
  test/user_model_cunit_test.c \
  $(MODULES_SOURCES)

post_model_cunit_test_SOURCES = \
  test/post_model_cunit_test.c \
  $(MODULES_SOURCES)

post_collection_model_cunit_test_SOURCES = \
  test/post_collection_model_cunit_test.c \
  $(MODULES_SOURCES)

string_type_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
configuration_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
repository_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
post_model_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
user_model_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@
post_collection_model_cunit_test_CFLAGS = \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@ \
  @CUNIT_CFLAGS@

string_type_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
configuration_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
repository_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
post_model_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
user_model_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@
post_collection_model_cunit_test_LDADD = \
  @CURL_LIBS@ \
  @JANSSON_LIBS@ \
  @CUNIT_LIBS@



# Verify that all source files using _() are listed in po/POTFILES.in.
# The idea is to run this before making pretests, as well as official
# releases, so that translators will be sure to have all the messages.
# (From coreutils.)
po-check:
	if test -f po/POTFILES.in; then					\
	  grep -E -v '^(#|$$)' po/POTFILES.in				\
	    | grep -v '^src/false\.c$$' | sort > $@-1;			\
	  files=;							\
	  for file in $$($(CVS_LIST_EXCEPT)) `find * -name '*.[ch]'`; do \
	    case $$file in						\
	    gnulib/* | man/*) continue;;				\
	    esac;							\
	    case $$file in						\
	    *.[ch])							\
	      base=`expr " $$file" : ' \(.*\)\..'`;			\
	      { test -f $$base.l || test -f $$base.y; } && continue;;	\
	    esac;							\
	    files="$$files $$file";					\
	  done;								\
	  grep -E -l '\b(N?_|gettext *)\([^)"]*("|$$)' $$files		\
	    | sort -u > $@-2;						\
	  diff -u $@-1 $@-2 || exit 1;					\
	  rm -f $@-1 $@-2;						\
	fi


# Example of updating the online web pages for the documentation
# with the gendocs.sh script; see
# http://www.gnu.org/prep/maintain/html_node/Invoking-gendocs_002esh.html
#
gendocs = build-aux/gendocs.sh
gendocs_envvars = GENDOCS_TEMPLATE_DIR=doc
#
manual = shill
manual_title=Shill, GNU Command line social network
email = $(PACKAGE_BUGREPORT)
gendocs_args = --email $(email) $(manual) $(manual_title)
#
www_target = $(HOME)/gnu/www/shill/manual
#
doctemp = doc/wwwtemp
wwwdoc:
	rm -rf $(doctemp) && mkdir $(doctemp)
	cd $(doctemp) \
	&& ln -s ../*.texi . \
	&& env $(gendocs_envvars) $(gendocs) $(gendocs_args)
	cp -arf $(doctemp)/manual/. $(www_target)
	ls -ltu $(www_target)/html_node | tail  # $VCS rm -f obsolete files
# followed by $VCS add of new files and cvs commit.

include $(top_srcdir)/lib/local.mk
include $(top_srcdir)/doc/local.mk

dist-hook: gen-ChangeLog

gen_start_date = 2011-12-17
.PHONY: gen-ChangeLog
gen-ChangeLog:
	$(AM_V_GEN)if test -d .git; then				\
	  log_fix="$(srcdir)/build-aux/git-log-fix";			\
	  test -e "$$log_fix"						\
	    && amend_git_log="--amend=$$log_fix"			\
	    || amend_git_log=;						\
	  $(top_srcdir)/build-aux/gitlog-to-changelog			\
	    $$amend_git_log --since=$(gen_start_date) > $(distdir)/cl-t && \
	    { rm -f $(distdir)/ChangeLog &&				\
	      mv $(distdir)/cl-t $(distdir)/ChangeLog; }		\
	fi
