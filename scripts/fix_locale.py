#coding:utf8

from libjade import *

# for ubunut, add these lines to /var/lib/locales/supported.d/zh

c='''zh_CN.UTF-8 UTF-8
zh_SG.UTF-8 UTF-8
zh_CN.GBK GBK
zh_TW.BIG5 BIG5'''

fp='/var/lib/locales/supported.d/zh'
if isfile(fp):
	s=fread(fp)
	if c not in s:
		fappend(c, fp)
else:
	fwrite(c, fp)

# then run below as root
run('sudo locale-gen')


#cat /var/lib/locales/supported.d/zh-hans 


if __name__=='__main__':
	pass

