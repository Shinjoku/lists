# Para mais simplicidade, usar esse site:
	#  http://www.sourcecode.net.br/2011/11/criando-interfaces-graficas-com-glade-e.html

from Tkinter import *

class Application:
	
	def __init__(self, master=None):
		self.widget1 = Frame(master)
		self.widget1.pack()
		self.msg = Label(self.widget1, text="Primeiro widget")
		self.msg["font"] = ("Verdana", "10", "italic", "bold")
		self.msg.pack()
		self.sair = Button(self.widget1)
		self.sair["text"] = "Clique Aqui"
		self.sair["font"] = ("Calibri", "10")
		self.sair["width"] = 10
		# self.sair["command"] = self.widget1.quit ==> para quitar
		self.sair.bind('<Button-1>', self.mudarTexto)
		self.sair.pack()
		pass
	
	
	def mudarTexto(self, event):
		if self.msg['text'] == 'Primeiro widget':
			self.msg['text'] = 'O botao recebeu um clique'
		else:
			self.msg['text'] = 'Primeiro widget'

# Main that calls the graphics
root = Tk()
Application(root)
root.mainloop()