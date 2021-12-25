package cp213;

import java.io.PrintStream;

/**
 * Food class definition.
 *
 * @author David Brown
 * @version 2021-09-24
 */
public class Food implements Comparable<Food> {

    // Constants
    public static final String ORIGINS[] = { "Canadian", "Chinese", "Indian", "Ethiopian", "Mexican", "Greek",
	    "Japanese", "Italian", "Moroccan", "Scottish", "Columbian", "English" };

    /**
     * Creates a string of food origins in the format:
     *
     * <pre>
Origins
 0 Canadian
 1 Chinese
...
11 English
     * </pre>
     *
     * @return A formatted numbered string of valid food origins.
     */
    public static String originsMenu() {

	// your code here
    	String Origin = "Origins" + "\n";
    	int i = 0;
    	int len = ORIGINS.length;
    	while(i < len) {
    		if(i < 10) 
    			
    			Origin+= " " + i + " " + ORIGINS[i] + "\n";
    		else
    			Origin+= i + " " + ORIGINS[i] + "\n";
    		i++;
    	}
    	
	return Origin;
    }

    // Attributes
    private String name = null;
    private int origin = 0;
    private boolean isVegetarian = false;
    private int calories = 0;

    /**
     * Food constructor.
     *
     * @param name         food name
     * @param origin       food origin code
     * @param isVegetarian whether food is vegetarian
     * @param calories     caloric content of food
     */
    public Food(final String name, final int origin, final boolean isVegetarian, final int calories) {

	// your code here
    	super();
    	this.name = name;
    	this.origin = origin;
    	this.isVegetarian = isVegetarian;
    	this.calories = calories;
    	
    return;
    }

    /*
     * (non-Javadoc) Compares this food against another food.
     *
     * @see java.lang.Comparable#compareTo(java.lang.Object)
     */
    /**
     * Foods are compared by name, then by origin if the names match.
     * Must ignore case.
     */
    @Override
    public int compareTo(final Food target) {

	// your code here
    	String n = this.name.toLowerCase();
    	String m = target.name.toLowerCase();
    	int comp = n.compareTo(m);
    	if(comp == 0) {
    		if(this.origin == target.origin) {
    			comp = 0;
    		}
    		else if(this.origin < target.origin)
    			comp = -1;
    		else
    			comp = 1;
    	}
    return comp;
    }

    /**
     * Getter for calories attribute.
     *
     * @return calories
     */
    public int getCalories() {

	// your code here

	return calories;
    }

    /**
     * Getter for name attribute.
     *
     * @return name
     */
    public String getName() {

	// your code here

	return name;
    }

    /**
     * Getter for origin attribute.
     *
     * @return origin
     */
    public int getOrigin() {

	// your code here

	return origin;
    }

    /**
     * Getter for string version of origin attribute.
     *
     * @return string version of origin
     */
    public String getOriginString() {

	// your code here
    return ORIGINS[origin];
    }

    /**
     * Getter for isVegetarian attribute.
     *
     * @return isVegetarian
     */
    public boolean isVegetarian() {

	// your code here

	return isVegetarian;
    }

    /*
     * (non-Javadoc)
     *
     * @see java.lang.Object//toString() Creates a formatted string of food data.
     */
    /**
     * Returns a string version of a Food object in the form:
<pre>
Name:       name
Origin:     origin string
Vegetarian: true/false
Calories:   calories
</pre>
     */
    @Override
    public String toString() {

	// your code here
    String org = getOriginString();
	return ("Name:       " + name + "\n" + "Origin:     " + org + "\n" + "Vegetarian: " + isVegetarian + "\n" + "Calories:   " + calories);
    }

    /**
     * Writes a single line of food data to an open PrintStream. The contents of
     * food are written as a string in the format name|origin|isVegetarian|calories to ps.
     *
     * @param ps The PrintStream to write to.
     */
    public void write(final PrintStream ps) {

	// your code here
    	ps.append(name+"|"+origin+"|"+isVegetarian+"|"+calories);
    	
	return;
    }

}
