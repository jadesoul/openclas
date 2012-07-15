#!/usr/bin/env python

from shutil import copy
from os import system as run, mkdir as md, makedirs as mds
from os import chdir as cd, listdir as ls, name as osname
from os.path import exists, isfile, isdir

# update from svn if possible
run('svn up')

# create build dir for cmake
if not exists('build'): md('build')

# prepare bin dir and data files
if not exists('bin'): md('bin')
if not exists('bin/data'):
	md('bin/data')
	for i in ls('data'):
		src='data/'+i
		if isfile(src):
			print 'copying:', src
			copy(src, 'bin/data')

# configure cmake
cd('build')
if osname=='nt':
	run('cmake .. -G "MinGW Makefiles"')
else:
	run('cmake ..')
	
# start make
run('make')
