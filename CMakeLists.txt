# CMakeList.txt : CMake project for CZT_spectrum_tail, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CZTSpectrumTail")

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

# Add source to this project's executable.
add_executable (CZTSpectrumTail "CZTSpectrumTail.cpp" ${sources} ${headers})
target_link_libraries(CZTSpectrumTail ${Geant4_LIBRARIES})

set(CZTSPECTRUMTAIL_SCRIPTS
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
)

foreach(_script ${CZTSPECTRUMTAIL_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
endforeach()

set_property(TARGET CZTSpectrumTail PROPERTY CXX_STANDARD 17)

# TODO: Add tests and install targets if needed.
