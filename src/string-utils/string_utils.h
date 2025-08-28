#include <string>
#include <iterator>

namespace StringUtils
{
    std::string trim(const std::string& s);

    class StringTokenizer
    {
        public:
        StringTokenizer();
        StringTokenizer(const std::string& str,std::string separators);
        StringTokenizer(const StringTokenizer& tokenizer);
        StringTokenizer& operator=(const StringTokenizer& tokenizer);
        ~StringTokenizer();

        std::string& operator[](std::size_t index);
        size_t length() const;
        std::string* data();

        class iterator {
                std::string* it;
            public:
                using iterator_category = std::forward_iterator_tag;
                using value_type        = std::string;
                using difference_type   = std::ptrdiff_t;
                using pointer           = value_type*;
                using reference         = value_type&;

                iterator(std::string* iter);

                reference operator*();
                pointer   operator->();

                iterator& operator++();
                iterator  operator++(int);

                bool operator==(const iterator& iter) const;
                bool operator!=(const iterator& iter) const;
        };

        iterator begin() const;
        iterator end() const;

    private:
        std::string* tokens;
        size_t size;
    };
}