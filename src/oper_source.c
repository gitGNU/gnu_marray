/* marray/oper_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005, 2007 Jordi Burguet-Castell
 * based on the gsl_matrix code from Brian Gough
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

int 
FUNCTION(marray, add) (TYPE(marray) * a, const TYPE(marray) * b)
{
  unsigned int j;
  size_t i, n;

  if (a->rank != b->rank)
    GSL_ERROR ("marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("marray sizes are different", GSL_EBADLEN);

  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] += b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(marray, sub) (TYPE(marray) * a, const TYPE(marray) * b)
{
  unsigned int j;
  size_t i, n;

  if (a->rank != b->rank)
    GSL_ERROR ("marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("marray sizes are different", GSL_EBADLEN);
  
  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] -= b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(marray, mul_elements) (TYPE(marray) * a,
                                    const TYPE(marray) * b)
{
  unsigned int j;
  size_t i, n;


  if (a->rank != b->rank)
    GSL_ERROR ("marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("marray sizes are different", GSL_EBADLEN);

  
  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] *= b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(marray, div_elements) (TYPE(marray) * a,
                                    const TYPE(marray) * b)
{
  unsigned int j;
  size_t i, n;

  if (a->rank != b->rank)
    GSL_ERROR ("marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("marray sizes are different", GSL_EBADLEN);
  
  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] /= b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(marray, scale) (TYPE(marray) * a, const double x)
{
  size_t i, n;

  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] *= x;

  return GSL_SUCCESS;
}


int 
FUNCTION(marray, add_constant) (TYPE(marray) * a, const double x)
{
  size_t i, n;

  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] += x;

  return GSL_SUCCESS;
}
