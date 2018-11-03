/* bytea_bitops.c
 *
 * Add bitwise logical operations to bytea columns as a postgres extension. 
 * Source: https://www.postgresql.org/message-id/74a3f8f0-d1d4-1d6e-dd81-fb2cf89ef88f%40gmail.com
 *
 *
 * Adding bytea bit operation functions similar to varbit's bit operations.
 * Written by Christian Rossow
 * License: Do whatever you want with this code.
 *
 * To build:
 * gcc -I`pg_config --includedir` -fpic -c bytea_bitops.c
 * gcc -shared -o bytea_bitops.so bytea_bitops.o
 * sudo cp bytea_bitops.so /usr/lib/postgresql/10/lib/
 * cd /usr/lib/postgresql/10/lib/
 * sudo chmod +r bytea_bitops.so
 */

#include "postgres.h"
#include "fmgr.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(bytea_xor);
Datum bytea_xor(PG_FUNCTION_ARGS)
{
    bytea*  ba1 = PG_GETARG_BYTEA_P(0);
    bytea*  ba2 = PG_GETARG_BYTEA_P(1);
    bytea*  result;
    char*   str1 = VARDATA(ba1);
    char*   str2 = VARDATA(ba2);
    char*   resstr;
    int32   len;
    int32   i;

    if (VARSIZE(ba1) != VARSIZE(ba2))
    {
		ereport(ERROR,
				(errcode(ERRCODE_STRING_DATA_LENGTH_MISMATCH),
				 errmsg("cannot XOR bytea of different sizes")));
    }

    len = VARSIZE(ba1);
    result = (bytea *) palloc(len);
    SET_VARSIZE(result, len);

    resstr = VARDATA(result);
    for (i=0; i < len - VARHDRSZ; ++i)
    { 
        resstr[i] = str1[i] ^ str2[i];
    }

    PG_RETURN_BYTEA_P(result);
}

PG_FUNCTION_INFO_V1(bytea_and);
Datum bytea_and(PG_FUNCTION_ARGS)
{
    bytea*  ba1 = PG_GETARG_BYTEA_P(0);
    bytea*  ba2 = PG_GETARG_BYTEA_P(1);
    bytea*  result;
    char*   str1 = VARDATA(ba1);
    char*   str2 = VARDATA(ba2);
    char*   resstr;
    int32   len;
    int32   i;

    if (VARSIZE(ba1) != VARSIZE(ba2))
    {
		ereport(ERROR,
				(errcode(ERRCODE_STRING_DATA_LENGTH_MISMATCH),
				 errmsg("cannot AND bytea of different sizes")));
    }

    len = VARSIZE(ba1);
    result = (bytea *) palloc(len);
    SET_VARSIZE(result, len);

    resstr = VARDATA(result);
    for (i=0; i < len - VARHDRSZ; ++i)
    { 
        resstr[i] = str1[i] & str2[i];
    }

    PG_RETURN_BYTEA_P(result);
}

PG_FUNCTION_INFO_V1(bytea_or);
Datum bytea_or(PG_FUNCTION_ARGS)
{
    bytea*  ba1 = PG_GETARG_BYTEA_P(0);
    bytea*  ba2 = PG_GETARG_BYTEA_P(1);
    bytea*  result;
    char*   str1 = VARDATA(ba1);
    char*   str2 = VARDATA(ba2);
    char*   resstr;
    int32   len;
    int32   i;

    if (VARSIZE(ba1) != VARSIZE(ba2))
    {
		ereport(ERROR,
				(errcode(ERRCODE_STRING_DATA_LENGTH_MISMATCH),
				 errmsg("cannot AND bytea of different sizes")));
    }

    len = VARSIZE(ba1);
    result = (bytea *) palloc(len);
    SET_VARSIZE(result, len);

    resstr = VARDATA(result);
    for (i=0; i < len - VARHDRSZ; ++i)
    { 
        resstr[i] = str1[i] | str2[i];
    }

    PG_RETURN_BYTEA_P(result);
}

PG_FUNCTION_INFO_V1(bytea_not);
Datum bytea_not(PG_FUNCTION_ARGS)
{
    bytea*  ba1 = PG_GETARG_BYTEA_P(0);
    bytea*  result;
    char*   str1 = VARDATA(ba1);
    char*   resstr;
    int32   len = VARSIZE(ba1);
    int32   i;

    result = (bytea *) palloc(len);
    SET_VARSIZE(result, len);

    resstr = VARDATA(result);
    for (i=0; i < len - VARHDRSZ; ++i)
    { 
        resstr[i] = ~str1[i];
    }

    PG_RETURN_BYTEA_P(result);
}

PG_FUNCTION_INFO_V1(bytea_bitsset);
Datum bytea_bitsset(PG_FUNCTION_ARGS)
{
    bytea*  ba1 = PG_GETARG_BYTEA_P(0);
    int32   result = 0;
    char*   str1 = VARDATA(ba1);
    int32   len = VARSIZE(ba1) - VARHDRSZ;
    int32   i;

    for (i=0; i < len; ++i)
    { 
        uint8_t c = (uint8_t) str1[i];
        //elog(WARNING, "processing char 0x%02x before %d", c, result);
        result += (c & 0x01); c = c >> 1;   // 1
        result += (c & 0x01); c = c >> 1;   // 2
        result += (c & 0x01); c = c >> 1;   // 3
        result += (c & 0x01); c = c >> 1;   // 4
        result += (c & 0x01); c = c >> 1;   // 5
        result += (c & 0x01); c = c >> 1;   // 6
        result += (c & 0x01); c = c >> 1;   // 7
        result += (c & 0x01);               // 8
    }

    PG_RETURN_INT32(result);
}
