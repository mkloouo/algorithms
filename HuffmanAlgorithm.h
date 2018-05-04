//
// Created by modnosumov on 5/4/18.
//

#ifndef STD_THREADS_TASK_HUFFMANALGORITHM_H
#define STD_THREADS_TASK_HUFFMANALGORITHM_H

#include <string>
#include <memory>
#include <vector>
#include <map>

namespace HuffmanAlgorithm {
	using FrequencyPair = std::pair<std::string, int>;

	class Node {
	public:
		Node() : Node({"", 0}) {
		}

		Node(FrequencyPair fp, std::shared_ptr<Node> l = nullptr,
			 std::shared_ptr<Node> r = nullptr);

		Node(Node const& other) = default;

		FrequencyPair freqPair;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
	};
	template <class Value, class Comparator>
	static Value deleteMin(std::vector<Value>& v, Comparator less) {
		auto minIt = v.begin();
		for (auto it = minIt; it != v.end(); ++it) {
			if (less(*it, *minIt)) {
				minIt = it;
			}
		}
		Value minValue = *minIt;
		v.erase(minIt);
		return minValue;
	};

/**
 * @brief Applies Huffman encoding algorithm to str
 * @param str Common string in format "abc"
 * @return Dictionary in format {'a', '10001'}
 */
	std::map<char, std::string> getHuffmanEncodingDictionary(std::string const& str);

/**
 * @brief Encodes common string using dictionary
 * @param dictionary Encoding dictionary in format {'a', '01001'}
 * @param toEncode Common string in format "abc"
 * @return Encoded string in format "0100110101"
 */
	std::string encodeHuffman(std::map<char, std::string> const& dictionary,
							  std::string const& toEncode);

/**
 * @brief Decodes Huffman-algorithm encoded string using dictionary
 * @param dictionary Encoding dictionary in format {'a', "01001"}
 * @param encodedString String in format "01001101"
 * @return Decoded string in format "ab"
 */
	std::string decodeHuffman(std::map<char, std::string> const& dictionary,
							  std::string const& encodedString);

}

#endif // STD_THREADS_TASK_HUFFMANALGORITHM_H
