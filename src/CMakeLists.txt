set(PUBLIC_HEADER_LIST
	"${odd_SOURCE_DIR}/include/odd/odd.hpp"
)

SET(CXX_LIST
	OireachtasFilter.cpp
	OireachtasConf.cpp
	OireachtasApi.cpp
)

add_library(odd ${CXX_LIST} ${PUBLIC_HEADER_LIST})
add_executable(odd-bin oddcli.cpp)

set_target_properties(odd PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADER_LIST}) 

install(TARGETS odd-bin DESTINATION bin)
install(TARGETS odd 
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include/odd
)

set_target_properties(odd-bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_include_directories(odd PUBLIC ../include)
target_link_libraries(odd PRIVATE curl)

target_link_libraries(odd-bin PRIVATE odd)

target_compile_features(odd PUBLIC cxx_std_20)
target_compile_features(odd-bin PUBLIC cxx_std_20)

set_target_properties(odd-bin PROPERTIES OUTPUT_NAME odd)
