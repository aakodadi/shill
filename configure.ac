dnl Process this file with autoconf to produce a configure script.
dnl
dnl This file is free software; as a special exception the author gives
dnl unlimited permission to copy and/or distribute it, with or without
dnl modifications, as long as this notice is preserved.
dnl
dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
dnl implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

dnl Initialize "autoconf".
AC_INIT([GNU shill],
        [m4_esyscmd([build-aux/git-version-gen .tarball-version])],
        [akodadi.abdelhakim@gmail.com], [],
        [http://www.gnu.org/software/shill/])


dnl Put autotools auxiliary files in a subdir, so they don't clutter top dir.
dnl Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

dnl Initialize "automake".
AM_INIT_AUTOMAKE([
        1.11.1
        subdir-objects
        -Wall
        -Werror
])

dnl Minimum Autoconf version required.
AC_PREREQ([2.62])

dnl Safety check - list a source file that wouldn't be in other directories.
AC_CONFIG_SRCDIR([src/main.c])

dnl Put configuration results here
AC_CONFIG_HEADERS([src/config.h])

dnl Checks for programs.
dnl We need a C compiler.
AC_PROG_CC

dnl We use gnulib
gl_EARLY
gl_INIT

dnl We want support for unusual archivers such as Microsoft lib
AM_PROG_AR

dnl Copyright will apply as long as these sources are in use, e.g., are
dnl being compiled, which is reasonable year to claim the copyright.
AC_DEFINE([COPYRIGHT_YEAR],
        [m4_esyscmd([date +%Y])],
        [year in copyright message])

dnl Are we building from git checked-out sources, or a tarball ?
dnl This is used in "Makefile.am" to avoid re-generating the manpage
dnl when building from tarballs.
AM_CONDITIONAL([BUILD_FROM_GIT], [test -d "$srcdir/.git"])
AM_CONDITIONAL([GIT_CROSS_COMPILING],
               [test -d "$srcdir/.git" && test $cross_compiling = yes])

dnl Checks for libraries.
PKG_CHECK_MODULES([CURL], [libcurl])
PKG_CHECK_MODULES([JANSSON], [jansson])
PKG_CHECK_MODULES([CUNIT], [cunit])

dnl Checks for header files.
dnl AC_CHECK_HEADERS([stddef.h stdlib.h string.h termios.h unistd.h])

dnl Checks for typedefs, structures, and compiler characteristics.
dnl AC_TYPE_SIZE_T

dnl Checks for library functions.
dnl AC_FUNC_MALLOC
dnl AC_CHECK_FUNCS([strerror])

dnl GNU help2man creates man pages from --help output; in many cases, this
dnl is sufficient, and obviates the need to maintain man pages separately.
dnl However, this means invoking executables, which we generally cannot do
dnl when cross-compiling, so we test to avoid that (the variable
dnl "cross_compiling" is set by AC_PROG_CC).
AS_IF([test $cross_compiling = no], [
  AM_MISSING_PROG([HELP2MAN], [help2man])
], [
  HELP2MAN=:
])

dnl i18n support from GNU gettext.
AM_GNU_GETTEXT_VERSION([0.19.7])
AM_GNU_GETTEXT([external])

dnl Put automake generated files results here
AC_CONFIG_FILES([Makefile
           po/Makefile.in
           lib/Makefile])

dnl copy configuration testing files
AC_CONFIG_LINKS([test/valid_config.json:test/valid_config.json])
AC_CONFIG_LINKS(
[test/valid_config_without_user.json:test/valid_config_without_user.json])

AC_OUTPUT
