import string
import os

class Skeleton:
  def __init__(self, skeleton, methods, includes, prefix, lang):
    self.includes = includes
    self.prefix = prefix
    self.lang = lang
    self.methods = []
    for method in methods:
      self.methods.append(self.lang.method_name(method, prefix, self.lang.naming))
    self.skeleton, ext = os.path.splitext(skeleton)
    self.filename = self.skeleton + lang.ext
    if lang.filenaming == 'downcase':
      self.filename = string.lower(self.filename)
  
  def create(self):
    self.result = []
    a = self.result.append
    for node in self.lang.skeleton.childNodes:
      if node.nodeType is node.TEXT_NODE:
        if len(self.result) != 0 and self.result[-1] != '\n' or node.nodeValue != '\n':
          a(string.replace(node.nodeValue, '$(skeleton)', self.skeleton))
      elif node.nodeType is node.ELEMENT_NODE:
        if node.tagName == 'class':
          a(string.replace(node.getAttribute('template'), '$(skeleton)', self.skeleton))
        elif node.tagName == 'include':
          a(self.lang.comment + 'CUPPA:include=+\n')
          for file in self.includes:
            a(self.lang.include_gen(file) + '\n')
          a(self.lang.comment + 'CUPPA:include=-\n')
        elif node.tagName == 'usercode':
          a(self.lang.comment + 'CUPPA:usercode=+\n')
          for line in node.childNodes:
            a(string.replace(line.nodeValue, '$(skeleton)', self.skeleton))
          a(self.lang.comment + 'CUPPA:usercode=-\n')
        elif node.tagName == 'method':
          a(self.lang.comment + 'CUPPA:decl=+\n')
          for method in self.methods:
            a(self.lang.method_decl(method))
            for line in self.lang.method_def:
              a(string.replace(line, '$(skeleton)', self.skeleton))
            a('\n')
          a(self.lang.comment + 'CUPPA:decl=-\n')
        elif node.tagName == 'suite':
          prefix = node.getAttribute('prefix')
          if prefix == 'off' and self.prefix == 0:
            a(self.lang.comment + 'CUPPA:suite=+\n')
          if prefix == 'on' and self.prefix == 1 or prefix == 'off' and self.prefix == 0:
            a(self.lang.suite(self.skeleton, self.methods, self.prefix) + '\n')
          if prefix == 'off' and self.prefix == 0:
            a(self.lang.comment + 'CUPPA:suite=-')
    