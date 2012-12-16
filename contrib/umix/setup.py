#!/usr/bin/env python

"""setup script for the umigame with XML distribution:
   umigame is Unit test skeleton generator."""

# smart_install_data is written at following URL:
# http://mail.python.org/pipermail/distutils-sig/2002-May/002880.html

from distutils.core import setup
from distutils.command.install_data import install_data
import os, glob

data_files = []
src_file = []
for f in glob.glob(os.path.join('libumix', '*')):
    if f.endswith('.xml') and os.path.isfile(f):
        data_files.append(f)
    elif f.endswith('.py') and os.path.isfile(f):
        src_file.append(f[:-3])

class smart_install_data(install_data):
  def run(self):
    install_cmd = self.get_finalized_command('install')
    self.install_dir = getattr(install_cmd, 'install_lib')
    return install_data.run(self)

setup (
  name = 'umix',
  version='1.0',
  description = 'unittest skeleton generator',
  author = "Shibukawa Yoshiki",
  author_email = "yoshiki@shibu.jp",
  url = "http://www.UnitTest.org",
  py_modules = src_file,
  scripts = ["bin/umix.py"],
  cmdclass = {'install_data': smart_install_data},
  data_files = [('libumix', data_files)]
)
