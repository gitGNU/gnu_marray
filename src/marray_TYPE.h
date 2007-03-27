/* marray/marray_NAME.h
 *
 * Copyright (C) 2003, 2004, 2007 Jordi Burguet-Castell
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

/*
 * This file contains the basic declarations for a marray.
 */
#ifndef __MARRAY_NAME_H__
#define __MARRAY_NAME_H__

#include <stdlib.h>


#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "marray_utilities.h"

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS


/*
 * A marray is a struct with the rank of the marray (number of
 * indices it has), an array with the number of elements available for
 * each index, and an array to store the n1*n2*...*nm values.
 *
 * For the moment, there is no tda, as opossed to matrices, because it
 * would complicate quite a bit the algorithms and probably it is not
 * worth it.
 */
typedef struct
{
  unsigned int rank;
  size_t * dimension;
  size_t size;
  TYPE * data;
} marray_NAME;


/*
 * There is not such a thing as "marray views", in contrast with the
 * case for gsl_matrix.
 */

/* Allocation */

marray_NAME *
marray_NAME_alloc(const unsigned int rank, const size_t * dimension);

marray_NAME *
marray_NAME_calloc(const unsigned int rank, const size_t * dimension);

marray_NAME *
marray_NAME_copy(marray_NAME * t);

void marray_NAME_free(marray_NAME * t);


/* Views */

/*
 * There are no views.
 */


/* Conversions */

gsl_matrix_NAME * marray_NAME_2matrix(marray_NAME * t);
gsl_vector_NAME * marray_NAME_2vector(marray_NAME * t);


/* Operations */

TYPE marray_NAME_get(const marray_NAME * t, const size_t * indices);
void marray_NAME_set(marray_NAME * t, const size_t * indices, const TYPE x);


TYPE * marray_NAME_ptr(marray_NAME * t, const size_t * indices);
const TYPE * marray_NAME_const_ptr(const marray_NAME * t, const size_t * indices);

void marray_NAME_set_zero(marray_NAME * t);
void marray_NAME_set_all(marray_NAME * t, TYPE x);

int marray_NAME_fread(FILE * stream, marray_NAME * t);
int marray_NAME_fwrite(FILE * stream, const marray_NAME * t);
int marray_NAME_fscanf(FILE * stream, marray_NAME * t);
int marray_NAME_fprintf(FILE * stream, const marray_NAME * t, const char * format);

int marray_NAME_memcpy(marray_NAME * dest, const marray_NAME * src);
int marray_NAME_swap(marray_NAME * t1, marray_NAME * t2);

TYPE marray_NAME_max(const marray_NAME * t);
TYPE marray_NAME_min(const marray_NAME * t);
void marray_NAME_minmax(const marray_NAME * t, TYPE * min_out, TYPE * max_out);

void marray_NAME_max_index(const marray_NAME * t, size_t * indices);
void marray_NAME_min_index(const marray_NAME * t, size_t * indices);
void marray_NAME_minmax_index(const marray_NAME * t, size_t * imin, size_t * imax);

int marray_NAME_isnull(const marray_NAME * t);

int marray_NAME_add(marray_NAME * a, const marray_NAME * b);
int marray_NAME_sub(marray_NAME * a, const marray_NAME * b);
int marray_NAME_mul_elements(marray_NAME * a, const marray_NAME * b);
int marray_NAME_div_elements(marray_NAME * a, const marray_NAME * b);
int marray_NAME_scale(marray_NAME * a, const double x);
int marray_NAME_add_constant(marray_NAME * a, const double x);


/* inline functions if you are using GCC */

#ifdef HAVE_INLINE
extern inline
size_t
marray_NAME_position(const size_t * indices, const marray_NAME * t)
{
  size_t shift, position;
  unsigned int i;

  shift = t->size;
  position = 0;
  for (i = 0; i < t->rank; i++)
    {
#if GSL_RANGE_CHECK
      if (indices[i] >= t->dimension[i])
        return t->size;
#endif
      shift /= t->dimension[i];
      position += shift * indices[i];
    }

  return position;
}


extern inline 
TYPE
marray_NAME_get(const marray_NAME * t, const size_t * indices)
{
  size_t position;

  position = marray_NAME_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_VAL("index out of range", GSL_EINVAL, 0);
#endif

  return t->data[position];
}


extern inline
void
marray_NAME_set(marray_NAME * t, const size_t * indices, const TYPE x)
{
  size_t position;
  
  position = marray_NAME_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_VOID("index out of range", GSL_EINVAL);
#endif

  t->data[position] = x;
}


extern inline 
TYPE *
marray_NAME_ptr(marray_NAME * t, const size_t * indices)
{
  size_t position;

  position = marray_NAME_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_NULL("index out of range", GSL_EINVAL);
#endif

  return (TYPE *) (t->data + position);
}


extern inline 
const TYPE *
marray_NAME_const_ptr(const marray_NAME * t, const size_t * indices)
{
  size_t position;

  position = marray_NAME_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_NULL("index out of range", GSL_EINVAL);
#endif

  return (const TYPE *) (t->data + position);
} 

#endif

__END_DECLS

#endif /* __MARRAY_NAME_H__ */
