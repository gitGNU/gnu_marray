/* marray/file_source.c
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
 * Reads the (binary stored) contents of a marray from a stream.
 *
 * The marray must be properly allocated before calling to this function.
 */
int
FUNCTION(marray, fread) (FILE * stream, TYPE(marray) * t)
{
  size_t n = t->size;
  ATOMIC * data = t->data;

  size_t items = fread(data, MULTIPLICITY * sizeof(ATOMIC), n, stream);

  if (items != n)
    {
      GSL_ERROR ("fread failed", GSL_EFAILED);
    }

  return GSL_SUCCESS;
}


/*
 * Writes the contents of marray t to a stream, in binary form.
 */
int
FUNCTION(marray, fwrite) (FILE * stream, const TYPE(marray) * t)
{
  size_t n = t->size;
  ATOMIC * data = t->data;

  size_t items = fwrite(data, MULTIPLICITY * sizeof(ATOMIC), n, stream);

  if (items != n)
    {
      GSL_ERROR ("fwrite failed", GSL_EFAILED);
    }

  return GSL_SUCCESS;
}


#if !(defined(USES_LONGDOUBLE) && !defined(HAVE_PRINTF_LONGDOUBLE))
int
FUNCTION(marray, fprintf) (FILE * stream, const TYPE(marray) * t,
				const char *format)
{
  size_t i;
  size_t n = t->size ;

  ATOMIC * data = t->data;

  int status = 0;

  for (i = 0; i < n; i++)
    {
      int k;
      for (k = 0; k < MULTIPLICITY; k++)
        {
          if (k > 0)
            {
              status = putc(' ', stream);
              
              if (status == EOF)
                {
                  GSL_ERROR ("putc failed", GSL_EFAILED);
                }
            }
          
          status = fprintf(stream, format, data[MULTIPLICITY * i + k]);
          
          if (status < 0)
            {
              GSL_ERROR ("fprintf failed", GSL_EFAILED);
            }
        }
      
      status = putc ('\n', stream);

      if (status == EOF)
        {
          GSL_ERROR ("putc failed", GSL_EFAILED);
        }
    }

  return GSL_SUCCESS;
}


int
FUNCTION(marray, fscanf) (FILE * stream, TYPE(marray) * t)
{
  size_t i;
  size_t n = t->size;

  ATOMIC * data = t->data;

  for (i = 0; i < n; i++)
    {
      int k;
      for (k = 0; k < MULTIPLICITY; k++)
        {
          ATOMIC_IO tmp;

          int status = fscanf(stream, IN_FORMAT, &tmp) ;

          data[MULTIPLICITY * i + k] = tmp;

          if (status != 1)
            GSL_ERROR ("fscanf failed", GSL_EFAILED);
        }
    }

  return GSL_SUCCESS;
}

#endif
