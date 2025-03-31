#include <iostream>
#include <random>
#include <vector>

class Book
{

public:
    // common attributes that belong to books
    std::string title;
    std::string author;
    std::string publisher;
    std::string ISBN; // ISBN is also stored as a string because some can begin with 0,
};
class LibraryBook : public Book
{ // child class of the book class
public:
    int book_id;
    bool available = true; // its own unique attribute for availability
};

void getBookinfo();
void checkStatus();
void calculateFine();
void borrowBook();
void showMenu();
void displayBooks();
void borrowHistory();
bool validISBN(const std::string &isbnStr);

const int MAX_BOOKS = 10; // the max amount of books our array can hold
int borrow_count = 0; //increases as books are borrowed
int book_counter = 0;         // increases as books are added to the library
LibraryBook books[MAX_BOOKS]; // array of books
// dynamic array of borrowed books,that holds the book ID and title
std::vector<std::vector<std::string>> borrowed_books(MAX_BOOKS, std::vector<std::string>(2));
int array_size = sizeof(books) / sizeof(LibraryBook); // the amount of items inside the book array

int main()
{ // main function

    showMenu();

    return 0;
}

void showMenu()
{

    int choice;

    do
    {
        std::cout << "Select a operation:\n1) Get book info\n2) Check status\n3) Calculate fine\n4) Borrow book\n5) Display books\n6) Display borrowed books\n7) Exit\nCHOICE: ";
        std::cin >> choice;

        switch (choice) // error handling for each option
        {
        case 1:
            if (array_size == book_counter)
            { // checks for when the array is full
                std::cout << "Error: Maximum number of books reached\n";
            }
            else
            {
                getBookinfo();
            }

            break;

        case 2:
            if (book_counter == 0)
            { // checks is array is empty
                std::cout << "Error: No books in library yet\n";
            }
            else
            {
                checkStatus();
            }

            break;

        case 3:
            calculateFine();
            break;

        case 4:
            // question didnt mention to add this but the system cant be complete
            // without being able to borrow out books,it will also validate that the other
            //  functions work properly
            if (book_counter == 0)
            {
                std::cout << "Error: No books in the library yet\n";
            }
            else
            {
                borrowBook();
            }

            break;
        case 5:
            // question also didnt mention this
            if (book_counter == 0)
            {
                std::cout << "Error: No books in the library yet\n";
            }
            else
            {
                displayBooks();
            }
            break;

        case 6:
            if (book_counter == 0)
            {
                std::cout << "No books have been borrowed yet\n";
            }
            else
            {
                borrowHistory();
            }
            break;
        case 7:
            // Exits the system

            break;

        default:
            std::cout << "Invalid choice,try again\n";
        }

    } while (choice != 7);
}

void borrowHistory()
{
    std::cout << "All borrowed books\n";
    for (auto &book : borrowed_books)
    {
        if (!book[0].empty() && !book[1].empty())
        {
            // will only display the books if there are any borrowed out
            std::cout << "******************\n";
            std::cout << "Book ID: " << book[0] << "\n";
            std::cout << "Book title:" << book[1] << "\n";
            std::cout << "******************\n";
        }
    }
}

bool validISBN(const std::string &isbnStr)
{
    std::string cleanIsbn;
    for (char c : isbnStr)
    {
        if (isdigit(c))
        {                   // checks to see whether the character is a number or not
            cleanIsbn += c; // adds to the string if it is
        }
    }

    // Check length (10 or 13)
    if (cleanIsbn.length() != 10 && cleanIsbn.length() != 13)
    {
        return false; // ISBN numbers are only 10 and 13 digits
    }

    if (cleanIsbn.length() == 10)
    {
        // ISBN 10 validation
        return true;
    }
    else
    {
        // ISBN 13 validation
        return true;
    }
}

