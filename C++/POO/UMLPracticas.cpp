#include <iostream>

class Product {
private:
    int code;
    int price;
    std::string description;
    std::string type;
public:
    Product() : code(0), price(0), description(" "), type(" ") {}
    ~Product();
};

class SaleItem {
private:
    Product product;
public:
    int quantity; 
    SaleItem() : quantity(0) {}
    ~SaleItem();
};

class Sale {
private:
    int date;
    DiscountPolicy *dcp;
public:
    Sale() : date(0) {}
    ~Sale();

    void getTotal();

};

class DiscountPolicy {
public:
    DiscountPolicy();
    ~DiscountPolicy();

    void getDiscount(Sale sasalele);
};

class CardDiscound {};
class QuantityDiscount {};
class MondayDiscount {};

int main() {
    // 33;
    return 0;
}