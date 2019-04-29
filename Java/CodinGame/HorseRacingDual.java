import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int res = 0, dif;
        int[] value = new array[N];
        
        for (int i = 0; i < N; i++) {
            int pi = in.nextInt();
            value[i] = pi;
        }
        
        for(int i = 0; i < N - 1; i++){
            compara = value[i];
            for(int j = i + 1; j < N; j++){
                if(value[j] - value[i] < dif && value[j] - value[i] > 0)
                    dif = value[j] - value[i];
            }
        }
        
        /** In order to achieve a score of 100%, it is necessary to find a way to avoid to do that many comparisons.
            Try to answer the following question: which modification of the input data would allow you to find the answer with a single loop (N-1 comparisons)?**/
        
        // Write an action using System.out.println()
        // To debug: System.err.println("Debug messages...");

        System.out.println(res);
    }
}
/*
Standard Output Stream:
-1906243687
*/