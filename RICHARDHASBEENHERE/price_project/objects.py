class Site:

    def __init__(self, name):
        self.name = name
        self.url = 'http://' + self.name.lower() + ".com"

    def set_config(self, config):
        self.config = config
        self.start = getattr(self, 'start', 0) # getattr(object, name[, default_value])
        del self.config['start']