package cp213;

import java.io.PrintStream;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Utilities for working with Food objects.
 *
 * @author David Brown
 * @version 2021-09-24
 */
public class FoodUtilities {

    /**
     * Determines the average calories in a list of foods. No rounding necessary.
     * Foods list parameter may be empty.
     *
     * @param foods a list of Food
     * @return average calories in all Food objects
     */
    public static int averageCalories(final ArrayList<Food> foods) {

	// your code here
    	int len = foods.size();
    	int tt = 0;
    	for(int i = 0; i<len; i++) {
    		tt += foods.get(i).getCalories();
    	}
  
	return tt/len;
    }

    /**
     * Determines the average calories in a list of foods for a particular origin.
     * No rounding necessary. Foods list parameter may be empty.
     *
     * @param foods  a list of Food
     * @param origin the origin of the Food
     * @return average calories for all Foods of the specified origin
     */
    public static int averageCaloriesByOrigin(final ArrayList<Food> foods, final int origin) {

	// your code here
    	int len = foods.size();
    	int tt = 0;
    	int count = 0;
    	for(int i = 0; i<len; i++) {
    		if (foods.get(i).getOrigin() == origin) {
    			count += 1;
        		tt += foods.get(i).getCalories();
    		}
    	}

	return tt/count;
    }

    /**
     * Creates a list of foods by origin.
     *
     * @param foods  a list of Food
     * @param origin a food origin
     * @return a list of Food from origin
     */
    public static ArrayList<Food> getByOrigin(final ArrayList<Food> foods, final int origin) {

	// your code here
    	int len = foods.size();
    	ArrayList<Food> foodOrigin = new ArrayList<Food>();
    	for(int i = 0; i<len; i++) {
    		if (foods.get(i).getOrigin() == origin) 
    			foodOrigin.add(foods.get(i));
    	}

	return foodOrigin;
    }


    /**
     * Creates a Food object by requesting data from a user. Uses the format:
     *
     * <pre>
    Name: name
    Origins
     0 Canadian
     1 Chinese
    ...
    11 English
    Origin: origin number
    Vegetarian (Y/N): Y/N
    Calories: calories
     * </pre>
     *
     * @param keyboard a keyboard Scanner
     * @return a Food object
     */
    public static Food getFood(final Scanner keyboard) {

	// your code here
    	Scanner input = new Scanner(System.in);
    	System.out.println("Name: ");
    	String name = input.next();
    	System.out.println("Origins\r\n"
    			+ " 0 Canadian\r\n"
    			+ " 1 Chinese\r\n"
    			+ " 2 Indian\r\n"
    			+ " 3 Ethiopian\r\n"
    			+ " 4 Mexican\r\n"
    			+ " 5 Greek\r\n"
    			+ " 6 Japanese\r\n"
    			+ " 7 Italian\r\n"
    			+ " 8 Moroccan\r\n"
    			+ " 9 Scottish\r\n"
    			+ "10 Columbian\r\n"
    			+ "11 English");
    	
    	System.out.println("Origin: ");
    	String origin = input.next();
    	int origins = Integer.parseInt(origin);
    	
    	System.out.println("Vegetarian (Y/N): ");
    	String isVegetarian = input.next();  
    	Boolean veg = true;
    	if(isVegetarian.contentEquals("N")) {
    		veg = false;
    	} 		
    	
    	System.out.println("Calories: ");
    	String calories = input.next();
    	int cals = Integer.parseInt(calories);
    	
    	Food food = new Food(name, origins, veg, cals);

	return food;
    }

    /**
     * Creates a list of vegetarian foods.
     *
     * @param foods a list of Food
     * @return a list of vegetarian Food
     */
    public static ArrayList<Food> getVegetarian(final ArrayList<Food> foods) {

	// your code here
    	int len = foods.size();
    	ArrayList<Food> veg = new ArrayList<Food>();
    	for(int i = 0; i<len; i++) {
    		if (foods.get(i).isVegetarian() == true) 
    			veg.add(foods.get(i));
    	}

	return veg;
    }

    /**
     * Creates and returns a Food object from a line of string data.
     *
     * @param line a vertical bar-delimited line of food data in the format
     *             name|origin|isVegetarian|calories
     * @return the data from line as a Food object
     */
    public static Food readFood(final String line) {

	// your code here
    	String[] stuff = line.split("[|]");
    	String name = stuff[0];
    	int origin = Integer.valueOf(stuff[1]);
    	Boolean isVegetarian = Boolean.valueOf(stuff[2]);
    	int calories = Integer.valueOf(stuff[3]);
    	Food object = new Food(name, origin, isVegetarian, calories);

	return object;
    }

    /**
     * Reads a file of food strings into a list of Food objects.
     *
     * @param fileIn a Scanner of a Food data file in the format
     *               name|origin|isVegetarian|calories
     * @return a list of Food
     */
    public static ArrayList<Food> readFoods(final Scanner fileIn) {

	// your code here
    	ArrayList<Food> food = new ArrayList<Food>();
    	while(fileIn.hasNextLine()) {
    		food.add(readFood(fileIn.nextLine()));
    	}

	return food;
    }

    /**
     * Searches for foods that fit certain conditions.
     *
     * @param foods        a list of Food
     * @param origin       the origin of the food; if -1, accept any origin
     * @param maxCalories  the maximum calories for the food; if 0, accept any
     * @param isVegetarian whether the food is vegetarian or not; if false accept
     *                     any
     * @return a list of foods that fit the conditions specified
     */
    public static ArrayList<Food> foodSearch(final ArrayList<Food> foods, final int origin, final int maxCalories,
	    final boolean isVegetarian) {

	// your code here
    	int len = foods.size();
    	ArrayList<Food> food = new ArrayList<Food>();
    	for(int i = 0; i<len; i++) {
    		if(foods.get(i).getOrigin() == origin || origin == -1) {
    			if (foods.get(i).getCalories() <= maxCalories || maxCalories == 0) {
    				if (foods.get(i).isVegetarian() == true || isVegetarian == false) {
    					food.add(foods.get(i));
    				}
    			}
    		}
    	}

	return food;
    }

    /**
     * Writes the contents of a list of Food to a PrintStream.
     *
     * @param foods a list of Food
     * @param ps    the PrintStream to write to
     */
    public static void writeFoods(final ArrayList<Food> foods, PrintStream ps) {

	// your code here
    	int len = foods.size();
    	for(int i = 0; i<len; i++) {
    		ps.print(foods.get(i));
    	}

    }
}
