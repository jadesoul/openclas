#coding:utf8

import os, sys
from os import listdir, getcwd as cwd, chdir as cd
from os.path import split as splitdir, splitext, join, dirname, isfile, islink, isdir, exists

bin_dir=join(dirname(__file__), '..', 'bin')
sys.path.append(bin_dir)

import libpyopenclas as _openclas

__is_inited=False

def init():
	'''初始化'''
	global __is_inited
	if not __is_inited:
		try:
			assert _openclas.init(bin_dir)
		except Exception, e:
			print 'can not init the _openclas, exception=%s' % e
			print 'bin_dir=%s' % bin_dir
			sys.exit()
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
	txt='''English Words
他说的确实在理。
19９5年底ｇoｏgｌｅ在1月份大会上说的确实在理。
这个门的把手坏了好几天了。
你把手抬高一点儿。
这个动作的要领其实很简单。
下午我要领工资，恐怕赶不回去。
办独生子女证，一对夫妻一次性交一百元钱。
我知道你不知道我知道你不知道我知道你不知道。
已经分房和尚未分房的同志。
馆内陈列着周恩来和邓颖超生前使用过的物品。
我爱北京天安门和西藏的布达拉宫。
美国白宫和悉尼歌剧院是我喜欢的。
提高人民生活水平。
你去咬死猎人的狗。
你去逮住咬死猎人的狗。
张华平喜欢看书。
舒展喜欢看书。
吴胜兰喜欢听歌。
我喜欢刘亦菲的歌声。
'''
	for s in txt.strip().split('\n'):
		print s
		print seg_str(s)
		print tag_str(s)
		print
	
	print seg_file('1500.txt', '1500.seg')
	print tag_file('1500.txt', '1500.tag')
	
