#include "common.hpp"
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(libpyopenclas)
{
	def("init", openclas_init);
	def("deal_str", openclas_deal_str);
	def("deal_file", openclas_deal_file);
}