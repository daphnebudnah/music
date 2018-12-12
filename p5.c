setwd("D:/divya/DA LAB")
lr<-read.table("Advertising.csv",header=TRUE,sep=",")
lr
tv <-mean(lr$TV)
rad <- mean(lr$radio)
sale <- mean(lr$sales)
tv
rad
sale

#TV
num<-0
den<-0

for(i in 0:ncol(lr)+1){
  num =num + (lr[i,2] - tv) * (lr[i,4] - sale)
  den = den + ((lr[i,2] - tv) ^ 2)
  # print(i)
}

num
den
b1<- num/den
b1

#radio
num<-0
den<-0

for(i in 0:ncol(lr)+1){
  num =num + (lr[i,3] - rad) * (lr[i,4] - sale)
  den = den + ((lr[i,3] - rad) ^ 2)
  # print(i)
}

num
den
b2<- num/den
b2

#b0
b0<-sale-(b1*tv )-(b2*rad)
b0

a <- transform(lr, yp= b0 + ( b1 * lr$TV)  + ( b2  * lr$radio ) )
k <- c(a$yp)

rss <- 0
for (i in 0:ncol(lr)+1){
  rss=rss+(lr[i,4]-k[i])^2
  #print(rss)
}
rss

rse <- sqrt(rss/(nrow(lr)-2))
rse

tss<- 0
for (i in 0:ncol(lr)+1){
  tss=tss+(lr[i,4]-sale)^2
  #print(tss)
}
tss

r_sqr <- 1 - rss / tss
r_sqr

odis1<- a[order(a$TV),c(2,5)]
odis1
plot(odis1$TV,odis1$yp,col="red")
lines(odis1$TV,odis1$yp,col="green")


odis2<- a[order(a$radio),c(3,5)]
odis2
plot(odis2$radio,odis2$yp,col="red")
lines(odis2$radio,odis2$yp,col="green")

x1<- readline(prompt="Enter TV Budget: ")
# convert character into integer
x1 <- as.integer(x1)
x1

x2<- readline(prompt="Enter Radio Budget: ")
x2 <- as.integer(x2)
x2

y <- b0 + b1 * x1 + b2 * x2
y


mod<-lm(sales~TV+radio+newspaper,data=lr)
summary(mod)
pred<-predict(mod,lr[1,])
pred
lr[1,]
