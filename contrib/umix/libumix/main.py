import os

class Main:
  def __init__(self, main, lang):
    self.lang = lang
    self.main, ext = os.path.splitext(main)
    self.filename = self.main + lang.ext
  
  def create(self):
    self.result = []
    for node in self.lang.main.childNodes:
      self.result.append(node.nodeValue)
