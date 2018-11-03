FROM postgres:10
EXPOSE 5432
RUN apt-get update && apt-get install -y build-essential postgresql-server-dev-10

COPY bytea_bitops.c /bytea_bitops.c 
RUN gcc -I /usr/include/postgresql/9.6/server -fpic -c /bytea_bitops.c
RUN gcc -shared -o /bytea_bitops.so /bytea_bitops.o
RUN chmod 644 bytea_bitops.so
RUN cp bytea_bitops.so /usr/lib/postgresql/10/lib/
RUN rm bytea_bitops.so bytea_bitops.o
RUN cd /usr/lib/postgresql/10/lib/

