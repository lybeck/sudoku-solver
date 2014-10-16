package fi.spektrum.sudoku.dlx;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author Lasse Lybeck
 */
public class DLXParser {

    private final int[][] sudoku;
    private final int n;
    private final int n2;
    private final int n4;
    private final int cols;
    private final ColumnNode header;
    private Map<Integer, ColumnNode> columns;
    int[] indices;
    Node[] nodes;

    public DLXParser(int[][] sudoku) {
        this.sudoku = sudoku;
        n2 = sudoku.length;
        n = (int) Math.sqrt(n2);
        n4 = n2 * n2;
        cols = 4 * n2 * n2;
        indices = new int[4];
        nodes = new Node[4];
        header = parseSudoku();
    }

    public ColumnNode getHeader() {
        return header;
    }

    public final ColumnNode parseSudoku() {

        ColumnNode h = initHeader();
        initMap(h);

        for (int i = 0; i < sudoku.length; ++i) {
            for (int j = 0; j < sudoku[i].length; ++j) {
                int num = sudoku[i][j];
                if (num != 0) {
                    addRow(i, j, num);
                } else {
                    for (int k = 1; k <= n2; k++) {
                        addRow(i, j, k);
                    }
                }
            }
        }

        return h;
    }

    private ColumnNode initHeader() {
        ColumnNode h = new ColumnNode();
        h.setRight(h);
        h.setLeft(h);
        h.setUp(h);
        h.setDown(h);
        h.setColumn(h);
        return h;
    }

    private void initMap(ColumnNode h) {
        columns = new HashMap<>(cols);
        ColumnNode prev = h;
        ColumnNode curr;
        for (int i = 0; i < cols; i++) {
            curr = new ColumnNode();
            curr.setName(i);
            curr.setUp(curr);
            curr.setDown(curr);
            curr.setLeft(prev);
            prev.setRight(curr);
            columns.put(i, curr);
            prev = curr;
        }
        prev.setRight(h);
        h.setLeft(prev);
    }

    private void addRow(int i, int j, int num) {
        setupNodes(num);
        setupIndices(i, j, num);
        addRowToSparseMatrix();
    }

    private void setupNodes(int num) {
        initNodes(num);
        Node prev = nodes[0];
        Node curr;
        for (int i = 1; i < nodes.length; i++) {
            curr = nodes[i];
            curr.setLeft(prev);
            prev.setRight(curr);
            prev = curr;
        }
        prev.setRight(nodes[0]);
        nodes[0].setLeft(prev);
    }

    private void initNodes(int num) {
        nodes[0] = new Node();
        nodes[1] = new Node();
        nodes[2] = new Node();
        nodes[3] = new Node();
        for (Node node : nodes) {
            node.setValue(num);
        }
    }

    private void setupIndices(int i, int j, int num) {
        indices[0] = n2 * i + j;
        indices[1] = n4 + n2 * i + (num - 1);
        indices[2] = 2 * n4 + n2 * j + (num - 1);
        indices[3] = 3 * n4 + n2 * getBoxNumber(i, j, n) + (num - 1);
    }

    private int getBoxNumber(int i, int j, int n) {
        int ib = i / n;
        int jb = j / n;
        return ib * n + jb;
    }

    private void addRowToSparseMatrix() {
        for (int i = 0; i < nodes.length; i++) {
            addNodeToSparseMatrix(nodes[i], indices[i]);
        }
    }

    private void addNodeToSparseMatrix(Node node, int index) {
        ColumnNode column = columns.get(index);
        column.getUp().setDown(node);
        node.setUp(column.getUp());
        column.setUp(node);
        node.setDown(column);
        node.setColumn(column);
        column.increaseSize();
    }
}
