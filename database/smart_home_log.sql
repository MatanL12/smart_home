DROP DATABASE IF EXISTS smart_home_logg;
CREATE DATABASE IF NOT EXISTS smart_home_logg;
USE smart_home_logg;

SELECT 'CREATING DATABASE STRUCTURE' as 'INFO';

DROP TABLE IF EXISTS events;

CREATE TABLE events (
    EventID   INT             NOT NULL AUTO_INCREMENT,
    Time      VARCHAR(50)     NOT NULL,
    Type      VARCHAR(50)     NOT NULL,
    Floor     VARCHAR(50)     NOT NULL,
    Room      VARCHAR(50)     NOT NULL,
    Payload   VARCHAR(100),
    PRIMARY KEY (EventID)
);

flush /*!50503 binary */ logs;
