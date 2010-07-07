PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE utf_table (                col1 INTEGER NOT NULL,                col2 CHAR(25),                col3 VARCHAR(25),                col4 NUMERIC NOT NULL,                col5 TEXT(25),                PRIMARY KEY (col1),                UNIQUE (col2)            );
COMMIT;
