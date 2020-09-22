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

size_t ListBasedCommandLineInterface::cursor() const {
  return countUntil(_cursor);
}

size_t ListBasedCommandLineInterface::capacity() const {
  return countUntil(_end);
}

std::string ListBasedCommandLineInterface::toString() const {
  string content = "";
  auto vcursor = _start->next;
  while(vcursor != _end) {
    content.append(1, vcursor->content);
    vcursor = vcursor->next;
  }
  return content;
}

size_t ListBasedCommandLineInterface::size() const {
  return capacity();
}

CommandLineInterface* ListBasedCommandLineInterface::type(char c) {
  auto node = make_shared<Node>(c);
  if (_cursor == _end) {
    auto theNodeBefore = _cursor->prev;
    theNodeBefore->next = node;
    node->prev = theNodeBefore;
    node->next = _end;
    _end->prev = node;
  } else {
    auto theNodeBefore = _cursor->prev;
    theNodeBefore->next = node;
    auto current = _cursor;
    current->prev = node;
    node->prev = theNodeBefore;
    node->next = current;
  }
  return this;
}

CommandLineInterface* ListBasedCommandLineInterface::right() {
  if (_cursor != _end) {
    _cursor = _cursor->next;
  }
  return this;
}

CommandLineInterface* ListBasedCommandLineInterface::left() {
  if (_cursor->prev != _start) {
    _cursor = _cursor->prev;
  }
  return this;
}

std::size_t ListBasedCommandLineInterface::countUntil(std::shared_ptr<Node> toFind) const {
  int pos = 0;
  auto vcursor = _start->next;
  while(vcursor != toFind && vcursor != _end) {
    ++pos;
    vcursor = vcursor->next;
  }
  return pos;
}