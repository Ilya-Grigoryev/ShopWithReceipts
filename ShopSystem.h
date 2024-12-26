#ifndef PDFCREATOR_SHOPSYSTEM_H
#define PDFCREATOR_SHOPSYSTEM_H

#include "Receipt.h"

using namespace receipt;

class ShopSystem {
    Receipt receipt;
    std::vector<ShopItem> products {
            ShopItem("Apple", 2.40, 100),
            ShopItem("Banana", 1.20, 150),
            ShopItem("Pineapple", 3.50, 30),
            ShopItem("Cucumber", 1.10, 200),
            ShopItem("Watermelon", 4.50, 50),
            ShopItem("Melon", 3.00, 40),
            ShopItem("Orange", 2.00, 120),
            ShopItem("Lemon", 1.50, 90),
            ShopItem("Lime", 1.60, 70),
            ShopItem("Grapes", 2.80, 60),
            ShopItem("Peach", 3.20, 80),
            ShopItem("Plum", 2.50, 50),
            ShopItem("Pear", 2.60, 100),
            ShopItem("Kiwi", 2.90, 60),
            ShopItem("Strawberry", 4.00, 40),
            ShopItem("Blueberry", 5.00, 30),
            ShopItem("Raspberry", 5.50, 25),
            ShopItem("Cherry", 3.80, 45),
            ShopItem("Carrot", 1.20, 150),
            ShopItem("Potato", 0.90, 300),
            ShopItem("Onion", 0.80, 250),
            ShopItem("Garlic", 2.50, 100),
            ShopItem("Tomato", 2.30, 200),
            ShopItem("Bell Pepper", 3.00, 120),
            ShopItem("Zucchini", 1.70, 180),
            ShopItem("Eggplant", 2.00, 90),
            ShopItem("Spinach", 3.50, 70),
            ShopItem("Lettuce", 1.50, 150)
    };

private:
    void list();

    void help();

    void add(size_t, size_t);

    void cart();

    void buy();

    void add_all();

public:
    ShopSystem();

    bool command(const std::string&, std::istringstream&);

};


#endif //PDFCREATOR_SHOPSYSTEM_H
