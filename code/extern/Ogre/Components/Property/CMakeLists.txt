#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# Paging optional component
############################################################

PROJECT(OgreProperty)

# define header and source files for the library
set (HEADER_FILES
	include/OgreProperty.h
	include/OgrePropertyPrerequisites.h
)

set (SOURCE_FILES
	src/OgreProperty.cpp
)


# Add needed definitions 
add_definitions(-DOGRE_PROPERTY_EXPORTS -D_MT -D_USRDLL)

# include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OGRE_SOURCE_DIR}/OgreMain/include)
include_directories(${Boost_INCLUDE_DIRS})

# setup target
add_library(OgreProperty ${OGRE_COMP_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADER_FILES} ${PLATFORM_SOURCE_FILES})
set_target_properties(OgreProperty PROPERTIES VERSION ${OGRE_SOVERSION})
target_link_libraries(OgreProperty OgreMain)
if (OGRE_CONFIG_THREADS)
  target_link_libraries(OgreProperty ${Boost_LIBRARIES})
endif ()

# install 
ogre_config_component(OgreProperty)

if (APPLE AND NOT OGRE_BUILD_PLATFORM_IPHONE)
    # Set the INSTALL_PATH so that Components can be installed in the application package
    set_target_properties(OgreProperty
       PROPERTIES BUILD_WITH_INSTALL_RPATH 1
       INSTALL_NAME_DIR "@executable_path/../Components"
    )

	# Copy headers into the main Ogre framework
	add_custom_command(TARGET OgreProperty POST_BUILD
	  COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp ARGS -exclude .DS_Store -exclude .hg -exclude 'CMakeLists.txt' -resolve-src-symlinks ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${OGRE_BINARY_DIR}/lib/$(CONFIGURATION)/Ogre.framework/Headers/
	)
endif()

install(FILES ${HEADER_FILES}
  DESTINATION include/OGRE/Property
)

