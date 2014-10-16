package fi.spektrum.sudoku;

import fi.spektrum.sudoku.solver.AbstractSolver;
import fi.spektrum.sudoku.solver.Reader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class SolverMain {

    public static void main(String[] args) throws FileNotFoundException {

        File f = checkInput(args);

        Reader reader = new Reader(new FileInputStream(f));

        AbstractSolver solver = new MySolver(reader);

        // solver.printBoard(solver.getBoard());
        solver.solve();
        solver.printBoard(solver.getBoard());
    }

    /**
     * Helper method to see if the input is valid.
     * <p>
     * @param args
     * <p>
     * @return
     */
    private static File checkInput(String[] args) {

        if (args.length != 1) {
            System.out.println("Can't run program!");
            System.exit(1);
        }

        String filename = args[0];

        File f = new File(filename);
        if (!f.exists()) {
            System.out.println("File: " + filename + ", doesn't exist!");
            System.exit(1);
        }

        return f;
    }
}