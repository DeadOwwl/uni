#Alina Kragel, FAMCS, 2nd course, 10th group
#1
#1.1
v <- seq(13, 6.5, len = 6);
print(v);
#1.2
vv <- vector("double", 5)
vv[1] <- abs(13-13)+2;
vv[5] <- 100;
q <- (vv[5]/vv[1])^(1/(5 - 1));
for (i in 2:5)
{
  vv[i] <- vv[i - 1] * q
}
print(vv)
#1.3
if ((v[1]+vv[1])%%2==0){
  m = rbind(v, vv)
}

if ((v[1]+vv[1])%%2!=0){
  m = rbind(vv, v)
}
print(m)

#2
dataframe <- data.frame(num = c(1, 2, 3, 4, 9999.999), logic = c(F, T, F, T, F), factor = c("I", "HOPE", "U'LL", "WORK, ", "R"))
print(dataframe)
afterframe <- dataframe[dataframe$logic>0, ]
print(afterframe)

#3
iris <- read.csv(file = "iris.csv", header = TRUE)
#3.a
print("Количество ирисов каждого вида, у которых ширина чашелистика не превосходит 3 см")
print(nrow(subset(iris, Sepal.Width <= 3 & Species == "setosa")))
print(nrow(subset(iris, Sepal.Width <= 3 & Species == "versicolor")))
print(nrow(subset(iris, Sepal.Width <= 3 & Species == "virginica")))
#3.b
print("Количество ирисов каждого вида у которых длина лепестка более 4,5 см;")
print(nrow(subset(iris, Petal.Length > 4.5 & Species == "setosa")))
print(nrow(subset(iris, Petal.Length > 4.5 & Species == "versicolor")))
print(nrow(subset(iris, Petal.Length > 4.5 & Species == "virginica")))
#3.c
print("Условия выше одновременно")
print(nrow(subset(iris, Sepal.Width <= 3 & Petal.Length > 4.5 & Species == "setosa")))
print(nrow(subset(iris, Sepal.Width <= 3 & Petal.Length > 4.5 & Species == "versicolor")))
print(nrow(subset(iris, Sepal.Width <= 3 & Petal.Length > 4.5 & Species == "virginica")))
#3.d
print("Средняя ширина лепестка у каждого вида ирисов")
print(mean(subset(iris,Species == "setosa")$Petal.Width))
print(mean(subset(iris,Species == "versicolor")$Petal.Width))
print(mean(subset(iris,Species == "virginica")$Petal.Width))

