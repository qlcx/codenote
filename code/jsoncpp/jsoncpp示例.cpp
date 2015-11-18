#include <iostream>
#include <string>
#include "json/json.h"
using namespace std;

int main() {
	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;
	Json::Value item1;
	Json::Value item2;
	
	root["res"] = "translist";
	root["size"] = 5;

	item1["string"] = "jsoncppѧϰ";
	item1["number"] = 999;
	item1["aaaaaa"] = "bbbbbb";
	arrayObj.append(item1);

	item2["string"] = "I'm gsd";
	item2["number2"] = 666;
	item2["ccccccd"] = "dddddd";
	arrayObj.append(item2);

	for (int i = 0; i < 4; i++)
	{
		item["index"] = i;
		arrayObj.append(item);
	}

	root["array"] = arrayObj;
	root.toStyledString();

	string out = root.toStyledString();
	cout << out << endl;

	cout << "----------------------------" << endl;

	Json::Reader reader;
	Json::Value value;
	
	if (reader.parse(out, value))
	{
		cout << "res: " << value["res"].asString()  <<endl;
		cout << "size: " << value["size"].asInt() <<endl;

		Json::Value arrayObj = value["array"];
		cout << "array size = " << arrayObj.size() << endl;
		for(unsigned int i = 0; i < arrayObj.size(); i++)
		{
			if(arrayObj[i].isMember("index"))
			{
				cout << "index = " << arrayObj[i]["index"].asInt() << endl;
			}
			if(arrayObj[i].isMember("string"))
			{
				cout << "string = " << arrayObj[i]["string"].asString() << endl;
			}
		}

	}
	return 0;
}
