usn<-c("1MS15CS500","1MS15CS501","1MS15CS502","1MS15CS503","1MS15CS504")
cie<-c(43,45,36,42,35)
see<-c(33,23,25,36,38)
data<-data.frame(usn,cie,see)
data
m=0
pos=0
for(i in 1:5)
{
print(usn[i])
total=cie[i]+see[i]
print("total=")
print(total)
if(total>=90)
print("Grade S")
else if(total >=75)
print("Grade A")
else if(total >=65)
print("Grade B")
else
print("Fail")
if(total>m)
{
m=total
pos=i
}
}
print("topper:");usn[pos]

csv method
MyData <- read.csv(file="student.csv")
MyData
usn<-MyData[[1]]
cie<-MyData[[2]]
see<-MyData[[3]]
dept<-MyData[[4]]
m=0
pos=0
for(i in 1:5)
{
print(usn[i])
total=cie[i]+see[i]
print("total=")
print(total)
if(total>=90)
print("Grade S")
else if(total >=75)
print("Grade A")
else if(total >=65)
print("Grade B")
else
print("Fail")
if(total>m)
{
m=total
pos=i
}
}
print("topper:");usn[pos]
