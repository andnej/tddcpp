#ifndef CLI
#define CLI
#include <string>
#include <cstring>
#include <cctype>

class CommandLineInterface {
  public:
    static const size_t InitialCapacity{4};

    CommandLineInterface() : _capacity(InitialCapacity), _cursor(0) {
      _storage = new char[_capacity];
      initStorage();
    }
    CommandLineInterface* type(char c);
    CommandLineInterface* right();
    CommandLineInterface* left();

    size_t cursor() const;
    size_t capacity() const;
    size_t size() const;
    std::string toString() const;
  private:
    void initStorage();
    void initStorage(char * storageptr, int capacity);
    void resize();
    size_t _cursor;
    size_t _capacity;
    char* _storage;
};

#endif