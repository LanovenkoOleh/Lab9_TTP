#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>


class Book {
public:
    Book(std::string title, std::string author)
        : title_(std::move(title)), author_(std::move(author)) {}
    const std::string& title() const { return title_; }
    const std::string& author() const { return author_; }
private:
    std::string title_, author_;
};


class IBookRepository {
public:
    virtual ~IBookRepository() = default;
    virtual void save(const Book& book) = 0;
};


class IBookNotifier {
public:
    virtual ~IBookNotifier() = default;
    virtual void notify(const Book& book) = 0;
};


class ConsoleRepository final : public IBookRepository {
public: void save(const Book& book) override;
};


class EmailNotifier final : public IBookNotifier {
public: void notify(const Book& book) override;
};


class Library {
public:
    Library(IBookRepository& repository, IBookNotifier& notifier)
        : repository_(repository), notifier_(notifier) {}
    void addBook(const Book& book);
    const std::vector<Book>& books() const { return books_; }
    void displayBooks() const;
private:
    std::vector<Book> books_;
    IBookRepository& repository_;
    IBookNotifier& notifier_;
};
