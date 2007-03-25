/* jbc_marray/oper_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005 Jordi Burguet-Castell
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

int 
FUNCTION(jbc_marray, add) (TYPE(jbc_marray) * a, const TYPE(jbc_marray) * b)
{
  unsigned int j;
  size_t i, n;

  if (a->rank != b->rank)
    GSL_ERROR ("jbc_marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("jbc_marray sizes are different", GSL_EBADLEN);

  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] += b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(jbc_marray, sub) (TYPE(jbc_marray) * a, const TYPE(jbc_marray) * b)
{
  unsigned int j;
  size_t i, n;


  if (a->rank != b->rank)
    GSL_ERROR ("jbc_marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("jbc_marray sizes are different", GSL_EBADLEN);
  
  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] -= b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(jbc_marray, mul_elements) (TYPE(jbc_marray) * a,
                                    const TYPE(jbc_marray) * b)
{
  unsigned int j;
  size_t i, n;


  if (a->rank != b->rank)
    GSL_ERROR ("jbc_marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("jbc_marray sizes are different", GSL_EBADLEN);

  
  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] *= b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(jbc_marray, div_elements) (TYPE(jbc_marray) * a,
                                    const TYPE(jbc_marray) * b)
{
  unsigned int j;
  size_t i, n;

  if (a->rank != b->rank)
    GSL_ERROR ("jbc_marrays have different number of indices", GSL_EBADLEN);

  for (j = 0; j < b->rank; j++)
    if (a->dimension[j] != b->dimension[j])
      GSL_ERROR ("jbc_marray sizes are different", GSL_EBADLEN);
  
  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] /= b->data[i];

  return GSL_SUCCESS;
}


int 
FUNCTION(jbc_marray, scale) (TYPE(jbc_marray) * a, const double x)
{
  size_t i, n;

  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] *= x;

  return GSL_SUCCESS;
}


int 
FUNCTION(jbc_marray, add_constant) (TYPE(jbc_marray) * a, const double x)
{
  size_t i, n;

  n = a->size;

  for (i = 0; i < n; i++)
    a->data[i] += x;

  return GSL_SUCCESS;
}
