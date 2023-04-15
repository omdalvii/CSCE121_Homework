#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string, std::vector;

#define DEBUG_ON false
#define DEBUG(X)                                                                               \
    if (DEBUG_ON)                                                                              \
    {                                                                                          \
        std::cout << "[DEBUG] (" << __FUNCTION__ << ":" << __LINE__ << ") " << X << std::endl; \
    }

Network::Network() : users({}), posts({}), tags({})
{
}

void Network::loadFromFile(string fileName)
{
    std::ifstream file(fileName);

    if (!(file.is_open()))
    {
        throw std::invalid_argument("File could not be opened");
    }

    // Iterate through each line in the input file
    string line;
    long unsigned int i;
    while (getline(file, line))
    {
        DEBUG("Current line: " << line)

        // Get first word to check type
        string type = "";
        i = 0;
        while(line.at(i) != ' ') 
        {
            type += line.at(i);
            i++;

            if (i == line.size()){
                throw std::runtime_error("Missing arguments");
            }
        }
        line.erase(0, i+1); // Remove first word from line string

        // Check type to see how to proceed
        if (type == "User")
        {
            DEBUG("Type: User")

            // Check to make sure that username is the only other argument in line
            if(line.find(' ') != string::npos) {
                // If not, throw runtime exeption
                DEBUG("Invalid Username: " << line)
                throw std::runtime_error("Invalid User format");
            }
            else{
                for (i = 0; i < line.size(); i++)
                {
                    char curr = line.at(i);
                    if (!(((curr >= 'a') & (curr <= 'z')) | ((curr >= 'A') & (curr <= 'Z')))){
                        throw std::runtime_error("Invalid username format");
                    }
                }

                // If proper format, add user
                addUser(line);
            }
        }
        else if (type == "Post")
        {
            DEBUG("Type: Post")

            // Check postID 
            string ID = "";
            i = 0;
            while(line.at(i) != ' ') 
            {
                char curr = line.at(i);
                DEBUG("Current character: " << curr)
                if((curr >= '0') & (curr <= '9')) // Check that ID is made of digits
                {
                    ID += curr;
                    i++;
        
                    if (i == line.size()){
                        throw std::runtime_error("Missing arguments");
                    }
                }
                else // If non-digit characters, throw runtime error
                {
                    DEBUG("Invalid postID")
                    throw std::runtime_error("Invalid post format");
                }
            }
            line.erase(0, i+1); // Remove postID from line string
            unsigned int postID = stoi(ID); // Create an int to store ID
            DEBUG("Post ID: " << postID)

            // Get username
            string username = "";
            i = 0;
            while(line.at(i) != ' ') 
            {
                username += line.at(i);
                i++;
                    
                if (i == line.size()){
                    throw std::runtime_error("Missing arguments");
                }
            }
            line.erase(0, i+1); // Remove username from line string

            // Format username
            for (long unsigned int i = 0; i < username.length(); i++)
            {
                char curr = username.at(i);
                if (!(((curr >= 'a') & (curr <= 'z')) | ((curr >= 'A') & (curr <= 'Z')))){
                        throw std::runtime_error("Invalid username format");
                    }
                if ((curr >= 'A') & (curr <= 'Z'))
                {
                    DEBUG("Converting " << username.at(i) << " to lowercase...")
                    username.at(i) += 32;
                }
            }
            DEBUG("Username: " << username)

            // Create post
            addPost(postID, username, line);
        }
        else{
            throw std::runtime_error("Unknown type found in input");
        }
        
    }
}

void Network::addUser(string userName)
{
    DEBUG("Username: " << userName);
    // Convert to lowercase
    for (long unsigned int i = 0; i < userName.length(); i++)
    {
        if ((userName.at(i) >= 'A') & (userName.at(i) <= 'Z'))
        {
            DEBUG("Converting " << userName.at(i) << " to lowercase...");
            userName.at(i) += 32;
        }
    }

    // Check that username is not taken
    for (User *user : users)
    {
        DEBUG("Checking against user " << user->getUserName())
        if (userName == user->getUserName())
        {
            DEBUG("Username taken")
            throw std::invalid_argument("Username is already taken");
        }
    }

    // Create new user and add to network
    DEBUG("Creating new user...");
    User *newUser = new User(userName);
    users.push_back(newUser);

    // Print confirmation message
    std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText)
{
    DEBUG("Adding post by " << userName << ", ID = " << postId);

    // Check that postID is unique and user exist
    DEBUG("Checking postID...")
    for (long unsigned int i = 0; i < posts.size(); i++)
    {
        unsigned int checkID = posts.at(i)->getPostId();
        string checkUser = posts.at(i)->getPostUser();
        if (checkID == postId)
        {
            throw std::invalid_argument("Post ID must be a unique number");
        }
    }

    DEBUG("Checking User exists...")
    bool userFound = false;
    for (User *user : users)
    {
        if (user->getUserName() == userName)
        {
            userFound = true;
        }
    }
    if (!userFound)
    {
        throw std::invalid_argument("User not found");
    }

    // Create post and add to network
    DEBUG("Creating new post...")
    Post *newPost = new Post(postId, userName, postText);
    posts.push_back(newPost);

    // Add post to user data member
    DEBUG("Adding post to user profile...")
    for (User *user : users)
    {
        if (user->getUserName() == userName)
        {
            user->addUserPost(newPost);
        }
    }

    // Get vector of tags from post
    vector<string> postTags = newPost->findTags();

    // Add post to tags/create new tags
    DEBUG("Finding tags...")
    for (string postTag : postTags)
    {
        bool newTag = true;

        // Check through tags on network to see if tag already exists
        for (Tag *tag : tags)
        {
            if (tag->getTagName() == postTag)
            {
                // If found, add post to tag member data
                tag->addTagPost(newPost);
                newTag = false;
            }
        }

        // If tag not found, try to create a new tag
        try
        {
            if (newTag)
            {
                Tag *newTag = new Tag(postTag);
                // Add post to tag member data
                newTag->addTagPost(newPost);
                // Add tag to network member data
                tags.push_back(newTag);
            }
        }
        catch (std::exception &excpt)
        {
            DEBUG("Tag Error: " << excpt.what())
        }
    }

    // Print output
    std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post *> Network::getPostsByUser(string userName)
{
    for (User *user : users)
    {
        if (user->getUserName() == userName)
        {
            return user->getUserPosts();
        }
    }

    // If not found, throw exception
    throw std::invalid_argument("User not found");
}

vector<Post *> Network::getPostsWithTag(string tagName)
{
    for (Tag *tag : tags)
    {
        if (tag->getTagName() == tagName)
        {
            return tag->getTagPosts();
        }
    }
    // If not found, throw exception
    throw std::invalid_argument("Tag not found");
}

vector<string> Network::getMostPopularHashtag()
{
    // Figure out max number of posts within any tag
    long unsigned int numPosts = 0;
    for (Tag *tag : tags)
    {
        if (tag->getTagPosts().size() > numPosts)
        {
            numPosts = tag->getTagPosts().size();
        }
    }

    // Find all tags with numPosts posts and add to a vector
    vector<string> tagNames;
    for (Tag *tag : tags)
    {
        if (tag->getTagPosts().size() == numPosts)
        {
            tagNames.push_back(tag->getTagName());
        }
    }

    // Return vector of tag names
    return tagNames;
}

Network::~Network()
{
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        delete users.at(i);
    }

    for (unsigned int i = 0; i < tags.size(); ++i)
    {
        delete tags.at(i);
    }

    for (unsigned int i = 0; i < posts.size(); ++i)
    {
        delete posts.at(i);
    }
}
