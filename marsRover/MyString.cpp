# include <iostream>

# include "MyString.h"

// Constructors
MyString::MyString()
{
    // TODO: Complete constructor
}

MyString::MyString(const MyString& myString)
{
    // TODO: Complete constructor
}

MyString::MyString(const char* s)
{
    // TODO: Complete constructor
}

// Destructor
MyString::~MyString()
{
    // TODO: Complete destructor
}

/**
 * Resizes the myString to a length of n characters.
 * 
 * If n is smaller than the current myString length, the current value is shortened to its first n character, 
 * removing the characters beyond the nth.
 * 
 * If n is greater than the current myString length, the current content is extended by inserting at the end as 
 * many characters as needed to reach a size of n.
*/
void MyString::resize(size_t n)
{

}

/**
 * Returns the size of the storage space currently allocated for the myString, expressed in terms of bytes.
 * 
 * This capacity is not necessarily equal to the myString length. It can be equal or greater, with the extra 
 * space allowing the object to optimize its operations when new characters are added to the myString.
*/
size_t MyString::capacity() const noexcept
{
    // TODO: Complete function
    return 0;
}

/**
 * Returns the length of the myString, in terms of bytes.
 * 
 * This is the number of actual bytes that conform the contents of the myString, which is not necessarily 
 * equal to its storage capacity.
*/
size_t MyString::size() const noexcept
{
    // TODO: Complete function
    return 0;
}

/**
 * Returns the length of the myString, in terms of bytes.
 * 
 * This is the number of actual bytes that conform the contents of the myString, which is not necessarily 
 * equal to its storage capacity.
*/
size_t MyString::length() const noexcept
{
    // TODO: Complete function
    return 0;
}

/**
 * Returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) 
 * representing the current value of the string object.
 * 
 * This array includes the same sequence of characters that make up the value of the myString object plus an 
 * additional terminating null-character ('\0') at the end.
 * 
 * The pointer returned points to the internal array currently used by the myString object to store the characters 
 * that conform its value.
*/
const char* MyString::data() const noexcept
{
    // TODO: Complete function
    return new char[0];
}

/**
 * Returns whether the myString is empty (i.e. whether its length is 0).
*/
bool MyString::empty() const noexcept
{
    // TODO: Complete function
    return false;
}

/**
 * Returns a reference to the first character of the myString.
*/
const char& MyString::front() const
{
    // TODO: Complete function
    return '0';
}

/**
 * Returns a reference to the character at position pos in the myString.
 * 
 * The function automatically checks whether pos is the valid position of a character in the myString (i.e., 
 * whether pos is less than the myString length), throwing an out_of_range exception if it is not.
*/
const char& MyString::at(size_t pos) const
{
    // TODO: Complete function
    return '0';
}

/**
 * Erases the contents of the string, which becomes an empty string (with a length of 0 characters).
*/
void MyString::clear() noexcept
{
    // TODO: Complete function
}

/**
 * Searches the myString for the first occurrence of the sequence specified by its arguments.
 * 
 * When pos is specified, the search only includes characters at or after position pos, ignoring 
 * any possible occurrences that include characters before pos.
 * 
 * Notice that unlike member find_first_of, whenever more than one character is being searched for, 
 * it is not enough that just one of these characters match, but the entire sequence must match.
*/
size_t MyString::find(const MyString& str, size_t pos = 0) const noexcept
{

}

/**
 * Assigns a new value to the string, replacing its current contents.
*/
MyString& MyString::operator = (const MyString& str)
{
    
}

/**
 * Extends the string by appending additional characters at the end of its current value
*/
MyString& MyString::operator += (const MyString& str)
{
    
}

/**
 * Inserts the sequence of characters that conforms value of str into os.
*/
std::ostream& operator << (std::ostream& os, const MyString& str)
{

}