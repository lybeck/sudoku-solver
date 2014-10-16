package fi.spektrum.sudoku.dlx;

/**
 *
 * @author Lasse Lybeck
 */
public class ColumnNode extends Node {

    private int size;

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    @Override
    public ColumnNode getRight() {
        return (ColumnNode) super.getRight();
    }

    @Override
    public ColumnNode getLeft() {
        return (ColumnNode) super.getLeft();
    }

    void decreaseSize() {
        --size;
    }
    
    void increaseSize() {
        ++size;
    }
}
