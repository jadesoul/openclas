#!/usr/bin/env python

from shutil import rmtree as rm
from os.path import exists

# del build dir and bin dir
for d in 'build bin python/build'.split():
	if exists(d): rm(d)
	
	
	
	
	
	
	