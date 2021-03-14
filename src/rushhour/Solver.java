package rushhour;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
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
import java.util.Scanner;
import java.util.Map.Entry;

public class Solver {

    static Character[][] convertToGrid(Map<Character, Integer> u, Metadata metadata) {

        Character[][] grid = new Character[6][6];

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                grid[i][j] = '.';
            }
        }

        for (Character car : metadata.cars) {
            Boolean orientation = metadata.orientation.get(car);
            Integer size = metadata.size.get(car);
            Integer fp = metadata.fixedPosition.get(car);
            Integer vp = u.get(car);

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

    static List<Map<Character, Integer>> getNeighbors(Map<Character, Integer> u, Metadata metadata) {

        List<Map<Character, Integer>> neighbors = new ArrayList<Map<Character, Integer>>();
        Character[][] grid = convertToGrid(u, metadata);

        for (Character car : metadata.cars) {
            Boolean orientation = metadata.orientation.get(car);
            Integer size = metadata.size.get(car);
            Integer fp = metadata.fixedPosition.get(car);
            Integer vp = u.get(car);

            for (int np = vp - 1; np >= 0; np -= 1) {
                if ((orientation && grid[np][fp] != '.') || (!orientation && grid[fp][np] != '.')) {
                    break;
                }

                Map<Character, Integer> neighbor = new HashMap<Character, Integer>();
                for (Entry<Character, Integer> entry : u.entrySet()) {
                    if (entry.getKey().equals(car)) {
                        neighbor.put(entry.getKey(), np);
                    } else {
                        neighbor.put(entry.getKey(), entry.getValue());
                    }
                }

                neighbors.add(neighbor);
            }

            for (int np = vp + size; np <= 6; np++) {
                if ((np < 6 && orientation && grid[np][fp] != '.') || (np < 6 && !orientation && grid[fp][np] != '.')
                        || (np == 6 && !car.equals(metadata.x))) {
                    break;
                }

                Map<Character, Integer> neighbor = new HashMap<Character, Integer>();
                for (Entry<Character, Integer> entry : u.entrySet()) {
                    if (entry.getKey().equals(car)) {
                        neighbor.put(entry.getKey(), np - size + 1);
                    } else {
                        neighbor.put(entry.getKey(), entry.getValue());
                    }
                }

                neighbors.add(neighbor);
            }
        }

        metadata.node_count += neighbors.size();
        return neighbors;
    }

    static List<Map<Character, Integer>> shortest_path(Map<Map<Character, Integer>, Map<Character, Integer>> prev,
            Map<Character, Integer> src, Map<Character, Integer> target) {

        List<Map<Character, Integer>> path = new ArrayList<Map<Character, Integer>>();
        Map<Character, Integer> u = target;
        while (prev.containsKey(u)) {
            path.add(0, u);
            u = prev.get(u);
        }

        path.add(0, src);
        return path;
    }

    static List<Map<Character, Integer>> solve(Map<Character, Integer> src, Metadata metadata) {

        Map<Map<Character, Integer>, Integer> dist = new HashMap<Map<Character, Integer>, Integer>();
        Map<Map<Character, Integer>, Map<Character, Integer>> prev = new HashMap<Map<Character, Integer>, Map<Character, Integer>>();
        dist.put(src, 0);

        List<Map.Entry<Integer, Map<Character, Integer>>> q = new ArrayList<>();
        q.add(new AbstractMap.SimpleEntry<>(0, src));

        while (!q.isEmpty()) {
            Collections.sort(q, new Comparator<Map.Entry<Integer, Map<Character, Integer>>>() {
                @Override
                public int compare(Map.Entry<Integer, Map<Character, Integer>> a1,
                        Map.Entry<Integer, Map<Character, Integer>> a2) {
                    return a1.getKey().compareTo(a2.getKey());
                }
            });

            Map.Entry<Integer, Map<Character, Integer>> item = q.remove(0);

            Integer distu = item.getKey();
            Map<Character, Integer> u = item.getValue();

            if (u.get(metadata.x) == 5) {
                return shortest_path(prev, src, u);
            }

            for (var v : getNeighbors(u, metadata)) {
                Integer alt = distu + 1;
                if (!dist.containsKey(v) || alt < dist.get(v)) {
                    dist.put(v, alt);
                    prev.put(v, u);
                    q.add(new AbstractMap.SimpleEntry<>(alt, v));
                }
            }
        }

        return Arrays.asList();
    }

    static String convertPathToInstruction(List<Map<Character, Integer>> path, Metadata metadata) {
        String instruction = "";

        for (int i = 1; i < path.size(); i++) {
            var currEntry = path.get(i);
            var prevEntry = path.get(i-1);
            for (Character car : currEntry.keySet()) {
                if (!currEntry.get(car).equals(prevEntry.get(car))) {
                    Integer d = currEntry.get(car) - prevEntry.get(car);
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
        Map<Character, Integer> src = new HashMap<Character, Integer>();
        for (Character car : metadata.cars) {
            src.put(car, (metadata.orientation.get(car)) ? metadata.tiles.get(car).get(0)[0]
                    : metadata.tiles.get(car).get(0)[1]);
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