ALTER USER "postgres" WITH PASSWORD '123';
CREATE ROLE hlr1_role;
ALTER ROLE hlr1_role WITH SUPERUSER;
CREATE SCHEMA hlr1_schema AUTHORIZATION hlr1_role;
GRANT ALL ON SCHEMA hlr1_schema TO hlr1_role;

SET ROLE TO hlr1_role;

SET search_path =  hlr1_schema;

DROP TABLE IF EXISTS "users";

CREATE TABLE "users"
(
    "id" BIGINT NOT NULL,
    "email" VARCHAR(100) NOT NULL,
    "first_name" VARCHAR(50) NOT NULL,
    "last_name" VARCHAR(50) NOT NULL,
    "gender" CHAR NOT NULL,
    "birth_date" BIGINT NOT NULL,
    PRIMARY KEY(id)
);

DROP TABLE IF EXISTS "location";

CREATE TABLE "location"
(
    "id" BIGINT NOT NULL,
    "place" TEXT NOT NULL,
    "country" VARCHAR(50) NOT NULL,
    "city" VARCHAR(50) NOT NULL,
    "distance" BIGINT NOT NULL,
    PRIMARY KEY ("id")
);

DROP TABLE IF EXISTS "visit";

CREATE TABLE "visit"
(
    "id" BIGINT NOT NULL,
    "location" BIGINT NOT NULL,
    "usr" BIGINT NOT NULL,
    "visited_at" BIGINT NOT NULL,
    "mark" INTEGER NOT NULL,
    PRIMARY KEY ("id")
);

