cmake_minimum_required(VERSION 3.23)

project(FPImpl
  VERSION      0.1.0
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
