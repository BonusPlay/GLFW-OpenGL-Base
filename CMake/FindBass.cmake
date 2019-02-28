# - Try to find Bass
# Once done this will define
#  BASS_FOUND - System has Bass
#  BASS_INCLUDE_DIRS - The Bass include directories
#  BASS_LIBRARIES - The libraries needed to use Bass
#  BASS_DEFINITIONS - Compiler switches required for using Bass

find_package(PkgConfig)

find_path(BASS_INCLUDE_DIR bass/bass.h
          PATH_SUFFIXES bass)

find_library(BASS_LIBRARY NAMES libbass)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set BASS_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Bass DEFAULT_MSG
                                  BASS_LIBRARY BASS_INCLUDE_DIR)

mark_as_advanced(BASS_INCLUDE_DIR BASS_LIBRARY)

set(BASS_LIBRARIES ${BASS_LIBRARY})
set(BASS_INCLUDE_DIRS ${BASS_INCLUDE_DIR})