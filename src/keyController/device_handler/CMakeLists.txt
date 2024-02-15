add_library(Devices)

target_sources(Devices
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/DeviceImporter.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/DeviceImporter.cpp"
		${OS_HEADER}
)

target_include_directories(Devices
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/../"
)

target_include_directories(Devices PRIVATE ${SDL2})

target_link_libraries(Devices PRIVATE SDL2::SDL2-static)
