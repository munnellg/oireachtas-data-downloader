set(HEADER_LIST
	"${odd_SOURCE_DIR}/include/odd/odd.hpp"
)

SET(CXX_LIST
	OireachtasFilter.cpp
	OireachtasConf.cpp
	OireachtasApi.cpp
)

add_library(odd-dev ${CXX_LIST} ${HEADER_LIST})
add_executable(odd main.cpp)

set_target_properties(odd PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# target_include_directories(odd PUBLIC ../include)
target_include_directories(odd-dev PUBLIC ../include)
target_link_libraries(odd-dev PRIVATE curl)

target_link_libraries(odd PRIVATE odd-dev)

target_compile_features(odd-dev PUBLIC cxx_std_20)
target_compile_features(odd PUBLIC cxx_std_20)
