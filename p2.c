setwd("D:/divya/DA LAB")
dm <- read.csv("./week3_data.csv")
stud<-read.csv("./week3_data.csv",header=TRUE,sep=",",stringsAsFactors=FALSE)
stud
#	Check for impossible data for marks
check_marks <- function(x){
  if(as.numeric(x)){}
  else{cat("Impossible ",x,"\n")}
  if(as.numeric(x)> 0 & as.numeric(x) <100 ){}
  else{cat("Impossible ",x,"\n")}
}
c = sapply(stud$sem1, FUN = check_marks)
c = sapply(stud$sem2, FUN = check_marks)
c = sapply(stud$sem3, FUN = check_marks)

# Check for impossible data for gender
check_gender <- function(x){
  gender <- c('f','m','female','male')
  x <- tolower(x)
  if(x %in% gender){
  }
  else{
    cat("Impossible ",x,"\n")
  }
}
a = sapply(stud$gender, FUN = check_gender)

# Check for impossible data for name
check_name <- function(x){
  grep("[^[:alpha:]]",x)
}
b = check_name(stud$name)
cat("Impossible ",b)

#If marks field has>100 and <0 replace them with respective values
stud$sem1[stud$sem1>100]<-(100)
stud$sem1[stud$sem1<0]<-(0)
stud$sem2[stud$sem2>100]<-(100)
stud$sem2[stud$sem2<0]<-(0)
stud$sem3[stud$sem3>100]<-(100)
stud$sem3[stud$sem3<0]<-(0)


#If gender col has  "f","female" replace with "F". Similarly do for Male gender value also.
#If gender col has any other value replace with null
stud$gender <- ifelse(stud$gender == 'f'|stud$gender=="female", 'F', stud$gender)
stud$gender <- ifelse(stud$gender == 'm'|stud$gender=="male", 'M', stud$gender)
stud$gender <- ifelse(stud$gender !='M'&stud$gender!='F', 'NA', stud$gender)

#name col should not have special char, numbers. Check for this and omit such characters.
stud$name<- gsub("[^[:alpha:]]", "", stud$name,ignore.case = TRUE)

#sub wise average
stud$sem1_avg<-mean(stud$sem1)
stud$sem2_avg<-mean(stud$sem2)
stud$sem3_avg<-mean(stud$sem3)

print(stud)
