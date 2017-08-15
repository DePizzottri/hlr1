cmake_minimum_required(VERSION 3.2)

project(HighloadR1)

if(WIN32)
  include_directories("D:/lib/date")
  include_directories("C:/lib/boost_1_62_0")
  include_directories("C:/lib/json/src")
  include_directories("D:/lib/sqlpp11/include")
  include_directories("D:/lib/sqlpp11-connector-postgresql/include")
  include_directories("D:/Dev/pq/include")
  include_directories("C:/Code/restbed/source")
  link_directories("C:/lib/boost_1_62_0/stage_x86/lib")
  link_directories("D:/Dev/pq/lib")
  link_directories("C:/Code/restbed/build")
  link_directories("D:/lib/sqlpp11-connector-postgresql/build_vs14_u3_x86/src/$(Configuration)")
else()
  message("Build for UNIX")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")
  find_package("PostgreSQL")
  include_directories(${PostgreSQL_INCLUDE_DIRS})
  find_package("Boost" REQUIRED COMPONENTS system filesystem)
  find_package("Threads")
  include_directories(${Boost_INCLUDE_DIRS})
  include_directories("../date")
  include_directories("../json/src")
  include_directories("../sqlpp11/include")
  include_directories("../sqlpp11-connector-postgresql/include")
  include_directories("../restbed/distribution/include")
  link_directories("../restbed/distribution/library")
  link_directories("../sqlpp11-connector-postgresql/build/src")
  link_directories(${Boost_LIBRARY_DIRS})
endif(WIN32)

add_executable(HighloadR1 src/highloadr1.cpp
			src/import.cpp
			src/get.cpp
			src/select.cpp
			src/update.cpp
			src/database.cpp
)

if(WIN32)
  target_link_libraries(HighloadR1 libpq.lib)
  target_link_libraries(HighloadR1 sqlpp-postgresql.lib)
  target_link_libraries(HighloadR1 restbed.lib)
  target_link_libraries(HighloadR1 ${Boost_LIBRARIES})
else()
  target_link_libraries(HighloadR1 ${PostgreSQL_LIBRARIES})
  target_link_libraries(HighloadR1 sqlpp-postgresql)
  target_link_libraries(HighloadR1 restbed)
  target_link_libraries(HighloadR1 ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries(HighloadR1 ${Boost_LIBRARIES})
endif(WIN32)

