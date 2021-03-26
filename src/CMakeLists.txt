# stationaryorbit.mathematics:/src/CMakeLists.txt
# Copyright 2020-2021 zawa-ch.
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

add_library(stationaryorbit.mathematics SHARED
    ${Include_Dir}/stationaryorbit/mathematics.algorithm.hpp
    ${Include_Dir}/stationaryorbit/mathematics.fuzzy.hpp
    ${Include_Dir}/stationaryorbit/mathematics.primitives.hpp
    ${Include_Dir}/stationaryorbit/mathematics.set.hpp
    differencial.cpp
    fuzzybool.cpp
    integral.cpp
    newtoncoef.cpp
    polynomialfunction.cpp
    taylorseries.cpp
)
