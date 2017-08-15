#include "database.hpp"

#include <sqlpp11/postgresql/connection.h>

sql::connection & get_connection() {
    static auto config = [] {
        auto config = std::make_shared<sql::connection_config>();
        config->host = "localhost";
        config->user = "postgres";
        config->password = "123";
        //config->debug = true;

        return config;
    }();

    thread_local sql::connection db(config);

    auto res = db.execute("SET ROLE TO hlr1_role;");
    res = db.execute("SET search_path =  hlr1_schema;");

    return db;
}