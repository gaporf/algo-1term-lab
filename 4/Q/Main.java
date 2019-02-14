import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    private static BigInteger n;
    private static int m, M;
    private static long mod;
    private static long[][] matrix;

    private static int myPow(int a) {
        int ans = 1;
        while (a-- > 0) {
            ans *= 2;
        }
        return ans;
    }

    private static boolean check(int a, int b) {
        int yes = -1;
        for (int j = 1; j < M; j *= 2) {
            if ((a & j) == (b & j)) {
                if (yes != -1 && (a & j) == yes * 2) {
                    return false;
                } else {
                    yes = (a & j);
                }
            } else {
                yes = -1;
            }
        }
        return true;
    }

    private static long[][] multiply(long[][] first, long[][] second) {
        long[][] ans = new long[M][M];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                ans[i][j] = 0;
                for (int k = 0; k < M; k++) {
                    ans[i][j] = (ans[i][j] + first[i][k] * second[k][j]) % mod;
                }
            }
        }
        return ans;
    }

    private static long[][] binPow(BigInteger n) {
        if (n.equals(BigInteger.ZERO)) {
            long[][] ans = new long[M][M];
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                    if (i == j) {
                        ans[i][j] = 1;
                    } else {
                        ans[i][j] = 0;
                    }
                }
            }
            return ans;
        } else {
            long[][] ans = binPow(n.divide(BigInteger.valueOf(2)));
            ans = multiply(ans, ans);
            if (n.mod(BigInteger.valueOf(2)).equals(BigInteger.ONE)) {
                ans = multiply(ans, matrix);
            }
            return ans;
        }
    }

    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("nice3.in"));
        FileWriter out = new FileWriter(new File("nice3.out"));
        n = in.nextBigInteger();
        m = in.nextInt();
        mod = in.nextLong();
        M = myPow(m);
        matrix = new long[M][M];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                if (check(i, j)) {
                    matrix[i][j] = 1;
                }
            }
        }
        long[][] ans = binPow(n.subtract(BigInteger.ONE));
        long bigAns = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                bigAns = (bigAns + ans[i][j]) % mod;
            }
        }
        out.write(Long.toString(bigAns));
        out.close();
    }
}
