#include "ShopItem.h"
#include <cmath>

ShopItem::ShopItem(std::string title, double price, size_t quantity = 0) {
    this->title = title;
    this->price = price;
    this->quantity = quantity;
}

double ShopItem::get_total() const {
    return this->price * this->quantity;
}

std::string ShopItem::toString() const {
    return std::to_string(quantity) + "/" + title + "/" +
    std::to_string(static_cast<int>(price)) + "." + std::to_string(static_cast<int>(price*100)%100);
}

bool ShopItem::operator==(const ShopItem & other) const {
    return (title == other.title && price == other.price);
}

void ShopItem::plus(int count) {
    quantity += count;
}

size_t ShopItem::get_quantity() const {
    return quantity;
}

std::string ShopItem::get_title() const {
    return title;
}

double ShopItem::get_price() const {
    return price;
}
