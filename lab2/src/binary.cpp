#include "../include/binary.h"

Binary::Binary() : _size{0}, _data{nullptr} {}

Binary::Binary(const size_t &n, unsigned char value)
{
    validateBit(value);
    _size = n;
    _data = new unsigned char[n];
    for (int i = 0; i < n; ++i)
    {
        _data[i] = value;
    }
}

Binary::Binary(const std::initializer_list<unsigned char> &values)
{
    _size = values.size();
    _data = new unsigned char[_size];

    size_t i = 0;
    for (unsigned char digit : values)
    {
        validateBit(digit);
        _data[i++] = digit;
    }
}

Binary::Binary(const std::string &str)
{
    _size = str.size();
    _data = new unsigned char[_size];

    for (size_t i = 0; i < _size; i++)
    {
        validateBit(str[i]);
        _data[i] = str[i];
    }
}

Binary::Binary(const Binary &other)
{
    _size = other._size;
    _data = new unsigned char[_size];

    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }
}

Binary::Binary(Binary &&other) noexcept
{
    _size = other._size;
    _data = other._data;
    other._data = nullptr;
    other._size = 0;
}

Binary &Binary::operator=(const Binary &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] _data;
    _size = other._size;
    _data = new unsigned char[_size];

    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }

    return *this;
}

Binary &Binary::operator+=(const Binary &other)
{
    int thisNumb = 0;
    for (size_t i = 0; i < _size; ++i)
    {
        thisNumb = (thisNumb << 1) | (_data[i] - '0');
    }

    int otherNumb = 0;
    for (size_t j = 0; j < other._size; ++j)
    {
        otherNumb = (otherNumb << 1) | (other._data[j] - '0');
    }

    int sumNumb = thisNumb + otherNumb;

    size_t newSize = 0;
    unsigned char *newData = new unsigned char[sizeof(sumNumb) * 8 + 1]{0};

    while (sumNumb > 0)
    {
        newData[newSize++] = (sumNumb % 2) + '0';
        sumNumb /= 2;
    }

    for (size_t i = 0; i < newSize / 2; ++i)
    {
        std::swap(newData[i], newData[newSize - 1 - i]);
    }

    delete[] _data;
    _data = newData;
    _size = newSize;

    return *this;
}

Binary &Binary::operator-=(const Binary &other)
{
    if (_size < other._size)
    {
        throw std::underflow_error("Subtraction result would be negative.");
    }

    int carry = 0;
    for (size_t i = 0; i < _size; i++)
    {
        int otherDigit = (i < other._size) ? (other._data[other._size - i - 1] - '0') : 0;
        int diff = (_data[_size - i - 1] - '0') - otherDigit - carry;

        if (diff < 0)
        {
            _data[_size - i - 1] = diff + 2 + '0';
            carry = 1;
        }
        else
        {
            _data[_size - i - 1] = diff + '0';
            carry = 0;
        }
    }

    if (carry != 0)
    {
        throw std::underflow_error("Subtraction result would be negative.");
    }

    return *this;
}

bool Binary::operator==(const Binary &other) const
{
    if (_size != other._size)
    {
        return false;
    }

    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] != other._data[i])
        {
            return false;
        }
    }
    return true;
}

bool Binary::operator<(const Binary &other) const
{
    if (_size > other._size)
    {
        return false;
    }

    if (_size < other._size)
    {
        return true;
    }

    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] < other._data[i])
        {
            return true;
        }
        if (_data[i] > other._data[i])
        {
            return false;
        }
    }
    return false;
}

bool Binary::operator>(const Binary &other) const
{
    return other < *this;
}

size_t Binary::getSize() const
{
    return _size;
}

unsigned char *Binary::getData() const
{
    return _data;
}

Binary::~Binary() noexcept
{
    delete[] _data;
    _data = nullptr;
    _size = 0;
}

void Binary::validateBit(unsigned char digit)
{
    if (digit != '0' && digit != '1')
    {
        throw std::invalid_argument("Invalid binary digit");
    }
}