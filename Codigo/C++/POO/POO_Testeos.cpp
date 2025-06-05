#include <iostream>
#include <string>
using namespace std;

class user {
public:
    int hours[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    void changeHours(int number) {
        for (int i = 0; i < 10; i++) {
            hours[i] = hours[i] * number;
        }
    }
};

int main() {
    user user1;
    user user2;
    int auxiliari = user1.getHours();
    user1.setHours(user2.getHours());
    user2.setHours(auxiliari);
    return 0;
}