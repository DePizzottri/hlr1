#include "select.hpp"

#include <json.hpp>
#include <sqlpp11/sqlpp11.h>

#include "database.hpp"
#include "hlr1.h"

namespace sql = sqlpp::postgresql;

using json = nlohmann::json;

using namespace restbed;
using namespace std;

void users_visits(Service & service) {
    auto resource = make_shared< Resource >();
    resource->set_path("/users/{id: .*}/visits");
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

            auto qParameters = request->get_query_parameters();

            hlr1::Visit visits{};
            hlr1::Location locations{};
            auto db_query = dynamic_select(db)
                .dynamic_columns(visits.mark, visits.visitedAt, locations.country)
                .dynamic_from(visits.left_outer_join(locations).on(visits.location == locations.id))
                .dynamic_where();
            //db_query.from.add(dynamic_);

            {
                auto it = qParameters.find("fromDate");
                if (it != qParameters.end()) {
                    uint32_t fromDate{ 0 };
                    try {
                        fromDate = std::stoll(it->second);
                        db_query.where.add(visits.visitedAt > fromDate);
                    }
                    catch (...) {
                        session->close(BAD_REQUEST);
                        return;
                    }
                }
            }

            {
                auto it = qParameters.find("toDate");
                if (it != qParameters.end()) {
                    uint32_t toDate{ 0 };
                    try {
                        toDate = std::stoll(it->second);
                        db_query.where.add(visits.visitedAt < toDate);
                    }
                    catch (...) {
                        session->close(BAD_REQUEST);
                        return;
                    }
                }
            }

            {
                auto it = qParameters.find("country");
                if (it != qParameters.end()) {
                    db_query.where.add(locations.country == it->second);
                }
            }

            {
                auto it = qParameters.find("toDistance");
                if (it != qParameters.end()) {
                    uint32_t toDistance{ 0 };
                    try {
                        toDistance = std::stoll(it->second);
                        db_query.where.add(locations.distance < toDistance);
                    }
                    catch (...) {
                        session->close(BAD_REQUEST);
                        return;
                    }
                }
            }

            auto resp = json::object();

            auto rows = db(db_query);

            for (const auto& row : db(db_query)) {
                auto obj = json::object();

                //row;
                obj["mark"] = row.mark.value();
                obj["visited_at"] = row.visitedAt.value();
                obj["place"] = row.country.value();

                resp["visits"].push_back(obj);
            }

            auto resps = resp.dump();

            session->close(OK, resps, { { "Content-Length", ::to_string(resps.size()) } });
        }
        );
    }
    service.publish(resource);
}

void locations_avg(Service & service) {
    auto resource = make_shared< Resource >();
    resource->set_path("/locations/{id: .*}/avg");
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

            {
                hlr1::Location location_table{};
                auto rows = db(select(all_of(location_table)).from(location_table).where(location_table.id == id));

                if (rows.empty()) {
                    session->close(NOT_FOUND);
                    return;
                }
            }


            auto qParameters = request->get_query_parameters();

            hlr1::Visit visits{};
            hlr1::Users users{};
            auto db_query = dynamic_select(db)
                .columns(avg(visits.mark).as(sqlpp::alias::a))
                .from(visits.left_outer_join(users).on(visits.usr == users.id))
                .dynamic_where();

            db_query.where.add(visits.location == id);

            {
                auto it = qParameters.find("fromDate");
                if (it != qParameters.end()) {
                    uint32_t fromDate{ 0 };
                    try {
                        fromDate = std::stoll(it->second);
                        db_query.where.add(visits.visitedAt > fromDate);
                    }
                    catch (...) {
                        session->close(BAD_REQUEST);
                        return;
                    }
                }
            }

            {
                auto it = qParameters.find("toDate");
                if (it != qParameters.end()) {
                    uint32_t toDate{ 0 };
                    try {
                        toDate = std::stoll(it->second);
                        db_query.where.add(visits.visitedAt < toDate);
                    }
                    catch (...) {
                        session->close(BAD_REQUEST);
                        return;
                    }
                }
            }

            auto today = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
            {
                auto it = qParameters.find("fromAge");
                if (it != qParameters.end()) {
                    int64_t fromAge{ 0 };
                    try {
                        fromAge = std::stoll(it->second);
                        db_query.where.add(users.birthDate  <= today - fromAge);
                    }
                    catch (...) {
                        session->close(BAD_REQUEST);
                        return;
                    }
                }
            }

            {
                auto it = qParameters.find("toAge");
                if (it != qParameters.end()) {
                    int64_t toAge{ 0 };
                    try {
                        toAge = std::stoll(it->second);
                        db_query.where.add(users.birthDate >= today - toAge);
                    }
                    catch (...) {
                        session->close(BAD_REQUEST);
                        return;
                    }
                }
            }

            {
                auto it = qParameters.find("gender");
                if (it != qParameters.end()) {
                    db_query.where.add(users.gender > it->second);
                }
            }


            auto rows = db(db_query);

            auto resp = json::object();

            if (rows.empty()) {
                auto resps = resp.dump();
                resp["avg"] = 0.0;
                session->close(OK, resps, { { "Content-Length", ::to_string(resps.size()) } });
                return;
            }

            stringstream ss;

            ss << fixed << setprecision(5) << rows.begin()->a.value();

            double l{ 0 };

            ss >> l;

            resp["avg"] = l;

            auto resps = resp.dump();

            session->close(OK, resps, { { "Content-Length", ::to_string(resps.size()) } });
        }
        );
    }
    service.publish(resource);
}

void select_methods(Service & service) {
    users_visits(service);
    locations_avg(service);
}