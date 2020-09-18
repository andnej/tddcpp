#include "Soundex.hpp"

std::string Soundex::encode(const std::string& word) const {
  auto encoded = head(word);

  if (word.length() > 1) {
    encoded += "1";
  }
  return zeropad(head(word) + encodedDigits(word));
}

std::string Soundex::head(const std::string& word) const {
  return word.substr(0, 1);
}

std::string Soundex::encodedDigits(const std::string& word) const {
  if (word.length() > 1) {
    return "1";
  } else {
    return "";
  }
}

std::string Soundex::zeropad(const std::string& word) const {
  int zeroNeeded = MaxCodeLength - word.length();
  return word + std::string(zeroNeeded, '0');
}