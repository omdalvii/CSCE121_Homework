# ifndef MYSTRING_H
# define MYSTRING_H

class MyString {
    private:
    char* chars;
    size_t charCount;
    // TODO: Figure out private members

    public:
    MyString();
    MyString(const MyString& myString);
    MyString(const char* s);
    ~MyString();

    void resize(size_t n);
    size_t capacity() const noexcept;
    size_t size() const noexcept;
    size_t length() const noexcept;
    const char* data() const noexcept;
    bool empty() const noexcept;
    const char& front() const;
    const char& at (size_t pos) const;
    void clear() noexcept;
    size_t find (const MyString& str, size_t pos = 0) const noexcept;

    MyString& operator = (const MyString& str);
    MyString& operator += (const MyString& str);
};

std::ostream& operator << (std::ostream& os, const MyString& str);

# endif
