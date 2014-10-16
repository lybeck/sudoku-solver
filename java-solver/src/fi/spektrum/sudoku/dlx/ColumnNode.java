package fi.spektrum.sudoku.dlx;

/**
 *
 * @author Lasse Lybeck
 */
public class ColumnNode extends Node {

    private int size;
    private int name;

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public int getName() {
        return name;
    }

    public void setName(int name) {
        this.name = name;
    }
}