void borrowBook()
{
    int id;
    std::cout << "\nEnter book ID: ";
    std::cin >> id;
    bool found = false;
    // loops through the book array and checks if the book exists
    for (LibraryBook &book : books)
    {
        if (book.book_id == id)
        {
            found = true;
            if (book.available == false)
            { // if the book is not available
                std::cout << "Book is already borrowed out\n";
                return;
            }
            // adds the information to the array
            borrowed_books[borrow_count][0] = std::to_string(book.book_id);
            borrowed_books[borrow_count][1] = book.title;
            book.available = false;
            borrow_count++; // increments counter to add to the  next to position of array
            std::cout << "Book has been successfully borrowed\n";
            std::cout << "************\n";
            std::cout << book.book_id << '\n';
            std::cout << book.title << '\n';
            std::cout << book.author << '\n';
            std::cout << book.publisher << '\n';
            std::cout << book.ISBN << '\n';
            std::cout << book.available << '\n';
            std::cout << "************\n";
        }
    }
    if (!found)
    {
        // if the book is not found
        std::cout << "Book doesn't exist.\n";
    }
}

void displayBooks()
{
    // loops through book array and prints info
    std::cout << "All available books\n";
    for (LibraryBook book : books)
    {
        std::cout << "************\n";
        std::cout << "Book ID: " << book.book_id << '\n';
        std::cout << "Book title: " << book.title << '\n';
        std::cout << "Book author: " << book.author << '\n';
        std::cout << "Book publisher: " << book.publisher << '\n';
        std::cout << "ISBN number: " << book.ISBN << '\n';
        std::cout << "Availability(1 = true,0=false):  " << book.available << '\n'; // its printed as its boolean
        std::cout << "************\n";
    }
}

void calculateFine()
{
    int overdue_fee = 10; // R10 a day
    // The lending period in this scenario is 14 days
    // for everyday the book is late its a R10 fee
    int days;
    std::cout << "Amount of days overdue:";
    std::cin >> days;

    overdue_fee *= days;

    std::cout << "The fee due is R" << overdue_fee << '\n';
}

void checkStatus()
{
    int id;
    std::cout << "Enter book ID: ";
    std::cin >> id;

    for (LibraryBook book : books)
    {
        if (book.book_id == id)
        { // first checks if the id entered matches an id in array

            book.available == true ? std::cout << "Book is available\n" : std::cout << "Book is not available\n";
        }
    }
}

void getBookinfo()
{
    LibraryBook book;
    bool uniqueId = false;

    // generates a random ID between 1-10
    while (!uniqueId)
    {
        book.book_id = rand() % 10 + 1; // 0 is not an option here
        uniqueId = true;

        // checks if this ID already exists
        for (int i = 0; i < book_counter; i++)
        { // cant use a for each loop because the variable and object here has the same name
            if (books[i].book_id == book.book_id)
            {
                uniqueId = false; // if it does exist the loop repeats till it finds a id that hasnt been used yet
                break;
            }
        }
    }

    std::cout << "Book ID: " << book.book_id << "\n";
    std::cout << "Enter book title: ";
    std::cin.ignore(); // Clear the newline from previous input
    while (std::getline(std::cin, book.title) && book.title.empty())
    { // validation for all the possible user errors
        std::cout << "Error: Title cannot be empty.\nEnter book title: ";
    }

    std::cout << "Enter book author: ";
    while (std::getline(std::cin, book.author) && book.author.empty())
    {
        std::cout << "Error: Author cannot be empty.\nEnter book author: ";
    }
    std::cout << "Enter book publisher: ";
    while (std::getline(std::cin, book.publisher) && book.publisher.empty())
    {
        std::cout << "Error: Publisher cannot be empty.\nEnter book publisher: ";
    }

    std::cout << "Enter book ISBN: ";
    std::string isbnInput;
    while (std::cin >> isbnInput && !validISBN(isbnInput)) // I didnt use get line because its not supposed to have any spaces
    {
        std::cout << "Error: Invalid ISBN.\nPlease enter a valid 10 or 13 digit ISBN: ";
    }
    book.ISBN = isbnInput;

    books[book_counter] = book; // adds book to array
    book_counter++;             // increments the counter
}
