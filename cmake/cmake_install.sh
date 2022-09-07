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

echo "\n****************************************************************************"
echo "* puutools"
echo "* ---------"
echo "* Live tracking of lineage/phylogenetic trees and evolutionary events in"
echo "* individual-based forward-in-time simulations of evolution."
echo "*"
echo "* Copyright © 2022 Charles Rocabert"
echo "* Web: https://github.com/charlesrocabert/puutools/"
echo "*"
echo "* puutools is free software: you can redistribute it and/or modify"
echo "* it under the terms of the GNU General Public License as published by"
echo "* the Free Software Foundation, either version 3 of the License, or"
echo "* (at your option) any later version."
echo "*"
echo "* puutools is distributed in the hope that it will be useful,"
echo "* but WITHOUT ANY WARRANTY; without even the implied warranty of"
echo "* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
echo "* GNU General Public License for more details."
echo "*"
echo "* You should have received a copy of the GNU General Public License"
echo "* along with this program.  If not, see <http://www.gnu.org/licenses/>."
echo "****************************************************************************"

echo "\n>>> Call CMake ...\n"
cmake ..

echo "\n>>> Install puutools ...\n"
sudo cmake --install .

echo "\n>>> Do some cleaning ...\n"
bash cmake_clean.sh

