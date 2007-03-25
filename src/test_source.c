/* jbc_marray/test_source.c
 * 
 * Copyright (C) 2002, 2003, 2004, 2005 Jordi Burguet-Castell
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

void FUNCTION(test, func) (void);
void FUNCTION(test, trap) (void);
void FUNCTION(test, text) (void);
void FUNCTION(test, binary) (void);


void
FUNCTION(test, func) (void)
{
  size_t i, j, k;    /* jbc_marray indices */
  size_t counter;    /* to fill a jbc_marray */
  size_t indices[RANK];  /* to pass jbc_marray indices */


  /*
   * Test allocation.
   */
  TYPE(jbc_marray) * t = FUNCTION(jbc_marray, alloc) (RANK, DIMENSION);

  gsl_test (t->data == 0,
            NAME (jbc_marray) "_alloc returns valid pointer");
  gsl_test (t->rank != RANK,
            NAME (jbc_marray) "_alloc returns valid rank");
  gsl_test (t->dimension[0] != DIMENSION[0] && t->dimension[1] != DIMENSION[1]
            && t->dimension[2] != DIMENSION[2],
            NAME (jbc_marray) "_alloc returns valid dimensions");


  /*
   * Test set.
   */
  counter = 0;
  for (i = 0; i < DIMENSION[0]; i++)
    {
      for (j = 0; j < DIMENSION[1]; j++)
        {
          for (k = 0; k < DIMENSION[2]; k++)
            {
              counter++;
              indices[0] = i;  indices[1] = j;  indices[2] = k;
              FUNCTION(jbc_marray, set) (t, indices, (BASE) counter);
            }
        }
    }


  {
    status = 0;
    counter = 0;

    for (i = 0; i < DIMENSION[0]; i++)
      {
        for (j = 0; j < DIMENSION[1]; j++)
          {
            for (k = 0; k < DIMENSION[2]; k++)
              {
                counter++;
                if (t->data[DIMENSION[2]*DIMENSION[1]*i + DIMENSION[2]*j + k]
                    != (BASE) counter)
                  status = 1;
              }
          }
      }
    
    gsl_test (status, NAME (jbc_marray) "_set writes into array");
  }
  



  /* Test get */
  {
    status = 0;
    counter = 0;
    for (i = 0; i < DIMENSION[0]; i++)
      {
        for (j = 0; j < DIMENSION[1]; j++)
          {
            for (k = 0; k < DIMENSION[2]; k++)
              {
                counter++;
                indices[0] = i;  indices[1] = j;  indices[2] = k;
                if (FUNCTION(jbc_marray, get) (t, indices) != (BASE) counter)
                  status = 1;
              }
          }
      }

    gsl_test (status, NAME (jbc_marray) "_get reads from array");
  }


  FUNCTION(jbc_marray, free) (t);   /* free whatever is in t */

  /* New round of tests */

  t = FUNCTION(jbc_marray, calloc) (RANK, DIMENSION);

  /* Fill the jbc_marray again */
  counter = 0;
  for (i = 0; i < DIMENSION[0]; i++)
    {
      for (j = 0; j < DIMENSION[1]; j++)
        {
          for (k = 0; k < DIMENSION[2]; k++)
            {
              counter++;
              indices[0] = i;  indices[1] = j;  indices[2] = k;
              FUNCTION(jbc_marray, set) (t, indices, (BASE) counter);
            }
        }
    }


  /*
   * Test maximum and minimum.
   */
  {
    indices[0] = 0;  indices[1] = 0;  indices[2] = 0;
    BASE exp_max = FUNCTION(jbc_marray, get) (t, indices);
    BASE exp_min = FUNCTION(jbc_marray, get) (t, indices);
    size_t exp_imax = 0, exp_jmax = 0, exp_kmax = 0;
    size_t exp_imin = 0, exp_jmin = 0, exp_kmin = 0;

    for (i = 0; i < DIMENSION[0]; i++)
      {
        for (j = 0; j < DIMENSION[1]; j++)
          {
            for (k = 0; k < DIMENSION[2]; k++)
              {
                indices[0] = i;  indices[1] = j;  indices[2] = k;
                BASE value = FUNCTION(jbc_marray, get) (t, indices);

                if (value > exp_max) {
                  exp_max = value;
                  exp_imax = i;  exp_jmax = j;  exp_kmax = k;
                }
                if (value < exp_min) {
                  exp_min = FUNCTION(jbc_marray, get) (t, indices);
                  exp_imin = i;  exp_jmin = j;  exp_kmin = k;
                }
              }
          }
      }

    /* Test maximum */
    {
      BASE max = FUNCTION(jbc_marray, max) (t);

      gsl_test (max != exp_max,
                NAME(jbc_marray) "_max returns correct maximum value");
    }

    /* Test minimum */
    {
      BASE min = FUNCTION(jbc_marray, min) (t);
      
      gsl_test (min != exp_min,
                NAME(jbc_marray) "_min returns correct minimum value");
    }

    /* Test minmax */
    {
      BASE min, max;
      FUNCTION(jbc_marray, minmax) (t, &min, &max);

      gsl_test (max != exp_max,
                NAME(jbc_marray) "_minmax returns correct maximum value");
      gsl_test (min != exp_min,
                NAME(jbc_marray) "_minmax returns correct minimum value");
    }

    /* Test min/max index */
    {
      size_t imax[RANK];

      FUNCTION(jbc_marray, max_index) (t, imax);

      status = 0;

      if (imax[0] != exp_imax)
        status = 1;

      if (imax[1] != exp_jmax)
        status = 1;

      if (imax[2] != exp_kmax)
        status = 1;

      gsl_test (status,
                NAME(jbc_marray) "_max_index returns correct maximum indices");
    }

    {
      size_t imin[RANK];

      FUNCTION(jbc_marray, min_index) (t, imin);

      status = 0;

      if (imin[0] != exp_imin)
        status = 1;

      if (imin[1] != exp_jmin)
        status = 1;

      if (imin[2] != exp_kmin)
        status = 1;

      gsl_test (status,
                NAME(jbc_marray) "_min_index returns correct minimum indices");
    }

    {
      size_t imin[RANK];
      size_t imax[RANK];

      FUNCTION(jbc_marray, minmax_index) (t, imin, imax);

      status = 0;

      if (imax[0] != exp_imax)
        status = 1;

      if (imax[1] != exp_jmax)
        status = 1;

      if (imax[2] != exp_kmax)
        status = 1;

      if (imin[0] != exp_imin)
        status = 1;

      if (imin[1] != exp_jmin)
        status = 1;

      if (imin[2] != exp_kmin)
        status = 1;
      
      gsl_test (status,
                NAME(jbc_marray) "_minmax_index returns correct indices");
    }
  }


  /*
   * Operations.
   */
  {
    TYPE (jbc_marray) * a = FUNCTION(jbc_marray, calloc) (RANK, DIMENSION);
    TYPE (jbc_marray) * b = FUNCTION(jbc_marray, calloc) (RANK, DIMENSION);

    for (i = 0; i < DIMENSION[0]; i++)
      {
        for (j = 0; j < DIMENSION[1]; j++)
          {
            for (k = 0; k < DIMENSION[2]; k++)
              {
                indices[0] = i;  indices[1] = j;  indices[2] = k;
                FUNCTION(jbc_marray, set) (a, indices,
                                           (BASE) (3 + i + 5 * j + 2 * k));
                FUNCTION(jbc_marray, set) (b, indices,
                                           (BASE) (3 + 2 * i + 4 * j + k));
              }
          }
      }
    
    /* Addition */
    FUNCTION(jbc_marray, memcpy) (t, a);
    FUNCTION(jbc_marray, add) (t, b);

    {
      status = 0;

      for (i = 0; i < DIMENSION[0]; i++)
        {
          for (j = 0; j < DIMENSION[1]; j++)
            {
              for (k = 0; k < DIMENSION[2]; k++)
                {
                  indices[0] = i;  indices[1] = j;  indices[2] = k;
                  BASE r = FUNCTION(jbc_marray, get) (t, indices);
                  BASE x = FUNCTION(jbc_marray, get) (a, indices);
                  BASE y = FUNCTION(jbc_marray, get) (b, indices);
                  BASE z = x + y;
                  if (r != z)
                    status = 1;
                }
            }
        }
      
      gsl_test(status, NAME(jbc_marray) "_add jbc_marray addition");
    }

    /* Subtraction */
    FUNCTION(jbc_marray, memcpy) (t, a);
    FUNCTION(jbc_marray, sub) (t, b);
    
    {
      status = 0;

      for (i = 0; i < DIMENSION[0]; i++)
        {
          for (j = 0; j < DIMENSION[1]; j++)
            {
              for (k = 0; k < DIMENSION[2]; k++)
                {
                  indices[0] = i;  indices[1] = j;  indices[2] = k;
                  BASE r = FUNCTION(jbc_marray, get) (t, indices);
                  BASE x = FUNCTION(jbc_marray, get) (a, indices);
                  BASE y = FUNCTION(jbc_marray, get) (b, indices);
                  BASE z = x - y;
                  if (r != z)
                    status = 1;
                }
            }
        }
      
      gsl_test(status, NAME(jbc_marray) "_sub jbc_marray subtraction");
    }

    /* Element multiplication */
    FUNCTION(jbc_marray, memcpy) (t, a);
    FUNCTION(jbc_marray, mul_elements) (t, b);

    {
      status = 0;

      for (i = 0; i < DIMENSION[0]; i++)
        {
          for (j = 0; j < DIMENSION[1]; j++)
            {
              for (k = 0; k < DIMENSION[2]; k++)
                {
                  indices[0] = i;  indices[1] = j;  indices[2] = k;
                  BASE r = FUNCTION(jbc_marray, get) (t, indices);
                  BASE x = FUNCTION(jbc_marray, get) (a, indices);
                  BASE y = FUNCTION(jbc_marray, get) (b, indices);
                  BASE z = x * y;
                  if (r != z)
                    status = 1;
                }
            }
        }
      
      gsl_test(status,
               NAME(jbc_marray) "_mul_elements elements multiplication");
    }

    /* Element division */
    FUNCTION(jbc_marray, memcpy) (t, a);
    FUNCTION(jbc_marray, div_elements) (t, b);

    {
      status = 0;

      for (i = 0; i < DIMENSION[0]; i++)
        {
          for (j = 0; j < DIMENSION[1]; j++)
            {
              for (k = 0; k < DIMENSION[2]; k++)
                {
                  indices[0] = i;  indices[1] = j;  indices[2] = k;
                  BASE r = FUNCTION(jbc_marray, get) (t, indices);
                  BASE x = FUNCTION(jbc_marray, get) (a, indices);
                  BASE y = FUNCTION(jbc_marray, get) (b, indices);
                  BASE z = x / y;
                  if (fabs(r - z) > 2 * GSL_FLT_EPSILON * fabs(z))
                      status = 1;
                }
            }
        }
      
      gsl_test(status, NAME(jbc_marray) "_div_elements elements division");
    }


    FUNCTION(jbc_marray, free) (a);
    FUNCTION(jbc_marray, free) (b);
  }


  FUNCTION(jbc_marray, free) (t);
}


