package cp213;

/**
 * @author Tommy Le 200298530
 * @version 2021-09-11
 */
public class Numbers {

    /**
     * Determines closest value of two values to a target value.
     *
     * @param target the target value
     * @param v1     first comparison value
     * @param v2     second comparison value
     * @return one of v1 or v2 that is closest to target, v1 is the value chosen if
     *         v1 and v2 are an equal distance from target
     */
    public static double closest(final double target, final double v1, final double v2) {

	// your code here
    	double diff = 0.0;
    	double secDiff = 0.0;
    	if(target > v1) {
    		diff = target - v1;
    	}
    	else {
    		diff = v1 - target;
    	}
    	if(target > v2) {
    		secDiff = target - v2;
    	}
    	else {
    		secDiff = v2 - target;
    	}
    	if(diff == secDiff) {
    		return v1;
    	}
    	if(diff < secDiff) {
    		return v1;
    	}
    	else {
    		return v2;
    	}
  
    }


    /**
     * Determines if n is a prime number. Prime numbers are whole numbers greater
     * than 1, that have only two factors – 1 and the number itself. Prime numbers
     * are divisible only by the number 1 or itself.
     *
     * @param n an integer
     * @return true if n is prime, false otherwise
     */
    public static boolean isPrime(final int n) {

	// your code here
    	int num = 0;
    	int num2 = 2;
    	boolean isPrime = false;
    	while (num2 < n) {
    		if(n % num2 == 0) {
    			num = 1;
    			isPrime = false;
    		}
    		num2 += 1;
    	}
    	if (num == 0) {
    		isPrime = true;
    	}

	return isPrime;
    }

    /**
     * Sums and returns the total of a partial harmonic series. This series is the
     * sum of all terms 1/i, where i ranges from 1 to n (inclusive). Ex:
     *
     * n = 3: sum = 1/1 + 1/2 + 1/3 = 1.8333333333333333
     *
     * @param n an integer
     * @return sum of partial harmonic series from 1 to n
     */
    public static double sumPartialHarmonic(final int n) {

	// your code here
    	double sum = 0;
    	for (double x = 1; x <= n; x++) {
    		sum += 1/x;
    	}
    	
    return sum;
    }

}
