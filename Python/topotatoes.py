from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import inch, cm

# ------------------------------------------------------ D O  N O T  C H A N G E -----------------------------------------------------------------------

# c.drawString(x, y, str)
# Put a string from coordinates (x,y)
# c.line(x1, y1, x2, y2)
# Draw a line from (x1, y2) to (x2, y2)

# THE TOPOTATOES SORT
class pair:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# Offset is a local margin to the right, that comes right after the data and separate the main info and the line (whose size is defined by line_size)
offset = 0.2 * cm
#blank = 1.6 * cm

# Page size (x, y), and default margin values (left, right)
page_size = pair(595, 841)
margins = pair(10, 585)

def drawSquare(c, pairs):
    
    # Say to the canvas to begin drawing a path
    p = c.beginPath()
    
    for i in range(len(pairs)):
        if i == 0:  # The path must move to a point before lining to a point
            p.moveTo(pairs[i].x, pairs[i].y)
        else:       # From now on, the path keeps lining to the vertices to form the 4 edges of the square  
            p.lineTo(pairs[i].x, pairs[i].y)

    
    # Tells the canvas to draw that path        
    c.drawPath(p)    # Working
def drawData(c, data, data_description, p, line_size):
    
    x = p.x + c.stringWidth(data) + offset
    
    c.drawString(p.x, p.y, data)
    c.drawCentredString((x * 2 + line_size)/2, p.y, data_description)
    c.line(x, p.y - 1, x + line_size, p.y - 1)        # Working
def drawTextField(c, text, y):
    
    square_size = pair(margins.y - margins.x, 4 * cm)
    
    c.drawString(margins.x, y, text)
    
    drawSquare(c, [ pair(margins.x, y - 1),                             # Start point
                    pair(margins.x + square_size.x, y - 1),             # Top right
                    pair(margins.x + square_size.x, y - square_size.y), # Bottom right
                    pair(margins.x, y - square_size.y),                 # Bottom let
                    pair(margins.x, y)                                  # Start point again
                    ])            # Working

def get_blank(c, content):
    
    length = len(content)
    accum = 0
    for key, value in range(length):
        accum += c.stringWidth(key) - 1 + value
    
    end_blank = page_size.x - accum
    
    return end_blank / length
    
    

# Instantiate a new canvas, aka pdf file, with the page size of an A4 paper        
c = canvas.Canvas("hello.pdf", pagesize=A4)

# Set the font to Times Roman at size 40
c.setFont("Courier-Bold", 30)

# Instantiate a pair that'll represent the physical properties (x and y, or witdh and height)
this_page = pair(21 * cm, 29.7 * cm)

# Tells the canvas to draw the image at x=20 and y=20, with width=20 and height=20
c.drawImage("TheBrozLogo2.png", margins.x, this_page.y - 120, width=120, height=120)

# c.stringWidth,(string)

# Tells the canvas the draw a string from the center of the coordinate (this_page.x/2, this_page.y - 50)
c.drawCentredString((this_page.x * 1.8)/3, this_page.y - 60, "MISSION REPORT")

# Tells the canvas to update the actual font size to 12
c.setFontSize(12)

# It represents the actual level (think of it like a floor) of data
level = 175

# Here is the content from up to down of the wanted page
content = {
    "ANº SS:": 2.5 * cm,
    "BDATA ENTRADA:": 2.5 * cm, 
    "CNº DE ENTRADA:": 2.5 * cm, 
    "DCLIENTE:": 6 * cm,
    "ERESPONSAVEL:": 6 * cm, 
    "FCARGO/DEPTO:": 6 * cm,
    "GSOLICITANTE:": 6 * cm,
    "HCARGO/DEPTO:": 6 * cm,
    "ITELEFONE:": 3 * cm, 
    "JRAMAL:": cm, 
    "KFAX:": 3 * cm,
    "LE-MAIL:": 4 * cm,
    "MDATA ENVIO ORÇAMENTO:": 2.5 * cm, 
    "NDATA APROVAÇÃO:": 2.5 * cm, 
    "ODATA LIBERAÇÃO:": 2.5 * cm,
    "PNº DO PEDIDO:": 2.5 * cm,
    "QVALOR MATERIAL:": 2.5 * cm, 
    "RVALOR MÃO OBRA:": 2.5 * cm, 
    "SVALOR TOTAL:": 2.5 * cm,
    "TNº NF SERVIÇO:": 2.5 * cm, 
    "UNº NF VENDA:": 2.5 * cm, 
    "VNº NF DEVOLUÇÃO:": 2.5  * cm,
    "WRESPONSÁVEL PREENCHIMENTO:": 5 * cm, 
    "XEXECUTANTE:": 4.5 * cm,
    "YDESCRIÇÃO:": 'txtf',
    "ZACESSÓRIOS:": 'txtf',
    "[OBSERVAÇÃO:": 'txtf'
}

# ------------------------------------------------------------------- D O  N O T  C H A N G E ---------------------------------------------------------
#drawData(c, "DATA ENTRADA:", "23/04/2010", pair(margins.x, page_size.y - (0.7 * level)))
#drawTextField(c, "DESCRIÇÃO", page_size.y - (0.9 * level))

percent = 0.55
X = margins.x + 150

for cont in sorted(content.items()): # cont = (key, value)
    
    Y = (percent * level) # 0.7 * 175
    
    if cont[1] == 'txtf':
        X = margins.x
        percent += 0.8
        drawTextField(c, cont[0][1::], page_size.y - Y)
    else:
        
        drawData(c, cont[0][1::], '12/16/1991', pair(X, page_size.y - Y), cont[1])
        
        X += cont[1] + c.stringWidth(cont[0]) - 1

        if (X >= page_size.x) or (page_size.x - X < cont[1]):
            percent += 0.2
            X = margins.x
    
c.save()