// assume grid is made up of either a-z or A-Z
package rushhour;

import java.io.BufferedReader;
import java.io.Writer;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Solver {

    static Character[][] convertToGrid(int []u, Metadata metadata) {

        Character[][] grid = new Character[6][6];

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                grid[i][j] = '.';
            }
        }

        for (Character car : metadata.cars) {
            int car_int = Character.isUpperCase(car) ? car - 65 : car - 97;
            Boolean orientation = metadata.orientation.get(car);
            Integer size = metadata.size[car_int];
            Integer fp = metadata.fixedPosition[car_int];
            Integer vp = u[car_int];

            if (car.equals(metadata.x) && vp + size > 6) {
                size -= 1;
            }

            for (int d = 0; d < size; d++) {
                if (orientation) {
                    grid[vp + d][fp] = car;
                } else {
                    grid[fp][vp + d] = car;
                }
            }
        }

        return grid;
    }

    static List<int[]> getNeighbors(int []u, Metadata metadata) {

        List<int[]> neighbors = new ArrayList<int[]>();
        Character[][] grid = convertToGrid(u, metadata);

        for (Character car : metadata.cars) {
            int car_int = Character.isUpperCase(car) ? car - 65 : car - 97;
            Boolean orientation = metadata.orientation.get(car);
            Integer size = metadata.size[car_int];
            Integer fp = metadata.fixedPosition[car_int];
            Integer vp = u[car_int];

            for (int np = vp - 1; np >= 0; np -= 1) {
                if ((orientation && grid[np][fp] != '.') || (!orientation && grid[fp][np] != '.')) {
                    break;
                }

                var neighbor = Arrays.copyOf(u, u.length);
                neighbor[car_int] = np;

                neighbors.add(neighbor);
            }

            for (int np = vp + size; np <= 6; np++) {
                if ((np < 6 && orientation && grid[np][fp] != '.') || (np < 6 && !orientation && grid[fp][np] != '.')
                        || (np == 6 && !car.equals(metadata.x))) {
                    break;
                }

                var neighbor = Arrays.copyOf(u, u.length);
                neighbor[car_int] = np - size + 1;

                neighbors.add(neighbor);
            }
        }

        metadata.node_count += neighbors.size();
        return neighbors;
    }

    static List<int[]> shortest_path(Map<String, int[]> prev,
            int[] src, int[] target) {

        List<int[]> path = new ArrayList<int[]>();
        int[] u = target;        
        while (prev.containsKey(Arrays.toString(u))) {
            path.add(0, u);
            u = prev.get(Arrays.toString(u));
        }

        path.add(0, src);
        return path;
    }

    static List<int[]> solve(int[] src, Metadata metadata) {

        Map<String, Integer> dist = new HashMap<String, Integer>();
        Map<String, int[]> prev = new HashMap<String, int[]>();
        dist.put(Arrays.toString(src), 0);

        List<Map.Entry<Integer, int[]>> q = new ArrayList<>();
        q.add(new AbstractMap.SimpleEntry<>(0, src));

        while (!q.isEmpty()) {
            Collections.sort(q, new Comparator<Map.Entry<Integer, int[]>>() {
                @Override
                public int compare(Map.Entry<Integer, int[]> a1,
                        Map.Entry<Integer, int[]> a2) {
                    return a1.getKey().compareTo(a2.getKey());
                }
            });

            Map.Entry<Integer, int[]> item = q.remove(0);

            Integer distu = item.getKey();
            int[] u = item.getValue();

            int car_int = Character.isUpperCase(metadata.x) ? metadata.x - 65 : metadata.x - 97;
            if (u[car_int] == 5) {
                return shortest_path(prev, src, u);
            }

            for (int[] v : getNeighbors(u, metadata)) {
                Integer alt = distu + 1;
                String key = Arrays.toString(v);
                if (!dist.containsKey(key) || alt < dist.get(key)) {
                    dist.put(key, alt);
                    prev.put(key, u);
                    q.add(new AbstractMap.SimpleEntry<>(alt, v));
                }
            }
        }

        return Arrays.asList();
    }

    static String convertPathToInstruction(List<int[]> path, Metadata metadata) {
        String instruction = "";

        for (int i = 1; i < path.size(); i++) {
            var currEntry = path.get(i);
            var prevEntry = path.get(i-1);
            for (Character car : metadata.cars) {
                int car_int = Character.isUpperCase(car) ? car - 65 : car - 97;
                if (currEntry[car_int] != prevEntry[car_int]) {
                    Integer d = currEntry[car_int] - prevEntry[car_int];
                    Boolean v = metadata.orientation.get(car);
                    instruction += String.format("%s%s%d\n", car,
                            (v && d > 0) ? "D" : (v && d < 0) ? "U" : (d > 0) ? "R" : "L",
                            (car.equals(metadata.x)) ? Math.abs(d) - 1 : Math.abs(d)
                    );
                }
            }
        }

        return instruction;
    }

    /**
     * Alternative solve method that doesn't require reading/writing to files.
     * 
     * @param jam bb...g\na..c.g\naxxc.g\na..c..\ne...ff\ne.ddd. or similar
     */
    public static String solve(String jam) {

        Character grid[][] = new Character[6][6];

        int i = 0;
        for (String line : jam.split("\n")) {
            int j = 0;
            for (Character c : line.toCharArray()) {
                grid[i][j] = c;
                j += 1;
            }
            i += 1;
        }

        Metadata metadata = new Metadata(grid);
        int[] src = new int[26];
        for (Character car : metadata.cars) {
            int car_int = Character.isUpperCase(car) ? car - 65 : car - 97;
            src[car_int] = metadata.orientation.get(car) ? metadata.tiles.get(car).get(0)[0]
                    : metadata.tiles.get(car).get(0)[1];
        }

        var path = solve(src, metadata);

        return convertPathToInstruction(path, metadata);
    }

    /**
     * Main solve method.
     * 
     * @param input Input file containing RushHour puzzle.
     * @param output Output file for RushHour solution.
     * @throws Exception if the file not found.
     */
    public static void solveFromFile(String input, String output)
            throws Exception {

        String jam = "";
        try (BufferedReader reader = Files.newBufferedReader(Paths.get(input))) {
            String line = null;
            do {
                line = reader.readLine(); 
                if (line != null) { jam += line + "\n"; }
            }
            while (line != null && !line.isEmpty());
        }

        String instruction = solve(jam);
        try (Writer writer = Files.newBufferedWriter(Paths.get(output),
                Charset.defaultCharset())) {
            writer.write(instruction);
        }
    }

}
