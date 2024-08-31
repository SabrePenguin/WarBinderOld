add_library(wx_gui)

target_sources(wx_gui
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/WXGui.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/WXGui.cpp"
		
		
)

target_include_directories(wx_gui
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
		"${wxWidgets_SOURCE_DIR}/include"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/../"
		"${CMAKE_CURRENT_LIST_DIR}/../sdl_common"
		"${CMAKE_CURRENT_LIST_DIR}/../../keyController/bind"
		"${CMAKE_CURRENT_LIST_DIR}/../../keyController/control"
		"${CMAKE_CURRENT_LIST_DIR}/../../keyController/options"
		${SDL3}
)

target_link_libraries(wx_gui
		wxcore
		wxbase
		wxaui
		wxadv
		wxgl
		wxhtml
		wxmedia
		wxnet
		wxpropgrid
		wxqa
		wxribbon
		wxrichtext
		wxstc
		wxwebview
		wxxml
		wxxrc
		sdl_common_gui
	SDL3::SDL3-static
)