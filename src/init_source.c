/* jbc_marray/init_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005 Jordi Burguet-Castell
 * based on the gsl_matrix code from Gerard Jungman, Brian Gough
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * This code follows as close as possible that of init_source.c in
 * the gsl/matrix directory
 */

#include "marray_utilities.h"

#include <string.h>  /* to use memcpy() */


/* ------ Allocation ------ */

/*
 * Allocate memory for a jbc_marray and return a pointer to it.
 */
TYPE(jbc_marray) *
FUNCTION(jbc_marray, alloc) (const unsigned int rank, const size_t * dimension)
{
  unsigned int i;
  size_t n;
  TYPE(jbc_marray) * t;

  for (i = 0; i < rank; i++)
    {
      if (dimension[i] == 0)
        GSL_ERROR_VAL ("jbc_marray dimension must be positive integer",
                       GSL_EINVAL, 0);
    }
  
  t = (TYPE(jbc_marray) *) malloc (sizeof (TYPE(jbc_marray)));

  if (t == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for jbc_marray struct",
		     GSL_ENOMEM, 0);
    }

  n = 1;
  for (i = 0; i < rank; i++)
    {
      n *= dimension[i];
    }

  n *= MULTIPLICITY;

  t->data = (ATOMIC *) malloc (n * sizeof (ATOMIC));

  if (t->data == 0)
    {
      GSL_ERROR_VAL ("failed to allocate space for data",
		     GSL_ENOMEM, 0);
    }

  t->rank = rank;
  t->dimension = (size_t *) malloc (rank * sizeof(size_t));
  for (i = 0; i < rank; i++)
    {
      t->dimension[i] = dimension[i];
    }
  t->size = n;

  return t;
}


/*
 * Same as jbc_marray_alloc, but put all elements to 0.
 */
TYPE(jbc_marray) *
FUNCTION(jbc_marray, calloc) (const unsigned int rank, const size_t * dimension)
{
  size_t i;
  size_t n;

  TYPE(jbc_marray) * t = FUNCTION(jbc_marray, alloc) (rank, dimension);

  if (t == 0)
    return NULL;
  
  /* initialize jbc_marray to zero */
  
  n = t->size;
  for (i = 0; i < n; i++)
    t->data[i] = 0;

  return t;
}


/*
 * Copy from an existing jbc_marray.
 */
TYPE(jbc_marray) *
FUNCTION(jbc_marray, copy) (TYPE(jbc_marray) * tt)
{
  unsigned int i;
  TYPE(jbc_marray) * t = FUNCTION(jbc_marray, alloc) (tt->rank, tt->dimension);

  if (t == 0)
    return NULL;
  
  memcpy(t->data, tt->data, sizeof(BASE) * tt->size);

  return t;
}


/*
 * Free memory.
 */
void
FUNCTION(jbc_marray, free) (TYPE(jbc_marray) * t)
{
  free(t->data);
  free(t->dimension);
  free(t);
}



/* ------ Conversions ------ */


/*
 * Convert a rank 2 jbc_marray to a matrix.
 */
TYPE (gsl_matrix) *
FUNCTION (jbc_marray, 2matrix) (TYPE (jbc_marray) * t)
{
  TYPE(gsl_matrix) * m;

  if (t->rank != 2)
    GSL_ERROR_NULL("jbc_marray of rank != 2", GSL_EINVAL);


  m = (TYPE (gsl_matrix) *) malloc (sizeof (TYPE (gsl_matrix)));
  if (m == 0)
    GSL_ERROR_VAL ("failed to allocate space for matrix struct",
                   GSL_ENOMEM, 0);

  m->data = t->data;
  m->size1 = t->dimension[0];
  m->size2 = t->dimension[1];
  m->tda = t->dimension[0];
  m->block = NULL;  /* note that this is no problem because owner=0 */
  m->owner = 0;

  return m;
}


/*
 * Convert a rank 1 jbc_marray to a vector.
 */
TYPE (gsl_vector) *
FUNCTION (jbc_marray, 2vector) (TYPE (jbc_marray) * t)
{
  TYPE(gsl_vector) * v;

  if (t->rank != 1)
    GSL_ERROR_NULL("jbc_marray of rank != 1", GSL_EINVAL);


  v = (TYPE (gsl_vector) *) malloc (sizeof (TYPE (gsl_vector)));
  if (v == 0)
    GSL_ERROR_VAL ("failed to allocate space for vector struct",
                   GSL_ENOMEM, 0);

  v->data = t->data;
  v->size = t->dimension[0];
  v->stride = 1;
  v->block = NULL;  /* note that this is no problem because owner=0 */
  v->owner = 0;

  return v;
}




/* ------ Operations ------ */


/*
 * t = 0  (all elements = 0)
 */
void
FUNCTION(jbc_marray, set_zero) (TYPE(jbc_marray) * t)
{
  ATOMIC * const data = t->data;
  size_t i, n;

  n = t->size;

  for (i = 0; i < n; i++)
    {
      *(BASE *) (data + MULTIPLICITY * i) = 0;
    }
}


/*
 * t_ijk = x  (for i,j,k = 0,1,...,dimension-1)
 */
void
FUNCTION(jbc_marray, set_all) (TYPE(jbc_marray) * t, BASE x)
{
  size_t i, n;
  ATOMIC * const data = t->data;

  n = t->size;
  for (i = 0; i < n; i += MULTIPLICITY)
    *(BASE *) (data + MULTIPLICITY * i) = x;
}
