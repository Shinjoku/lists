#Usa-se append para colocar objetos numa lista
lista = []
lista.append(1)

nomes = ["zeh", "pao"]

for x in nomes:
    print x

print nomes
print nomes[1]

#Soma de listas nao soma os elementos e sim as concatena
impares = [1,3,5,7,9]
pares = [2,4,6,8]

print impares + pares

#Definicoes de listas tambem aceita repeticoes por iteradoressss
batata = [ [1,2] * 3]
for x in batata:
    print x