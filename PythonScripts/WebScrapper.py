import os
import requests

for index in range(1, 500):
  URL = f"https://www.gutenberg.org/cache/epub/{index}/pg{index}.txt"
  page = requests.get(URL)

  text = page.text
  if not text[:15] == '<!DOCTYPE html>' and not os.path.isfile(f"books/{index}.txt"):
    file = open(f"books/{index}.txt", "w+", encoding='utf-8')
    file.write(page.text)
    file.close()