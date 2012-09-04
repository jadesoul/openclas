#ifndef COMMON_HPP_1342284964_45
#define COMMON_HPP_1342284964_45
/**
 * File: common.hpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-07-15 00:56:04.500000
 * Written In: Peking University, beijing, China
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <exception>
#include <string>
#include <locale>
#include <openclas/serialization.hpp>
#include <openclas/segment.hpp>
#include <openclas/utility.hpp>

#ifdef DEBUG
	#define debug(...) __VA_ARGS__
#else
	#define debug(...)
#endif

using namespace std;
using namespace openclas;
using namespace openclas::ict;

Dictionary dict;

const char* core_name = "data/core.ocd";

string wstringtostring(const wstring& input, const char* using_locale="zh_CN.UTF-8") {
	string current_locale=setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, using_locale);
	const wchar_t* src = input.c_str();
	size_t dst_len = 3 * input.size() + 1;
	char *dst = new char[dst_len];
	memset(dst, 0, dst_len);
	wcstombs(dst, src, dst_len);
	string output=dst;
	delete [] dst;
	setlocale(LC_ALL, current_locale.c_str());
	return output;
}

wstring stringtowstring(const string& input, const char* using_locale="zh_CN.UTF-8") {
	string current_locale=setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, using_locale);
	const char* src = input.c_str();
	size_t dst_len = input.size() + 1;
	wchar_t *dst = new wchar_t[dst_len];
	wmemset(dst, 0, dst_len);
	mbstowcs(dst, src, dst_len);
	wstring output = dst;
	delete [] dst;
	setlocale(LC_ALL, current_locale.c_str());
	return output;
}

// test file existence
bool file_exists(const char* filename) {
	ifstream in(filename);
	if (in.fail()) {
		ostringstream oss;
		oss << "File [" << filename << "] is not exist.";
		cout<<oss.str()<<endl;
		in.close();
		return false;
	}
	in.close();
	return true;
}

// dict initialization
bool openclas_init(const char* data_dir) {
	string fp_core_dict=string(data_dir)+"/"+string(core_name);

	//cout<<"fp_core_dict="<<fp_core_dict<<endl;
	if (!file_exists(fp_core_dict.c_str())) return false;
	
	load_from_ocd_file(dict, fp_core_dict.c_str());
	
	debug( cout<<"dict size: "<<dict.words().size()<<endl; )

	size_t word_tag_count = 0;
	for (Dictionary::word_dict_type::const_iterator iter = dict.words().begin(); iter != dict.words().end(); ++iter) {
		word_tag_count += (*iter)->tags.size();
	}
	
	debug( cout<<"word_tag_count: "<<word_tag_count<<endl; )

	size_t transit_count = 0;
	for (Dictionary::word_dict_type::const_iterator iter = dict.words().begin(); iter != dict.words().end(); ++iter)
	{
		transit_count += (*iter)->forward.size();
	}
	
	debug( cout<<"transit_count: "<<transit_count<<endl; )

	//	Punctuation as Terminal of each segment
	DictEntry* entry_w = dict.add_word(get_special_word_string(WORD_TAG_W));
	if (entry_w->tags.size() == 0)
	{
		DictEntry* entry_begin = dict.get_word(get_special_word_string(WORD_TAG_BEGIN));
		entry_w->add(WORD_TAG_W, entry_begin->tags.front().weight);
	}
	return true;
}

const string openclas_deal_str(const char* str, bool tag) {
	debug( cout<<"now in openclas_deal_str"<<endl; )
	debug( cout<<"input str="<<str<<endl; )
	wstring input=stringtowstring(str);
		
	wostringstream out;
	std::vector<Segment::segment_type> segs=Segment::segment(input, dict, 1);
	out<<Segment::segment_to_string(input, segs.at(0), tag);
	
	debug( cout<<"output wstringtostring(out.str())="<<wstringtostring(out.str())<<endl; )
	
	return wstringtostring(out.str());
}

bool openclas_deal_file(const char* src, const char* dst, bool tag) {
	if (!file_exists(src)) return false;
	
	wifstream in(src);
	in.imbue(locale_utf8);
	
	wofstream out(dst);
	out.imbue(locale_utf8);
	
	const int BUF_SIZE=1024*64;
	wchar_t* buf=new wchar_t[BUF_SIZE];
	while (in.getline(buf, BUF_SIZE)) {
		wstring line(buf);
		std::vector<Segment::segment_type> segs = Segment::segment(line, dict, 1);
		out<<Segment::segment_to_string(line, segs.at(0), tag)<<endl;
	}
	
	delete [] buf;
	in.close();
	out.close();
	return true;
}

int openclas_seg_tag(int argc, char* argv[], bool tag) {
	if (argc<3 || argc >4) {
		cout<<"Usage: openclas_seg <input filename> <output filename> [data dir]"<<endl;
		return 1;
	}
	const char* data_dir=".";
	const char* src=argv[1];
	const char* dst=argv[2];
	if (argc==4) data_dir=argv[3];
	if (!openclas_init(data_dir)) return 2;
	if (!openclas_deal_file(src, dst, tag)) return 3;
	return 0;
}

#endif /* COMMON_HPP_1342284964_45 */
