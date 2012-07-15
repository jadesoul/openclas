#!/usr/bin/env python

from shutil import rmtree as rm
from os.path import exists

# del build dir and bin dir
if exists('build'): rm('build')
if exists('bin'): rm('bin')