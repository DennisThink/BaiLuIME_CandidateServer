cmake_minimum_required(VERSION 2.8)
project(EndServer)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
include_directories(../include/thirdparty/)
include_directories(../include/thirdparty/asio/)
include_directories(../include/thirdparty/spdlog/)
include_directories(${THIRD_PARTY_FOLDER}/json11/)
include_directories(../include/thirdparty/fmt/include/)
include_directories(../include/common/)
include_directories(../include/DaemonApp/)
include_directories(${CANDIDATE_GENERATOR_DIR}/code/include/)
if(APPLE)
    include_directories(${PROJECT_SOURCE_DIR} "/usr/local/include" "/usr/local/ssl/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    link_directories(/usr/local/lib)
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
else()
    include_directories(${PROJECT_SOURCE_DIR} "/usr/local/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

link_directories(/usr/local/ssl/lib)
link_directories(/usr/local/lib64)

if(WIN32)
else()
link_libraries(dl )
link_libraries(pthread)
endif()

set(SERVER_FILES 
		EndServerMain.cpp
		CServerSess.h CServerSess.cpp
        CEndServer.h CEndServer.cpp
        ../include/DaemonApp/DaemonSvcApp.h 
        ../include/DaemonApp/DaemonSvcApp.cpp

        ${THIRD_PARTY_FOLDER}/json11/json11.cpp
        #../include/thirdparty/fmt/src/format.cc
        #../include/thirdparty/fmt/src/posix.cc
        )

SET(CORE_FOLDER ./src/core)
SET(SOURCE_CANDIDATE_GENERATOR 
${CANDIDATE_GENERATOR_DIR}/code/src/core/RimeIceDictionary.cpp         
${CANDIDATE_GENERATOR_DIR}/code/src/core/SimpleQuanPinGenerator.cpp
${CANDIDATE_GENERATOR_DIR}/code/src/core/RimeCandidateGenerator.cpp  
${CANDIDATE_GENERATOR_DIR}/code/src/core/SimpleCandidateGenerator.cpp
${CANDIDATE_GENERATOR_DIR}/code/src/core/LongestCommonSubstringDistance.cpp
)
add_executable(EndServer ${SERVER_FILES} ${SOURCE_CANDIDATE_GENERATOR} ../../src/core/CandidateGeneratorManager.cpp)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)  