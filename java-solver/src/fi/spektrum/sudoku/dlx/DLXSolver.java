package fi.spektrum.sudoku.dlx;

import fi.spektrum.sudoku.solver.AbstractSolver;
import fi.spektrum.sudoku.solver.Reader;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

/**
 *
 * @author Lasse Lybeck
 */
public class DLXSolver extends AbstractSolver {

    private final ColumnNode header;
    Map<Integer, Node> o;

    public DLXSolver(Reader reader) {
        super(reader);
        header = new DLXParser(getBoard()).getHeader();
        o = new TreeMap<>();
    }

    @Override
    public void solve() {
        search(0);
    }

    private void search(int k) {
        
        System.out.println("search");
        System.out.println("k = " + k);
        
        if (header.getRight() == header) {
            // done!
            System.out.println("Found solution!");
            printSolution();
            return;
        }
        ColumnNode c = selectColumn(header);
        coverColumn(c);
        Node r = c.getDown();
        while (r != c) {
            o.put(k, r);
            Node j = r.getRight();
            while (j != r) {
                coverColumn(j.getColumn());
                j = j.getRight();
            }
            search(k + 1);
            r = o.get(k);
            c = c.getRight();
            j = r.getLeft();
            while (j != r) {
                uncoverColumn(j.getColumn());
                j = j.getRight();
            }
            uncoverColumn(c);
            r = r.getRight();
        }
    }

    private ColumnNode selectColumn(ColumnNode h) {
        
        System.out.println("selectColumn");
        
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
        
        System.out.println("coverColumn");
        
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
        
        System.out.println("uncoverColumn");
        
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
        int i = 0;
        for (int k : o.keySet()) {
            Node node = o.get(k);
            System.out.print(node.getValue() + " ");
            if (((++i) % getN2()) == 0) {
                System.out.println();
            }
        }
    }

}
