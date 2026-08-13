import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class WaveGeneratorAlgorithm {

    public static void main(String[] args) {
        Integer waveNumber = 99; // Example wave number, can be changed for testing
        List<String> wave1 = generateWave(waveNumber);
        for (String monster : wave1) {
            System.out.print(monster + " ");
        }
        System.out.println("\nWave: " + waveNumber);
        System.out.println("Total monsters: " + wave1.size());
        System.out.println("Monster quantities: " + monstersQuantity);
    }

    /**
     * Array of standard monster type identifiers (excludes boss type F).
     */
    private static final String[] monsterTypes = { "A", "B", "C", "D", "E" };

    /**
     * 2D matrix storing generated monsters for a wave before randomization.
     * Rows represent monster types, columns represent wave positions.
     */
    private static String[][] waveMonstersMatrix;

    /**
     * Predefined monster type distribution ratios for each difficulty tier.
     * Key: wave number threshold (0, 10, 20, etc.)
     * Value: array of [typeA, typeB, typeC, typeD, typeE] ratios
     *
     * Distribution increases in complexity and introduces higher-tier monsters
     * as wave thresholds increase.
     */
    private static final HashMap<Integer, int[]> WAVE_VARIATIONS = new HashMap<>() {
        {
            put(0, new int[] { 1, 0, 0, 0, 0 }); // Waves 1-9: mostly type A
            put(10, new int[] { 1, 0, 0, 0, 0 }); // Waves 10-19
            put(20, new int[] { 1, 1, 0, 0, 0 }); // Waves 20-29
            put(30, new int[] { 2, 2, 0, 0, 0 }); // Waves 30-39
            put(40, new int[] { 2, 3, 1, 0, 0 }); // Waves 40-49
            put(50, new int[] { 2, 4, 2, 0, 0 }); // Waves 50-59: introduces type E
            put(60, new int[] { 3, 5, 3, 2, 0 }); // Waves 60-69
            put(70, new int[] { 4, 5, 3, 3, 0 }); // Waves 70-79
            put(80, new int[] { 3, 3, 4, 3, 3 }); // Waves 80-89
            put(90, new int[] { 3, 2, 5, 5, 3 }); // Waves 90+: highest difficulty
        }
    };

    /**
     * The final wave list containing all monsters for the current wave in
     * randomized order.
     */
    private static List<String> finalWave = new ArrayList<>();

    /**
     * The total number of monsters to spawn in the current wave.
     * Calculated based on wave number and caps at 150 maximum.
     */
    private static Integer monstersQuantity;

    /**
     * The current wave number being generated.
     */
    private static Integer waveNumber;

    /**
     * Private constructor to prevent instantiation of this utility class.
     */
    private WaveGeneratorAlgorithm() {
    }

    /**
     * Generates a complete monster wave for the specified wave number.
     *
     * Wave 1 is hardcoded: 8 type A monsters and 2 type B monsters (10 total).
     * Waves 2 and beyond use the matrix generation system with scaling difficulty.
     * Monster quantity = 15 + ((waveNumber - 2) / 2), capped at 150.
     * Every 10th wave (10, 20, 30, etc.) includes a boss monster (type F).
     *
     * @param waveNumberParam the wave number to generate (starting from 1)
     * @return a list of monster type strings ("A", "B", "C", "D", "E", "F")
     *         in randomized spawn order
     *
     * @see #WAVE_VARIATIONS for difficulty scaling
     */
    public static List<String> generateWave(int waveNumberParam) {
        finalWave = new ArrayList<>();
        waveNumber = waveNumberParam;

        if (waveNumber == 1) {
            monstersQuantity = 10;
        } else {
            monstersQuantity = 13 + ((waveNumber - 2) / 2);
            if (monstersQuantity > 150) {
                monstersQuantity = 150;
            }
        }

        generateWaveFromMatrix(getWaveVariation());

        return finalWave;
    }

    /**
     * Retrieves the monster type distribution variation for the current wave.
     * Maps wave numbers to their difficulty tier and returns the corresponding
     * ratio array.
     * Uses the nearest lower threshold from WAVE_VARIATIONS.
     *
     * Example: wave 25 falls in tier 20, so uses the ratio at key 20.
     * If wave number exceeds the highest tier (90+), uses the tier 90 values.
     *
     * @return array of [typeA, typeB, typeC, typeD, typeE] ratios for the current
     *         wave tier
     */
    private static int[] getWaveVariation() {
        Integer variationKey = waveNumber / 10 * 10;
        return WAVE_VARIATIONS.getOrDefault(variationKey, new int[] { 3, 4, 5, 4, 3 });
    }

    /**
     * Generates a wave from the difficulty matrix using weighted random selection.
     *
     * Process:
     * 1. Creates a matrix of pre-generated monsters organized by type
     * 2. Builds a pool of monsters based on the required distribution ratios
     * 3. Randomly selects from the pool and adds to finalWave, removing each
     * selected monster
     *
     * This ensures proper type distribution while maintaining randomness.
     *
     * @param monstersNeeded array of [typeA, typeB, typeC, typeD, typeE] quantities
     *                       needed
     */
    private static void generateWaveFromMatrix(int[] monstersNeeded) {
        createWaveMatrix();
        List<String> monsters = new ArrayList<>();

        for (int i = 0; i < monstersQuantity; i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < monstersNeeded[j]; k++) {
                    monsters.add(waveMonstersMatrix[j][i]);
                }
            }
        }

        for (int i = 0; i < monstersQuantity; i++) {
            int randomIndex = (int) (Math.random() * monsters.size());
            finalWave.add(monsters.get(randomIndex));
            monsters.remove(randomIndex);
        }
    }

    /**
     * Creates a 2D matrix of pre-generated monsters organized by type.
     * Each row represents a monster type (0-4 for types A-E), each column a wave
     * position.
     *
     * Monsters are generated with level weighting:
     * - Row 0 (type A): level 1 (weak)
     * - Row 1 (type B): level 2
     * - Row 2 (type C): level 3
     * - Rows 3-4 (types D-E): level 4 (strong)
     *
     * This matrix is then used by {@link #generateWaveFromMatrix(int[])}
     * to create the final wave with proper distribution.
     */
    private static void createWaveMatrix() {
        waveMonstersMatrix = new String[5][monstersQuantity];
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < monstersQuantity; j++) {
                switch (i) {
                    case 0 -> waveMonstersMatrix[i][j] = getRandomMonster(0);
                    case 1 -> waveMonstersMatrix[i][j] = getRandomMonster(1);
                    case 2 -> waveMonstersMatrix[i][j] = getRandomMonster(2);
                    case 3 -> waveMonstersMatrix[i][j] = getRandomMonster(3);
                    case 4 -> waveMonstersMatrix[i][j] = getRandomMonster(4);
                }
                System.out.println("Generated monster for type " + i + ": " + waveMonstersMatrix[i][j]);
            }
        }
    }

    /**
     * Generates a random monster type based on the specified difficulty level.
     *
     * Level 0: mostly type A (weak).
     * Level 1: more type B, some type A.
     * Level 2: introduces type C, with some A and B.
     * Level 3: includes types D and E (strong), with some A, B, C.
     * Level 4: balanced mix of all types (used for highest difficulty waves).
     *
     * @param level the difficulty level (0-4, where 0 is weakest)
     * @return a random monster type string ("A", "B", "C", "D", or "E")
     */
    private static String getRandomMonster(Integer level) {
        int randomIndex = (int) (Math.random() * (level + 1));
        return monsterTypes[randomIndex];
    }

}
