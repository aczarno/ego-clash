# Install script for directory: C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/OGRE")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/Release/OgrePaging.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Release" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/Release/OgrePaging.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/RelWithDebInfo/OgrePaging.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/RelWithDebInfo" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/RelWithDebInfo/OgrePaging.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/MinSizeRel/OgrePaging.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/MinSizeRel" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/MinSizeRel/OgrePaging.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/Debug/OgrePaging_d.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Debug" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/Debug/OgrePaging_d.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/Paging" TYPE FILE FILES
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgreGrid2DPageStrategy.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePage.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageConnection.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageContent.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageContentCollection.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageContentCollectionFactory.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageContentFactory.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePagedWorld.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePagedWorldSection.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageFileFormats.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageManager.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePageStrategy.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePaging.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgrePagingPrerequisites.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/Paging/include/OgreSimplePageContentCollection.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

