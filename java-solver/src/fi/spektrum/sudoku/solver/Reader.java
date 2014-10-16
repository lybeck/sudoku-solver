package fi.spektrum.sudoku.solver;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Reader {

    private final BufferedReader reader;
    private StringTokenizer tokenizer;

    public Reader(InputStream input) {
        this.reader = new BufferedReader(new InputStreamReader(input));
        this.tokenizer = new StringTokenizer("");
    }

    private String next() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

}
