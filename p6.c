ds <- read.csv('lab6.csv')
ds
ds$Student = gsub('Yes',1,ds$Student)
ds$Student = gsub('No',0,ds$Student)
ds$Ethnicity = gsub('Caucasian',1,ds$Ethnicity)
ds$Ethnicity = gsub('Asian',-1,ds$Ethnicity)
ds$Ethnicity = gsub('African American',0,ds$Ethnicity)
ds$Gender = gsub('Female',1,ds$Gender)
ds$Gender = gsub('Male',0,ds$Gender)
ds

# balance = b0 + b1*student + b2*income
x1 = mean(as.integer(ds$Student))
x2 = mean(ds$Income)
y = mean(ds$Balance)
num1 = sum(((as.integer(ds$Student))-x1)*(ds$Balance-y))
deno1= sum(((as.integer(ds$Student))-x1)^2)
b1 = num1/deno1
num2 = sum((ds$Income-x2)*(ds$Balance-y))
deno2= sum((ds$Income-x2)^2)
b2 = num2/deno2
b0 = y - b1*x1 - b2*x2
ds$balance_pred_1= b0 + b1*(as.integer(ds$Student)) + b2*ds$Income
ds

# balance = b0 + b1*gender
x = mean(as.integer(ds$Gender))
y = mean(ds$Balance)
num = sum(((as.integer(ds$Gender))-x1)*(ds$Balance-y))
deno= sum(((as.integer(ds$Gender))-x1)^2)
b1 = num/deno
b0 = y - b1*x
ds$balance_pred_2= b0 + b1*(as.integer(ds$Gender))
ds

# balance = b0 + b1*ethnicity
x = mean(as.integer(ds$Ethnicity))
y = mean(ds$Balance)
num = sum(((as.integer(ds$Ethnicity))-x1)*(ds$Balance-y))
deno= sum(((as.integer(ds$Ethnicity))-x1)^2)
b1 = num/deno
b0 = y - b1*x
ds$balance_pred_3= b0 + b1*(as.integer(ds$Ethnicity))
ds
