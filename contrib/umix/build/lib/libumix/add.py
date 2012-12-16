import os, string
from re import compile

class Add:
  def __init__(self, adder, lang, methods, includes):
    self.lang = lang
    self.filename = os.path.splitext(adder)[0] + self.lang.ext
    self.includes = includes
    self.allmethods = []
    self.new_methods = []
    self.read()
    for method in methods:
      self.new_methods.append(
        self.lang.method_name(method, self.prefix, self.lang.naming))
    self.allmethods = self.allmethods + self.new_methods
  
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
          for line in self.usercodes:
            a(line)
          a(self.lang.comment + 'CUPPA:usercode=-\n')
        elif node.tagName == 'method':
          a(self.lang.comment + 'CUPPA:decl=+\n')
          for method in self.methods:
            a(self.lang.method_decl(method[0]) + '\n')
            a(method[1])
          for method in self.new_methods:
            a(self.lang.method_decl(method))
            for line in self.lang.method_def:
              a(string.replace(line, '$(skeleton)', self.skeleton))
            a('\n')
          a(self.lang.comment + 'CUPPA:decl=-\n')
        elif node.tagName == 'suite':
          prefix = node.getAttribute('prefix')
          if self.prefix == 0 and prefix == 'off':
            a(self.lang.comment + 'CUPPA:suite=+\n')
          if prefix == 'on' and self.prefix == 1 or prefix == 'off' and self.prefix == 0:
            a(self.lang.suite(self.skeleton, self.allmethods, self.prefix) + '\n')
          if self.prefix == 0 and prefix == 'off':
            a(self.lang.comment + 'CUPPA:suite=-')
  
  def read(self):
    self.methods = []
    self.usercodes = []
    self.prefix = 1
    method = []
    methodname = ''
    mode = 0 #(0:none, 1:include, 2:usercode, 3:decl)
    for line in open(self.filename).readlines():
      if mode is 0: #none
        if line == '%sCUPPA:include=+\n' % self.lang.comment:
          mode = 1
        elif line == '%sCUPPA:usercode=+\n' % self.lang.comment:
          mode = 2
        elif line == '%sCUPPA:decl=+\n' % self.lang.comment:
          mode = 3
        elif line == '%sCUPPA:suite=+\n' % self.lang.comment:
          self.prefix = 0
        else:
          match = self.lang.class_re.match(line)
          if match:
            if self.lang.class_re.pattern == '':
              self.skeleton = ''
            else:
              self.skeleton = match.group(1)
      elif mode is 1: #include
        file = self.lang.include_split(line)
        if file is not None:
          self.includes.append(file)
        elif line == '%sCUPPA:include=-\n' % self.lang.comment:
          mode = 0
      elif mode is 2: #usercode
        if line == '%sCUPPA:usercode=-\n' % self.lang.comment:
          mode = 0
        else:
          self.usercodes.append(line)
      elif mode is 3: #decl
        if line != '%sCUPPA:decl=-\n' % self.lang.comment:
          methoddef = self.lang.method_split(line)
          if methoddef:
            if methodname != '':
              self.methods.append((methodname,string.join(method, '')))
              self.allmethods.append(methodname)
              method = []
            methodname = methoddef
          else:
            method.append(line)
        else:
          self.methods.append((methodname,string.join(method, '')))
          self.allmethods.append(methodname)
          mode = 0

  
