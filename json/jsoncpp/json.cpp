#include <cstdio>
#include <json/json.h>
#include <fstream>

using namespace std;


int main()
{
        Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	ifstream in("ac_power.json");
	bool parsingSuccessful = reader.parse(
		in, root);
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		printf("Failed to parse configuration %s\n",
		       reader.getFormatedErrorMessages().c_str());
		return 1;
	}
	printf("%s\n", root[0u]["conditions"][0u]["key"].asString().c_str());
	printf("%d\n", root[0u]["conditions"][0u]["value"].asBool());
	return 0;
}
