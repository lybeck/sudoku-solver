package fi.spektrum.sudoku;

import fi.spektrum.sudoku.solver.AbstractSolver;
import fi.spektrum.sudoku.solver.Reader;
import java.util.Arrays;

public class MySolver extends AbstractSolver {

    private final boolean[] values;

    public MySolver(Reader reader) {
        super(reader);
        values = new boolean[getN2()];
    }

    @Override
    public void solve() {

        int[][] board = new int[getN2()][getN2()];
        for (int row = 0; row < getN2(); row++) {
            System.arraycopy(getBoard()[row], 0, board[row], 0, getN2());
        }
        setBoard(solve2(board));
    }

    private int[][] solve2(int[][] board) {

        int n = 0;
        int direction = 1;

        while (n >= 0 && n < getN2() * getN2()) {

            int row = n / getN2();
            int col = n % getN2();

            if (getBoard()[row][col] == 0 && board[row][col] < getN2()) {
                direction = 1;
                board[row][col] += 1;
                if (noDouble(board, row, col)) {
                    n++;
                }
            } else if (getBoard()[row][col] == 0) {
                board[row][col] = 0;
                n--;
                direction = -1;
            } else {
                n += direction;
            }
        }

        return board;
    }

    private boolean noDouble(int[][] board, int row, int col) {

        Arrays.fill(values, false);

        for (int r = 0; r < getN2(); r++) {
            if (board[r][col] != 0) {
                if (values[board[r][col] - 1]) {
                    return false;
                }
                values[board[r][col] - 1] = true;
            }
        }

        Arrays.fill(values, false);

        for (int c = 0; c < getN2(); c++) {
            if (board[row][c] != 0) {
                if (values[board[row][c] - 1]) {
                    return false;
                }
                values[board[row][c] - 1] = true;
            }
        }

        int minRow = (row % getN()) * getN();
        int maxRow = minRow + getN();
        int minCol = (col % getN()) * getN();
        int maxCol = minCol + getN();

        Arrays.fill(values, false);

        for (int r = minRow; r < maxRow; r++) {
            for (int c = minCol; c < maxCol; c++) {
                if (board[r][c] != 0) {
                    if (values[board[r][c] - 1]) {
                        return false;
                    }
                    values[board[r][c] - 1] = true;
                }
            }
        }

        return true;
    }

}
