#include <iostream>
#include <algorithm>
#include "HuffmanAlgorithm.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main() {
	string input;
	getline(cin, input);
	auto dictionary = HuffmanAlgorithm::getHuffmanEncodingDictionary(input);

	std::for_each(dictionary.begin(), dictionary.end(),
				  [](std::pair<char, std::string> const& entry) {
					  cout << entry.first << ": " << entry.second << endl;
				  });

	string encodedString = HuffmanAlgorithm::encodeHuffman(dictionary, input);
	cout << encodedString << endl;
	string decodedString = HuffmanAlgorithm::decodeHuffman(dictionary, encodedString);
	cout << decodedString << endl;
	return 0;
}
