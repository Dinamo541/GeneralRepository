#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

int phraseToNumber(string phrase) {
    static const map<string, int> phraseMap = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
        {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"ten", 10},
        {"eleven", 11}, {"twelve", 12}, {"thirteen", 13}, {"fourteen", 14},
        {"fifteen", 15}, {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18},
        {"nineteen", 19}, {"twenty", 20}, {"thirty", 30}, {"forty", 40},
        {"fifty", 50}, {"sixty", 60}, {"seventy", 70}, {"eighty", 80},
        {"ninety", 90}
    };
    transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower);
    auto it = phraseMap.find(phrase);
    return (it != phraseMap.end()) ? it->second : 0;
}

string takeOutFirstPhrase(string& numberInLetters) {
    size_t pos = numberInLetters.find(' ');
    string firstPhrase;
    if (pos != string::npos) {
        firstPhrase = numberInLetters.substr(0, pos);
        numberInLetters = numberInLetters.substr(pos + 1);
    } else {
        firstPhrase = numberInLetters;
        numberInLetters = "";
    }
    return firstPhrase;
}

bool isPhraseValid(string phrase) {
    static const map<string, bool> validPhrases = {
        {"zero", true}, {"one", true}, {"two", true}, {"three", true}, {"four", true}, {"five", true},
        {"six", true}, {"seven", true}, {"eight", true}, {"nine", true}, {"ten", true},
        {"eleven", true}, {"twelve", true}, {"thirteen", true}, {"fourteen", true},
        {"fifteen", true}, {"sixteen", true}, {"seventeen", true}, {"eighteen", true},
        {"nineteen", true}, {"twenty", true}, {"thirty", true}, {"forty", true},
        {"fifty", true}, {"sixty", true}, {"seventy", true}, {"eighty", true},
        {"ninety", true}, {"hundred", true}, {"thousand", true}, {"million", true},
        {"and", true}, {"a", true}, {"billion", true}, {"trillion", true}
    };
    transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower);
    return validPhrases.find(phrase) != validPhrases.end();
}

bool isPhraseDifferentFromNumber(string phrase) {
    transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower);
    return (phrase == "million" || phrase == "thousand" || phrase == "hundred" ||
            phrase == "and" || phrase == "a" || phrase == "billion" || phrase == "trillion");
}

int main() {
    string numberInLetters = "", phrase = "", option = "1", allowedCharacters = "12";
    int number = 0;
    cout << "Welcome to the number converter from letters to numbers." << endl;
    while (option != "2") {
        number = 0, phrase = "", numberInLetters = "";
        cout << "Enter a number in letters, 1 to see which words are allowed or 2 to exit: ";
        getline(cin, numberInLetters);
        if (numberInLetters.empty()) {
            cout << "You must enter a number in letters." << endl;
            continue;
        } else if (numberInLetters.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ12 ") != string::npos) {
            cout << "The number must only contain letters and spaces." << endl;
            continue;
        } else if (numberInLetters == "1") {
            cout << "The allowed words are: zero, one, two, three, four, five, six, seven, eight, nine, ten," << endl;
            cout << "eleven, twelve, thirteen, fourteen, fifteen, sixteen, seventeen," << endl;
            cout << "eighteen, nineteen, twenty, thirty, forty, fifty, sixty," << endl;
            cout << "seventy, eighty, ninety, hundred, thousand, million." << endl;
            cout << "If you use 'and' or 'a' that will not affect the final result. Press enter to back." << endl;
            cin.get();
            continue;
        } else if (numberInLetters == "2") {
            cout << "Goodbye, the program is off." << endl;
            return 0;
        } 
        transform(numberInLetters.begin(), numberInLetters.end(), numberInLetters.begin(), ::tolower);
        string lastPhrase = "";
        number = 0;
        while (!numberInLetters.empty()) {
            phrase = takeOutFirstPhrase(numberInLetters);
            if (phrase == lastPhrase) {
                cout << "Sorry, but your number cannot repeat the same word twice at the same time. Try again." << endl;
                continue;
            } else if (!isPhraseValid(phrase)) {
                cout << "The written number has some grammatical errors. Please check the spaces, spelling, and order." << endl;
                break;
            } else if (!isPhraseDifferentFromNumber(phrase)) {
                number += phraseToNumber(phrase);
            } else if (phrase == "trillion") {
                number *= 1000000000000;
            } else if (phrase == "billion") {
                number *= 1000000000;
            } else if (phrase == "million") {
                number *= 1000000;
            } else if (phrase == "thousand") {
                number *= 1000;
            } else if (phrase == "hundred") {
                number *= 100;
            }
            lastPhrase = phrase;
        }
        cout << "The number is: " << number << endl;
        do {
            cout << "Do you want to try again? (1. Yes / 2. No): ";
            cin >> option;
            cin.ignore();
            if (option.find_first_not_of(allowedCharacters) != string::npos) {
                cout << "That is not a valid option, please select another option." << endl;
            }
        } while (option.find_first_not_of(allowedCharacters) != string::npos);
    }
    cout << "Goodbye, the program is off." << endl;
    return 0;
8;}