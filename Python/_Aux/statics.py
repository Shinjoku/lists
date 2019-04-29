import math

def media(arr):
    return sum(arr)/len(arr)

def var(arr, media):
    count = 0
    for i in arr:
        count += (i - media) ** 2
    return count

def std_dev(variance):
    return math.sqrt(variance)



arr = list(map(float, input().split()))
middle = media(arr)
variance = var(arr, middle)
standard_deviation = std_dev(variance)

if(len(arr) % 2 == 0):
    mediana = (arr[math.floor(len(arr) / 2)] + arr[math.floor((len(arr) + 1) / 2)]) / 2
else:
    mediana = arr[math.floor(len(arr)/2)]
    
print ('Tamanho: ', len(arr), 'Mediana',  mediana, 'Média:', middle, 'Variância:', variance, 'Desvio Padrão:', standard_deviation)