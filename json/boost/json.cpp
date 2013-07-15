#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <cstdio>

using boost::property_tree::ptree;
using namespace std;

const string FILENAME = "test.json";


int main()
{
	ptree pt;
	read_json("ac_power.json", pt);
	write_xml("ac_power.xml", pt,
		  std::locale(),
		  boost::property_tree::xml_parser::xml_writer_make_settings(
			  ptree::key_type::value_type(' '), 2));
	return 0;
}
