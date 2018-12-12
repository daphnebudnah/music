setwd("D:/divya/DA LAB")
bank<-read.table("knn.csv",header=TRUE,sep=",")
bank
x<- readline(prompt="Enter Age: ")
x <- as.integer(x)
y <- readline(prompt="Enter Loan Amount: ")
y <- as.integer(y)
dis <- transform(bank, distance= sqrt((x-bank$Age)^2+(y-bank$Loan)^2 ) )
dis
odis<- dis[order(dis$distance),c(5,6)]
odis
k<- readline(prompt="Enter k: ")
# convert character into integer
k <- as.integer(k)
nn<-head(odis,k)
knn<-table(nn$Paid)
nn
knn
print_class<-function(x)
{
if(x){
  print("yes")
}else{
  print("no")
}
}
if(length(knn)==1)       #to check if the Paid column is entirely 1 or 0
{
  print_class(nn[[1]][1])   #if so then take 1st Paid value either 1 or 0
} else {
  if(knn[[1]][1]>knn[[2]][1])  #else both o and 1 is present then check which has got more frequency
    print_class(0)
  else
    print_class(1)
}
  
