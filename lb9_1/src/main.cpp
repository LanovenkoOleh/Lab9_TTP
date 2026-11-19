#include "Library.h"
#include <iostream>


int main() {

    std::cout << "=== Mandatory task: Library ===\n";

    ConsoleRepository repository;

    EmailNotifier notifier;

    Library library(repository, notifier);

    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger"));

    library.addBook(Book("To Kill a Mockingbird", "Harper Lee"));

    library.displayBooks();
}
