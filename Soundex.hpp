#ifndef SOUNDEX_HPP
#define SOUNDEX_HPP
#include <string>

class Soundex {
  public:
    static const size_t MaxCodeLength{4};
    std::string encode(const std::string& word) const;
  private:
    std::string head(const std::string& word) const;
    std::string encodedDigits(const std::string& word) const;
    std::string zeropad(const std::string& word) const;
};


#endif