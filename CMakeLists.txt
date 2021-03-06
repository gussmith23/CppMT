project (CMT)

cmake_minimum_required (VERSION 2.6)

option(BUILD_TRAX_CLIENT "Build the trax client." OFF)

find_package(OpenCV REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_definitions ("-Wall")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(opensurf/include/)

if(WIN32)
add_executable (cmt common.cpp gui.cpp main.cpp
    CMT.cpp Consensus.cpp Fusion.cpp Matcher.cpp Tracker.cpp
    fastcluster/fastcluster.cpp getopt/getopt.cpp opensurf/src/fasthessian.cpp opensurf/src/integral.cpp opensurf/src/ip_interface.cpp opensurf/src/ipoint.cpp opensurf/src/surf.cpp opensurf/src/utils.cpp opensurf/src/opensurf_cmt_wrapper.cpp
    )
else()
add_executable (cmt common.cpp gui.cpp main.cpp
    CMT.cpp Consensus.cpp Fusion.cpp Matcher.cpp Tracker.cpp
    fastcluster/fastcluster.cpp opensurf/src/fasthessian.cpp opensurf/src/integral.cpp opensurf/src/ip_interface.cpp opensurf/src/ipoint.cpp opensurf/src/surf.cpp opensurf/src/utils.cpp opensurf/src/opensurf_cmt_wrapper.cpp)
endif()

target_link_libraries(cmt ${OpenCV_LIBS})

if(BUILD_TRAX_CLIENT)
    set(TRAX_DIR "" CACHE FILEPATH "Path to trax")

    include_directories(${TRAX_DIR}/include)

    add_executable (trax_client cmt common.cpp gui.cpp trax.cpp
        CMT.cpp Consensus.cpp Fusion.cpp Matcher.cpp Tracker.cpp
        fastcluster/fastcluster.cpp)

    find_library(TRAX_LIBRARY NAMES trax HINTS "${TRAX_DIR}/lib")

    target_link_libraries(trax_client ${OpenCV_LIBS} ${TRAX_LIBRARY})

endif()

