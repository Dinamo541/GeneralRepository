import java.util.concurrent.ThreadLocalRandom;

public class MainOne {
    private String[] monstersList;
    private int monstersCount;
    private int level;

    public MainOne(int newLevel) {
        this.level = newLevel;
        if (level <= 1)
            this.monstersCount = 1;
        else
            this.monstersCount = 15 + ((level - 2) * 4);
        this.monstersList = new String[this.monstersCount];
        createMonstersList();
    }

    private void createMonstersList() {
        if (level == 1) {
            for (int i = 0; i < monstersCount; i++) {
                if (i < 9)
                    monstersList[i] = "A";
                else
                    monstersList[i] = "B";
            }
        } else if (level >= 2 && level < 10) {
            for (int i = 0; i < monstersCount; i++) {
                if (i < (monstersCount / 2))
                    monstersList[i] = "A";
                else if (i < (monstersCount / 2) + 3)
                    monstersList[i] = "B";
                else
                    monstersList[i] = randomizeMonstersLevelOne(1);
            }
        } else { // level >= 10
            for (int i = 0; i < monstersCount; i++)
                monstersList[i] = randomizeMonstersLevelOne(5);
        }
    }

    private String randomizeMonstersLevelOne(int randomIndex) {
        if (randomIndex < 0)
            randomIndex = 0;
        if (randomIndex > 5)
            randomIndex = 5;
        int r = ThreadLocalRandom.current().nextInt(0, randomIndex + 1);
        switch (r) {
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

    public void print() {
        for (int i = 0; i < monstersCount; i++)
            System.out.println(monstersList[i]);
    }

    public static void main(String[] args) {
        System.out.println("Starting Java MainOne test");
        MainOne game = new MainOne(9);
        System.out.println("Created game, monsters: (" + game.monstersCount + ")");
        game.print();
        System.out.println("Finished");
    }
}
