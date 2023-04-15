#include <iostream>
#include <string>
#include <stdexcept>
#include "User.h"

using std::string, std::vector;

#define DEBUG_ON false
#define DEBUG(X)                                                                               \
    if (DEBUG_ON)                                                                              \
    {                                                                                          \
        std::cout << "[DEBUG] (" << __FUNCTION__ << ":" << __LINE__ << ") " << X << std::endl; \
    }

User::User(string userName) : userName(userName), userPosts(0)
{
    DEBUG("Username: " << userName);

    // validate input
    if (userName == "")
    {
        throw std::invalid_argument("Username cannot be empty");
    }
    for (char c : userName)
    {
        if ((c <'a') | (c > 'z'))
        {
            throw std::invalid_argument("Username must consist of lowercase characters");
        }
    }
}

string User::getUserName()
{
    return userName;
}

vector<Post *> &User::getUserPosts()
{
    return userPosts;
}

void User::addUserPost(Post *post)
{
    if (post == nullptr)
    {
        throw std::invalid_argument("Post is nullptr");
    }
    userPosts.push_back(post);
}
