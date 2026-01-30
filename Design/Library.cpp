#include <bits/stdc++.h>
using namespace std;

// Forward declarations
class Book;
class Member;

/* ===================== STATE ===================== */
class State {
public:
    virtual void borrow(Book* book, Member* member) = 0;
    virtual void returnBook(Book* book) = 0;
    virtual string name() = 0;
    virtual ~State() = default;
};

/* ===================== BOOK ===================== */
class Book {
    int id;
    string title;
    string author;
    State* state;
    Member* borrowedBy;

public:
    Book(int id, string title, string author)
        : id(id), title(title), author(author),
          state(nullptr), borrowedBy(nullptr) {}

    void setState(State* s) {
        state = s;
    }

    void setBorrowedBy(Member* m) {
        borrowedBy = m;
    }

    Member* getBorrowedBy() {
        return borrowedBy;
    }

    void borrow(Member* member) {
        state->borrow(this, member);
    }

    void returnBook() {
        state->returnBook(this);
    }

    int getId() const { return id; }
    string getTitle() const { return title; }
};

/* ===================== MEMBER ===================== */
class Member {
    int id;
    string name;

public:
    Member(int id, string name) : id(id), name(name) {}
    int getId() const { return id; }
    string getName() const { return name; }
};

/* ===================== STATES ===================== */
class AvailableState : public State {
public:
    static AvailableState* instance() {
        static AvailableState instance;
        return &instance;
    }

    void borrow(Book* book, Member* member) override;
    void returnBook(Book* book) override {
        cout << "Book is already available\n";
    }

    string name() override {
        return "Available";
    }
};

class BorrowedState : public State {
public:
    static BorrowedState* instance() {
        static BorrowedState instance;
        return &instance;
    }

    void borrow(Book* book, Member* member) override {
        cout << "Book already borrowed\n";
    }

    void returnBook(Book* book) override;

    string name() override {
        return "Borrowed";
    }
};

/* ===================== STATE IMPLEMENTATIONS ===================== */
void AvailableState::borrow(Book* book, Member* member) {
    book->setBorrowedBy(member);
    book->setState(BorrowedState::instance());
    cout << "Book borrowed by " << member->getName() << "\n";
}

void BorrowedState::returnBook(Book* book) {
    cout << "Book returned by "
         << book->getBorrowedBy()->getName() << "\n";
    book->setBorrowedBy(nullptr);
    book->setState(AvailableState::instance());
}

/* ===================== LIBRARY ===================== */
class Library {
    unordered_map<int, unique_ptr<Book>> books;

public:
    void addBook(int id, string title, string author) {
        if (books.count(id)) {
            cout << "Book already exists\n";
            return;
        }
        auto book = make_unique<Book>(id, title, author);
        book->setState(AvailableState::instance());
        books[id] = move(book);
    }

    void borrowBook(int bookId, Member* member) {
        if (!books.count(bookId)) {
            cout << "Book not found\n";
            return;
        }
        books[bookId]->borrow(member);
    }

    void returnBook(int bookId) {
        if (!books.count(bookId)) {
            cout << "Book not found\n";
            return;
        }
        books[bookId]->returnBook();
    }
};

/* ===================== MAIN ===================== */
int main() {
    Library library;

    Member bharani(1, "Bharani");
    Member kavi(2, "Kavi");

    library.addBook(101, "Narnia", "C.S. Lewis");

    library.borrowBook(101, &bharani);
    library.borrowBook(101, &kavi);

    library.returnBook(101);
    library.returnBook(101);

    return 0;
}
