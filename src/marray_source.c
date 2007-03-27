/* jbc_marray/jbc_marray_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005, 2007 Jordi Burguet-Castell
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to:
 *   Free Software Foundation, Inc.
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 */

#include <gsl/gsl_check_range.h>

#ifndef HIDE_INLINE_STATIC
size_t
FUNCTION(jbc_marray, position) (const size_t * indices, const TYPE (jbc_marray) * t)
{
  size_t shift, position;
  unsigned int i;

  shift = t->size;
  position = 0;
  for (i = 0; i < t->rank; i++)
    {
      if (gsl_check_range)
        if (indices[i] >= t->dimension[i])
          return t->size;

      shift /= t->dimension[i];
      position += shift * indices[i];
    }

  return position;
}


BASE
FUNCTION(jbc_marray, get) (const TYPE (jbc_marray) * t, const size_t * indices)
{
  size_t position;

  position = FUNCTION(jbc_marray, position) (indices, t);
  if (gsl_check_range)
    if (position >= t->size)
      GSL_ERROR_VAL("index out of range", GSL_EINVAL, 0);

  return *(BASE *) (t->data + MULTIPLICITY * position);
}


void
FUNCTION(jbc_marray, set) (TYPE (jbc_marray) * t, const size_t * indices, const BASE x)
{
  size_t position;

  position = FUNCTION(jbc_marray, position) (indices, t);
  if (gsl_check_range)
    if (position >= t->size)
      GSL_ERROR_VOID("index out of range", GSL_EINVAL);

  *(BASE *) (t->data + MULTIPLICITY * position) = x;
}


BASE *
FUNCTION(jbc_marray, ptr) (TYPE (jbc_marray) * t, const size_t * indices)
{
  size_t position;

  position = FUNCTION(jbc_marray, position) (indices, t);
  if (gsl_check_range)
    if (position >= t->size)
      GSL_ERROR_NULL("index out of range", GSL_EINVAL);

  return (BASE *) (t->data + MULTIPLICITY * position);
}


const BASE *
FUNCTION(jbc_marray, const_ptr) (const TYPE (jbc_marray) * t, const size_t * indices)
{
  size_t position;

  position = FUNCTION(jbc_marray, position) (indices, t);
  if (gsl_check_range)
    if (position >= t->size)
      GSL_ERROR_NULL("index out of range", GSL_EINVAL);

  return (const BASE *) (t->data + MULTIPLICITY * position);
}

#endif
