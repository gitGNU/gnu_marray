/* marray/marray_utilities.c
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

#include <config.h>
#include <gsl/gsl_errno.h>

#include "marray_utilities.h"

/*
 * Auxiliary functions.
 */



/*
 * Changes the absolute position ("pos") in the marray viewed as an array
 * to its set of indices ("indices").
 *
 * It returns in the argument "indices" an array with indices[i] being
 * the ith index that corresponds to position "pos" in a marray with
 * dimensions "dimension".
 *
 * The "indices" array must be allocated with enough space *before*
 * calling this function.
 */
void position2index(unsigned int rank, size_t * dimension, size_t pos,
                    size_t * indices)
{
  unsigned int i;

  for (i = 0; i < rank; i++)
    {
      indices[i] = pos - dimension[i] * (pos / dimension[i]);
      pos /= dimension[i];
    }
}
