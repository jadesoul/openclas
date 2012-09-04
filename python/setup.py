#!/usr/bin/env python
from distutils import sysconfig
from distutils.core import setup
from os import listdir, getcwd, mkdir
from os.path import isfile, exists

# generate pth file
if not exists('build'): mkdir('build')
f=open('build/openclas.pth', 'w')
f.write(getcwd())
f.close()

# setup
site_packages_path=sysconfig.get_python_lib()
setup(
	name='openclas',
	version='1.0',
	description='Python Binding for Jadesoul\'s Open Chinese Lexical Analysis System',
	author='Jaden Wu',
	author_email='wslgb2006@gmail.com',
	url='http://jadesoul.sinaapp.com/',
	license='Python Software Foundation License',
	packages=[],
	scripts=[],
	data_files=[(site_packages_path, ["build/openclas.pth"])]
)
