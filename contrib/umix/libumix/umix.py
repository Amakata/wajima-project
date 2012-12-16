from config import load
from getopt import getopt
from skeleton import Skeleton
from add import Add
from main import Main
import sys, string, os

def init(argv):
  opts, methods = getopt(argv, 'hl:r:vm:s:a:fi:NP:ducS', ['help', 'lang=', 'reference=', 'version' ,'main=', 'skeleton=', 'add=', 'cout', 'force', 'include=', 'prefix=', 'downcase', 'uppercase', 'camel', 'snake'])
  xunit = load()
  includes = []
  prefix = 1
  force = 0
  cout = 0
  add = None
  skeleton = None
  main = None
  lang = None
  downcase = None
  snake = None
  for opt, value in opts:
    if '-h' == opt or '--help' == opt:
      usage()
      sys.exit(0)
    elif '-v' == opt or '--version' == opt:
      version()
      for lang in xunit.lang.items():
        print '  ' + lang[1].version + '(--lang ' + lang[0] + ')'
      sys.exit(0)
    elif '-r' == opt or '--reference' == opt:
      try:
        print xunit.lang[value].reference
      except KeyError:
        sys.stderr.write('Un Support Language:%s' % value)
        sys.exit(1)
    elif '-l' == opt or '--lang' == opt:
      try:
        lang = xunit.lang[value]
      except KeyError:
        sys.stderr.write('Un Support Language:%s' % value)
        sys.exit(1)
    elif '-m' == opt or '--main' == opt:
      main = value
    elif '-s' == opt or '--skeleton' == opt:
      skeleton = value
    elif '-a' == opt or '--add' == opt:
      add = value
      force = 1
    elif '-P' == opt or '--prefix' == opt:
      if value == '+':
        prefix = 1
      elif value == '-':
        prefix = 0
      else:
        raise ValueError, "prefix option can accept only '+' or '-'"
    elif '-f' == opt or '--force' == opt:
      force = 1
    elif '-d' == opt or '--downcase' == opt:
      downcase = 1
    elif '-u' == opt or '--uppercase' == opt:
      downcase = 0
    elif '-S' == opt or '--snake' == opt:
      snake = 1
    elif '-c' == opt or '--camel' == opt:
      snake = 0
    elif '--cout' == opt:
      cout = 1
    elif '-i' == opt or '--include' == opt:
      includes.append(value)
  if add is not None:
    add = Add(add, language(xunit, lang, add), methods, includes)
    add.create()
    output(add.filename, add.result, force, cout)
  else:
    if skeleton is not None:
      skeleton = Skeleton(skeleton, methods, includes, prefix, 
        language(xunit, lang, skeleton))
      skeleton.create()
      output(skeleton.filename, skeleton.result, force, cout)
    if main is not None:
      main = Main(main, language(xunit, lang, main))
      main.create()
      output(main.filename, main.result, force, cout)

def output(filename, contents, force, cout):
  if contents[0] == '\n':
    output = string.join(contents[1:], '')
  else:
    output = string.join(contents, '')
  if cout:
    print output
    return
  sys.stderr.write('writing %s ...' % filename)
  if os.path.exists(filename):
    if not force:
      sys.stderr.write('already exist(skip)\n')
      sys.exit(1)
    else:
      os.rename(filename, filename + '.bak')
  open(filename, 'w+').write(output)
  sys.stderr.write('finish!\n')
  
def language(xunit, lang, path):
  if lang is not None:
    return lang
  top, ext = os.path.splitext(path)
  try:
    return xunit.optext[ext]
  except KeyError:
    sys.stderr.write('No Support Extension: %s' % ext)
    sys.exit(1)

def version():
   print 'Umigame with XML(umix) 1.0\n'
   
def usage():
  print """
create skeleton: umix -s Class [-l lang] [-Pf] [--cout] [-i include] [methods]
create main:     umix -m MainFile [-l lang] [-f] [--cout]
add method:      umix -a File [-l lang] [--cout] [-i include] [methods]

mode_option:
  --help,      -h        : display help
  --lang,      -l <Name> : output language
  --reference, -r <Name> : assertion quick reference for <Name> language
  --version,   -v        : print version
  --main,      -m <Name> : create test launcher
  --skeleton,  -s <Name> : create skeleton class <Name>
  --add,       -a <Name> : add testmethod to existing TestCase file

common_options:
  --cout                 : output from standard-out
  --force,     -f        : force creation
  --include,   -i <Name> : include 'Name'
  --prefix,    -P        : add prefix 'test'
"""

def main():
  if '--dos' in sys.argv:
    argv = []
    for line in open(sys.argv[2]).readlines():
      arg = string.replace(line, '\r', '')
      argv.append(string.replace(arg, '\n', ''))
    init(argv[1:])
  elif len(sys.argv) == 1:
    init(['-v'])
  else:
    init(sys.argv[1:])

main()