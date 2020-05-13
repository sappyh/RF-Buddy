INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_ANNOTATOR annotator)

FIND_PATH(
    ANNOTATOR_INCLUDE_DIRS
    NAMES annotator/api.h
    HINTS $ENV{ANNOTATOR_DIR}/include
        ${PC_ANNOTATOR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    ANNOTATOR_LIBRARIES
    NAMES gnuradio-annotator
    HINTS $ENV{ANNOTATOR_DIR}/lib
        ${PC_ANNOTATOR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/annotatorTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ANNOTATOR DEFAULT_MSG ANNOTATOR_LIBRARIES ANNOTATOR_INCLUDE_DIRS)
MARK_AS_ADVANCED(ANNOTATOR_LIBRARIES ANNOTATOR_INCLUDE_DIRS)
