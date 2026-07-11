#include <iostream>
using namespace std;

void setup()
{
    for (int i = 2; i < 7; i++)
    {
        pinMode(i, OUTPUT);
    }
}

int TIME = 300;
void loop()
{
    for (int i = 2; i < 7; i++)
    {
        digitalWrite(i, HIGH);
        delay(TIME);
        digitalWrite(i, LOW);
        delay(TIME);
    }
    for (int i = 5; i > 2; i--)
    {
        digitalWrite(i, HIGH);
        delay(TIME);
        digitalWrite(i, LOW);
        delay(TIME);
    }
}

// Mock functions to simulate Arduino behavior

string HIGH = "HIGH";
string LOW = "LOW";
string OUTPUT = "OUTPUT";

void pinMode(int pin, string mode)
{
}

void digitalWrite(int pin, string value)
{
}

void delay(int ms)
{
}
