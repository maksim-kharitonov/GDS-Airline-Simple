# Properties->C/C++->General->Additional Include Directories
include_directories (
    .
    "${PROJECT_SOURCE_DIR}/sirena"
    "${PROJECT_SOURCE_DIR}/amadeus"
)

file (GLOB APP_SOURCES
	  "*.h"
      "*.cpp"
      "*.cxx")
source_group("" FILES ${APP_SOURCES})

# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
add_executable (app ${APP_SOURCES})

# Properties->Linker->Input->Additional Dependencies
target_link_libraries (app  sirena amadeus)

# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
set_property(TARGET app PROPERTY FOLDER "executables")

# Properties->General->Output Directory
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_custom_command(
        TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/app/conf/
                ${PROJECT_BINARY_DIR}/bin/conf)

# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS app
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)
install(DIRECTORY "conf" 
        DESTINATION ${PROJECT_SOURCE_DIR}/_install
        FILES_MATCHING PATTERN "*.ini" )
