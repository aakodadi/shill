/*
   File:   timestamp.h
   Author: Abdelhakim Akodadi <akodadi.abdelhakim@gmail.com>
   Brief: created_at and updated_at fields will be often used in this project.
   So lets go ahead and define them once for all. afterwards we will be
   dealing with just one timestamp field.

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

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "time.h"

#ifdef __cplusplus
extern "C"
{
#endif

  struct _timestamp
  {
    time_t created_at;
    time_t updated_at;
  };

  typedef struct _timestamp timestamp;


#ifdef __cplusplus
}
#endif

#endif /* TIMESTAMP_H */
