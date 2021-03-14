import rushhour.Solver;

/**
 * Create solution file for each test case
 */
public class TestSolutions {

    public static void main(String[] args) throws Exception {

        String[][] files = {
            {"D:/_input/A00.txt", "D:/_output/A00.txt"},
            {"D:/_input/A01.txt", "D:/_output/A01.txt"},
            {"D:/_input/A02.txt", "D:/_output/A02.txt"},
            {"D:/_input/A03.txt", "D:/_output/A03.txt"},
            {"D:/_input/A04.txt", "D:/_output/A04.txt"},
            {"D:/_input/A05.txt", "D:/_output/A05.txt"},
            {"D:/_input/A06.txt", "D:/_output/A06.txt"},
            {"D:/_input/A07.txt", "D:/_output/A07.txt"},
            {"D:/_input/A08.txt", "D:/_output/A08.txt"},
            {"D:/_input/A09.txt", "D:/_output/A09.txt"},
            {"D:/_input/A10.txt", "D:/_output/A10.txt"},
            {"D:/_input/B11.txt", "D:/_output/B11.txt"},
            {"D:/_input/B12.txt", "D:/_output/B12.txt"},
            {"D:/_input/B13.txt", "D:/_output/B13.txt"},
            {"D:/_input/B14.txt", "D:/_output/B14.txt"},
            {"D:/_input/B15.txt", "D:/_output/B15.txt"},
            {"D:/_input/B16.txt", "D:/_output/B16.txt"},
            {"D:/_input/B17.txt", "D:/_output/B17.txt"},
            {"D:/_input/B18.txt", "D:/_output/B18.txt"},
            {"D:/_input/B19.txt", "D:/_output/B19.txt"},
            {"D:/_input/B20.txt", "D:/_output/B20.txt"},
            {"D:/_input/C21.txt", "D:/_output/C21.txt"},
            {"D:/_input/C22.txt", "D:/_output/C22.txt"},
            {"D:/_input/C23.txt", "D:/_output/C23.txt"},
            {"D:/_input/C24.txt", "D:/_output/C24.txt"},
            {"D:/_input/C25.txt", "D:/_output/C25.txt"},
            {"D:/_input/C26.txt", "D:/_output/C26.txt"},
            {"D:/_input/C27.txt", "D:/_output/C27.txt"},
            {"D:/_input/C28.txt", "D:/_output/C28.txt"},
            {"D:/_input/C29.txt", "D:/_output/C29.txt"},
            {"D:/_input/D30.txt", "D:/_output/D30.txt"},
            {"D:/_input/D31.txt", "D:/_output/D31.txt"},
            {"D:/_input/D32.txt", "D:/_output/D32.txt"},
            {"D:/_input/D33.txt", "D:/_output/D33.txt"},
            {"D:/_input/D34.txt", "D:/_output/D34.txt"},
            {"D:/_input/D35.txt", "D:/_output/D35.txt"}
        };

        for (String[] inputOutput : files) {
            Solver.solveFromFile(inputOutput[0], inputOutput[1]);
        }
    }

}
