survey<-read.csv("Advertising.csv",header = TRUE,sep = ",")
colnames(survey)
model<-lm(sales~radio+TV+newspaper,data=survey)
summary(model)
car::vif(model)

model1<-lm(newspaper~radio+TV,survey)
summary(model1)

findComp1<-function(x){
  return((x-xbar)*(x-xbar))
}

xbar<-mean(survey$radio)

deno<-sapply(survey$radio,findComp1)
denominator<-sum(deno)

n<-length(survey$radio)
n

findComp2<-function(x){
  return((1/n)+((x-xbar)*(x-xbar)/denominator))
}

high_val<-sapply(survey$radio,findComp2)
high_val

#If high_val if greater than (p+1)/n , (p is 1 here because we use only radio)it is a high leverage point
print('High leverage points are ')
for(i in 1:n)
{
  if(high_val[i]>(2/n))
    print(survey$radio[i])
}

#Collinearity using correlation matrix
cor(survey)

#If value is close to 1 then they are correlated 
