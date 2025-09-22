#include "BodyComposition.hpp"
#include <iostream>
#include <string>

BodyComposition::BodyComposition() : height(0.0f), weight(0.0f) {}

BodyComposition::BodyComposition(float newHeight, float newWeight) {
    setHeight(newHeight);
    setWeight(newWeight);
}

float BodyComposition::getHeight() const {
    return height;
}

float BodyComposition::getWeight() const {
    return weight;
}

float BodyComposition::getBMI() const {
    if (height > 0) {
        return weight / (height * height);
    }
    return 0.0f;
}

std::string BodyComposition::getObesityType() const {
    float BMI = getBMI();
    if (BMI < 18.5) {
        return "Infrapeso";
    } else if (BMI <= 24.9) {
        return "Normal";
    } else if (BMI <= 29.9) {
        return "Sobrepeso";
    } else if (BMI <= 39.9) {
        return "Obesidad";
    } else {
        return "Obesidad Morbida";
    }
}

void BodyComposition::setHeight(float newHeight) {
    if (newHeight >= 0.05f && newHeight <= 4.0f) {
        height = newHeight;
    } else {
        height = 0.0f;
    }
}

void BodyComposition::setWeight(float newWeight) {
    if (newWeight >= 10.0f && newWeight <= 800.0f) {
        weight = newWeight;
    } else {
        weight = 0.0f;
    }
}

std::string BodyComposition::toString() const {
    return "Persona (Altura: " + std::to_string(height) +
           " Peso: " + std::to_string(weight) + ")";
}