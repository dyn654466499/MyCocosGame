#include "XMLParser.h"

using namespace std;
using namespace cocos2d;

// �ո�
const static int SPACE = 32;
// ����
const static int NEXTLINE = 10;
// tab �����Ʊ��
const static int TAB = 9;

string replace(string source, string pattern, string dstPattern)
{
    string result;
    string::size_type pos;

    int lenSource = source.length();
	int i = 0;

    for(i = 0; i < lenSource; ++i)
    {
        pos = source.find(pattern, i);
        if(string::npos == pos)
            break;

        if(pos < lenSource)
        {
            string s = source.substr(i, pos - i);
            result += s;
            result += dstPattern;
            i = pos + pattern.length() - 1;
        }
    }
    result += source.substr(i);
    return result;
}

XMLParser* XMLParser::parseWithFile(const char *xmlFileName)
{
	XMLParser *pXMLParser = new XMLParser();
	if(	pXMLParser->initWithFile(xmlFileName) )
	{
		pXMLParser->autorelease();	
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithFile(const char *xmlFileName)
{
	m_pDictionary = new CCDictionary();
	SAXParser _parser;
	_parser.setDelegator(this);
	auto sharedFileUtils = FileUtils::getInstance();

	string fullPath = sharedFileUtils->fullPathForFilename(xmlFileName);

	return _parser.parse(fullPath.c_str());
}

XMLParser* XMLParser::parseWithString(const char *content)
{
	XMLParser *pXMLParser = new XMLParser();
	if( pXMLParser->initWithString(content) )
	{
		pXMLParser->autorelease();	
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithString(const char *content)
{
	m_pDictionary = new CCDictionary();
	SAXParser _parse;
	_parse.setDelegator(this);
	return _parse.parse(content, strlen(content) );
}


void XMLParser::startElement(void *ctx, const char *name, const char **atts)
{
	this->startXMLElement = (char *)name;
	//CCLog("start=%s", startXMLElement.c_str());
	if(this->startXMLElement == "string")
	{
		while(atts && *atts)
		{
			const char *attsKey = *atts;	
			if(0 == strcmp(attsKey, "name"))
			{
				++ atts;
				const char *attsValue = *atts;
				m_key = attsValue;
				break;
			}
			++ atts;
		}
		
	}

}

void XMLParser::endElement(void *ctx, const char *name)
{
	this->endXMLElement = (char *)name;
	//CCLog("end=%s", endXMLElement.c_str());
}



void XMLParser::textHandler(void *ctx, const char *s, int len)
{
	if(this->m_key.length() == 0)
		return;
	
	string value((char*)s, 0, len);
	//CCLOG("s=%s, len=%d", value.c_str(), value.length());
	//�Ƿ�ȫ�Ƿ������ַ�
	bool noValue = true;
	
	for(int i = 0; i < value.length(); ++i)
	{
		char c = value.at(i);
		//CCLOG("v=%d", c);

		if(c != SPACE && c != NEXTLINE && c != TAB)
		{
			noValue = false;	
			break;
		}
	}
	if(noValue) return;
	string result = replace(value, string("\\n"), string("\n"));
	String *pString = CCString::create(result);
	log("key=%s value=%s", m_key.c_str(), pString->getCString());
	this->m_pDictionary->setObject(pString, this->m_key);
}


CCString* XMLParser::getString(const char *key)
{
	string strKey(key);
	return (CCString *)this->m_pDictionary->objectForKey(strKey);
}

XMLParser::XMLParser()
{
}

XMLParser::~XMLParser()
{
	CC_SAFE_DELETE(this->m_pDictionary);
}
