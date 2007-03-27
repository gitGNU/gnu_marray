/* marray/oper_complex_source.c
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
FUNCTION(marray, add) (TYPE (marray) * a,
                           const TYPE (marray) * b)
{
  return marray_add(a, b);
}


int
FUNCTION(marray, sub) (TYPE (marray) * a,
                           const TYPE (marray) * b)
{
  return marray_sub(a, b);
}


int
FUNCTION(marray, mul_elements) (TYPE (marray) * a,
                                    const TYPE (marray) * b)
{
  const unsigned int rank = a->rank;
  const size_t dimension  = a->dimension;
  size_t i, n;

  if (b->rank != rank || b->dimension != dimension)
    {
      GSL_ERROR ("marrays must have same dimensions", GSL_EBADLEN);
      return 1;
    }

  
  n = a->size / 2;

  for (i = 0; i < n; i++)
    {
      ATOMIC ar = a->data[2*i];
      ATOMIC ai = a->data[2*i+1];

      ATOMIC br = b->data[2*i];
      ATOMIC bi = b->data[2*i+1];

      a->data[2*i]   = ar * br - ai * bi;
      a->data[2*i+1] = ar * bi + ai * br;
    }

  return GSL_SUCCESS;
}


int
FUNCTION(marray, div_elements) (TYPE (marray) * a,
                                    const TYPE (marray) * b)
{
  const unsigned int rank = a->rank;
  const size_t dimension  = a->dimension;
  size_t i, n;

  if (b->rank != rank || b->dimension != dimension)
    {
      GSL_ERROR ("marrays must have same dimensions", GSL_EBADLEN);
      return 1;
    }

  
  n = a->size / 2;

  for (i = 0; i < n; i++)
    {
      ATOMIC ar = a->data[2*i];
      ATOMIC ai = a->data[2*i+1];

      ATOMIC br = b->data[2*i];
      ATOMIC bi = b->data[2*i+1];

      ATOMIC s = 1.0 / hypot(br, bi);

      ATOMIC sbr = s * br;
      ATOMIC sbi = s * bi;
      
      a->data[2*i]     = (ar * sbr + ai * sbi) * s;
      a->data[2*i + 1] = (ai * sbr - ar * sbi) * s;
    }

  return GSL_SUCCESS;
}


int FUNCTION(marray, scale) (TYPE (marray) * a, const BASE x)
{
  size_t i, n;

  ATOMIC xr = GSL_REAL(x);
  ATOMIC xi = GSL_IMAG(x);

  n = a->size / 2;

  for (i = 0; i < n; i++)
    {
      ATOMIC ar = a->data[2*i];
      ATOMIC ai = a->data[2*i + 1];
      
      a->data[2*i]     = ar * xr - ai * xi;
      a->data[2*i + 1] = ar * xi + ai * xr;
    }
  
  return GSL_SUCCESS;
}


int FUNCTION(marray, add_constant) (TYPE (marray) * a, const BASE x)
{
  size_t i, n;

  ATOMIC xr = GSL_REAL(x);
  ATOMIC xi = GSL_IMAG(x);

  n = a->size / 2;

  for (i = 0; i < n; i++)
    {
      a->data[2*i]     += xr;
      a->data[2*i + 1] += xi;
    }

  return GSL_SUCCESS;
}
