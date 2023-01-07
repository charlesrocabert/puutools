#!/usr/bin/env Rscript

#***************************************************************************
# puutools
# ---------
# Easy-to-use C++ library for the live tracking of lineage and phylogenetic
# trees in individual-based forward-in-time simulations.
#
# Copyright © 2022-2023 Charles Rocabert
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
#***************************************************************************

rm(list=ls())

library("ape")

setwd(Path to example/output folder)

best = read.table("lineage_best.txt", sep=" ", h=T)
all  = read.table("lineage_all.txt", sep=" ", h=T)
tree = read.tree("phylogenetic_tree.phb")

png("figure1.png", width=1000, height=800, units="px", pointsize=20)
par(mfrow=c(2,2))
plot(best$generation, best$mutation_size, xlab="Generation", ylab="Mutation size", main="\n\nFixed mutation sizes", col="cornflowerblue", type="l", lwd=2)
plot(best$generation, best$trait, xlab="Generation", ylab="Phenotypic trait", main="\n\nPhenotypic trait evolution", col="cornflowerblue", type="l", lwd=2)
plot(best$generation, best$fitness, xlab="Generation", ylab="Fitness", main="\n\nFitness", col="cornflowerblue", type="l", lwd=2)
plot(tree, root.edge=T, show.node.label=F, show.tip.label=F, use.edge.length=F, main="\n\nPhylogenetic tree (root excluded)")
mtext("Tracing back the lineage of the last best individual", side = 3, line = -1.5, outer = TRUE)
axisPhylo()
dev.off()

