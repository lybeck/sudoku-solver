package fi.spektrum.sudoku;

import fi.spektrum.sudoku.solver.AbstractSolver;
import fi.spektrum.sudoku.solver.Reader;

public class MySolver extends AbstractSolver {

    public MySolver(Reader reader) {
        super(reader);
    }

    @Override
    public void solve() {

        Integer[][] board = new Integer[getBoardSize()][getBoardSize()];
        for (int row = 0; row < getBoardSize(); row++) {
            System.arraycopy(getBoard()[row], 0, board[row], 0, getBoardSize());
        }

        setBoard(solve2(board));
    }

    private Integer[][] solve2(Integer[][] board) {

        int n = 0;
        int direction = 1;

        while (n >= 0 && n < getBoardSize() * getBoardSize()) {

            int row = n / getBoardSize();
            int col = n % getBoardSize();

            if (getBoard()[row][col] == 0 && board[row][col] < getBoardSize()) {
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

    private boolean noDouble(Integer[][] board, int row, int col) {

        boolean[] values = new boolean[getBoardSize()];

        for (int r = 0; r < getBoardSize(); r++) {
            if (board[r][col] != 0) {
                if (values[board[r][col] - 1]) {
                    return false;
                }
                values[board[r][col] - 1] = true;
            }
        }

        values = new boolean[getBoardSize()];

        for (int c = 0; c < getBoardSize(); c++) {
            if (board[row][c] != 0) {
                if (values[board[row][c] - 1]) {
                    return false;
                }
                values[board[row][c] - 1] = true;
            }
        }

        int minRow = (row % getBlockSize()) * getBlockSize();
        int maxRow = minRow + getBlockSize();
        int minCol = (col % getBlockSize()) * getBlockSize();
        int maxCol = minCol + getBlockSize();

        values = new boolean[getBoardSize()];

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
