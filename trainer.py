import os
import csv

#print(os.getcwd())
training_data = os.path.join(os.getcwd(), "training_data")
#print(os.listdir(training_data))
training_dict = {}
k = 5

for filename in os.listdir(training_data):
    print(filename)
    f = open(os.path.join(training_data, filename), 'r')
    content = f.read()
    for i in range(len(content)):
        if (i < k):
            continue
        else:
            if (content[i - k:i] not in training_dict):
                training_dict[content[i - k:i]] = {}
                training_dict[content[i - k:i]][content[i]] = 1
            else:
                if (content[i] not in training_dict[content[i - k:i]]):
                    training_dict[content[i - k:i]][content[i]] = 1
                else:
                    training_dict[content[i - k:i]][content[i]] += 1
    f.close()

with open(os.path.join(os.getcwd(), 'training_data.csv'), 'w') as f:
    for i in training_dict:
        for j in training_dict[i]:
            f.write(str('"') + i + str('"'))
            f.write(',')
            f.write(str('"') + j + str('"'))
            f.write(',')
            f.write(str('"') + str(training_dict[i][j]) + str('"'))
            f.write('\n')
f.close()



#for i in training_dict:
#    for j in i:
#        print(j)
    #print(i)
    #print(len(content))


#Build the bridges

#Export it outside
