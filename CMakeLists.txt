cmake_minimum_required(VERSION 2.8)

project(cybereye)

#enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV 3 REQUIRED)
find_package(Doxygen)
find_package(Boost REQUIRED)
include_directories(cybereye)

if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(
	doc #ALL # - uncomment ALL to include doc generation in 'make all' target 
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

set(HEADERS
				# Interfaces
				cybereye/collector.h
				cybereye/coremanager.h
				cybereye/engine.h
				cybereye/imgobj.h
				cybereye/tracker.h
				cybereye/dispatcher.h
				cybereye/receiver.h
				cybereye/collection.h
				#Realisations
				cybereye/bkgsegmentationengine.h
				cybereye/cybereye.h
				cybereye/objectdispatcher.h
				cybereye/objcollection.h
				cybereye/objtracker.h
				cybereye/imgcollector.h
				cybereye/watershedengine.h
				cybereye/recognitionengine.h
	)
set(SOURCES 
				src/cybereye.cpp
				src/collector.cpp
				src/coremanager.cpp
				src/engine.cpp
				src/imgobj.cpp
				src/tracker.cpp
				src/bkgsegmentationengine.cpp
				src/objectdispatcher.cpp
				src/objcollection.cpp
				src/objtracker.cpp
				src/imgcollector.cpp
				src/watershedengine.cpp
				src/recognitionengine.cpp
				${HEADERS} #QtCreator hack to display headers
	)
add_library(cybereye ${SOURCES})

install(
	TARGETS cybereye 
	LIBRARY DESTINATION lib 
	ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/cybereye)
install(FILES ce.h DESTINATION include)

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
