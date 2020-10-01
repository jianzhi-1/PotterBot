import os
import csv
import random

training_data = os.path.join(os.getcwd(), "training_data")
training_dict = {}
f = open(os.path.join(os.getcwd(), 'training_data.csv'), 'r')
reader = csv.reader(f)
for line in reader:
    if (line[0] not in training_dict):
        training_dict[line[0]] = {}
    training_dict[line[0]][line[1]] = int(line[2])

f.close()
print(training_dict)

#k = 5
#totallen = 300 #how many char
#cur = "Thank" #starting three char
#message = cur

def get_message(k, totallen, cur):
    message = cur

    for i in range(totallen):
        if (cur not in training_dict):
            #randomly generate a character
            r1 = random.randint(0, 25)
            c = chr(97 + r1)
            message = message + c
            cur = cur[1:k] + c
        else:
            total = 0
            ii = ' '
            for j in training_dict[cur]:
                total += training_dict[cur][j]
            r1 = random.randint(0, total - 1)
            for j in training_dict[cur]:
                if (r1 - training_dict[cur][j] < 0):
                    ii = j
                    break
                else:
                    r1 -= training_dict[cur][j]
            cur = cur[1:k] + ii
            message = message + ii
    return message

#print(message)
