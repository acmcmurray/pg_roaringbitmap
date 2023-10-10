#ifndef __ROARINGBITMAP_H__
#define __ROARINGBITMAP_H__

/* Created by ZEROMAX on 2017/3/20.*/

#include "postgres.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fmgr.h"
#include "catalog/pg_type.h"
#include "utils/builtins.h"
#include "utils/array.h"
#include "utils/bytea.h"
#include "utils/memutils.h"
#include "utils/guc.h"
#include "lib/stringinfo.h"
#include "funcapi.h"
#include "libpq/pqformat.h"

/* must include "roaring.h" before redefine malloc functions */
#include "roaring.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

bool ArrayContainsNulls(ArrayType *array);

/* useful macros for accessing int4 arrays */
#define ARRPTR(x)  ( (int *) ARR_DATA_PTR(x) )
#define ARRNELEMS(x)  ArrayGetNItems(ARR_NDIM(x), ARR_DIMS(x))

/* reject arrays we can't handle; to wit, those containing nulls */
#define CHECKARRVALID(x) \
    do { \
        if (ARR_HASNULL(x) && ArrayContainsNulls(x)) \
            ereport(ERROR, \
                    (errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED), \
                     errmsg("array must not contain nulls"))); \
    } while(0)

#define ARRISEMPTY(x)  (ARRNELEMS(x) == 0)

#include "roaring.c"
#include "roaring_buffer_reader.c"

#endif
