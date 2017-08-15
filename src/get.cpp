#include "get.hpp"

#include <json.hpp>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/update.h>
#include <sqlpp11/insert.h>
#include <sqlpp11/connection.h>
#include <sqlpp11/functions.h>
#include <sqlpp11/select.h>

#include "hlr1.h"
#include "database.hpp"

namespace sql = sqlpp::postgresql;

using json = nlohmann::json;

using namespace restbed;
using namespace std;

template<class T>
void add_have(string & query, json & data, string const& field) {
    if (data.find(field) != data.end())
        query += field + "=" + to_string(data[field].get<T>()) + ",";
};

template<>
void add_have<string>(string & query, json & data, string const& field) {
    if (data.find(field) != data.end())
        query += field + "='" + data[field].get<string>() + "',";
};

void users(Service & service) {
    auto resource = make_shared< Resource >();
    resource->set_path("/users/{id: .*}");
    {
        resource->set_method_handler("GET",
            [](const shared_ptr<Session> session) {
            auto& db = get_connection();
            const auto& request = session->get_request();
            auto sid = request->get_path_parameter("id");
            uint32_t id{ 0 };
            try {
                id = std::stoll(sid);
            }
            catch (...) {
                session->close(NOT_FOUND);
                return;
            }

            hlr1::Users users_table{};
            auto respo = json::object();
            auto rows = db(select(all_of(users_table)).from(users_table).where(users_table.id == id));

            if (rows.empty()) {
                session->close(NOT_FOUND);
                return;
            }

            const auto& row = *rows.begin();

            respo["id"] = row.id.value();
            respo["email"] = row.email.value();
            respo["first_name"] = row.firstName.value();
            respo["last_name"] = row.lastName.value();
            respo["gender"] = row.gender.value();
            respo["birth_date"] = row.birthDate.value();

            const auto resp = respo.dump();

            session->close(OK, resp, { { "Content-Length", ::to_string(resp.size()) } });
        }
        );
    }

    {
        resource->set_method_handler("POST",
            [](const shared_ptr<Session> session) {
            auto& db = get_connection();
            const auto& request = session->get_request();
            auto sid = request->get_path_parameter("id");
            uint32_t id{ 0 };
            try {
                id = std::stoll(sid);
            }
            catch (...) {
                session->close(NOT_FOUND);
                return;
            }

            hlr1::Users users_table{};

            {
                auto rows = db(select(all_of(users_table)).from(users_table).where(users_table.id == id));

                if (rows.empty()) {
                    session->close(NOT_FOUND);
                    return;
                }
            }

            auto content_length = request->get_header("Content-Length", 0);

            session->fetch(content_length, [&](const shared_ptr< Session > session, const Bytes & body) {
                std::string sdata(reinterpret_cast<const char*> (body.data()), body.size());

                try {
                    auto data = json::parse(sdata);

                    if (data.empty()) {
                        session->close(BAD_REQUEST);
                        return;
                    }

                    string query = "UPDATE users SET ";

                    add_have<string>(query, data, "email");
                    add_have<string>(query, data, "first_name");
                    add_have<string>(query, data, "last_name");
                    add_have<string>(query, data, "gender");
                    add_have<int64_t>(query, data, "birth_date");

                    query = query.substr(0, query.size() - 1) + " WHERE id = " + to_string(id);

                    auto res = db.execute(query);

                    session->close(OK, "{}", { { "Content-Length", "2" } });
                }
                catch (...) {
                    session->close(BAD_REQUEST);
                    return;
                }
            });
        }
        );
    }
    service.publish(resource);
}