#if !(USES_LONGDOUBLE && !HAVE_PRINTF_LONGDOUBLE)
void
FUNCTION(test, text) (void)
{
  size_t i, j, k;    /* jbc_marray indices */
  size_t counter;    /* to fill a jbc_marray */
  size_t indices[RANK];  /* to pass jbc_marray indices */

  TYPE(jbc_marray) * t = FUNCTION(jbc_marray, alloc) (RANK, DIMENSION);

  {
    FILE *f = fopen("test.txt", "w");

    counter = 0;
    for (i = 0; i < DIMENSION[0]; i++)
      for (j = 0; j < DIMENSION[1]; j++)
        for (k = 0; k < DIMENSION[2]; k++)
          {
            counter++;
            indices[0] = i;  indices[1] = j;  indices[2] = k;
            FUNCTION(jbc_marray, set) (t, indices, (BASE) counter);
          }
    
    FUNCTION(jbc_marray, fprintf) (f, t, OUT_FORMAT);
    fclose(f);
  }

  {
    FILE *f = fopen("test.txt", "r");
    TYPE(jbc_marray) * tt = FUNCTION(jbc_marray, alloc) (RANK, DIMENSION);
    status = 0;

    FUNCTION(jbc_marray, fscanf) (f, tt);
    
    counter = 0;
    for (i = 0; i < DIMENSION[0]; i++)
      {
        for (j = 0; j < DIMENSION[1]; j++)
          {
            for (k = 0; k < DIMENSION[2]; k++)
              {
                counter++;
                if (tt->data[DIMENSION[2]*DIMENSION[1]*i + DIMENSION[2]*j + k]
                    != (BASE) counter)
                  status = 1;
              }
          }
      }

    gsl_test(status, NAME (jbc_marray) "_fprintf and fscanf");

    fclose(f);
    FUNCTION(jbc_marray, free) (tt);
  }

  FUNCTION(jbc_marray, free) (t);
}
#endif


