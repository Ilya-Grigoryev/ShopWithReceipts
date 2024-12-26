#ifndef PDFCREATOR_SHOPITEM_H
#define PDFCREATOR_SHOPITEM_H

#include <string>

class ShopItem {
    size_t quantity;
    std::string title;
    double price;

public:
    ShopItem(std::string, double, size_t);
    double get_total() const;
    size_t get_quantity() const;
    std::string get_title() const;
    double get_price() const;
    std::string toString() const;
    void plus(int);
    bool operator==(const ShopItem&) const;
};


#endif //PDFCREATOR_SHOPITEM_H
