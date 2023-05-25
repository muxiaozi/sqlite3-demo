cmake_minimum_required(VERSION 3.12.0)

project(Sqlite3Demo)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(demo main.cpp)

target_link_libraries(demo spdlog::spdlog unofficial::sqlite3::sqlite3)