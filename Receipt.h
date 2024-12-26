#ifndef PDFCREATOR_RECEIPT_H
#define PDFCREATOR_RECEIPT_H

#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <iostream>
#include "ShopItem.h"
#include "qrcodegen.hpp"


namespace receipt {

    const size_t WIDTH = 230;
    const size_t TABLE_STRING_HEIGHT = 10;


    class Receipt final {
        size_t height;
        std::string file_name = "receipt.pdf";
        std::vector<ShopItem> items = {};
        std::string date;
        std::string time;

    private:
        std::pair<std::string, std::string> getDateTimeAsString();

    public:
        static std::vector<std::vector<bool>> generateQrCode(const std::string&);

        std::vector<ShopItem>* getItems();

        void addItem(ShopItem);

        void print();

        void clear();
    };

}



#endif //PDFCREATOR_RECEIPT_H
