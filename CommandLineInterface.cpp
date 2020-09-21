#include "CommandLineInterface.hpp"
using namespace std;

size_t CharBasedCommandLineInterface::cursor() const {
  return _cursor;
}

size_t CharBasedCommandLineInterface::capacity() const {
  return _capacity;
}

string CharBasedCommandLineInterface::toString() const {
  return std::string(_storage);
}

void CharBasedCommandLineInterface::initStorage() {
  initStorage(_storage, _capacity);
}

void CharBasedCommandLineInterface::initStorage(char * storageptr, int capacity) {
  for (int i = 0; i != capacity; ++i) {
    *(storageptr + i) = '\0';
  }
}

void CharBasedCommandLineInterface::resize() {
  size_t newcapacity = _capacity * 2;
  char * newStorage = new char[newcapacity];
  initStorage(newStorage, newcapacity);
  strcpy(newStorage, _storage);
  delete[] _storage;
  _storage = newStorage;
  _capacity = newcapacity;
}

size_t CharBasedCommandLineInterface::size() const {
  return strlen(_storage);
}

CommandLineInterface* CharBasedCommandLineInterface::right() {
  if (_cursor < size()) {
    ++_cursor;
  }
  return this;
}

CommandLineInterface* CharBasedCommandLineInterface::left() {
  if (_cursor > 0) {
    --_cursor;
  }
  return this;
}

CommandLineInterface* CharBasedCommandLineInterface::type(char c) {
  if (size() == (_capacity - 1)) {
    resize();
  }
  char * current = _storage + _cursor;
  if (*current == '\0') {
    *(current) = c;
  } else {
    for(int i = size(); i != _cursor; --i) {
      *(_storage + i) = *(_storage + i - 1);
    }
    *(current) = c;
  }
  ++_cursor;
  return this;
}