#include <iostream>
#include <string>
#include <stdexcept>
#include "Post.h"

using std::string, std::vector;

#define DEBUG_ON false
#define DEBUG(X)                                                                               \
    if (DEBUG_ON)                                                                              \
    {                                                                                          \
        std::cout << "[DEBUG] (" << __FUNCTION__ << ":" << __LINE__ << ") " << X << std::endl; \
    }

Post::Post(unsigned int postId, string userName, string postText) : postId(postId), userName(userName), postText(postText)
{
    if ((postId == 0) || (userName == "") || (postText == ""))
    {
        throw std::invalid_argument("post constructor: invalid parameter values");
    }
}

unsigned int Post::getPostId()
{
    return postId;
}

string Post::getPostUser()
{
    return userName;
}

string Post::getPostText()
{
    return postText;
}

vector<string> Post::findTags()
{
    // split pst test into a vector of words
    string word = "";
    vector<string> words;
    for (char c : postText)
    {
        if (c != ' ')
        {
            word += c;
        }
        else
        {
            words.push_back(word);
            word = "";
        }
    }
    words.push_back(word);

    // iterate through words to find tags and format them properly
    vector<string> tags;
    for (string word : words)
    {
        DEBUG("Checking word \"" << word << "\"")
        if (word.at(0) == '#')
        {
            // format string
            int wordLen = word.length();
            for (int i = 0; i < wordLen; i++)
            {
                if ((word.at(i) >= 'A') && (word.at(i) <= 'Z'))
                {
                    word.at(i) += 32; // convert all uppercase letters to lowercase letters
                }
            }
            for (int i = wordLen - 1; i >= 0; i--)
            {
                if ((word.at(i) == '!') | (word.at(i) == '?') | (word.at(i) == ',') | (word.at(i) == '.'))
                {
                    word.erase(i, 1);
                }
                else
                {
                    break;
                }
            }

            // add to tags vector
            DEBUG("added tag \"" << word << "\" to tags!")
            tags.push_back(word);
        }
    }

    // return tag vector
    return tags;
}
