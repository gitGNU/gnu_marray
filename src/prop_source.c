/* marray/prop_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005, 2007 Jordi Burguet-Castell
 * based on the gsl_matrix test code from Gerard Jungman, Brian Gough
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
FUNCTION (marray, isnull) (const TYPE (marray) * t)
{
  size_t i, n;

  n = t->size;

  for (i = 0; i < n; i++)
    {
      if (t->data[i] != 0.0)
        return 0;
    }

  return 1;
}
