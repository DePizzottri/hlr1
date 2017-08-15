#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/sqlpp11.h>

#include <restbed>

#include "get.hpp"
#include "import.hpp"
#include "select.hpp"
#include "database.hpp"

namespace sql = sqlpp::postgresql;
using namespace restbed;

int main() {


#ifdef WIN32
    import("D:/_Code/highload_r1/test_data", get_connection()); 
#else
    import("/root/data", get_connection());
#endif

    auto settings = std::make_shared<Settings>();
    settings->set_port(80);
    settings->set_worker_limit(1);
    settings->set_default_header("Content-Type", "application/json;charset=utf-8");
    settings->set_default_header("Connection", "close");
    settings->set_connection_timeout(std::chrono::seconds{ 60 });

    Service service;

    access_methods(service);
    select_methods(service);

    service.start(settings);    
}
