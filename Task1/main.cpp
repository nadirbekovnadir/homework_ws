#include <iostream>
#include <string>

#include "PNITraxParser.h"

using namespace std;

//05430D083B183F91BCD8193EDF4DE94F00080015BCA408C0163BFB4DAB173F80F5081BC16EA4371cc12d31271d42513d4f4a000000004b000000004c00000000

int main()
{
	PNITraxParser parser;
	string str;

	cout << "Enter data:" << endl;
	cin >> str;
	cout << endl;

	char *bytes = new char[str.length() / 2];
	int offset = '0';
	string temp;
	temp.resize(2);

	for (int i = 0; i < str.length() - 1; i += 2)
	{
		temp[0] = str[i];
		temp[1] = str[i + 1];
		bytes[i / 2]  = stoi(temp, nullptr, 16);
	}

	parser.GetFromString(bytes, str.length());

	PNITraxParser::Data data = parser.GetData();

	parser.PrintData();

	cout << "Program ended!" << endl;

	return 0;
}
