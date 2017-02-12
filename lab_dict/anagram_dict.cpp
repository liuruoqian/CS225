/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            //cout << word << endl;
            string sorted = word;
            std::sort(sorted.begin(), sorted.end());
    	    auto lookup = dict.find(sorted);
    	    if (lookup != dict.end()){
    		    if(std::find((lookup->second).begin(), (lookup->second).end(), word) == (lookup->second).end()){
    			    (lookup->second).push_back(word);
    		    }	
    	    }
    	    else{
    		    std::vector<string> v;
    		    v.push_back(word);
    		    dict[sorted] = v;
    	    }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto & w : words){
    	string sorted = w;
        std::sort(sorted.begin(), sorted.end());
    	auto lookup = dict.find(sorted);
    	if (lookup != dict.end()){
    		if(std::find((lookup->second).begin(), (lookup->second).end(), w) == (lookup->second).end()){
    			(lookup->second).push_back(w);
    		}	
    	}
    	else{
    		std::vector<string> v;
    		v.push_back(w);
    		dict[sorted] = v;
    	}
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */

    string sorted = word;
    std::sort(sorted.begin(), sorted.end());
    auto lookup = dict.find(sorted);
    if (lookup != dict.end()){
        return lookup->second;
    }
    else return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    std::vector<std::vector<string>> vec;
    for (auto & pair : dict){
    	if ((pair.second).size() >= 2)
    		vec.push_back(pair.second);
    }
    return vec;
}
