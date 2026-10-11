
cmake_minimum_required(VERSION 3.20)

project(MyService LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("BaiLuIME_CandidateGenerator/code/source")
SET(SOURCE_CANDIDATE_GENERATOR 
./BaiLuIME_CandidateGenerator/code/source/RimeIceDictionary.cpp         
./BaiLuIME_CandidateGenerator/code/source/SimpleQuanPinGenerator.cpp
./BaiLuIME_CandidateGenerator/code/source/RimeCandidateGenerator.cpp  
./BaiLuIME_CandidateGenerator/code/source/SimpleCandidateGenerator.cpp
)

SET(SOURCE_FILE 
		./CCandidateServer.cpp
		./CCandidateServer.hpp
		./CandidateGeneratorManager.hpp 
		./CandidateGeneratorManager.cpp)

add_executable(MyService  ./main.cpp ${SOURCE_FILE} ${SOURCE_CANDIDATE_GENERATOR})

add_executable(ConsoleService  ./testMain.cpp ${SOURCE_FILE} ${SOURCE_CANDIDATE_GENERATOR})
target_link_libraries(MyService PRIVATE Advapi32)
add_subdirectory(server)