from selenium import webdriver
from time import sleep as wait
from selenium.webdriver.chrome.options import Options

def login():
	driver.find_element_by_name('identifier').send_keys('richardsoeuzin@gmail.com')
	driver.find_elements_by_xpath("//span[contains(text(), 'Seguinte')]")[0].click()
	wait(2)
	driver.find_element_by_name('password').send_keys('''ShoonkeyAtGoogle''')
	driver.find_elements_by_xpath("//span[contains(text(), 'Seguinte')]")[0].click()

"""
def print_window_handles():
	print("Window handles:")
	for i in driver.window_handles:
		print(i)
"""

default_options = Options()
default_options.add_argument('--start-maximized')		
# Opens a window in Google Chrome driver
driver = webdriver.Chrome(chrome_options = default_options)

# Visits the URIOJ login page
driver.get('https://urionlinejudge.com.br/judge/en/login')

# Finds the element with text = 'Google' and clicks it
google_btn = driver.find_elements_by_xpath("//a[contains(text(), 'Google')]")[0]
google_btn.click()

wait(1)

# Login with your credentials
login()
wait(1)

driver.find_elements_by_xpath("//*[contains(text(), 'Submissões')]")[0].click()
wait(1)

dropdown = driver.find_element_by_id("answer-id")
dropdown.find_element_by_xpath("//*[contains(text(), 'Accepted')]").click()
driver.find_element_by_css_selector(".submit input").click()
wait(1)


num = driver.find_element_by_id('table-info').text
driver.execute_script("window.scrollTo(0, document.body.scrollHeight)")
num = int(num[len(num)-2::])

i = 0

while i <= num:

	j = 0

	while True:
	
		driver.execute_script("window.scrollTo(0, document.body.scrollHeight * 0.3)")
		accepted_answers = driver.find_elements_by_css_selector("td.id")
		
		if j < len(accepted_answers):
			accepted_answers[j].click()
		else:
			break
			
		link = driver.find_element_by_css_selector('#dropbox a').click()
		driver.switch_to_window(driver.window_handles[1])
		#print_window_handles()
		
		if j == 0 and i == 0:
			driver.find_elements_by_css_selector('button')[0].click()
			driver.find_element_by_xpath("//p[contains(text(), 'Richard dos Santos Otto')]").click()
		
		wait(2)
		
		try:
			driver.find_element_by_xpath("//span[contains(text(), 'Permitir')]").click()
			login()
		except:
			print("Dropbox's already allowed to access your account")
			
		wait(1)
		#print_window_handles()
		driver.switch_to_window(driver.window_handles[1])
		driver.find_element_by_id('save-btn').click()
		#print_window_handles()
		driver.switch_to_window(driver.window_handles[0])
		print("Current window handler is: " + driver.current_window_handle)
		driver.back()
		j += 1
		wait(3)
	
	driver.find_element_by_xpath("//a[contains(text(), 'Próximo')]").click()
	i += 1
#driver.

# Now the need is to click the button with "Access with your Google account"(in PT-BR)
# find_element.click()
# And then continue to find what to do in the process
	
driver.quit()
	