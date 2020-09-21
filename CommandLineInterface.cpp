#include "CommandLineInterface.hpp"

size_t CommandLineInterface::cursor() const {
  return _cursor;
}

size_t CommandLineInterface::capacity() const {
  return _capacity;
}

std::string CommandLineInterface::toString() const {
  return std::string(_storage);
}

void CommandLineInterface::initStorage() {
  initStorage(_storage, _capacity);
}

void CommandLineInterface::initStorage(char * storageptr, int capacity) {
  for (int i = 0; i != capacity; ++i) {
    *(storageptr + i) = '\0';
  }
}

void CommandLineInterface::resize() {
  size_t newcapacity = _capacity * 2;
  char * newStorage = new char[newcapacity];
  initStorage(newStorage, newcapacity);
  strcpy(newStorage, _storage);
  delete _storage;
  _storage = newStorage;
  _capacity = newcapacity;
}

size_t CommandLineInterface::size() const {
  return strlen(_storage);
}

CommandLineInterface* CommandLineInterface::right() {
  if (_cursor < size()) {
    ++_cursor;
  }
  return this;
}

CommandLineInterface* CommandLineInterface::left() {
  if (_cursor > 0) {
    --_cursor;
  }
  return this;
}

CommandLineInterface* CommandLineInterface::type(char c) {
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