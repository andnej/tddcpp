#include "Soundex.hpp"

std::string Soundex::encode(const std::string& word) const {
  return zeropad(head(word) + encodedDigits(tail(word)));
}

std::string Soundex::head(const std::string& word) const {
  return word.substr(0, 1);
}

std::string Soundex::tail(const std::string& word) const {
  return word.substr(1);
}

std::string Soundex::encodedDigits(const std::string& word) const {
  if (word.length() > 0) {
    return "1";
  } else {
    return "";
  }
}

std::string Soundex::zeropad(const std::string& word) const {
  int zeroNeeded = MaxCodeLength - word.length();
  return word + std::string(zeroNeeded, '0');
}