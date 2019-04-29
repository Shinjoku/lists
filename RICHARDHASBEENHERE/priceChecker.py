from selenium import webdriver
from time import sleep
from selenium.webdriver.chrome.options import Options

LIST_SITES = [
    'www.pichau.com.br',
    'www.kabum.com.br',
    'www.balaodainformatica.com.br',
    'www.mercadolivre.com.br',
    'www.saraiva.com.br'
]

LIST_PRODUCTS = [
    'GTX 1060',
    'GTX 960',
    'GTX 760',
    'R9 270x',
]


# Loading Chrome Driver's options
default_options = Options()
default_options.add_argument('--start-maximized')

driver = webdriver.Chrome(chrome_options = default_options)

# This will search on every site the list of products.
for site in LIST_SITES:
    
    driver.get(site)
    for product in LIST_PRODUCTS:
        driver.find_elements_by_type("text")[0].send_keys(input(product))
        driver.find_elements_by_type("submit")[0].click()
        sleep(2)
        
    