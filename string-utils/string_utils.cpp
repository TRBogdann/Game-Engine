#include "string_utils.h"
#include "../exceptions/exceptions.h"
#include <string>



namespace StringUtils 
{
    std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    if (start == s.size())
        return "";

    size_t end = s.size() - 1;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end]))) {
        --end;
    }

    return s.substr(start, end - start + 1);
}

    StringTokenizer::StringTokenizer():tokens(nullptr),size(0)
    {

    }

    StringTokenizer::StringTokenizer(const std::string& str,std::string separators):tokens(nullptr),size(0)
    {
        if(str.length()>0)
        {
            size++;
            for(int i=0; i<str.length(); i++)
            {
                if(separators.find(str[i])!=-1)
                {
                    size++;
                }
            }

            size_t i = 0;
            size_t start = 0;
            this->tokens = new std::string[size];
            for(size_t end=0; end<str.length(); end++)
            {
                if(separators.find(str[end])!=-1 && end>start)
                {
                    this->tokens[i] = str.substr(start,end-start);
                    start = end+1;    
                    i++;
                }
            }

            if(str.length()>start)
            {
                this->tokens[i] = str.substr(start,str.length()-start);
            }
        }
    }

    StringTokenizer::StringTokenizer(const StringTokenizer& tokenizer):tokens(nullptr),size(0)
    {
        if(tokenizer.tokens)
        {
            this->size = tokenizer.size;
            this->tokens = new std::string[this->size];
            int i=0;
            for(auto& token:tokenizer)
            {
                this->tokens[i] = token;
                i++;
            }
        }
    }

    StringTokenizer& StringTokenizer::StringTokenizer::operator=(const StringTokenizer& tokenizer)
    {
        if(this->tokens)
        {
            delete[] this->tokens;
            this->tokens = nullptr;
            this->size = 0;
        }

        if(tokenizer.tokens)
        {
            this->size = tokenizer.size;
            this->tokens = new std::string[this->size];
            int i=0;
            for(auto& token:tokenizer)
            {
                this->tokens[i] = token;
                i++;
            }
        }

        return *this;
    }

    StringTokenizer::~StringTokenizer()
    {
        if(this->tokens)
        {
            delete[] this->tokens;
        }
    }

    std::string* StringTokenizer::data()
    {
        return this->tokens;
    }

    size_t StringTokenizer::length() const
    {
        return this->size;
    }

    std::string& StringTokenizer::operator[](size_t index)
    {
        if(this->tokens==nullptr)
        {
            throw ContainerException(
                ContainerException::INDEX_NULL_POINTER,
                "[StringTokenizer]: Null pointer indexation"
            );
        }

        if(this->size <= index)
        {
            throw ContainerException(
                ContainerException::INDEX_OUT_OF_BOUNDS,
                "[StringTokenizer]: Index out of bounds (size: "+std::to_string(size)+", index: "+std::to_string(index)+")"
            );
        }

        return this->tokens[index];
    }

    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::string;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type*;
    using reference         = value_type&;
    
    StringTokenizer::iterator::iterator(std::string* iter) : it(iter) {}

    reference StringTokenizer::iterator::operator*()  { return *it; }
    pointer   StringTokenizer::iterator::operator->() { return &(*it); }

    StringTokenizer::iterator& StringTokenizer::iterator::operator++() { ++it; return *this; }
    StringTokenizer::iterator  StringTokenizer::iterator::operator++(int) { auto tmp = *this; ++it; return tmp; }

    bool StringTokenizer::iterator::operator==(const iterator& iter) const { return it == iter.it; }
    bool StringTokenizer::iterator::operator!=(const iterator& iter) const { return it != iter.it; }

    StringTokenizer::iterator StringTokenizer::begin() const
    { 
        if(tokens)
            return iterator(&tokens[0]);
        
        return iterator(nullptr);
    }
    StringTokenizer::iterator StringTokenizer::end() const  
    { 
        if(tokens)
            return iterator(&tokens[size]); 

        return iterator(nullptr);
    }
}