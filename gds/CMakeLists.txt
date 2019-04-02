# Collect sources into the variable GDS_SOURCES with 
# having to explicitly list each header and source file
file (GLOB GDS_SOURCES
	  "*.h")

# Collect sources into the variable SIMPLE_FUNCTION_SOURCES  
file (GLOB SIMPLE_FUNCTION_SOURCES
      "simple/*.h"
      "simple/*.cxx")

# Another way to collect sources into a variable ADVANCED_FUNCTION_SOURCES
# by explicitly specifying the source files
set  (ADVANCED_FUNCTION_SOURCES
      "advanced/AdvancedFunctions.h"
      "advanced/AdvancedFunctions.cxx")

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("" FILES ${GDS_SOURCES})
source_group("simple" FILES ${SIMPLE_FUNCTION_SOURCES})
source_group("advanced" FILES ${ADVANCED_FUNCTION_SOURCES})

# Properties->C/C++->General->Additional Include Directories
include_directories (.)

# Set Properties->General->Configuration Type to Dynamic Library(.dll)
# Creates gds.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library(gds SHARED ${GDS_SOURCES} ${SIMPLE_FUNCTION_SOURCES} ${ADVANCED_FUNCTION_SOURCES})

# Creates a folder "libraries" and adds target project (gds.vcproj) under it
set_property(TARGET gds PROPERTY FOLDER "libraries")

# Properties->General->Output Directory
set_target_properties(gds PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Adds logic to INSTALL.vcproj to copy gds.dll to the destination directory
install (TARGETS gds
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
         LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)
