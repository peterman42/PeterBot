cmake_minimum_required(VERSION 2.6)
project(PeterBot)
FILE(GLOB_RECURSE INC_ALL "include/*.h")
#FILE(GLOB_RECURSE SRC_ALL "src/.cpp")

set(HEADERS  include include 3rd_party/crow-0.1/include 3rd_party/WiringPi-final_official_2.50/wiringPi)
set(SOURCES src/serverBot.cpp 
            src/main.cpp 
            src/robot.cpp 
            src/robot_back.cpp 
            src/robot_front.cpp 
            src/robot_left.cpp 
            src/robot_right.cpp 
            src/wheel.cpp 
            src/distance_object.cpp 
            src/move_watchdog.cpp 
            src/move.cpp)

if(WIN32)
    set(HEADERS /usr/local/include /usr/include )
    set(TARGET_COMPILE_OPTIONS -std=c++11 -g -Wall -pedantic)
    set(LINK_LIBRARIES wiringPi pthread boost_system crypt rt)
else(WIN32) # OTHER THAN WINDOWS
    set(TARGET_COMPILE_OPTIONS -std=c++11 -g -Wall -pedantic -Wextra)
    set(LINK_LIBRARIES wiringPi pthread boost_system crypt rt)
endif(WIN32)

include_directories(${HEADERS})
add_executable(${PROJECT_NAME} ${SOURCES} ${INC_ALL})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})
target_compile_options(${PROJECT_NAME} PUBLIC ${TARGET_COMPILE_OPTIONS})
install(TARGETS ${PROJECT_NAME} DESTINATION build)

