/*
   File:   system.h
   Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
   Brief: system-dependent declarations; include this first.
   right after <config.h>

   Copyright 1996, 2005, 2006, 2007, 2008, 2013, 2014 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

#ifndef SYSTEM_H
#define SYSTEM_H

/* Assume ANSI C89 headers are available.  */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Use POSIX headers.  If they are not available, we use the substitute
   provided by gnulib.  */
#include <getopt.h>
#include <unistd.h>
#include <termios.h>

/* Unicode. */
#include <wchar.h>
#include <wctype.h>

/* Windows includes */
#if defined(_WIN32)
#include <windows.h>
#endif

/* Internationalization.  */
#include "gettext.h"
#define _(str) gettext (str)
#define N_(str) gettext_noop (str)

/* Check for errors on write.  */
#include "closeout.h"

/* Errors handling*/
#include "error.h"
#include "assert.h"

/* Other includes  */
#include "configmake.h"
#include "dirname.h"
#include "progname.h"


#endif /* SYSTEM_H */
