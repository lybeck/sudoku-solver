package fi.spektrum.sudoku.solver;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

public abstract class AbstractSolver {

    private int n;
    private Integer[][] board;

    public AbstractSolver(Reader reader) {
        try {
            n = reader.nextInt();
            int n2 = n * n;
            board = new Integer[n2][n2];

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
    public Integer[][] getBoard() {
        return board;
    }

    public void setBoard(Integer[][] board) {
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
    public void printBoard(Integer[][] board) {

        // Making the number format to be 1 character longer than the biggest
        // number has tokens.
        int count = 2;
        int den = 10;
        while (board.length / den > 0) {
            den *= 10;
            count++;
        }

        // Creating the format string
        StringBuilder format = new StringBuilder();
        for (Integer item : board[0]) {
            format.append("%").append(count).append("d");
        }

        for (Integer[] board1 : board) {
            System.out.println(String.format(format.toString(), (Object[]) board1));
        }
    }
}
