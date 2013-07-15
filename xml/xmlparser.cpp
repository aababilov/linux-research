#include "xmlparser.hpp"


#include <string>
#include <cstring>

using namespace std;

typedef unsigned int gunichar;

int
unichar_to_utf8(gunichar val, char *out) {
	if (out == NULL)
		return (0);
	/*
	 * We are supposed to handle UTF8, check it's valid
	 * From rfc2044: encoding of the Unicode values on UTF-8:
	 *
	 * UCS-4 range (hex.)           UTF-8 octet sequence (binary)
	 * 0000 0000-0000 007F   0xxxxxxx
	 * 0000 0080-0000 07FF   110xxxxx 10xxxxxx
	 * 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
	 */
	if  (val >= 0x80) {
		char *savedout = out;
		gunichar bits;
		if (val <   0x800) { *out++= (val >>  6) | 0xC0;  bits=  0; }
		else if (val < 0x10000) { *out++= (val >> 12) | 0xE0;  bits=  6;}
		else if (val < 0x110000)  { *out++= (val >> 18) | 0xF0;  bits=  12; }
		else {
			return(0);
		}
		for ( ; bits >= 0; bits-= 6)
			*out++= ((val >> bits) & 0x3F) | 0x80 ;
		return (out - savedout);
	}
	*out = (char) val;
	return 1;
}

std::string
xmlDecodeEntities(const xmlChar *s)
{
	string ret;
	ret.reserve(strlen((const char*)s));
	for (; *s; ++s) {
		if (*s == '&') {
			gunichar charval = 0;
			xmlChar tmp;
			if ((s[1] == '#') && (s[2] == 'x')) {
				s += 3;
				tmp = *s;
				while (tmp && tmp != ';') { /* Non input consuming loop */
					if ((tmp >= '0') && (tmp <= '9'))
						charval = charval * 16 + (tmp - '0');
					else if ((tmp >= 'a') && (tmp <= 'f'))
						charval = charval * 16 + (tmp - 'a') + 10;
					else if ((tmp >= 'A') && (tmp <= 'F'))
						charval = charval * 16 + (tmp - 'A') + 10;
					else {
						charval = 0;
						--s;
						break;
					}
					s++;
					tmp = *s;
				}
			} else if  (s[1] == '#') {
				s += 2;
				tmp = *s;
				while (tmp && tmp != ';') { /* Non input consuming loops */
					if ((tmp >= '0') && (tmp <= '9'))
						charval = charval * 10 + (tmp - '0');
					else {
						charval = 0;
						--s;
						break;
					}
					s++;
					tmp = *s;
				}
			} else {
				continue;
			}
			char buf[6];
			buf[unichar_to_utf8(charval, buf)] = 0;
			ret += buf;		
		} else {
			ret += *s;
		}				
	}
	return ret;
}

using namespace std;

/**one (initialized) instance for class XmlParser */
xmlSAXHandler XmlParser::saxHandler = {0};

bool XmlParser::staticDataInited = XmlParser::initStaticData();

bool XmlParser::initStaticData()
{
	saxHandler.startElement = &xmlSAX2StartElement;
	saxHandler.endElement = xmlSAX2EndElement;
	return true;
}

void
XmlParser::xmlSAX2StartElement(void *ctx,
			       const xmlChar *fullname,
			       const xmlChar **atts)
{
	std::map<std::string, std::string> m_atts;
	for (const xmlChar **p = atts; *p; ++p) {
		string name = xmlDecodeEntities(*p);
		++p;
		m_atts[name] = xmlDecodeEntities(*p);	
	}

	((XmlParser*)ctx)->onStartElement((const char*)fullname, m_atts);
}

void
XmlParser::xmlSAX2EndElement(void *ctx, const xmlChar *name)
{
	((XmlParser*)ctx)->onEndElement((const char*)name);
}

bool XmlParser::parseFile(const char *filename)
{
	int result = xmlSAXUserParseFile(&saxHandler, this, filename);
	if (result != 0) {
		fprintf(stderr, "error parsing %s\n", filename);
	}
	return result == 0;
}

const xmlChar* XmlParser::xmlGetAttrValue(const xmlChar** attrs,const char* key)
{
	return xmlGetAttrValue(attrs,(xmlChar*) key);
}

const xmlChar* XmlParser::xmlGetAttrValue(const xmlChar** attrs,const xmlChar* key)
{
	if (attrs!=NULL) {      
		for (size_t i = 0; attrs[i]!=NULL;i+=2) {
			if (xmlStrEqual(attrs[i],key)) {
				return attrs[i+1];
			} 
		}
	}
	return NULL;
}
