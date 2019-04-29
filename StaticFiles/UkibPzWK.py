from sys import exit as stop


class StyleObject:
    
    # A style object receives a dictionary as parameter, with all style rules
    def __init__(self, dictionary, context = 'html'):
        
        self.properties = [[k, v] for k, v in dictionary.items()]
        self.context = context
    
    def __repr__(self):
        
        # Its representation depends on its context
        # CSS context is separated by a comma and a new line
            # - selector {property: arg}
        # HTML context (inline syntax) is just separated by whitespaces 
            # - property = "arg"
        
        new_properties = map(lambda item: '{}="{}"'.format(item[0], item[1]), self.properties)
        
        if self.context == 'html':
            sep = ' '
        elif self.context == 'css':
            sep = ',\n'
        else:
            error_message = "Tried to print an StyleObject with unknown context.\n"
            error_message += "The known options are 'html' and 'css'. (No '{}')".format(self.context)
            print(error_message)
            stop(1)
        
        return sep.join(new_properties)


class TagObject:
    
    def __init__(self, name, style = None, self_closing = False):
        
        self.name = name
        self.is_self_closing = self_closing
        self.content = []
        
        if style:
            self.style = ' ' + repr(style)
        else:
            self.style = ''
        
        if self.is_self_closing:
            self.element = '<{}{}/>'.format(self.name, self.style)
        else:
            self.start = '<{}{}>'.format(self.name, self.style)
            self.content = []
            self.end = '</{}>'.format(self.name)
    
    def add(self, *tag_objects):
        
        for i in tag_objects:
            self.content.append(i)
    
    def __repr__(self):
        
        if self.is_self_closing:
            return self.element
        else:
            
            if len(self.content) == 1:
                data = repr(self.content[0])
            else:
                data = map(repr, self.content)
                data = '\n'.join(data)
            
            sep = ''
            if self.name in ['html', 'div', 'body', 'head']:
                sep = '\n'
            
            return sep.join([self.start, data, self.end])


class Page:
    
    def __init__(self, title_text, filename = 'generated_html.html', encoding = 'utf-8'):
        
        self.filename = filename
        self.file = open(filename, 'w')
        self.encoding = encoding
        
        self.title_text = title_text
        self.page = TagObject('html')
        self.elements = ['<!doctype html>', self.page]
    
    def create_default(self):
        
        body = TagObject('body')
        head = TagObject('head')
        
        meta = TagObject('meta', StyleObject({'encoding': self.encoding}), self_closing = True)
        title = TagObject('title')
        title.content.append(self.title_text)
        
        head.add(meta, title)
        
        self.page.add(head)
        self.page.add(body)
        
        self.file.write(repr(self.page))


page = Page('My Page')
page.create_default()