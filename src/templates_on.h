/* If BASE is undefined we use function names like gsl_name()
   and assume that we are using doubles.

   If BASE is defined we used function names like gsl_BASE_name()
   and use BASE as the base datatype      */

#if defined(BASE_COMPLEX_DOUBLE)
#define BASE complex double
#define SHORT complex
#define ATOMIC complex double
#define IN_FORMAT "%lg"
#define OUT_FORMAT "%g"
#define ATOMIC_IO double
#define BASE_EPSILON GSL_DBL_EPSILON

#elif defined(BASE_LONG_DOUBLE)
#define BASE long double
#define SHORT long_double
#define ATOMIC long double
#define USES_LONGDOUBLE 1
#define IN_FORMAT "%Lg"
#define OUT_FORMAT "%Lg"
#define ATOMIC_IO ATOMIC
#define BASE_EPSILON GSL_DBL_EPSILON

#elif defined(BASE_DOUBLE)
#define BASE double
#define SHORT
#define ATOMIC double
#define IN_FORMAT "%lg"
#define OUT_FORMAT "%g"
#define ATOMIC_IO ATOMIC
#define BASE_EPSILON GSL_DBL_EPSILON

#elif defined(BASE_FLOAT)
#define BASE float
#define SHORT float
#define ATOMIC float
#define IN_FORMAT "%g"
#define OUT_FORMAT "%g"
#define ATOMIC_IO ATOMIC
#define BASE_EPSILON GSL_FLT_EPSILON

#elif defined(BASE_ULONG)
#define BASE unsigned long
#define SHORT ulong
#define ATOMIC unsigned long
#define IN_FORMAT "%lu"
#define OUT_FORMAT "%lu"
#define ATOMIC_IO ATOMIC

#elif defined(BASE_LONG)
#define BASE long
#define SHORT long
#define ATOMIC long
#define IN_FORMAT "%ld"
#define OUT_FORMAT "%ld"
#define ATOMIC_IO ATOMIC

#elif defined(BASE_UINT)
#define BASE unsigned int
#define SHORT uint
#define ATOMIC unsigned int
#define IN_FORMAT "%u"
#define OUT_FORMAT "%u"
#define ATOMIC_IO ATOMIC

#elif defined(BASE_INT)
#define BASE int
#define SHORT int
#define ATOMIC int
#define IN_FORMAT "%d"
#define OUT_FORMAT "%d"
#define ATOMIC_IO ATOMIC

#elif defined(BASE_USHORT)
#define BASE unsigned short
#define SHORT ushort
#define ATOMIC unsigned short
#define IN_FORMAT "%hu"
#define OUT_FORMAT "%hu"
#define ATOMIC_IO ATOMIC

#elif defined(BASE_SHORT)
#define BASE short
#define SHORT short
#define ATOMIC short
#define IN_FORMAT "%hd"
#define OUT_FORMAT "%hd"
#define ATOMIC_IO ATOMIC

#elif defined(BASE_UCHAR)
#define BASE unsigned char
#define SHORT uchar
#define ATOMIC unsigned char
#define IN_FORMAT "%u"
#define OUT_FORMAT "%u"
#define ATOMIC_IO unsigned int

#elif defined(BASE_CHAR)
#define BASE char
#define SHORT char
#define ATOMIC char
#define IN_FORMAT "%d"
#define OUT_FORMAT "%d"
#define ATOMIC_IO int

#else
#error unknown BASE_ directive in source.h
#endif

#define CONCAT2x(a,b) a ## _ ## b 
#define CONCAT2(a,b) CONCAT2x(a,b)
#define CONCAT3x(a,b,c) a ## _ ## b ## _ ## c
#define CONCAT3(a,b,c) CONCAT3x(a,b,c)

#if defined(BASE_DOUBLE)
#  define FUNCTION(dir,name) CONCAT2(dir,name)
#  define TYPE(dir) dir
#elif defined(BASE_COMPLEX_DOUBLE)
#  define FUNCTION(dir,name) dir ## _complex_ ## name
#  define TYPE(dir) dir ## _complex
#else
#  define FUNCTION(a,c) CONCAT3(a,SHORT,c)
#  define TYPE(dir) CONCAT2(dir,SHORT)
#endif

#define STRING(x) #x
#define EXPAND(x) STRING(x)
#define NAME(x) EXPAND(TYPE(x))
