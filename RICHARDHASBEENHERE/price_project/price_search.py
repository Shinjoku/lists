
from time import sleep as wait  # Sleeping is important because my internet speed may get me tired sometimes
from selenium import webdriver  # Webdriver kinda drives us through the web, we need it because it's damn useful
from selenium.webdriver.chrome.options import Options   # It's cool to open Chrome maximized at least, right?
from .objects import Site       # Made a Site object just because POO makes things beautiful
                                

# Global variables ---------------------------------------------------------------------------------
eBay = Site('eBay').set_config([
                                'input' : 'id = "gh-ac"', 
                                'button': 'id = "gh-btn"', 
                                'price' : 'span.bold',
                                'start': '',
                               ])

# Amazon has a custom start because its price CSS structure has the first 2 elements not being prices
Amazon = Site('Amazon').set_config([
                                    'input' : 'id = "twotabsearchtextbox"',
                                    'button': 'type = "submit"', 
                                    'price' : 'span.a-size-base.a-color-base',
                                    'start' : 3
                                   ])

OLX = Site('OLX').set_config(['input' : '',
                              'button': '',
                              'price' : ''])


SITES = ['US': [eBay, Amazon], 'BR': [OLX, MercadoLivre]]

# --------------------------------------------------------------------------------------------------

# Functions ----------------------------------------------------------------------------------------
def google(search_str):  # Googles a given string

    searcher = browser.find_element_by_name('q')
    searcher.send_keys(search_str)
    searcher.submit()

def perform_search_at(site): # Returns a list of prices, and the items related to it

def get_data_from(link):

    link.click()
    wait(.6)

    page = browser.find_element_by_tag_name('body')

    soup = BeautifulSoup(page.html)

    prices = soup.find_all("span", class_= "bold")

    print(result)



# --------------------------------------------------------------------------------------------------

product = input("What's the product you want to know the prices? ")

options = Options()
options.add_argument('--start-maximized')

browser = webdriver.Chrome(chrome_options = options)
browser.get('http://google.com')

google(product + " prices")

wait(.6)

results = browser.find_elements_by_css_selector('div.rc')

for result in results:
    page = result.find_element_by_tag_name('a')
    get_data_from(page)
    browser.back()