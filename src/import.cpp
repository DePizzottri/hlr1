#define _CRT_SECURE_NO_WARNINGS
#include "import.hpp"

#include <json.hpp>
#include <fstream>
#include <sqlpp11/sqlpp11.h>

#include "hlr1.h"

using json = nlohmann::json;

using namespace std;

namespace sql = sqlpp::postgresql;
namespace fs = boost::filesystem;

void import_users(fs::path const& file, sql::connection & db) {
    const auto tmp_file = fs::path(file.string() + ".tmp");
    try {
        std::ifstream fin(file.c_str());
        auto users = json::parse(fin);
        std::ofstream fout(tmp_file.c_str());

        fout << users["users"].dump();
        fout.close();

        fs::permissions(tmp_file, fs::owner_all | fs::group_all | fs::others_all);

        const string q1 = R"(
            create table temp_json (values text);
            copy temp_json from ')"; /// home / max / users_1.json
        const string q2 = tmp_file.string() + R"(';
            insert into users ("id", "email", "first_name", "last_name", "gender", "birth_date")

            select CAST(values->>'id' AS BIGINT) AS id,
                   CAST(values->>'email' AS VARCHAR(100)) AS email,
                   CAST(values->>'first_name' AS VARCHAR(100)) as first_name,
                   CAST(values->>'last_name' AS VARCHAR(100)) as last_name,
                   CAST(values->>'gender' AS CHAR) as gender,
                   CAST(values->>'birth_date' AS BIGINT) as birth_date      
            from   (
                       select json_array_elements(values::json) as values
                       from   temp_json
                   ) a;
            drop table if exists temp_json;            
        )";

        db.execute(q1 + q2);
    }
    catch (std::exception const& ex)
    {
        std::cerr << "Error insert user from file " + file.string() + " " + ex.what();
    }

    boost::system::error_code _;
    fs::remove(tmp_file, _);
}

void import_locations(fs::path const& file, sql::connection & db) {
    const auto tmp_file = fs::path(file.string() + ".tmp");
    try {
        std::ifstream fin(file.c_str());
        auto users = json::parse(fin);
        std::ofstream fout(tmp_file.c_str());

        fout << users["locations"].dump();
        fout.close();

        fs::permissions(tmp_file, fs::owner_all | fs::group_all | fs::others_all);

        const string q1 = R"(
            create table temp_json (values text);
            copy temp_json from ')"; /// home / max / users_1.json
        const string q2 = tmp_file.string() + R"(';
            insert into location ("id", "place", "country", "city", "distance")

            select CAST(values->>'id' AS BIGINT) AS id,
                   CAST(values->>'place' AS TEXT) AS place,
                   CAST(values->>'country' AS VARCHAR(50)) as country,
                   CAST(values->>'city' AS VARCHAR(50)) as city,
                   CAST(values->>'distance' AS BIGINT) as distance
            from   (
                       select json_array_elements(values::json) as values
                       from   temp_json
                   ) a;
            drop table if exists temp_json;            
        )";

        db.execute(q1 + q2);
    }
    catch (std::exception const& ex)
    {
        std::cerr << "Error insert locations from file " + file.string() + " " + ex.what();
    }

    boost::system::error_code _;
    fs::remove(tmp_file, _);
}

void import_visits(fs::path const& file, sql::connection & db) {
    const auto tmp_file = fs::path(file.string() + ".tmp");
    try {
        std::ifstream fin(file.c_str());
        auto users = json::parse(fin);
        std::ofstream fout(tmp_file.c_str());

        fout << users["visits"].dump();
        fout.close();

        fs::permissions(tmp_file, fs::owner_all | fs::group_all | fs::others_all);

        const string q1 = R"(
            create table temp_json (values text);
            copy temp_json from ')"; /// home / max / users_1.json
        const string q2 = tmp_file.string() + R"(';
            insert into visit ("id", "location", "usr", "visited_at", "mark")

            select CAST(values->>'id' AS BIGINT) AS id,
                   CAST(values->>'location' AS BIGINT) AS location,
                   CAST(values->>'user' AS BIGINT) as usr,
                   CAST(values->>'visited_at' AS BIGINT) as visited_at,
                   CAST(values->>'mark' AS INTEGER) as mark
            from   (
                       select json_array_elements(values::json) as values
                       from   temp_json
                   ) a;
            drop table if exists temp_json;           
        )";

        db.execute(q1 + q2);
    }
    catch (std::exception const& ex)
    {
        std::cerr << "Error insert visits from file " + file.string() + " " + ex.what();
    }

    boost::system::error_code _;
    fs::remove(tmp_file, _);
}

void import(fs::path const& dir, sql::connection & db) {
    try {
        cout << "Import data from " << dir << endl;
        for (const auto& file : fs::directory_iterator(dir)) {
            if (!fs::is_directory(file)) {
                if (file.path().filename().string().substr(0, 5) == "users") {
                    cout << "Import users from " << file.path() << endl;
                    import_users(file, db);
                }
                else if (file.path().filename().string().substr(0, 9) == "locations") {
                    cout << "Import locations from " << file.path() << endl;
                    import_locations(file, db);
                }
                else if (file.path().filename().string().substr(0, 6) == "visits") {
                    cout << "Import visits from " << file.path() << endl;
                    import_visits(file, db);
                }                
            }
        }
        cout << "Imported" << endl;
        db.execute(R"(
CREATE INDEX "users_bd" ON "users" ("birth_date");
CREATE INDEX "users_g" ON "users" ("gender");
CREATE INDEX "location_c" ON "location" ("country");
CREATE INDEX "location_d" ON "location" ("distance");
CREATE INDEX "visit_va" ON "visit" ("visited_at");
)");
        cout << "Indexes created" << endl;

        //import_users("D:/_Code/highload_r1/test_data/users_1.json", db);
        //import_locations("D:/_Code/highload_r1/test_data/locations_1.json", db);
        //import_visits("D:/_Code/highload_r1/test_data/visits_1.json", db);
    }
    catch (std::exception const& ex) {
        std::cerr << "Import exception: '" << ex.what() << "'";
    }
}
