cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

foreach(policy
    CMP0020
    CMP0043
    CMP0053
    CMP0054
    CMP0071
    CMP0072
    CMP0074 # CMake 3.12
    CMP0075 # CMake 3.12
    )
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()


PROJECT(ScDrv)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets REQUIRED QUIET)
find_package(Qt5Core REQUIRED QUIET)
find_package(Qt5Gui REQUIRED QUIET)
find_package(Qt5PrintSupport REQUIRED QUIET)
find_package(Qt5OpenGL REQUIRED QUIET)


include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES *.ui)
file(GLOB HDR_FILES *.h)
file(GLOB CXX_FILES *.cxx)
file(GLOB CPP_FILES *.cpp)
file(GLOB RC_FILES *.qrc)


qt5_wrap_ui(UISources ${UI_FILES} )
# CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
add_executable(ScDrv MACOSX_BUNDLE ${CXX_FILES} ${CPP_FILES} ${UISources} ${RC_FILES} ${HDR_FILES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(ScDrv ${VTK_LIBRARIES} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport Qt5::OpenGL Qt5::WinMain)
  else()
  target_link_libraries(ScDrv ${VTK_LIBRARIES} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport Qt5::OpenGL)
endif()
