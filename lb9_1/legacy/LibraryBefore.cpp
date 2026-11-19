#include <iostream>
#include <string>
#include <vector>

class BookBefore {
public:
    std::string title, author;
    void display() const { std::cout << "Title: " << title << ", Author: " << author << '\n'; }
    void saveToDatabase() const { std::cout << "Saving book to database...\n"; }
    void sendEmailNotification() const { std::cout << "Sending email notification about the new book...\n"; }
};

class LibraryBefore {
public:
    void addBook(const BookBefore& b) { books.push_back(b); b.saveToDatabase(); b.sendEmailNotification(); }
    void displayBooks() const { for (const auto& b : books) b.display(); }
private:
    std::vector<BookBefore> books;
};
