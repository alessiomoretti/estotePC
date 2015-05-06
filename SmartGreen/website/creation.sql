CREATE TABLE measures( id INTEGER PRIMARY KEY NOT NULL,
                       tempA             REAL NOT NULL,
                       tempB             REAL NOT NULL,
                       tempC             REAL NOT NULL,
                       moistA            VARCHAR(4) NOT NULL,
                       moistB            VARCHAR(4) NOT NULL,
                       moistC            VARCHAR(4) NOT NULL);

INSERT INTO measures VALUES(1, 0.0, 0.0, 0.0, "T", "T", "T");
