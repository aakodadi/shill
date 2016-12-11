/*
   File:   string_type.h
   Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>

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

#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#include <config.h>
#include "system.h"

#define STRING_CHUNK_SIZE 1024

#ifdef __cplusplus
extern "C"
{
#endif

  struct _string
  {
    char* s;
    unsigned long len;
  };

  typedef struct _string string;

  string string_create (const char* source);
  string string_n_create (const char* source, unsigned long size);
  string string_createf (const char* source, ...);
  unsigned long string_destroy (string* s);
  string string_cat (string s1, string s2);
  string string_catd (string* s1, string* s2);
  string string_cpy (string source);
  string string_cpyd (string* source);
  int string_cmp (string s1, string s2);
  string string_from_unsigned_long (unsigned long n);
  string string_gets (unsigned long max_size);
  string string_getpass (unsigned long max_size);


#ifdef __cplusplus
}
#endif

#endif /* STRING_TYPE_H */
