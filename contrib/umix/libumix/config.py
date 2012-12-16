from xml.dom.minidom import parse
from re import compile
from sys import path
import string
import os

class XUnit:
  def __init__(self, files):
    """ create xunit dom collection """
    self.lang = {}
    self.ext = {}
    self.optext = {}
    if len(files) is not 0:
      for file in files:
        if file[-3:] == 'xml':
          doc = parse(file).firstChild
          lang = doc.getAttribute('lang')
          ext = doc.getAttribute('ext')
          optext = doc.getAttribute('optext')
          xunit = XUnitNode(doc)
          xunit.ext = ext
          xunit.naming = doc.getAttribute('naming')
          xunit.filenaming = doc.getAttribute('filenaming')
          self.lang[lang] = xunit
          self.ext[ext] = xunit
          self.optext[optext] = xunit

class XUnitNode:
  def __init__(self, dom):
    self.version = string.strip(self.pull_text(dom.getElementsByTagName('version')))
    self.reference  = string.strip(
        self.pull_text(dom.getElementsByTagName('reference')))
    self.comment = dom.getAttribute('comment')
    self.skeleton = dom.getElementsByTagName('skeleton')[0]
    self.main = dom.getElementsByTagName('main')[0]
    self.include = self.skeleton.getElementsByTagName('include')[0].getAttribute(
        'template')
    self.include_re = compile(string.replace(self.include, '$(file)', '(.+)'))
    classdef = self.skeleton.getElementsByTagName('class')[0].getAttribute('template')
    classdef = string.replace(classdef, '(', '\(')
    classdef = string.replace(classdef, ')', '\)')
    classdef = string.replace(classdef, '$\(skeleton\)', '(.+)')
    classdef = string.replace(classdef, '*', '\*')
    self.class_re = compile(classdef)
    self.method = self.skeleton.getElementsByTagName('method')[0].getAttribute(
        'template')
    self.method_def = self.pull_text(self.skeleton.getElementsByTagName('method'))
    methoddef = string.replace(self.method, '(', '\(')
    methoddef = string.replace(methoddef, ')', '\)')
    methoddef = string.replace(methoddef, '$\(methodname\)', '(\S+)')
    methoddef = string.replace(methoddef, '*', '\*')
    self.method_re = compile(methoddef)
    self.suite_skel = {}
    for suite in self.skeleton.getElementsByTagName('suite'):
      key =  suite.getAttribute('prefix')
      methods = suite.getElementsByTagName('suitemethod')
      if key == 'on':
        self.suite_skel[1] = suite
      elif key == 'off':
        self.suite_skel[0] = suite
      if len(methods) is not 0:
        self.suite_def = methods[0].getAttribute('template')
  
  def include_gen(self, file):
    return string.replace(self.include, '$(file)', file)
  
  def include_split(self, sentence):
    match = self.include_re.match(sentence)
    if match:
      return match.group(1)
    else:
      return None
   
  def method_split(self, sentence):
    match = self.method_re.match(sentence)
    if match:
      return match.group(1)
    else:
      return None
  
  def method_decl(self, method):
    return string.replace(self.method, '$(methodname)', method)
  
  def method_name(self, method, prefix, naming):
    if prefix:
      if naming == 'snake':
        return 'test_' + string.lower(method[0]) + method[1:]
      elif naming == 'camel':
        return 'test' + string.capitalize(method)
      else:
        sys.stderr.write('xml error: unknown naming option:%s' % self.lang.naming)
        sys.exit(1)
    else:
      return method
  
  def suite(self, skeleton, methods, prefix=0):
    ret = []
    a = ret.append
    for node in self.suite_skel[prefix].childNodes:
      if node.nodeType is node.TEXT_NODE and node.nodeValue != '\n':
        a(string.replace(node.nodeValue, '$(skeleton)', skeleton))
      elif node.nodeType is node.ELEMENT_NODE and node.tagName == 'suitemethod':
        for method in methods:
          a(string.replace(string.replace(self.suite_def, '$(methodname)', method),
            '$(skeleton)', skeleton))
    return string.join(ret, '\n')

  def pull_text(self, dom):
    ret = []
    a = ret.append
    for node in dom[0].childNodes:
      a(node.nodeValue)
    return string.join(ret, '')

def load():
  """ load XML File """
  files = []
  try:
    for file in os.listdir(path[-1] + '/libumix'):
      files.append(os.path.abspath(path[-1] + '/libumix/' + file))
  except OSError:
    pass
  try:
    for file in os.listdir('umix'):
      files.append(os.path.abspath('./umix') + '/' + file)
  except OSError:
    pass
  return XUnit(files)