void locations(Service & service) {

    auto resource = make_shared< Resource >();
    resource->set_path("/locations/{id: .*}");
    {
        resource->set_method_handler("GET",
            [](const shared_ptr<Session> session) {
            auto& db = get_connection();
            const auto& request = session->get_request();
            auto sid = request->get_path_parameter("id");
            uint32_t id{ 0 };
            try {
                id = std::stoll(sid);
            }
            catch (...) {
                session->close(NOT_FOUND);
                return;
            }

            hlr1::Location location_table{};
            auto respo = json::object();
            auto rows = db(select(all_of(location_table)).from(location_table).where(location_table.id == id));

            if (rows.empty()) {
                session->close(NOT_FOUND);
                return;
            }

            const auto& row = *rows.begin();

            respo["id"] = row.id.value();
            respo["place"] = row.place.value();
            respo["country"] = row.country.value();
            respo["city"] = row.city.value();
            respo["distance"] = row.distance.value();

            const auto resp = respo.dump();

            session->close(OK, resp, { { "Content-Length", ::to_string(resp.size()) } });
        }
        );
    }

    {
        auto resource = make_shared<Resource>();
        resource->set_path("/locations/{id: .*}");
        resource->set_method_handler("POST",
            [](const shared_ptr<Session> session) {
            auto& db = get_connection();
            const auto& request = session->get_request();
            auto sid = request->get_path_parameter("id");
            uint32_t id{ 0 };
            try {
                id = std::stoll(sid);
            }
            catch (...) {
                session->close(NOT_FOUND);
                return;
            }

            hlr1::Location location_table{};

            {
                auto rows = db(select(all_of(location_table)).from(location_table).where(location_table.id == id));

                if (rows.empty()) {
                    session->close(NOT_FOUND);
                    return;
                }
            }

            auto content_length = request->get_header("Content-Length", 0);

            session->fetch(content_length, [&](const shared_ptr< Session > session, const Bytes & body) {
                std::string sdata(reinterpret_cast<const char*> (body.data()), body.size());
                try {
                    auto data = json::parse(sdata);

                    if (data.empty()) {
                        session->close(BAD_REQUEST);
                        return;
                    }

                    string query = "UPDATE location SET ";

                    add_have<string>(query, data, "place");
                    add_have<string>(query, data, "country");
                    add_have<string>(query, data, "city");
                    add_have<uint32_t>(query, data, "distance");

                    query = query.substr(0, query.size() - 1) + " WHERE id = " + to_string(id);

                    auto res = db.execute(query);

                    session->close(OK, "{}", { { "Content-Length", "2" } });
                }
                catch (...) {
                    session->close(BAD_REQUEST);
                    return;
                }
            });
        }
        );
        service.publish(resource);
    }
    service.publish(resource);
}

void visits(Service & service) {

    auto resource = make_shared< Resource >();
    resource->set_path("/visits/{id: .*}");
    {
        resource->set_method_handler("GET",
            [](const shared_ptr<Session> session) {
            auto& db = get_connection();
            const auto& request = session->get_request();
            auto sid = request->get_path_parameter("id");
            uint32_t id{ 0 };
            try {
                id = std::stoll(sid);
            }
            catch (...) {
                session->close(NOT_FOUND);
                return;
            }

            hlr1::Visit visit_table{};
            auto respo = json::object();
            auto rows = db(select(all_of(visit_table)).from(visit_table).where(visit_table.id == id));

            if (rows.empty()) {
                session->close(NOT_FOUND);
                return;
            }

            const auto& row = *rows.begin();

            respo["id"] = row.id.value();
            respo["location"] = row.location.value();
            respo["user"] = row.usr.value();
            respo["visited_at"] = row.visitedAt.value();
            respo["mark"] = row.mark.value();

            const auto resp = respo.dump();

            session->close(OK, resp, { { "Content-Length", ::to_string(resp.size()) } });
        }
        );
    }

    {
        auto resource = make_shared<Resource>();
        resource->set_path("/location/{id: .*}");
        resource->set_method_handler("POST",
            [](const shared_ptr<Session> session) {
            auto& db = get_connection();
            const auto& request = session->get_request();
            auto sid = request->get_path_parameter("id");
            uint32_t id{ 0 };
            try {
                id = std::stoll(sid);
            }
            catch (...) {
                session->close(NOT_FOUND);
                return;
            }

            hlr1::Visit visit_table{};

            {
                auto rows = db(select(all_of(visit_table)).from(visit_table).where(visit_table.id == id));

                if (rows.empty()) {
                    session->close(NOT_FOUND);
                    return;
                }
            }

            auto content_length = request->get_header("Content-Length", 0);

            session->fetch(content_length, [&](const shared_ptr< Session > session, const Bytes & body) {
                std::string sdata(reinterpret_cast<const char*> (body.data()), body.size());
                try {
                    auto data = json::parse(sdata);

                    if (data.empty()) {
                        session->close(BAD_REQUEST);
                        return;
                    }

                    string query = "UPDATE visit SET ";

                    add_have<uint32_t>(query, data, "location");
                    //add_have<uint32_t>(query, data, "usr");
                    if (data.find("user") != data.end())
                        query += "usr='" + data["user"].get<string>() + "',";
                    add_have<uint32_t>(query, data, "visited_at");
                    add_have<uint32_t>(query, data, "mark");

                    query = query.substr(0, query.size() - 1) + " WHERE id = " + to_string(id);

                    auto res = db.execute(query);

                    session->close(OK, "{}", { { "Content-Length", "2" } });
                }
                catch (...) {
                    session->close(BAD_REQUEST);
                    return;
                }
            });
        }
        );
    }
    service.publish(resource);
}

void access_methods(Service & service) {
    users(service);
    locations(service);
    visits(service);
}
