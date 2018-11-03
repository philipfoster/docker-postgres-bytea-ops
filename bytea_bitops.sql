DROP FUNCTION IF EXISTS bytea_xor(bytea, bytea);
CREATE FUNCTION bytea_xor(bytea, bytea) RETURNS bytea
AS 'bytea_bitops.so', 'bytea_xor'
LANGUAGE C STRICT;

DROP FUNCTION IF EXISTS bytea_and(bytea, bytea);
CREATE FUNCTION bytea_and(bytea, bytea) RETURNS bytea
AS 'bytea_bitops.so', 'bytea_and'
LANGUAGE C STRICT;

DROP FUNCTION IF EXISTS bytea_or(bytea, bytea);
CREATE FUNCTION bytea_or(bytea, bytea) RETURNS bytea
AS 'bytea_bitops.so', 'bytea_or'
LANGUAGE C STRICT;

DROP FUNCTION IF EXISTS bytea_not(bytea);
CREATE FUNCTION bytea_not(bytea) RETURNS bytea
AS 'bytea_bitops.so', 'bytea_not'
LANGUAGE C STRICT;

DROP FUNCTION IF EXISTS bytea_bitsset(bytea);
CREATE FUNCTION bytea_bitsset(bytea) RETURNS integer
AS 'bytea_bitops.so', 'bytea_bitsset'
LANGUAGE C STRICT;
