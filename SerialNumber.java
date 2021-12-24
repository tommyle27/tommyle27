package cp213;

import java.io.PrintStream;

import java.util.Scanner;
/**
 * @author Tommy Le 200298530
 * @version 2021-09-11
 */
public class SerialNumber {

    /**
     * Determines if a string contains all digits.
     *
     * @param str The string to test.
     * @return true if str is all digits, false otherwise.
     */
    public static boolean allDigits(final String str) {

	// your code here
 
    return str.replaceAll("\\d", "").equals("");
    }

    /**
     * Determines if a string is a good serial number. Good serial numbers are of
     * the form 'SN/nnnn-nnn', where 'n' is a digit.
     *
     * @param sn The serial number to test.
     * @return true if the serial number is valid in form, false otherwise.
     */
    public static boolean validSn(final String sn) {

	// your code here
    	int len = sn.length();
    	boolean val = false;
    	if(sn.charAt(0) == 'S' && sn.charAt(1) == 'N' && sn.charAt(2) == '/') {
    			char num = sn.charAt(3);
    			if(Character.isDigit(num)) {
    				char num1 = sn.charAt(3);
        			if(Character.isDigit(num1)) {
        				char num2 = sn.charAt(4);
            			if(Character.isDigit(num2)) {
            				char num3 = sn.charAt(5);
                			if(Character.isDigit(num3)) {
                				char num4 = sn.charAt(6);
                    			if(Character.isDigit(num4)) {
                        			if(sn.charAt(7) == '-') {
                        				char num5 = sn.charAt(8);
                            			if(Character.isDigit(num5)) {
                            				char num6 = sn.charAt(9);
                                			if(Character.isDigit(num6)) {
                                				char num7 = sn.charAt(10);
                                    			if(Character.isDigit(num7)) {
                                    				val = true;
                                    			}
                                			}
                                				
                            			}
                        			}
                    			}
                			}
            			}
        			}
    		}
    	}
    		

	return val;
    }

    /**
     * Evaluates serial numbers from a file. Writes valid serial numbers to
     * good_sns, and invalid serial numbers to bad_sns.
     *
     * @param fileIn  a file already open for reading
     * @param goodSns a file already open for writing
     * @param badSns  a file already open for writing
     */
    public static void validSnFile(final Scanner fileIn, final PrintStream goodSns, final PrintStream badSns) {

	// your code here
    	String alr = "";
    	while(fileIn.hasNext()) {
    		String alrt = fileIn.nextLine();
    		alr = alrt;
	    	if(validSn(alr) == true) {
	    		goodSns.println(alr);
	    	}
	    	else {
	    		badSns.println(alr);
	    	}
    	}
    	
	return;
    }

}
