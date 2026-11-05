#!/bin/bash
set -e

psql -v ON_ERROR_STOP=1 --username postgres <<-EOSQL
    CREATE DATABASE images_shard_0;
    CREATE DATABASE images_shard_1;
    CREATE DATABASE images_shard_2;
    CREATE DATABASE images_shard_3;
EOSQL
