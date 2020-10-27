set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_STL_SUPPORT YES)

doxygen_add_docs(docs odd/odd.hpp
	"${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
)

find_program(POD2MAN_EXECUTABLE NAMES pod2man)

set(POD2MAN_OPTS
	-s 1
	-c "odd manual"
)

set(MAN_NAMES odd.1)
set(MAN_FILES)
foreach(m IN LISTS MAN_NAMES)
	set(mf ${CMAKE_CURRENT_BINARY_DIR}/${m})
	set(ms ${CMAKE_CURRENT_SOURCE_DIR}/${m}.pod)
	add_custom_command(OUTPUT ${mf}
		COMMAND ${POD2MAN_EXECUTABLE} ${POD2MAN_OPTS} ${ms} ${mf}
		DEPENDS ${ms}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Building manpage ${mf}"
		VERBATIM
	)
	list(APPEND MAN_FILES ${mf})
endforeach()

add_custom_target(man ALL DEPENDS ${MAN_FILES})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/odd.1 DESTINATION ${CMAKE_INSTALL_PREFIX}/man/man1)
