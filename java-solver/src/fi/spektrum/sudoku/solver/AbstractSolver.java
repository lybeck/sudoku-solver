package fi.spektrum.sudoku.solver;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

public abstract class AbstractSolver {

    private int n;
    private int[][] board;

    public AbstractSolver(Reader reader) {
        try {
            n = reader.nextInt();
            int n2 = n * n;
            board = new int[n2][n2];

            for (int row = 0; row < n2; row++) {
                for (int col = 0; col < n2; col++) {
                    board[row][col] = reader.nextInt();
                }
            }
        } catch (IOException ex) {
            Logger.getLogger(AbstractSolver.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    public abstract void solve();

    /**
     * This method returns an array where the dimensions are: Integer[rows][cols].
     * <p>
     * Fields with the value 0 (zero) are empty fields.
     * <p>
     * @return
     */
    public int[][] getBoard() {
        return board;
    }

    public void setBoard(int[][] board) {
        this.board = board;
    }

    /**
     * How wide the block is.
     * <p>
     * @return
     */
    public int getN() {
        return n;
    }

    public int getN2() {
        return board.length;
    }

    /**
     * Prints the board to the standard output stream.
     * <p>
     * @param board
     */
    public void printBoard(int[][] board) {

        // Making the number format to be 1 character longer than the biggest
        // number has tokens.
        int count = 2;
        int den = 10;
        while (board.length / den > 0) {
            den *= 10;
            count++;
        }

        // Creating the format string
        String format = "%-" + count + "d";

        StringBuilder sb = new StringBuilder();
        for (int[] row : board) {
            for (int num : row) {
                sb.append(String.format(format, num));
            }
            sb.append("\n");
        }
        System.out.print(sb.toString());
    }
}
