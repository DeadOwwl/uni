library(cluster)
library(fpc)
library(party)
#1
a <- c(rnorm(10, 3), rnorm(15, 4), rnorm(20, 5), rnorm(25, 6), rnorm(30, 7))
b <- c(rnorm(10, 13), rnorm(15, 14), rnorm(20, 15), rnorm(25, 16), rnorm(30, 17))
plot(a,b)
#2
m = matrix(c(a, b), ncol=2)
clKMeans = kmeans(m, 5)
plot(m, col = clKMeans$cluster, pch = 20 + clKMeans$cluster, main = "К-means кластеризация", xlab = "a", ylab = "b")
clClara = clara(m, 5)
plot(m, col = clClara$clustering, pch = 20 + clClara$cluster, main = "Clara кластеризация", xlab = "a", ylab = "b")
clPam = pam(m, 5)
plot(m, col = clPam$clustering,pch = 20 + clPam$cluster, main = "Pam кластеризация", xlab = "a", ylab = "b")
#3
clKM = kmeansruns(m)
plot(m, col = clKM$cluster, pch = clKM$cluster, main = "Кластеризация через kmeanruns", xlab = "a", ylab = "b")
clPa = pamk(m)
plot(m, col = clPa$pamobject$clustering,pch = clPa$pamobject$clustering, main = "Кластеризация через pamk", xlab = "a", ylab = "b")
#4
df <- data.frame(a = a,b = b,cluster = clKMeans$cluster)
plot(ctree(clKMeans$cluster~.,df))

