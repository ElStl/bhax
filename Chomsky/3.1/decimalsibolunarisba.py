def dectoun(x):
    y=0
    for i in range(0,x):
        y=y*10+1
    return y;
def untodec(x):
    y=0
    while x>0:
        y=y+1
        x=int(x/10)
    return y
x=int(input("ynh: "))
c=int(input("choose one:\n1.Convert to unary\n2.Convert to decimal\n"))
a=0
if c==1:
    a= dectoun(x)
elif c==2:
    a=untodec(x)
print("result: ",a)
