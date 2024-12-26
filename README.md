# ShopWithReceipts

**ShopWithReceipts** is a command-line tool that allows you to "purchase" fruits and vegetables from a virtual shop. At the end of the purchase, it generates a PDF receipt containing the list of purchased items and a QR code with a summary of the purchase.

## Features

- **Shop Commands**:
  - `help`: Display this help message.
  - `list`: Show the list of available products.
  - `add <id> <qty>`: Add an item to cart by ID and quantity.
  - `cart`: Show my shopping cart.
  - `buy`: Make a purchase.
  - `add_all`: Buy up the whole shop, just for fun :)
  - `exit`: Close this app.

- **Receipt Generation**:
  - Generates a PDF document with the purchase list.
  - Includes a QR code with a summary of the purchase in the PDF document.

## Installation and launch

To install and run the application, you need the following:

- [C++ Compiler](https://gcc.gnu.org/)
- [QR Code Generator Library](https://github.com/nayuki/QR-Code-generator)
---
1. Clone the repository.
2. Download the following files from the QR Code Generator Library and place these files in project directory:
    - [qrcodegen.cpp](https://github.com/nayuki/QR-Code-generator/blob/master/cpp/qrcodegen.cpp)
    - [qrcodegen.hpp](https://github.com/nayuki/QR-Code-generator/blob/master/cpp/qrcodegen.hpp)

3. In the project directory:
```sh 
mkdir build && cd build
cmake .. && make
./ShopWithReceipts
```