void
FUNCTION(test, binary) (void)
{
  size_t i, j, k;    /* jbc_marray indices */
  size_t counter;    /* to fill a jbc_marray */
  size_t indices[RANK];  /* to pass jbc_marray indices */

  TYPE(jbc_marray) * t = FUNCTION(jbc_marray, calloc) (RANK, DIMENSION);

  {
    FILE *f = fopen("test.dat", "wb");

    counter = 0;
    for (i = 0; i < DIMENSION[0]; i++)
      {
        for (j = 0; j < DIMENSION[1]; j++)
          {
            for (k = 0; k < DIMENSION[2]; k++)
              {
                counter++;
                indices[0] = i;  indices[1] = j;  indices[2] = k;
                FUNCTION(jbc_marray, set) (t, indices, (BASE) counter);
              }
          }
      }
    
    FUNCTION(jbc_marray, fwrite) (f, t);
    fclose (f);
  }


  {
    FILE *f = fopen("test.dat", "rb");
    TYPE(jbc_marray) * tt = FUNCTION(jbc_marray, alloc) (RANK, DIMENSION);
    status = 0;

    FUNCTION(jbc_marray, fread) (f, tt);
    
    counter = 0;
    for (i = 0; i < DIMENSION[0]; i++)
      {
        for (j = 0; j < DIMENSION[1]; j++)
          {
            for (k = 0; k < DIMENSION[2]; k++)
              {
                counter++;
                if (tt->data[DIMENSION[2]*DIMENSION[1]*i + DIMENSION[2]*j + k] !=
                    (BASE) counter)
                  status = 1;
              }
          }
      }

    gsl_test(status, NAME (jbc_marray) "_write and read");

    fclose(f);
    FUNCTION(jbc_marray, free) (tt);
  }
  
  FUNCTION(jbc_marray, free) (t);
}



