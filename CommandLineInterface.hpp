#ifndef CLI
#define CLI
#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>

class CommandLineInterface {
  public:
    virtual CommandLineInterface* type(char c) = 0;
    virtual CommandLineInterface* right() = 0;
    virtual CommandLineInterface* left() = 0;
    virtual CommandLineInterface* remove() = 0;

    virtual size_t cursor() const = 0;
    virtual size_t capacity() const = 0;
    virtual size_t size() const = 0;
    virtual std::string toString() const = 0;

    virtual ~CommandLineInterface() = default;
};

class CharBasedCommandLineInterface : CommandLineInterface {
  public:
    static const size_t InitialCapacity{4};

    CharBasedCommandLineInterface() : _capacity(InitialCapacity), _cursor(0) {
      _storage = new char[_capacity];
      initStorage();
    }
    CommandLineInterface* type(char c) override;
    CommandLineInterface* right() override;
    CommandLineInterface* left() override;
    CommandLineInterface* remove() override;

    size_t cursor() const override;
    size_t capacity() const override;
    size_t size() const override;
    std::string toString() const override;

    CharBasedCommandLineInterface(const CharBasedCommandLineInterface &source) : _capacity(source._capacity), _cursor(source._cursor) {
      _storage = new char[_capacity];
      strcpy(_storage, source._storage);
    }

    CharBasedCommandLineInterface& operator=(const CharBasedCommandLineInterface &source) {
      _storage = new char[_capacity];
      strcpy(_storage, source._storage);
      _capacity = source._capacity;
      _cursor = source._cursor;

      return *this;
    }

    ~CharBasedCommandLineInterface() {
      delete[] _storage;
    }
  private:
    void initStorage();
    void initStorage(char * storageptr, int capacity);
    void shiftRightUntilCursor();
    void shiftLeftUntilCursor();
    void resize();
    size_t _cursor;
    size_t _capacity;
    char* _storage;
};

class ListBasedCommandLineInterface : CommandLineInterface {
  public:
    ListBasedCommandLineInterface() {
      _start = std::make_shared<Node>('\0');
      _end = std::make_shared<Node>('\0');
      _start->next = _end;
      _end->prev = _start;
      _cursor = _end;
    }
    CommandLineInterface* type(char c) override;
    CommandLineInterface* right() override;
    CommandLineInterface* left() override;
    CommandLineInterface* remove() override;

    size_t cursor() const override;
    size_t capacity() const override;
    size_t size() const override;
    std::string toString() const override;

    ~ListBasedCommandLineInterface() {
      _cursor = _start->next;
      while(_cursor != _end) {
        remove();
      }
    }
  private:
    struct Node {
      Node(char c) : content(c) {}
      char content;
      std::shared_ptr<Node> next;
      std::shared_ptr<Node> prev;
    };
    std::shared_ptr<Node> _start;
    std::shared_ptr<Node> _end;
    std::shared_ptr<Node> _cursor;

    std::size_t countUntil(std::shared_ptr<Node> toFind) const;
};

class VectorBasedCommandLineInterface : CommandLineInterface {
  public:
    static const size_t InitialCapacity{4};
    VectorBasedCommandLineInterface() : _cursor(0) {
      _storage.reserve(4);
    }
    CommandLineInterface* type(char c) override;
    CommandLineInterface* right() override;
    CommandLineInterface* left() override;
    CommandLineInterface* remove() override;

    size_t cursor() const override;
    size_t capacity() const override;
    size_t size() const override;
    std::string toString() const override;
  private:
    std::vector<char> _storage;
    int _cursor;
};

#endif