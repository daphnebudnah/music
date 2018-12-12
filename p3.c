setwd("D:/divya/DA LAB")
lr<-read.table("media.csv",header=TRUE,sep=",")
lr
budget <-mean(lr$budget)
sales <- mean(lr$sales)
num<-0
den<-0
for(i in 0:ncol(lr)+1){
  num =num + (lr[i,2] - budget) * (lr[i,3] - sales)
  den = den + ((lr[i,2] - budget) ^ 2)
  # print(i)
}
num
den
b1<- num/den
b0<- sales - b1 * budget
b0
b1
x<- readline(prompt="Enter Budget: ")
# convert character into integer
x <- as.integer(x)
y <- b0 + b1 * x
y
a <- transform(lr, yp= b0 + b1 * lr$budget   )
k <- c(a$yp)
rss <- 0
for (i in 0:ncol(lr)+1){
  rss=rss+(lr[i,3]-k[i])^2
  #print(rss)
}
rss
rse <- sqrt(rss/(nrow(lr)-2))
rse
tss<- 0
for (i in 0:ncol(lr)+1){
  tss=tss+(lr[i,3]-sales)^2
  #print(tss)
}
tss
r_sqr <- 1 - rss / tss
r_sqr
plot(lr$sales,lr$budget,col="red")
lines(lr$budget,k,col="green")
