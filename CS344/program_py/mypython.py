# Python Exploration
# By: Nathaniel Mohr

import random

fileList = ['file1', 'file2', 'file3']
num1 = random.randint(1,42)
num2 = random.randint(1,42)

for file in fileList:
    f = open(file, 'w')
    for x in range(0,10):
        f.write(chr(random.randint(97,122))) # Genereate random number from 97 - 122 (a - b in ascii)
    f.write("\n")
    f.close()

for file in fileList:
    f = open(file, 'r')
    print f.read(),
    f.close()

print num1
print num2
print num1*num2
