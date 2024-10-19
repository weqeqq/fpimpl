cmake_minimum_required(VERSION 3.23)

project(FPImpl
  VERSION      0.1.1
  LANGUAGES    CXX
  DESCRIPTION "Fast PImpl Implementation"
  HOMEPAGE_URL "https://github.com/weqeq/fpimpl")

add_library(FPImplLibrary  INTERFACE)
add_library(FPImpl::FPImpl ALIAS FPImplLibrary)

target_sources(FPImplLibrary INTERFACE
  FILE_SET  HEADERS
  BASE_DIRS headers
  FILES     headers/fpimpl/fpimpl.h)

set_target_properties(FPImplLibrary PROPERTIES
  CXX_STANDARD          17
  CXX_STANDARD_REQUIRED 1
  CXX_EXTENSION         0
  EXPORT_NAME FPImpl)

install(
  TARGETS  FPImplLibrary
  EXPORT   FPImplTargets
  FILE_SET HEADERS)

install(
  EXPORT      FPImplTargets
  COMPONENT   Development
  NAMESPACE   FPImpl::
  DESTINATION lib/cmake/FPImpl)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/FPImplVersion.cmake
  COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/FPImplVersion.cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/FPImplConfig.cmake
  DESTINATION lib/cmake/FPImpl)
