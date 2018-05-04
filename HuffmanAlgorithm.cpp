//
// Created by modnosumov on 5/4/18.
//

#include "HuffmanAlgorithm.h"

HuffmanAlgorithm::Node::Node(HuffmanAlgorithm::FrequencyPair fp,
							 std::shared_ptr<HuffmanAlgorithm::Node> l,
							 std::shared_ptr<HuffmanAlgorithm::Node> r)
	: freqPair(std::move(fp)),
	  left {std::move(l)},
	  right {std::move(r)} {
}

static void fillTraverseMap(std::shared_ptr<HuffmanAlgorithm::Node> const& node,
							std::map<std::string, std::string>& map, std::string s) {
	if (!node->freqPair.first.empty()) {
		map[node->freqPair.first] = s;
	} else {
		if (node->right) {
			fillTraverseMap(node->right, map, s + "1");
		}
		if (node->left) {
			fillTraverseMap(node->left, map, s + "0");
		}
	}
}

std::map<char, std::string> HuffmanAlgorithm::getHuffmanEncodingDictionary(std::string const& str) {
	std::vector<std::shared_ptr<Node>> nodes;
	{
		std::map<std::string, int> frequencies;
		for (auto&& c: str) {
			++frequencies[std::string {c}];
		}
		nodes.resize(frequencies.size());
		int i = 0;
		for (auto&& item: frequencies) {
			nodes[i++] = std::make_shared<Node>(item);
		}
	}

	auto cmpNodes = [](std::shared_ptr<Node> const& n1, std::shared_ptr<Node> const& n2) {
		return n1->freqPair.second < n2->freqPair.second;
	};

	if (nodes.size() == 1) {
		std::shared_ptr<Node> t = std::make_shared<Node>(
			FrequencyPair {"", nodes[0]->freqPair.second},
			nodes[0]);
		nodes.clear();
		nodes.push_back(t);
	} else {
		for (std::shared_ptr<Node> t, m1, m2; nodes.size() > 1;) {
			m1 = deleteMin(nodes, cmpNodes);
			m2 = deleteMin(nodes, cmpNodes);
			t = std::make_shared<Node>(
				FrequencyPair {"", m1->freqPair.second + m2->freqPair.second},
				m1,
				m2);
			nodes.push_back(t);
		}
	}

	std::map<std::string, std::string> traverseMap;
	fillTraverseMap(nodes[0], traverseMap, "");

	std::map<char, std::string> dictionary;
	for (auto&& p: traverseMap) {
		dictionary[p.first[0]] = p.second;
	}
	return dictionary;
}

std::string HuffmanAlgorithm::encodeHuffman(std::map<char, std::string> const& dictionary,
											std::string const& toEncode) {
	std::string encodedString;

	for (auto&& c: toEncode) {
		encodedString.append(dictionary.at(c));
	}
	return encodedString;
}

std::string HuffmanAlgorithm::decodeHuffman(std::map<char, std::string> const& dictionary,
											std::string const& encodedString) {
	std::string decodedString;
	std::string part;
	bool foundOccurence = false;
	for (unsigned long i = 0, j = 1; i < encodedString.size();) {
		part = encodedString.substr(i, j);
		for (const auto& it : dictionary) {
			if (it.second == part) {
				decodedString += it.first;
				i += j;
				j = 1;
				foundOccurence = true;
				break;
			}
		}
		if (!foundOccurence) {
			++j;
		} else {
			foundOccurence = false;
		}
	}
	return decodedString;
}
