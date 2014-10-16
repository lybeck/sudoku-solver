package fi.spektrum.sudoku.dlx;

/**
 *
 * @author Lasse Lybeck
 */
public class Node {
    
    private Node right;
    private Node left;
    private Node up;
    private Node down;
    private ColumnNode column;
    private int value;
    private int index;

    public Node getRight() {
        return right;
    }

    public void setRight(Node right) {
        this.right = right;
    }

    public Node getLeft() {
        return left;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public Node getUp() {
        return up;
    }

    public void setUp(Node up) {
        this.up = up;
    }

    public Node getDown() {
        return down;
    }

    public void setDown(Node down) {
        this.down = down;
    }

    public ColumnNode getColumn() {
        return column;
    }

    public void setColumn(ColumnNode column) {
        this.column = column;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }
}
