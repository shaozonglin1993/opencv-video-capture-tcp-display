# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.12)

add_definitions(-std=c++11)
#项目信息
project(video_demo)

#添加源文件
aux_source_directory(. DIR_SRCS)

set(CMAKE_BUILD_TYPE "Release")

enable_language(CXX)


if(WIN32)
	include_directories("/home/john/rti_connext_dds-6.0.0/include")
	include_directories("/home/john/rti_connext_dds-6.0.0/include/ndds")
	include_directories("/usr/local/include/opencv4")
elseif(UNIX)
	include_directories("/usr/local/include/ndds")
	include_directories("/usr/local/include/opencv4")
else()
	message("-- CMAKE_SYSTEM ISN't CONFIGURED!")
endif()

if(WIN32)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		add_definitions("-DRTI_64BIT=1")
		message("-- WIN ARCH = win64") 
	else()
	    message("-- WIN ARCH = win32") 
	endif()
elseif(UNIX)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		add_definitions("-DRTI_64BIT=1") 
		message("-- UNIX ARCH = linux64")
	else()
		message("-- UNIX ARCH = linux32")
	endif ()
	
	add_definitions( -DRTI_UNIX -DRTI_LINUX )
else()
	message("-- CMAKE_SYSTEM ISN't CONFIGURED!")
endif()


#链接库
if(WIN32)
	link_directories("/home/john/rti_connext_dds-6.0.0/lib/x64Linux3gcc5.4.0")
elseif(UNIX)
	link_directories("/usr/local/lib")
else()
	message("-- CMAKE_SYSTEM ISN't CONFIGURED!")
endif()

add_executable(demo ${DIR_SRCS})

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
	target_link_libraries(demo ${OpenCV_LIBS})
endif()

if(WIN32)
elseif(UNIX)
	target_link_libraries(demo -ldl -lnsl -lm -lpthread -lrt)
else()
	message("-- CMAKE_SYSTEM ISN't CONFIGURED!")
endif()

