/**
 * File: openclas_test.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-07-15 16:46:06.045000
 * Written In: Peking University, beijing, China
 */

#define DEBUG
#include "common.hpp"

int main (int argc, char* argv[]) {
	const char* data_dir=".";
	if (!openclas_init(data_dir)) return 1;
	
	cout<<openclas_deal_str("hi, i am jadesoul.", false)<<endl;
	cout<<openclas_deal_str("hi, i am jadesoul.", true)<<endl;
	cout<<openclas_deal_str("你好，我是冰玉之魂。", false)<<endl;
	cout<<openclas_deal_str("你好，我是冰玉之魂。", true)<<endl;
	
	return 0;
}


