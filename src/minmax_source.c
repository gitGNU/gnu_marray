/* marray/minmax_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005, 2007 Jordi Burguet-Castell
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
 * along with this program; if not, write to:
 *   Free Software Foundation, Inc.
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 */

/*
 * Finds the largest element of a marray.
 */
BASE
FUNCTION (marray, max) (const TYPE (marray) * t)
{
  size_t i, n;

  BASE max = t->data[0];

  n = t->size;

  for (i = 0; i < n; i++)
    {
      BASE x = t->data[i];
      if (x > max)
	max = x;
    }

  return max;
}


/*
 * Finds the smallest element of a marray.
 */
BASE
FUNCTION (marray, min) (const TYPE (marray) * t)
{
  size_t i, n;

  BASE min = t->data[0];

  n = t->size;

  for (i = 0; i < n; i++)
    {
      BASE x = t->data[i];
      if (x < min)
	min = x;
    }

  return min;
}


/*
 * Finds the smallest and largest elements of a marray.
 */
void
FUNCTION (marray, minmax) (const TYPE (marray) * t,
                         BASE * min_out, BASE * max_out)
{
  size_t i, n;

  BASE min = t->data[0];
  BASE max = t->data[0];

  n = t->size;

  for (i = 0; i < n; i++)
    {
      BASE x = t->data[i];
      if (x < min)
	{
	min = x;
	}
      if (x > max)
	max = x;
    }

  *min_out = min;
  *max_out = max;
}


/*
 * Finds the indices of the largest element of a marray.
 *
 * The array "indices" must have enough space to store all the indices
 * *before* calling this function.
 */
void
FUNCTION (marray, max_index) (const TYPE (marray) * t, size_t * indices)
{
  size_t i, n;

  BASE max = t->data[0];
  size_t max_index = 0;

  n = t->size;

  for (i = 0; i < n; i++)
    {
      BASE x = t->data[i];
      if (x > max)
        {
          max = x;
          max_index = i;
        }
    }

  position2index(t->rank, t->dimension, max_index, indices);
}


/*
 * Finds the index of the smallest element of a marray.
 *
 * The array "indices" must have enough space to store all the indices
 * *before* calling this function.
 */
void
FUNCTION (marray, min_index) (const TYPE (marray) * t,
                                  size_t * indices)
{
  size_t i, n;

  BASE min = t->data[0];
  size_t min_index = 0;

  n = t->size;

  for (i = 0; i < n; i++)
    {
      BASE x = t->data[i];
      if (x < min)
        {
          min = x;
          min_index = i;
        }
    }

  position2index(t->rank, t->dimension, min_index, indices);
}


/*
 * Finds the indices of the smallest and largest elements of a marray.
 *
 * The array "indices" must have enough space to store all the indices
 * *before* calling this function.
 */
void
FUNCTION (marray, minmax_index) (const TYPE (marray) * t,
                                     size_t * imin, size_t * imax)
{
  size_t i, n;

  BASE min = t->data[0];
  BASE max = t->data[0];
  size_t min_index = 0;
  size_t max_index = 0;

  n = t->size;

  for (i = 0; i < n; i++)
    {
      BASE x = t->data[i];
      if (x < min)
        {
          min = x;
          min_index = i;
        }
      if (x > max)
        {
          max = x;
          max_index = i;
        }
    }

  position2index(t->rank, t->dimension, min_index, imin);
  position2index(t->rank, t->dimension, max_index, imax);
}
