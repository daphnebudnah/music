small change in qn7
setwd("D:/divya/DA LAB")
survey<-read.csv("sales.csv",header = TRUE,sep = ",")
survey
survey$sales_increase<-gsub("Yes",1,survey$sales_increase)
survey$sales_increase<-gsub("No",0,survey$sales_increase)
survey
glm.fits= glm ( as.integer(sales_increase) ~ budget ,data = survey , family = binomial,control = list(maxit = 5))
summary(glm.fits)
summary ( glm.fits)$coef[ ,4]
#b0 <- summary ( glm.fits)$coef[ 1,4]
#b1 <- summary ( glm.fits)$coef[ 2,4]
glm.probs = predict(glm.fits,type="response")
glm.probs
odds <- glm.probs/(1+glm.probs)
odds
log(odds)

#alternate
setwd("D:/divya/DA LAB")
df<-read.csv("sales.csv",header = TRUE,sep = ",")
df
df$sales_increase<-gsub("Yes",1,df$sales_increase)
df$sales_increase<-gsub("No",0,df$sales_increase)
df
x = mean(df$budget)
y = mean(as.integer(df$sales_increase))
num = sum(((as.integer(df$sales_increase))-y)*(df$budget-x))
deno= sum((df$budget-x)^2)
b1 = num/deno
b0 = y - b1*x
b1
b0
summary(lm(as.integer(sales_increase)~budget,data=df))
df$logodds<-b0+b1*df$budget
df
e=2.71
df$odds<-e^df$logodds
df