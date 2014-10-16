package fi.spektrum.sudoku.dlx;

import fi.spektrum.sudoku.solver.AbstractSolver;
import fi.spektrum.sudoku.solver.Reader;
import java.util.Map;
import java.util.TreeMap;

/**
 *
 * @author Lasse Lybeck
 */
public class DLXSolver extends AbstractSolver {

    private final ColumnNode header;
    private final Map<Integer, Node> o;
    private boolean solved;

    public DLXSolver(Reader reader) {
        super(reader);
        header = new DLXParser(getBoard()).getHeader();
        o = new TreeMap<>();
        solved = false;
    }

    @Override
    public void solve() {
        search(0);
    }

    private void search(int k) {
        System.out.println("k = " + k);
        if (header.getRight() == header) {
            // done!
            System.out.println("Found solution!");
            printSolution();
            solved = true;
            return;
        }
        ColumnNode c = selectColumn(header);
        coverColumn(c);
        for (Node r = c.getDown(); r != c; r = r.getDown()) {
            o.put(k, r);
            for (Node j = r.getRight(); j != r; j = j.getRight()) {
                coverColumn(j.getColumn());
            }
            search(k + 1);
            if (solved) {
                return;
            }
            r = o.get(k);
            c = r.getColumn();
            for (Node j = r.getLeft(); j != r; j = j.getLeft()) {
                uncoverColumn(j.getColumn());
            }
            uncoverColumn(c);
        }
    }

    private ColumnNode selectColumn(ColumnNode h) {
        int min = Integer.MAX_VALUE;
        ColumnNode best = null;
        for (ColumnNode c = h.getRight(); c != h; c = c.getRight()) {
            if (c.getSize() < min) {
                    best = c;
                    min = c.getSize();
            }
        }
        return best;
    }

    private void coverColumn(ColumnNode c) {
        c.getRight().setLeft(c.getLeft());
        c.getLeft().setRight(c.getRight());
        for (Node i = c.getDown(); i != c; i = i.getDown()) {
            for (Node j = i.getRight(); j != i; j = j.getRight()) {
                j.getDown().setUp(j.getUp());
                j.getUp().setDown(j.getDown());
                j.getColumn().decreaseSize();
            }
        }
    }

    private void uncoverColumn(ColumnNode c) {
        for (Node i = c.getUp(); i != c; i = i.getUp()) {
            for (Node j = i.getLeft(); j != i; j = j.getLeft()) {
                j.getColumn().increaseSize();
                j.getDown().setUp(j);
                j.getUp().setDown(j);
            }
        }
        c.getRight().setLeft(c);
        c.getLeft().setRight(c);
    }

    private void printSolution() {

        System.out.println("printSolution");

        System.out.println("o.size() = " + o.size());
        System.out.println("Solution:");

        System.out.println("o = " + o);

        int[][] board = getBoard();

        for (int k : o.keySet()) {
            Node node = o.get(k);
            int index = node.getIndex();
            int i = DLXUtil.getRow(index, getN2());
            int j = DLXUtil.getColumn(index, getN2());
            board[i][j] = node.getValue();
        }
    }

}
