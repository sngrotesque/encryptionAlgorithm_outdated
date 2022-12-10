minValue = 1
maxValue = 50

result = []

for index in range(minValue, maxValue + 1):
    for x in range(2, index):
        print(index, x, index % x)
        if (index % x == 0):
            break
    else:
        result.append(index)

print(result)
