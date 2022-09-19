#!/usr/bin/env Rscript

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
#***************************************************************************

rm(list=ls())

library("tidyverse")
library("ape")

setwd(Path to example/output folder)

best = read.table("lineage_best.txt", sep=" ", h=T)
all  = read.table("lineage_all.txt", sep=" ", h=T)
tree = read.tree("phylogenetic_tree.phb")

png("figure1.png", width=1200, height=1000, units="px")
par(mfrow=c(2,2))
plot(best$generation, best$mutation_size, xlab="Generation", ylab="Mutation size", main="\n\nFixed mutation sizes", col="cornflowerblue", type="l", lwd=2)
plot(best$generation, best$trait, xlab="Generation", ylab="Phenotypic trait", main="\n\nPhenotypic trait evolution", col="cornflowerblue", type="l", lwd=2)
plot(best$generation, best$fitness, xlab="Generation", ylab="Fitness", main="\n\nFitness", col="cornflowerblue", type="l", lwd=2)
plot(tree, root.edge=T, show.node.label=F, show.tip.label=F, use.edge.length=F, main="\n\nPhylogenetic tree (root excluded)")
mtext("Tracing back the lineage of the last best individual", side = 3, line = -1.5, outer = TRUE)
axisPhylo()
dev.off()

p = ggplot(all, aes(generation, trait)) + stat_density_2d(aes(fill = ..density..), geom = "raster", contour=F, n=200) + scale_fill_distiller(palette=4, direction=-1) + theme_minimal() + ggtitle("Phenotypic trait trace along the lineage tree") + xlab("Generation") + ylab("Phenotypic trait")
ggsave("figure2.png", p)

