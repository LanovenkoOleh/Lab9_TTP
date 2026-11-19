#include "Library.h"
#include <iostream>
#include <stdexcept>
#include <string>


static int passed = 0;

#define CHECK(expr) do { if (!(expr)) throw std::runtime_error(std::string("FAILED: ") + #expr + " at line " + std::to_string(__LINE__)); ++passed; } while(0)


struct FakeRepository : IBookRepository {
    int calls = 0;
    void save(const Book&) override { ++calls; }
};

struct FakeNotifier : IBookNotifier {
    int calls = 0;
    void notify(const Book&) override { ++calls; }
};


int main() {
    try {
        { FakeRepository repo; FakeNotifier notifier; Library library(repo, notifier);
          library.addBook(Book("Book A", "Author A"));
          CHECK(repo.calls == 1); CHECK(notifier.calls == 1);
          CHECK(library.books().size() == 1); CHECK(library.books()[0].title() == "Book A"); }
        std::cout << "ALL TESTS PASSED: " << passed << " assertions\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
