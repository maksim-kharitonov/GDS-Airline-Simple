file (GLOB GDS_SOURCES
	  "GdsExports.h")

file (GLOB SIRENA_SOURCES
      "SirenaExports.h"
      "SirenaExports.cpp")

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("" FILES ${GDS_SOURCES})
source_group("" FILES ${SIRENA_SOURCES})

# Properties->C/C++->General->Additional Include Directories
include_directories (.)

# Set Properties->General->Configuration Type to Dynamic Library(.dll)
# Creates gds.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library(sirena SHARED ${GDS_SOURCES} ${SIRENA_SOURCES})

# Creates a folder "libraries" and adds target project (gds.vcproj) under it
set_property(TARGET sirena PROPERTY FOLDER "libraries")

# Properties->General->Output Directory
set_target_properties(sirena PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Adds logic to INSTALL.vcproj to copy gds.dll to the destination directory
install (TARGETS sirena
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
         LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)
