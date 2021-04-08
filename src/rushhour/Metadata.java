package rushhour;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Metadata {

    Character grid[][] = new Character[6][6];

    Character x;

    Set<Character> cars = new HashSet<Character>();

    Map<Character, List<Integer[]>> tiles = new HashMap<Character, List<Integer[]>>();

    Map<Character, Boolean> orientation = new HashMap<Character, Boolean>();

    int[] size = new int[26];

    int[] fixedPosition = new int[26];

    Integer node_count = 0;

    Metadata(Character[][] grid) {
        this.grid = grid;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (grid[i][j] == '.') {
                    continue;
                }

                cars.add(grid[i][j]);

                if (!tiles.containsKey(grid[i][j])) {
                    tiles.put(grid[i][j], new ArrayList<Integer[]>());
                }

                tiles.get(grid[i][j]).add(new Integer[] { i, j });
            }
        }

        this.x = cars.contains('X') ? 'X' : 'x';

        for (Character car : cars) {
            int car_int = Character.toLowerCase(car) - 97;
            orientation.put(car, (tiles.get(car).get(0)[0] != tiles.get(car).get(1)[0]));
            size[car_int] = tiles.get(car).size();
            fixedPosition[car_int] = orientation.get(car) ? tiles.get(car).get(0)[1] : tiles.get(car).get(0)[0];
        }
    }

}