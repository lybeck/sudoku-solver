package fi.spektrum.sudoku.dlx;

/**
 *
 * @author Lasse Lybeck
 */
public class DLXUtil {

    public static int getRow(int index, int n2) {
        return index / n2;
    }
    
    public static int getColumn(int index, int n2) {
        return index % n2;
    }
}
