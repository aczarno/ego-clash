# Install script for directory: C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem

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
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/Release/OgreRTShaderSystem.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Release" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/Release/OgreRTShaderSystem.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/RelWithDebInfo/OgreRTShaderSystem.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/RelWithDebInfo" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/RelWithDebInfo/OgreRTShaderSystem.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/MinSizeRel/OgreRTShaderSystem.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/MinSizeRel" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/MinSizeRel/OgreRTShaderSystem.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/lib/Debug/OgreRTShaderSystem_d.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Debug" TYPE SHARED_LIBRARY FILES "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/bin/Debug/OgreRTShaderSystem_d.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/RTShaderSystem" TYPE FILE FILES
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreRTShaderSystem.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderPrerequisites.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFFPColour.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFFPFog.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFFPLighting.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFFPRenderState.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFFPRenderStateBuilder.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFFPTexturing.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFFPTransform.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFunction.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderFunctionAtom.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderGenerator.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderParameter.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderProgram.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderProgramManager.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderProgramSet.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderProgramWriter.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderRenderState.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderSubRenderState.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderExNormalMapLighting.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderExPerPixelLighting.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderExIntegratedPSSM3.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderScriptTranslator.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderMaterialSerializerListener.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderProgramProcessor.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderCGProgramProcessor.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderCGProgramWriter.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderGLSLProgramProcessor.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderGLSLProgramWriter.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderProgramWriterManager.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderHLSLProgramProcessor.h"
    "C:/Users/aczarnopys/Desktop/ogreclean/ogre_src_v1-7-4/Components/RTShaderSystem/include/OgreShaderHLSLProgramWriter.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

