cmake_minimum_required(VERSION 2.8)

project(cybereye)
find_package(OpenCV 3)
include_directories(cybereye)
set(HEADERS
		cybereye/collector.h
		cybereye/coremanager.h
		cybereye/engine.h
		cybereye/imgobj.h
		cybereye/model.h
		cybereye/tracker.h
                cybereye/dispatcher.h
	)
set(SOURCES 
		src/collector.cpp
		src/coremanager.cpp
		src/engine.cpp
		src/imgobj.cpp
		src/model.cpp
		src/tracker.cpp
		${HEADERS} #QtCreator hack to display headers
	)
add_library(cybereye ${SOURCES})
install(
	TARGETS cybereye 
	LIBRARY DESTINATION lib 
	ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/cybereye)
install(FILES cybereye.h DESTINATION include)

message("\n")
if(${BUILD_SHARED_LIBS})
message("Building library: SHARED")
else()
message("Building library: STATIC")
endif()

message("Install directory: ${CMAKE_INSTALL_PREFIX}")
message("OpenCV location: ${OpenCV_DIR}")
message("OpenCV version: ${OpenCV_VERSION}")
message("\nTo remove CyberEye after 'make install' execute 'xargs rm -rf < install_manifest.txt' from the build directory")
message("\n")
