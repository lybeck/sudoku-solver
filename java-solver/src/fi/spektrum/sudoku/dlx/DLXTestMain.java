package fi.spektrum.sudoku.dlx;

import fi.spektrum.sudoku.util.Timer;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author Lasse Lybeck
 */
public class DLXTestMain {

    private static int[][] getTest() throws FileNotFoundException {
        String filename = "14-1.in";
        String path = "test-files/";
        File file = new File(path + filename);
        Scanner s = new Scanner(file);
        int n = s.nextInt();
        int[][] sudoku = new int[n * n][n * n];
        for (int i = 0; i < sudoku.length; i++) {
            for (int j = 0; j < sudoku[i].length; j++) {
                sudoku[i][j] = s.nextInt();
            }
        }
        return sudoku;
    }

    public static void main(String[] args) throws FileNotFoundException {

        Timer timer = new Timer();
        
        timer.tic();
        int[][] sudoku = getTest();
        timer.toc();
        
        
        timer.tic();
        
        ColumnNode h = new DLXParser(sudoku).getHeader();

        timer.toc();
        
        int i = 0;
        ColumnNode node = (ColumnNode) h.getRight();
        while (node != h) {

            int j = 0;
            Node nd = node.getDown();
            while (nd != node) {
                nd = nd.getDown();
                ++j;
            }

//            System.out.print("(" + node.getSize() + "," + j + ") ");
            ++i;
            node = (ColumnNode) node.getRight();
        }
//        System.out.println();
//        System.out.println("columns: " + i);

    }
}
