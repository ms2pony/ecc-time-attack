hash_str="5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"

e="0x{}"

# print(e.format(hash_str[0:2]))

i=len(hash_str);array=[]
while(i>0):
    # print(hash_str[i:i-2])
    array.append(e.format(hash_str[i-2:i]))
    i-=2

print(array)

cArray="{"

for i in array:
    i+=","
    # print(i)
    cArray+=i

cArray=cArray[0:-1]

cArray+="}"

print(cArray)
