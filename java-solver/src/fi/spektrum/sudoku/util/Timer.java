package fi.spektrum.sudoku.util;

/**
 *
 * @author Lasse Lybeck
 */
public class Timer {

    private long start;

    public void tic() {
        start = System.currentTimeMillis();
    }

    private long getElapsedMillis() {
        return System.currentTimeMillis() - start;
    }

    public double getElapsedSeconds() {
        return getElapsedMillis() / 1000.0;
    }

    public void toc() {

        long time = getElapsedMillis();
        long seconds = time / 1000;
        long millis = time - seconds * 1000;

        long minutes = seconds / 60;
        seconds %= 60;

        long hours = minutes / 60;
        minutes %= 60;

        long days = hours / 24;
        hours %= 24;

        StringBuilder sb = new StringBuilder();
        sb.append("Time elapsed: ");

        if (days > 0) {
            sb.append(days).append(" d, ");
        }
        if (days > 0 || hours > 0) {
            sb.append(hours).append(" h, ");
        }
        if (days > 0 || hours > 0 || minutes > 0) {
            sb.append(minutes).append(" min, ");
        }

        sb.append(seconds).append(".");
        if (millis < 100) {
            sb.append("0");
            if (millis < 10) {
                sb.append("0");
            }

        }
        sb.append(millis).append(" s.");
        System.out.println(sb.toString());
    }
}
