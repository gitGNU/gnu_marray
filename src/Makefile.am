# Copyright (C) 2002, 2003, 2004, 2007 Jordi Burguet-Castell

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or (at
# your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to:
#   Free Software Foundation, Inc.
#   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

lib_LTLIBRARIES = libmarray.la

libmarray_la_SOURCES = marray_utilities.c init.c marray.c file.c copy.c minmax.c oper.c prop.c

pkginclude_HEADERS = marray.h marray_char.h marray_double.h marray_float.h marray_int.h marray_long.h marray_long_double.h marray_short.h marray_uchar.h marray_uint.h marray_ulong.h marray_ushort.h


check_PROGRAMS = test test_static

TESTS = $(check_PROGRAMS)

test_LDADD =  -lgsl -lgslcblas libmarray.la
test_static_LDADD = -lgsl -lgslcblas libmarray.la

test_SOURCES = test.c
test_static_SOURCES = test_static.c

CLEANFILES = test.txt test.dat

info_TEXINFOS = marray.texi
marray_TEXINFOS = fdl.texi mathinclude.texi

EXTRA_DIST = marray_utilities.h templates_errfuncs.h templates_off.h templates_on.h copy_source.c file_source.c init_source.c minmax_source.c oper_complex_source.c oper_source.c prop_source.c marray_source.c test_source.c

