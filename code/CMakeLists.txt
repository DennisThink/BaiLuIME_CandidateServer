
cmake_minimum_required(VERSION 3.20)

project(MyService LANGUAGES CXX)

SET(THIRD_PARTY_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/../external/BaiLuIME_COMMON/thirdparty/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("BaiLuIME_CandidateGenerator/code/source")
include_directories(include)
SET(CORE_FOLDER ./src/core)
SET(SOURCE_CANDIDATE_GENERATOR 
./BaiLuIME_CandidateGenerator/code/source/RimeIceDictionary.cpp         
./BaiLuIME_CandidateGenerator/code/source/SimpleQuanPinGenerator.cpp
./BaiLuIME_CandidateGenerator/code/source/RimeCandidateGenerator.cpp  
./BaiLuIME_CandidateGenerator/code/source/SimpleCandidateGenerator.cpp
)

SET(SOURCE_FILE ${CORE_FOLDER}/CCandidateServer.cpp
				${CORE_FOLDER}/CandidateGeneratorManager.cpp)

add_executable(MyService  ./main.cpp ${SOURCE_FILE} ${SOURCE_CANDIDATE_GENERATOR})
target_link_libraries(MyService PRIVATE Advapi32)
add_subdirectory(src/examples)
add_subdirectory(server)
