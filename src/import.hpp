#include <boost/filesystem.hpp>
#include <sqlpp11/postgresql/connection.h>

void import(boost::filesystem::path const& dir, sqlpp::postgresql::connection & db);
