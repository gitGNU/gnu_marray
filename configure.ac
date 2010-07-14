dnl Copyright (C) 2002, 2003, 2004, 2007, 2010 Jordi Burguet-Castell

dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or (at
dnl your option) any later version.

dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to:
dnl   Free Software Foundation, Inc.
dnl   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

dnl Process this file with autoconf to produce a configure script.

AC_INIT

AM_INIT_AUTOMAKE(marray,1.00)
AM_CONFIG_HEADER(config.h)

AC_PROG_MAKE_SET

dnl Check for which system.
AC_CANONICAL_HOST

dnl Checks for programs.
AC_LANG(C)
AC_PROG_CC
AC_PROG_INSTALL

AC_PROG_LIBTOOL

dnl Check for libraries
AC_CHECK_LIB(m,main,[],[
 echo "Error! You need to have libm around."
 exit -1
])
AC_CHECK_LIB(gslcblas,cblas_scopy,[],[
 echo "Oops! You need to have libgslcblas and libgsl around."
 echo "Get them and try to ./configure again."
 exit -1
])
AC_CHECK_LIB(gsl,gsl_matrix_alloc,[],[
 echo "Oops! You need to have libgsl around."
 echo "Get it and try to ./configure again."
 exit -1
])

AC_OUTPUT(src/Makefile Makefile)
