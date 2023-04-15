# ifndef MYSTRING_H
# define MYSTRING_H

class myString {
    private:
    // TODO: Figure out private members

    public:
    myString();
    myString(const myString& myString);
    myString(const char* s);
    ~myString();

    void resize(size_t n);
    size_t capacity() const noexcept;
    size_t size() const noexcept;
    size_t length() const noexcept;
    const char* data() const noexcept;
    bool empty() const noexcept;
    const char& front() const;
    const char& at (size_t pos) const;
    void clear() noexcept;
    size_t find (const myString& str, size_t pos = 0) const noexcept;

    // TODO: Add operators
};

# endif
