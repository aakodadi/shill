# Process this file with automake to produce Makefile.in (in this,
# and all subdirectories).
# Makefile for the top-level directory of GNU shill.
#
# Copyright 1997, 1998, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2013,
# 2014, 2018 Free Software Foundation, Inc.
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
ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = \
  -DLOCALEDIR='"$(localedir)"' \
  -Ilib -I$(top_srcdir)/lib -I$(top_builddir)/lib \
  -Isrc -I$(top_srcdir)/src \
  -Iargument -I$(top_srcdir)/src/argument \
  -Icommand -I$(top_srcdir)/src/command \
  -Iconfiguration -I$(top_srcdir)/src/configuration \
  -Iservice -I$(top_srcdir)/src/service \
  -Itype -I$(top_srcdir)/src/type \
  -Imodel -I$(top_srcdir)/src/model \
  @CUNIT_CFLAGS@ \
  @CURL_CFLAGS@ \
  @JANSSON_CFLAGS@

LDADD = \
  $(LIBINTL) \
  $(top_builddir)/lib/lib$(PACKAGE).a \
  @CUNIT_LIBS@ \
  @CURL_LIBS@ \
  @JANSSON_LIBS@

# Additional files to distribute.
EXTRA_DIST = \
  README \
  README.md \
  README-dev \
  INSTALL \
  AUTHORS \
  COPYING \
  NEWS \
  ChangeLog.O \
  m4/gnulib-cache.m4 \
  man/shill.x \
  tests/valid_config.json \
  tests/valid_config_without_user.json \
  $(top_srcdir)/.version

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
  src/type/string_type.c \
  src/type/string_type.h \
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
  src/system.h \
  $(MODULES_SOURCES)

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
SUFFIXES =

BUILT_SOURCES = $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@

TESTS = \
  repository_cunit_test \
  string_type_cunit_test \
  configuration_cunit_test \
  post_model_cunit_test \
  user_model_cunit_test \
  post_collection_model_cunit_test

XFAIL_TESTS = \
  repository_cunit_test

check_PROGRAMS = \
  $(TESTS) \
  $(XFAIL_TESTS)

string_type_cunit_test_SOURCES = \
  tests/string_type_cunit_test.c \
  src/system.h \
  $(MODULES_SOURCES)

configuration_cunit_test_SOURCES = \
  tests/configuration_cunit_test.c \
  src/system.h \
  $(MODULES_SOURCES)

repository_cunit_test_SOURCES = \
  tests/repository_cunit_test.c \
  src/system.h \
  $(MODULES_SOURCES)

user_model_cunit_test_SOURCES = \
  tests/user_model_cunit_test.c \
  src/system.h \
  $(MODULES_SOURCES)

post_model_cunit_test_SOURCES = \
  tests/post_model_cunit_test.c \
  src/system.h \
  $(MODULES_SOURCES)

post_collection_model_cunit_test_SOURCES = \
  tests/post_collection_model_cunit_test.c \
  src/system.h \
  $(MODULES_SOURCES)


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

include $(top_srcdir)/doc/local.mk
include $(top_srcdir)/lib/local.mk

# include gnulib-tool generated makefile
include $(top_srcdir)/lib/gnulib.mk

dist-hook: gen-ChangeLog gen-tarball-version

.PHONY: gen-tarball-version
gen-tarball-version:
	echo $(VERSION) > $(distdir)/.tarball-version

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
