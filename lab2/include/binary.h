#pragma once

#include <initializer_list>
#include <string>
#include <stdexcept>
class Binary
{
public:
    Binary();
    Binary(const size_t &n, unsigned char value);
    Binary(const std::initializer_list<unsigned char> &values);
    Binary(const std::string &str);
    Binary(const Binary &other);
    Binary(Binary &&other) noexcept;
    ~Binary() noexcept;

    Binary &operator=(const Binary &other);
    Binary &operator+=(const Binary &other);
    Binary &operator-=(const Binary &other);

    bool operator==(const Binary &other) const;
    bool operator<(const Binary &other) const;
    bool operator>(const Binary &other) const;

    size_t getSize() const;
    unsigned char *getData() const;

private:
    size_t _size;
    unsigned char *_data;

    void validateBit(unsigned char digit);
};
