/* marray/marray_complex_double.h
 *
 * Copyright (C) 2010 Jordi Burguet-Castell
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
#ifndef __MARRAY_COMPLEX_DOUBLE_H__
#define __MARRAY_COMPLEX_DOUBLE_H__

#include <stdlib.h>
#include <complex.h>

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
  complex double * data;
} marray_complex;


/*
 * There is not such a thing as "marray views", in contrast with the
 * case for gsl_matrix.
 */

/* Allocation */

marray_complex *
marray_complex_alloc(const unsigned int rank, const size_t * dimension);

marray_complex *
marray_complex_calloc(const unsigned int rank, const size_t * dimension);

marray_complex *
marray_complex_copy(marray_complex * t);

void marray_complex_free(marray_complex * t);


/* Views */

/*
 * There are no views.
 */


/* Conversions */

gsl_matrix_complex * marray_complex_2matrix(marray_complex * t);
gsl_vector_complex * marray_complex_2vector(marray_complex * t);


/* Operations */

complex double marray_complex_get(const marray_complex * t, const size_t * indices);
void marray_complex_set(marray_complex * t, const size_t * indices, const complex double x);


complex double * marray_complex_ptr(marray_complex * t, const size_t * indices);
const complex double * marray_complex_const_ptr(const marray_complex * t, const size_t * indices);

void marray_complex_set_zero(marray_complex * t);
void marray_complex_set_all(marray_complex * t, complex double x);

int marray_complex_fread(FILE * stream, marray_complex * t);
int marray_complex_fwrite(FILE * stream, const marray_complex * t);
int marray_complex_fscanf(FILE * stream, marray_complex * t);
int marray_complex_fprintf(FILE * stream, const marray_complex * t, const char * format);

int marray_complex_memcpy(marray_complex * dest, const marray_complex * src);
int marray_complex_swap(marray_complex * t1, marray_complex * t2);

int marray_complex_isnull(const marray_complex * t);

int marray_complex_add(marray_complex * a, const marray_complex * b);
int marray_complex_sub(marray_complex * a, const marray_complex * b);
int marray_complex_mul_elements(marray_complex * a, const marray_complex * b);
int marray_complex_div_elements(marray_complex * a, const marray_complex * b);
int marray_complex_scale(marray_complex * a, const double x);
int marray_complex_add_constant(marray_complex * a, const double x);


/* inline functions if you are using GCC */

#ifdef HAVE_INLINE
extern inline
size_t
marray_complex_position(const size_t * indices, const marray_complex * t)
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
complex double
marray_complex_get(const marray_complex * t, const size_t * indices)
{
  size_t position;

  position = marray_complex_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_VAL("index out of range", GSL_EINVAL, 0);
#endif

  return t->data[position];
}

extern inline
void
marray_complex_set(marray_complex * t, const size_t * indices, const complex double x)
{
  size_t position;

  position = marray_complex_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_VOID("index out of range", GSL_EINVAL);
#endif

  t->data[position] = x;
}


extern inline 
complex double *
marray_complex_ptr(marray_complex * t, const size_t * indices)
{
  size_t position;

  position = marray_complex_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_NULL("index out of range", GSL_EINVAL);
#endif

  return (complex double *) (t->data + position);
} 

extern inline 
const complex double *
marray_complex_const_ptr(const marray_complex * t, const size_t * indices)
{
  size_t position;

  position = marray_complex_position(indices, t);
#if GSL_RANGE_CHECK
  if (position >= t->size)
    GSL_ERROR_NULL("index out of range", GSL_EINVAL);
#endif

  return (const complex double *) (t->data + position);
} 

#endif

__END_DECLS

#endif /* __MARRAY_COMPLEX_DOUBLE_H__ */
