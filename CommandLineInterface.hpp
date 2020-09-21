#ifndef CLI
#define CLI
#include <string>
#include <cstring>
#include <cctype>

class CommandLineInterface {
  public:
    static const size_t InitialCapacity{4};

    virtual CommandLineInterface* type(char c) = 0;
    virtual CommandLineInterface* right() = 0;
    virtual CommandLineInterface* left() = 0;

    virtual size_t cursor() const = 0;
    virtual size_t capacity() const = 0;
    virtual size_t size() const = 0;
    virtual std::string toString() const = 0;
};

class CharBasedCommandLineInterface : CommandLineInterface {
  public:
    typedef unsigned long size_t;

    CharBasedCommandLineInterface() : _capacity(InitialCapacity), _cursor(0) {
      _storage = new char[_capacity];
      initStorage();
    }
    CommandLineInterface* type(char c) override;
    CommandLineInterface* right() override;
    CommandLineInterface* left() override;

    size_t cursor() const override;
    size_t capacity() const override;
    size_t size() const override;
    std::string toString() const override;
  private:
    void initStorage();
    void initStorage(char * storageptr, int capacity);
    void resize();
    size_t _cursor;
    size_t _capacity;
    char* _storage;
};

#endif