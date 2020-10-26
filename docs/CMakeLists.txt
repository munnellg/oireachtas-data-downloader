set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_STL_SUPPORT YES)

doxygen_add_docs(docs odd/global.hpp
	"${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
)
