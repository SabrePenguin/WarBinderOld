add_library(userInterface)

if(WXSET)
	add_subdirectory(wx_widgets)
	set(WX_LIST_SOURCES
		"${CMAKE_CURRENT_LIST_DIR}/WXWrapper.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/WXWrapper.h"
	)
	set(WX_LINK
		wx_gui
	)
endif()

target_sources(userInterface
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/UserInterface.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/ptui.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/ptui.h"
		"${CMAKE_CURRENT_LIST_DIR}/UserInterface.cpp"
		${WX_LIST_SOURCES}
)

target_include_directories(userInterface
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/../keyController/"
		"${CMAKE_CURRENT_LIST_DIR}/../keyController/control/"
		"${CMAKE_CURRENT_LIST_DIR}/../keyController/bind/"
		"${SDL3}" 
)

target_link_libraries(userInterface
	PRIVATE
	SDL3::SDL3-static
	PUBLIC
	${WX_LINK}
)