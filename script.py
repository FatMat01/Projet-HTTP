import os


tab =  []
for i in range(0,1000):
    tab.append("test"+str(i)+".txt")
    os.system("./parseur ./testFile/"+tab[i])
    
