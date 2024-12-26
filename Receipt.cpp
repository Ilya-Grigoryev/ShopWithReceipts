#include "Receipt.h"


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

        std::pair<std::string, std::string> Receipt::getDateTimeAsString() {
            auto now = std::chrono::system_clock::now();
            std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

            std::ostringstream oss_date;
            std::ostringstream oss_time;
            oss_date << std::put_time(std::localtime(&now_time_t), "%d/%m/%y");
            oss_time << std::put_time(std::localtime(&now_time_t), "%H:%M:%S");

            return {oss_date.str(), oss_time.str()};
        }

        std::vector<std::vector<bool>> Receipt::generateQrCode(const std::string &data) {
            const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(data.c_str(), qrcodegen::QrCode::Ecc::LOW);

            const int size = qr.getSize();
            std::vector<std::vector<bool>> grid(size, std::vector<bool>(size));

            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                    grid[row][col] = qr.getModule(col, row);
                }
            }
            return grid;
        }

        std::vector<ShopItem>* Receipt::getItems() {
            return &items;
        }

        void Receipt::addItem(ShopItem item) {
            auto item_ptr = std::find(items.begin(), items.end(), item);
            if (item_ptr == items.end())
                items.push_back(std::move(item));
            else {
                item_ptr->plus(item.get_quantity());
            }
        }

        void Receipt::print() {
            std::tie(date, time) = getDateTimeAsString();
            height = 425 + (TABLE_STRING_HEIGHT * items.size());

            std::ofstream pdf(file_name, std::ios::binary);

            auto items_to_string = [this]() {
                std::string ans;
                for (const ShopItem& item : items)
                    ans += item.toString() + "\n";
                ans.pop_back();
                return ans;
            };
            std::vector<std::vector<bool>> qrData = generateQrCode(items_to_string());

            // 1. Titile
            pdf << "%PDF-1.4\n";

            // 2. Page
            pdf << "1 0 obj\n"
                << "<< /Type /Catalog /Pages 2 0 R >>\n"
                << "endobj\n";

            // 3. List of Pages
            pdf << "2 0 obj\n"
                << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                << "endobj\n";

            // 4. Page with Content
            pdf << "3 0 obj\n"
                << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 230 " << height << "]"
                << "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
                << "endobj\n";

            // 5. Content
            pdf << "4 0 obj\n"
                << "<< /Length 44 >>\n"
                << "stream\n"
                << "BT\n"
                << "/F1 19 Tf\n"
                << "20 " << height - 30 << " Td\n"
                << "(fruits/vegetables) Tj\n"
                << "ET\n"
                << "[3 2] 0 d\n"
                << "2 w\n"
                << "18 " << height - 35 << " 197 22 re\n"
                << "S\n"
                << "BT\n"
                << "/F1 9 Tf\n"
                << "32 " << height - 55 << " Td\n"
                << "( \"Fruits and Vegetables GmbH\") Tj\n"
                << "ET\n"
                << "BT\n"
                << "/F1 10 Tf\n"
                << "7 " << height - 100 << " Td\n"
                << "(DATE........................" << date << ") Tj\n"
                << "ET\n"
                << "BT\n"
                << "/F1 10 Tf\n"
                << "7 " << height - 120 << " Td\n"
                << "(TIME........................" << time << ") Tj\n"
                << "ET\n"
                << "BT\n"
                << "/F1 10 Tf\n"
                << "7 " << height - 140 << " Td\n"
                << "(LOCATION......................VIENNA) Tj\n"
                << "ET\n"
                << "BT\n"
                << "/F1 8 Tf\n"
                << "10 TL\n"
                << "5 " << height - 200 << " Td\n"
                << "(+-----+----------------+----------+----------+) Tj\n"
                << "T*\n"
                << "(| QTY | ITEM           | PRICE    | TOTAL    |) Tj\n"
                << "T*\n"
                << "(+-----+----------------+----------+----------+) Tj\n"
                << "T*\n";

            for (const auto& item : items) {
                pdf << "(| " << item.get_quantity()
                    << std::string(4 - std::to_string(item.get_quantity()).size(), ' ')
                    << "| " << item.get_title()
                    << std::string(15 - item.get_title().size(), ' ')
                    << "| " << std::fixed << std::setprecision(2) << item.get_price()
                    << std::string(6 - std::to_string(static_cast<int>(item.get_price())).size(), ' ')
                    << "| " << std::fixed << std::setprecision(2) << item.get_total()
                    << std::string(6 - std::to_string(static_cast<int>(item.get_total())).size(), ' ')
                    << "|) Tj\n" << "T*\n";
            }
            pdf << "(+-----+----------------+----------+----------+) Tj\n"
                << "T*\n";
            auto sum_of_total_price = [this]() {
                double sum = 0.0;
                for (const auto& item : items) {
                    sum += item.get_total();
                }
                return sum;
            };
            pdf << "(| SUM                             | "
                << std::fixed << std::setprecision(2) << sum_of_total_price()
                << std::string(6 - std::to_string(static_cast<int>(sum_of_total_price())).size(), ' ')
                << "|) Tj\n"
                << "T*\n"
                << "(+---------------------------------+----------+) Tj\n"
                << "ET\n";

            int size = qrData.size();
            int cellSize = static_cast<int>(120.0 / qrData.size());
            for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                    int x = (230 - size*cellSize)/2 + col * cellSize;
                    int y = 150 - row * cellSize;

                    if (qrData[row][col])
                        pdf << x << " " << y << " " << cellSize << " " << cellSize << " re f\n";
                }
            }

            pdf << "BT\n"
                << "/F1 10 Tf\n"
                << "30 " << 20 << " Td\n"
                << "(Thank you for your purchase!) Tj\n"
                << "ET\n";

            pdf << "endstream\n"
                << "endobj\n";

            // Font
            pdf << "5 0 obj\n"
                << "<< /Type /Font /Subtype /Type1 /BaseFont /Courier >>\n"
                << "endobj\n";

            // Trailer
            pdf << "trailer\n"
                << "<< /Size 6 /Root 1 0 R >>\n"
                << "startxref\n"
                << "400\n"
                << "%%EOF";

            pdf.close();
        }

        void Receipt::clear() {
            items.clear();
        }
}