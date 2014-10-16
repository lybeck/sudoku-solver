package fi.spektrum.sudoku.dlx;

import fi.spektrum.sudoku.solver.AbstractSolver;
import fi.spektrum.sudoku.solver.Reader;

/**
 *
 * @author Lasse Lybeck
 */
public class DLXSolver extends AbstractSolver {

    private final ColumnNode header;
    
    public DLXSolver(Reader reader) {
        super(reader);
        header = new DLXParser(getBoard()).getHeader();
    }

    @Override
    public void solve() {
        search(0);
    }

    private void search(int k) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

}
