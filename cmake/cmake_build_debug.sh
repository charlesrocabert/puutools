#!/bin/bash

#***************************************************************************
# puutools
# ---------
# Live tracking of lineage/phylogenetic trees and evolutionary events in
# individual-based forward-in-time simulations of evolution.
#
# Copyright © 2022 Charles Rocabert
# Web: https://github.com/charlesrocabert/puutools/
#
# puutools is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# puutools is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#***************************************************************************/

bash cmake_clean.sh
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

