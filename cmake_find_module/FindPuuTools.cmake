##
## Try to find puutools library
## (see https://github.com/charlesrocabert/puutools/)
## Once run this will define:
##
## PUUTOOLS_FOUND = system has PUUTOOLS lib
##
## PUUTOOLS_INCLUDE_DIR = where to find headers
##
## Charles Rocabert 09/2022
## (based on GSL module from Felix Woelk and Jan Woetzel)
##
## https://charlesrocabert.github.io/
## ----------------------------------
##


IF(WIN32)

  SET(PUUTOOLS_MINGW_PREFIX "c:/msys/local")
  SET(PUUTOOLS_MSVC_PREFIX "$ENV{LIB_DIR}")

  FIND_PATH(PUUTOOLS_INCLUDE_DIR puutools.h
    ${PUUTOOLS_MINGW_PREFIX}/include
    ${PUUTOOLS_MSVC_PREFIX}/include
    )

ELSE(WIN32)
  IF(UNIX)

    SET(PUUTOOLS_USR_PREFIX "/usr")
    SET(PUUTOOLS_USR_LOCAL_PREFIX "/usr/local")
    SET(PUUTOOLS_TARGET_PREFIX "/opt/target")
    SET(PUUTOOLS_OPT_LOCAL_PREFIX "/opt/local")

    FIND_PATH(PUUTOOLS_INCLUDE_DIR puutools.h
      ${PUUTOOLS_USR_PREFIX}/include
      ${PUUTOOLS_USR_LOCAL_PREFIX}/include
      ${PUUTOOLS_TARGET_PREFIX}/include
      ${PUUTOOLS_OPT_LOCAL_PREFIX}/include
      )

    MARK_AS_ADVANCED(
        GSL_INCLUDE_DIR
      )

  ENDIF(UNIX)
ENDIF(WIN32)


IF(PUUTOOLS_INCLUDE_DIR)

  SET(PUUTOOLS_FOUND 1)

  MESSAGE(STATUS "Using puutools from ${PUUTOOLS_INCLUDE_DIR}")

ELSE(PUUTOOLS_INCLUDE_DIR)

  MESSAGE(STATUS "Could not find puutools")

ENDIF(PUUTOOLS_INCLUDE_DIR)

