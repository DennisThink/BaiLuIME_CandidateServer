
cmake_minimum_required(VERSION 3.20)

project(MyService LANGUAGES CXX)
SET(BAILU_COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../external/BaiLuIME_COMMON/")
SET(THIRD_PARTY_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/../external/BaiLuIME_COMMON/thirdparty/")
SET(CANDIDATE_GENERATOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../external/BaiLuIME_CandidateGenerator/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("BaiLuIME_CandidateGenerator/code/source")
include_directories(include)
include_directories(${BAILU_COMMON_DIR}/include/)
SET(CORE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/core/")
SET(SOURCE_CANDIDATE_GENERATOR 
${CANDIDATE_GENERATOR_DIR}/code/src/core/RimeIceDictionary.cpp         
${CANDIDATE_GENERATOR_DIR}/code/src/core/SimpleQuanPinGenerator.cpp
${CANDIDATE_GENERATOR_DIR}/code/src/core/RimeCandidateGenerator.cpp  
${CANDIDATE_GENERATOR_DIR}/code/src/core/SimpleCandidateGenerator.cpp
${CANDIDATE_GENERATOR_DIR}/code/src/core/LongestCommonSubstringDistance.cpp
)

SET(SOURCE_FILE ${CORE_FOLDER}/CCandidateServer.cpp
				${CORE_FOLDER}/CandidateGeneratorManager.cpp)

add_executable(MyService  ./main.cpp ${SOURCE_FILE} ${SOURCE_CANDIDATE_GENERATOR})
target_link_libraries(MyService PRIVATE Advapi32)
add_subdirectory(src/examples)
add_subdirectory(server)
