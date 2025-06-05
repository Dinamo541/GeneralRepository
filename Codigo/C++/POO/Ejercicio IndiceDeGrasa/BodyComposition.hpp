#ifndef BODYCOMPOSITION_HPP
#define BODYCOMPOSITION_HPP

#include <iostream>
#include <string>

class BodyComposition {
private:
    float height;
    float weight;

public:
    BodyComposition();
    BodyComposition(float newHeight, float newWeight);

    float getHeight() const;
    float getWeight() const;
    float getBMI() const;
    std::string getObesityType() const;

    void setHeight(float newHeight);
    void setWeight(float newWeight);

    std::string toString() const;
};

#endif