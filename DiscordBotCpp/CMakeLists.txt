cmake_minimum_required(VERSION 3.15)

project(DiscordBotCPP)

find_package(dpp CONFIG REQUIRED)

find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME}
		src/main.cpp
  "src/BOT_TOKEN.cpp" "src/test.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE dpp::dpp)