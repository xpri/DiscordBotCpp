cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DiscordBotCPP)

find_package(dpp CONFIG REQUIRED)

find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME}
		src/main.cpp
	 "src/helper.cpp" "src/helper.h" "src/BOT_TOKEN.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE dpp::dpp)