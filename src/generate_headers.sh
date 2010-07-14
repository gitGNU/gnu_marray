#!/bin/sh

for i in char float int long short; do
    cp marray_TYPE.h marray_${i}.h
    perl -p -i.bak -e "s/NAME/${i}/g" marray_${i}.h
    perl -p -i.bak -e "s/TYPE/${i}/g" marray_${i}.h
done



cp marray_TYPE.h marray_long_double.h
perl -p -i.bak -e "s/NAME/long_double/g" marray_long_double.h
perl -p -i.bak -e "s/TYPE/long double/g" marray_long_double.h

cp marray_TYPE.h marray_uchar.h
perl -p -i.bak -e "s/NAME/uchar/g" marray_uchar.h
perl -p -i.bak -e "s/TYPE/unsigned char/g" marray_uchar.h

cp marray_TYPE.h marray_uint.h
perl -p -i.bak -e "s/NAME/uint/g" marray_uint.h
perl -p -i.bak -e "s/TYPE/unsigned int/g" marray_uint.h

cp marray_TYPE.h marray_ulong.h
perl -p -i.bak -e "s/NAME/ulong/g" marray_ulong.h
perl -p -i.bak -e "s/TYPE/unsigned long/g" marray_ulong.h

cp marray_TYPE.h marray_ushort.h
perl -p -i.bak -e "s/NAME/ushort/g" marray_ushort.h
perl -p -i.bak -e "s/TYPE/unsigned short/g" marray_ushort.h

rm *.bak

# To delete:
# rm `\ls -1 marray_*.h | grep -v double.h | grep -v complex | grep -v TYPE | grep -v utili`
