#!/usr/bin/env python

"""setup script for the umigame with XML distribution:
   umigame is Unit test skeleton generator."""

# smart_install_data is written at following URL:
# http://mail.python.org/pipermail/distutils-sig/2002-May/002880.html

from distutils.core import setup
import py2exe, os, glob

data_files = []
for f in glob.glob(os.path.join('libumix', '*')):
    if f.endswith('.xml') and os.path.isfile(f):
        data_files.append(f)

setup (
  name = 'umix',
  version='1.0',
  description = 'unittest skeleton generator',
  author = "Shibukawa Yoshiki",
  author_email = "yoshiki@shibu.jp",
  url = "http://www.UnitTest.org",
  scripts = ["bin/umix.py"],
  data_files = [('libumix', data_files)]
)
