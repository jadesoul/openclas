#coding:utf8

import os, sys
from os import listdir, getcwd as cwd, chdir as cd
from os.path import split as splitdir, splitext, join, dirname, isfile, islink, isdir, exists

bin_dir=join(dirname(__file__), '../bin')
sys.path.append(bin_dir)

import libpyopenclas as _openclas

__is_inited=False

def init():
	'''初始化'''
	global __is_inited
	if not __is_inited:
		assert _openclas.init(bin_dir)
		__is_inited=True
	
def deal_str(s, tag=True):
	'''切分句子， 同时可指定是否标注词性，要求s是unicode或者utf8'''
	init()
	if type(s) is unicode:
		return _openclas.deal_str(s.encode('utf8'), tag).decode('utf8')
	else:
		#make sure input be utf8
		return _openclas.deal_str(s, tag)
	
def deal_file(src, dst, tag=True):
	'''切分文件， 同时可指定是否标注词性，要求文件编码为utf8
	返回是否成功的提示信息'''
	init()
	if _openclas.deal_file(src, dst, tag):
		return 'success dealing file: %s -> %s' % (src, dst)
	else:
		return 'failed dealing file: %s -> %s' % (src, dst)
		
def seg_str(s):
	return deal_str(s, False)
	
def tag_str(s):
	return deal_str(s, True)
	
def seg_file(src, dst):
	return deal_file(src, dst, False)
	
def tag_file(src, dst):
	return deal_file(src, dst, True)

if __name__=='__main__':
	print seg_str('asadaksd sadfkasd f ')
	print tag_str('asadaksd sadfkasd f ')
	print seg_str(u'a中国海军在菲北部海域军演 菲方回应 华人在菲驻美使馆示威')
	print tag_str(u'a中国海军在菲北部海域军演 菲方回应 华人在菲驻美使馆示威')
	
	print seg_file('1500.txt', '1500.seg.txt')
	print tag_file('1500.txt', '1500.segtag.txt')
	