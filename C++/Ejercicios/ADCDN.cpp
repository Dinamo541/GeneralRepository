#include <iostream>
#include <string>
#include <random>

class ADCDN
{
private:
    std::string *monstersList;
    int monstersCount;
    int level;

public:
    ADCDN(int newLevel) : monstersList(nullptr), monstersCount(0), level(newLevel)
    {
        if (level <= 1)
            monstersCount = 1;
        else
            monstersCount = 15 + ((level - 2) * 4);
        monstersList = new std::string[monstersCount];
        createMonstersList();
    }

    ~ADCDN() { delete[] monstersList; }

    void createMonstersList()
    {
        if (level == 1)
        {
            for (int i = 0; i < monstersCount; i++)
            {
                if (i < 9)
                    monstersList[i] = "A";
                else
                    monstersList[i] = "B";
            }
        }
        else if (level >= 2 && level < 10)
        {
            for (int i = 0; i < monstersCount; i++)
            {
                if (i < (monstersCount / 2))
                    monstersList[i] = "A";
                else if (i < (monstersCount / 2) + 3)
                    monstersList[i] = "B";
                else
                    monstersList[i] = randomizeMonstersLevelOne(1);
            }
        }
        else
        { // level >= 10
            for (int i = 0; i < monstersCount; i++)
                monstersList[i] = randomizeMonstersLevelOne(2);
        }
    }

    std::string randomizeMonstersLevelOne(int randomIndex)
    {
        if (randomIndex < 0)
            randomIndex = 0;
        if (randomIndex > 5)
            randomIndex = 5;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, randomIndex);
        int r = dist(gen);
        switch (r)
        {
        case 0:
            return "A";
        case 1:
            return "B";
        case 2:
            return "C";
        case 3:
            return "D";
        default:
            return "E";
        }
    }

    void print() const
    {
        for (int i = 0; i < monstersCount; i++)
            std::cout << monstersList[i];
    }
};

int main()
{
    std::cout << "Starting test" << std::endl;
    ADCDN game(4);
    std::cout << "Created game, monsters: " << "(" << 9 << ")" << std::endl;
    game.print();
    std::cout << std::endl
              << "Finished" << std::endl;
    return 0;
}
