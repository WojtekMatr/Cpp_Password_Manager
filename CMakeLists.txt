cmake_minimum_required(VERSION 3.15)
project(PasswordManagerCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ---------- nlohmann/json ----------
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# ---------- sqlite3 ----------
FetchContent_Declare(
    sqlite3
    GIT_REPOSITORY https://github.com/sqlite/sqlite.git
    GIT_TAG version-3.45.1
)
FetchContent_MakeAvailable(sqlite3)

# ---------- Your app ----------
add_executable(PasswordManager
    manager.cpp
    ManagerHeader.h
)

# ---------- libsodium (manual Windows build) ----------
target_include_directories(PasswordManager PRIVATE
    ${PROJECT_SOURCE_DIR}/include/libsodium/include
)

target_link_libraries(PasswordManager PRIVATE
    nlohmann_json::nlohmann_json
    sqlite3
    ${PROJECT_SOURCE_DIR}/include/libsodium/x64/Release/v143/dynamic/libsodium.lib
)
