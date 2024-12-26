cmake_minimum_required(VERSION 3.16)
project(ShopWithReceipts)

set(CMAKE_CXX_STANDARD 17)


add_executable(ShopWithReceipts main.cpp qrcodegen.cpp ShopItem.cpp ShopItem.h Receipt.cpp Receipt.h ShopSystem.cpp ShopSystem.h)