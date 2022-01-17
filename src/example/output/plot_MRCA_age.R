setwd("/Users/charlesrocabert/git/puutools/src/example/output/")

d = read.table("MRCA_age_N200.txt", sep=" ", h=F)

N = 200

x = seq(0, 100000)
y = (1-1/N)^(x-1)*(1/N)
yl = 1/N*exp(-(x-1)/N)
hist(d[,1], probability=T, xlab="MRCA age", ylab="Frequency", main="Distribution of the MRCA age")
lines(x, yl, col="blue", lwd=1, lty=1)
lines(x, y, col="orange", lwd=3, lty=2)
legend("topright", legend=c("Coalescence probability distribution (N=200)", "Coalesence probability distribution (N=+Inf)"), col=c("orange", "blue"), lwd=c(3,1), lty=c(2,1))
