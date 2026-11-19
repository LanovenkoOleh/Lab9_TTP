#include "Library.h"
#include <iostream>


void ConsoleRepository::save(const Book&) { std::cout << "Saving book to database...\n"; }

void EmailNotifier::notify(const Book&) { std::cout << "Sending email notification about the new book...\n"; }

void Library::addBook(const Book& book) {
    books_.push_back(book);
    repository_.save(book);
    notifier_.notify(book);
}

void Library::displayBooks() const {
    for (const auto& b : books_)
        std::cout << "Title: " << b.title() << ", Author: " << b.author() << '\n';
}