void
FUNCTION(test, trap) (void)
{
  size_t indices[RANK];  /* to pass jbc_marray indices */
  double x;

  TYPE(jbc_marray) * t = FUNCTION(jbc_marray, calloc) (RANK, DIMENSION);

  /*
   * jbc_marray_set tests.
   */

  /* Overflow above upper bound */

  status = 0;
  indices[0] = DIMENSION[0]+1;  indices[1] = 0;  indices[2] = 0;
  FUNCTION(jbc_marray, set) (t, indices, (BASE) 1.2);

  gsl_test (!status,
            NAME (jbc_marray) "_set traps 1st index above upper bound");
  

  status = 0;
  indices[0] = 0;  indices[1] = DIMENSION[1]+1;  indices[2] = 0;
  FUNCTION(jbc_marray, set) (t, indices, (BASE) 1.2);

  gsl_test (!status,
            NAME (jbc_marray) "_set traps 2nd index above upper bound");

  status = 0;
  indices[0] = 0;  indices[1] = 0;  indices[2] = DIMENSION[2]+1;
  FUNCTION(jbc_marray, set) (t, indices, (BASE) 1.2);

  gsl_test (!status,
            NAME (jbc_marray) "_set traps 3rd index above upper bound");
  

  /* Overflow at upper bound */

  status = 0;
  indices[0] = 0;  indices[1] = DIMENSION[1];  indices[2] = 0;
  FUNCTION(jbc_marray, set) (t, indices, (BASE) 1.2);

  gsl_test (!status,
            NAME (jbc_marray) "_set traps 2nd index at upper bound");


  /* Underflow */

  status = 0;
  indices[0] = 0;  indices[1] = -1;  indices[2] = 0;
  FUNCTION(jbc_marray, set) (t, indices, (BASE) 1.2);

  gsl_test (!status,
            NAME (jbc_marray) "_set traps 2nd index below lower bound");


  /*
   * jbc_marray_get tests.
   */

  /* Overflow above upper bound */

  status = 0;
  indices[0] = DIMENSION[0]+1;  indices[1] = 0;  indices[2] = 0;
  x = FUNCTION(jbc_marray, get) (t, indices);

  gsl_test (!status,
            NAME (jbc_marray) "_get traps 1st index above upper bound");
  

  status = 0;
  indices[0] = 0;  indices[1] = DIMENSION[1]+1;  indices[2] = 0;
  x = FUNCTION(jbc_marray, get) (t, indices);

  gsl_test (!status,
            NAME (jbc_marray) "_get traps 2nd index above upper bound");

  status = 0;
  indices[0] = 0;  indices[1] = 0;  indices[2] = DIMENSION[2]+1;
  x = FUNCTION(jbc_marray, get) (t, indices);

  gsl_test (!status,
            NAME (jbc_marray) "_get traps 3rd index above upper bound");
  

  /* Overflow at upper bound */

  status = 0;
  indices[0] = 0;  indices[1] = DIMENSION[1];  indices[2] = 0;
  x = FUNCTION(jbc_marray, get) (t, indices);

  gsl_test (!status,
            NAME (jbc_marray) "_get traps 2nd index at upper bound");


  /* Underflow */

  status = 0;
  indices[0] = 0;  indices[1] = -1;  indices[2] = 0;
  x = FUNCTION(jbc_marray, get) (t, indices);

  gsl_test (!status,
            NAME (jbc_marray) "_get traps 2nd index below lower bound");



  FUNCTION(jbc_marray, free) (t);
}
