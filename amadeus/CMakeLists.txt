file (GLOB GDS_SOURCES
	  "*.h"
      "*.cpp")

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("" FILES ${GDS_SOURCES})

# Set Properties->General->Configuration Type to Dynamic Library(.dll)
# Creates amadeus.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library(amadeus SHARED ${GDS_SOURCES})

target_link_libraries(amadeus ws2_32)

# Creates a folder "libraries" and adds target project (gds.vcproj) under it
set_property(TARGET amadeus PROPERTY FOLDER "libraries")

# Properties->General->Output Directory
set_target_properties(amadeus PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Adds logic to INSTALL.vcproj to copy gds.dll to the destination directory
install (TARGETS amadeus
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
         LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)
