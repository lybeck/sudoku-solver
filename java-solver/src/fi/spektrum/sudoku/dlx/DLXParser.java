package fi.spektrum.sudoku.dlx;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
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

    public DLXParser(int[][] sudoku) {
        this.sudoku = sudoku;
        n2 = sudoku.length;
        n = (int) Math.sqrt(n2);
        n4 = n2 * n2;
        cols = 4 * n2 * n2;
        header = parseSudoku();
    }

    public ColumnNode getHeader() {
        return header;
    }

    public final ColumnNode parseSudoku() {

        ColumnNode h = initHeader();
        columns = initMap(h);

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

    private int[][] getDLXMatrix(int[][] sudoku) {
        List<int[]> list = new ArrayList<>();
        for (int i = 0; i < sudoku.length; ++i) {
            for (int j = 0; j < sudoku[i].length; ++j) {
                int num = sudoku[i][j];
                if (num != 0) {
                    list.add(makeRow(i, j, num));
                } else {
                    for (int k = 1; k <= n2; k++) {
                        list.add(makeRow(i, j, k));
                    }
                }
            }
        }
        int[][] mat = list.toArray(new int[list.size()][cols]);
        return mat;
    }

    private int[] makeRow(int i, int j, int num) {
        int[] row = new int[cols];
        int ind = n2 * i + j;
        row[ind] = num;
        row[n4 + n2 * i + (num - 1)] = num;
        row[2 * n4 + n2 * j + (num - 1)] = num;
        row[3 * n4 + n2 * getBoxNumber(i, j, n) + (num - 1)] = num;
        return row;
    }

    private int getBoxNumber(int i, int j, int n) {
        int ib = i / n;
        int jb = j / n;
        return ib * n + jb;
    }

    private void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int i : row) {
                if (i != 0) {
                    System.out.print(i);
                } else {
                    System.out.print(" ");
                }
            }
            System.out.println();
        }
    }

    private Map<Integer, ColumnNode> initMap(ColumnNode h) {
        Map<Integer, ColumnNode> map = new HashMap<>(cols);
        ColumnNode prev = h;
        ColumnNode curr;
        for (int i = 0; i < cols; i++) {
            curr = new ColumnNode();
            curr.setUp(curr);
            curr.setDown(curr);
            curr.setLeft(prev);
            prev.setRight(curr);
            map.put(i, curr);
            prev = curr;
        }
        prev.setRight(h);
        h.setLeft(prev);
        return map;
    }

    private void addRow(int i, int j, int num) {
        Node[] nodes = getNodes(num);
        int[] indices = getIndices(i, j, num);
        addRowToSparseMatrix(nodes, indices);
    }

    private Node[] getNodes(int num) {
        Node[] nodes = initNodes(num);
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
        return nodes;
    }

    private Node[] initNodes(int num) {
        Node[] nodes = new Node[4];
        nodes[0] = new Node();
        nodes[1] = new Node();
        nodes[2] = new Node();
        nodes[3] = new Node();
        for (Node node : nodes) {
            node.setValue(num);
        }
        return nodes;
    }

    protected int[] getIndices(int i, int j, int num) {
        int[] inds = new int[4];
        inds[0] = n2 * i + j;
        inds[1] = n4 + n2 * i + (num - 1);
        inds[2] = 2 * n4 + n2 * j + (num - 1);
        inds[3] = 3 * n4 + n2 * getBoxNumber(i, j, n) + (num - 1);
        return inds;
    }

    private void addRowToSparseMatrix(Node[] nodes, int[] indices) {
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
        column.setSize(column.getSize() + 1);
    }
}
