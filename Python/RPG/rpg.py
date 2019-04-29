# rpg.py
# I'm trying to learn dictionaries, functions and the basics.

# Utility imports:
import os        # To allow os.system('clear')
import pickle    # To allow serialize objects

# Begin class Character:
class Character(object):
    name = None
    inventory = None
    
    def __init__(self, name):
        self.name = name
        self.inventory = {}
    
    def getName(self):
        return self.name
    
    def getInventory(self):
        return self.inventory

    def invToString(self):
        r = ''
        
        for k, v in self.inventory.items():
            r += '| ' + str(k) + ': ' + str(v) + '\n'
        
        return r

    def __str__(self):
        return 'Nome: ' + self.name + '\n' + 'Inventario:\n' + self.invToString() + '\n'
# End class Character

# Begin addToInventory;
def addToInventory(stuff, inv):
    
    for k in stuff:
        if k not in inv.keys():
            inv[k] = 1
        else:
            inv[k] += 1
        
    return inv
# End addToinventory;   

# Begin save:
def save(char):
    pickle.dump(char, open('personagem.pkl', 'wb'))
# End save;

# Begin updateChar:
def updateChar():
    try:
        char = pickle.load(open('personagem.pkl'))
        return char
    except:
        return None
# End updateChar

# Begin Delete:
def delete():
    try:
        arq = os.remove('personagem.pkl')
        return 1
    except:
        return None

# Begin menu;
def menu(char):
    
    os.system('clear')
    
    print '1 - Printa inventario'
    print '2 - Adiciona um loot ao inventario'
    print '3 - Informacoes do personagem'
    print '4 - Salvar jogo'
    print '5 - Deletar jogo salvo'
    print 'q - Sair'
    
    action = raw_input()
    
    if action == '1':
        pass
    
    elif action == '2':
        char.inventory = addToInventory(dragonLoot, char.inventory)
        pass
    
    elif action == '3':
        print char
        pass
    
    elif action == '4':
        save(char)
        pass
    
    elif action == '5':
        if delete():
            print 'Jogo deletado com sucesso!'
        else:
            print 'Nao existe jogo para ser deletado!'
        pass
    
    elif action == 'q':
        exit()
    
    else:
        print 'Digite um numero valido'
    
    print 'Pressione qualquer tecla para prosseguir'
    action = raw_input()
# End menu;

# Begin Main:
char = updateChar()

if char == None:
    print 'Digite o nome do seu personagem:'
    char = Character(raw_input())
    char.inventory = {'Gold': 500}       # Gold inicial

dragonLoot = {'Dagger': 1, 'Bones': 1}   # Drops do dragao

while(1):
    menu(char)
# End main;
    