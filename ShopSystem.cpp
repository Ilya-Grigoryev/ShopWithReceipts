#include "ShopSystem.h"


#include "Receipt.h"

using namespace receipt;

    void ShopSystem::list() {
        std::cout << "╔═════╦══════════════════════╦════════════╦════════════╗\n";
        std::cout << "║ ID  ║ Product              ║ Price (€)  ║ Quantity   ║\n";
        std::cout << "╠═════╬══════════════════════╬════════════╬════════════╣\n";

        for (size_t i = 0; i < products.size(); ++i) {
            const auto& item = products[i];
            std::cout << "║ " << std::setw(3) << i << " ║ "
                      << std::setw(20) << std::left << item.get_title() << " ║ "
                      << std::setw(10) << std::right << std::fixed << std::setprecision(2) << item.get_price() << " ║ "
                      << std::setw(10) << item.get_quantity() << " ║\n";
        }

        std::cout << "╚═════╩══════════════════════╩════════════╩════════════╝\n";
        std::cout << "ADD-cmd: add <id> <qty>\n\n";
        std::cout << "CMD --> ";
    }

    void ShopSystem::help() {
        std::cout << R"(
           *******************************************************
           *                                                     *
           *     WELCOME TO THE "FRUITS/VEGETABLES" SHOP!        *
           *                                                     *
           *******************************************************

           Your shop for the freshest fruits and vegetables!

           Available commands:
           -------------------------------------------------------
           help                 - Display this help message.
           list                 - Show the list of available products.
           add <id> <qty>       - Add an item to cart by ID and quantity.
           cart                 - Show my shopping cart.
           buy                  - Make a purchase.
           add_all              - Buy up the whole shop, just for fun :)
           exit                 - Close this app.
           -------------------------------------------------------
        )" << "\n";
        std::cout << "CMD --> ";
    }

    void ShopSystem::add(size_t id, size_t qty) {
        if (id >= products.size() || qty == 0 || products[id].get_quantity() < qty)
            std::cout << "Invalid ID or Quantity\n";
        else {
            receipt.addItem(ShopItem(products[id].get_title(), products[id].get_price(), qty));
            products[id].plus(-static_cast<int>(qty));
            std::cout << products[id].get_title() << " (X" << qty << ") was successfully added to the cart\n";
        }
        std::cout << "CMD --> ";
    }

    void ShopSystem::cart() {
        std::cout << "╔═════╦══════════════════════╦════════════╦════════════╗\n";
        std::cout << "║ №   ║ Product              ║ Price (€)  ║ Quantity   ║\n";
        std::cout << "╠═════╬══════════════════════╬════════════╬════════════╣\n";

        for (size_t i = 0; i < receipt.getItems()->size(); ++i) {
            const auto& item = receipt.getItems()->at(i);
            std::cout << "║ " << std::setw(3) << i+1 << " ║ "
                      << std::setw(20) << std::left << item.get_title() << " ║ "
                      << std::setw(10) << std::right << std::fixed << std::setprecision(2) << item.get_price() << " ║ "
                      << std::setw(10) << item.get_quantity() << " ║\n";
        }
        auto sum_of_total_price = [this]() {
            double sum = 0.0;
            for (const auto& item : *receipt.getItems()) {
                sum += item.get_total();
            }
            return sum;
        };
        std::cout << "╠═════╩══════════════════════╩════════════╬════════════╣\n";
        std::cout << "║ Sum                                     ║ " << std::setw(10) << sum_of_total_price() << " ║\n";
        std::cout << "╚═════════════════════════════════════════╩════════════╝\n";
        std::cout << "BUY-cmd: buy\n\n";
        std::cout << "CMD --> ";
    }

    void ShopSystem::buy() {
        if (receipt.getItems()->empty())
            std::cout << "But your cart is empty!\n";
        else {
            receipt.print();
            receipt.clear();
            std::cout << "Thank you for your purchase!\nReceipt was printed!\n";
        }
        std::cout << "CMD --> ";
    }

    void ShopSystem::add_all() {
        for (auto& item : products) {
            receipt.addItem(ShopItem(item.get_title(), item.get_price(), item.get_quantity()));
            item.plus(-static_cast<int>(item.get_quantity()));
        }
        std::cout << "You added the whole shop to the cart, thanks Mr. Rich!\n";
        std::cout << "CMD --> ";
    }

    ShopSystem::ShopSystem() { help(); }

    bool ShopSystem::command(const std::string& cmd, std::istringstream& iss) {
        if (cmd.empty())
            return false;
        if (cmd == "help") {
            help();
            return true;
        } else if (cmd == "list") {
            list();
            return true;
        } else if (cmd == "add") {
            size_t id, qty;
            iss >> id >> qty;
            add(id, qty);
            return true;
        } else if (cmd == "cart") {
            cart();
            return true;
        } else if (cmd == "buy") {
            buy();
            return true;
        } else if (cmd == "add_all") {
            add_all();
            return true;
        }
        return false;
    }