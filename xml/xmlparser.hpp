#ifndef _xmlparser_hpp
#define _xmlparser_hpp

#include <string>
#include <map>

#include <libxml/parser.h>

/** abstract base class for SAX2 Parser based on libxml2 */
class XmlParser {
	static void xmlSAX2StartElement(void *ctx,
					const xmlChar *fullname,
					const xmlChar **atts);
	static void xmlSAX2EndElement(void *ctx, const xmlChar *name);
	static bool initStaticData();

	static xmlSAXHandler saxHandler;
	static bool staticDataInited;
public:
	virtual ~XmlParser() {};
	bool parseFile(const std::string& filename) { return parseFile(filename.c_str()); }
	virtual bool parseFile(const char *filename);
   
	static const xmlChar* xmlGetAttrValue(const xmlChar** attrs,const char* key);
	static const xmlChar* xmlGetAttrValue(const xmlChar** attrs,const xmlChar* key);

protected:
	virtual void onStartElement(std::string fullname,
				    std::map<std::string, std::string> &atts) = 0;
	virtual void onEndElement(std::string fullname) = 0;
};

#endif

