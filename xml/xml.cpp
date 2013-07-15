#include <cstdio>
#include "xmlparser.hpp"

using namespace std;
class TablixParser: public XmlParser {
public:

	virtual bool parseFile(const char *filename);
protected:
	virtual void onStartElement(std::string fullname,
				    std::map<std::string, std::string> &atts);
	virtual void onEndElement(std::string fullname);
};

bool TablixParser::parseFile(const char *filename)
{
	return XmlParser::parseFile(filename);
}

void TablixParser::onStartElement(std::string fullname,
				  std::map<std::string, std::string> &atts)
{
	printf("%s\n", fullname.c_str());
	for (std::map<std::string, std::string>::iterator i = atts.begin();
	     i != atts.end();
	     ++i) {		
		printf("   %s=%s\n", i->first.c_str(), i->second.c_str());
	}
}

void TablixParser::onEndElement(std::string fullname)
{
	printf("%s\n", fullname.c_str());
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("what file?\n");
		return 1;
	}
	TablixParser parser;	
	parser.parseFile(argv[1]);
	return 0;
}

