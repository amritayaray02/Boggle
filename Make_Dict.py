to_read = open("EngDict.txt","r")
to_write = open("GameDict.txt","w")

words = to_read.readlines()
valid = []

for i in words:

    if(len(i)>3 and len(i)<27):
        i = "#" + i[:-1] + "#\n"
        valid.append(i)

to_write.writelines(valid)