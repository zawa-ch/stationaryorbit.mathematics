# stationaryorbit.mathematics:/cmake/Findstationaryorbit.mathematics.cmake
# Copyright 2021 zawa-ch.
# GPLv3 (or later) license
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.
# If not, see <http://www.gnu.org/licenses/>.
#

# stationaryorbit.core の探索
if(NOT stationaryorbit.core_FOUND)
    find_path(stationaryorbit_core cmake/Findstationaryorbit.core.cmake
        PATHS
            dependencies
            ..
        PATH_SUFFIXES
            stationaryorbit.core
    )
    if(EXISTS "${stationaryorbit_core}/cmake/Findstationaryorbit.core.cmake")
        message("found Findstationaryorbit.core.cmake in ${stationaryorbit_core}/cmake")
        set(stationaryorbit.core_ROOT "${stationaryorbit_core}")
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${stationaryorbit_core}/cmake")
    endif()
    find_package(stationaryorbit.core REQUIRED)
    set(stationaryorbit_core_MODULE_NAME stationaryorbit.core::stationaryorbit.core)
endif()

# インクルードディレクトリの探索
find_path(stationaryorbit_mathematics_INCLUDE_DIR stationaryorbit/mathematics
    PATHS
        ENV stationaryorbit.mathematics_ROOT
        ENV stationaryorbit.mathematics_INCLUDE_DIR
        ${stationaryorbit.mathematics_ROOT}
    PATH_SUFFIXES
        include/
    NO_PACKAGE_ROOT_PATH
)
set(stationaryorbit.mathematics_INCLUDE_DIRS
    ${stationaryorbit.core_INCLUDE_DIRS}
    ${stationaryorbit_mathematics_INCLUDE_DIR}
)
unset(stationaryorbit_mathematics_INCLUDE_DIR)
message("include dir: ${stationaryorbit.mathematics_INCLUDE_DIRS}")
mark_as_advanced(stationaryorbit.mathematics_INCLUDE_DIRS)

list(APPEND stationaryorbit.mathematics_NAMES stationaryorbit.mathematics libstationaryorbit.mathematics)

# ライブラリパスの探索
find_library(stationaryorbit_mathematics_LIBRARY
    NAMES
        stationaryorbit.mathematics
        libstationaryorbit.mathematics
    NAMES_PER_DIR
    PATHS
        ENV stationaryorbit.mathematics_ROOT
        ENV stationaryorbit.mathematics_LIB_DIR
        ${stationaryorbit.mathematics_ROOT}
    PATH_SUFFIXES
        lib/
        build/src/
    NO_PACKAGE_ROOT_PATH
)
set(stationaryorbit.mathematics_LIBRARIES ${stationaryorbit_mathematics_LIBRARY} )
unset(stationaryorbit_mathematics_LIBRARY)
message("library dir: ${stationaryorbit.mathematics_LIBRARIES}")
mark_as_advanced(stationaryorbit.mathematics_LIBRARIES)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(stationaryorbit.mathematics
    REQIRED_VARS
        stationaryorbit.mathematics_LIBRARIES
        stationaryorbit.mathematics_INCLUDE_DIRS
)

if(stationaryorbit.mathematics_FOUND AND NOT TARGET stationaryorbit.mathematics::stationaryorbit.mathematics)
    add_library(stationaryorbit.mathematics::stationaryorbit.mathematics UNKNOWN IMPORTED)
    set_target_properties(stationaryorbit.mathematics::stationaryorbit.mathematics
        PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
            IMPORTED_LOCATION "${stationaryorbit.mathematics_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${stationaryorbit.mathematics_INCLUDE_DIRS}"
            INTERFACE_LINK_LIBRARIES stationaryorbit.core::stationaryorbit.core
    )
endif()
