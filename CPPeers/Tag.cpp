#include <iostream>
#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string, std::vector;

#define DEBUG_ON false
#define DEBUG(X)                                                                               \
    if (DEBUG_ON)                                                                              \
    {                                                                                          \
        std::cout << "[DEBUG] (" << __FUNCTION__ << ":" << __LINE__ << ") " << X << std::endl; \
    }

Tag::Tag(string tagName) : tagName(tagName), tagPosts(0)
{
    DEBUG("Tag Name - " << tagName)

    // make sure tagName is valid
    int tagLen = tagName.length();
    if (tagLen < 2)
    {
        throw std::invalid_argument("Tag name must be at least two characters");
    }
    for (int i = 0; i < tagLen; i++)
    {
        char current = tagName.at(i);

        if (i == 0)
        {
            if (current != '#')
            {
                throw std::invalid_argument("Tag name must start with #");
            }
        }
        else
        {
            if (current < 'a' || current > 'z')
            {
                DEBUG("Error thrown on index" << i << " [" << current << "]")
                throw std::invalid_argument("Tag name must consist of lowercase characters");
            }
        }
    }
}

string Tag::getTagName()
{
    return tagName;
}

vector<Post *> &Tag::getTagPosts()
{
    return tagPosts;
}

void Tag::addTagPost(Post *post)
{
    if (post == nullptr)
    {
        throw std::invalid_argument("Post is nullptr");
    }
    tagPosts.push_back(post);
}