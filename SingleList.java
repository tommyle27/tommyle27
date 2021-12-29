package cp213;

/**
 * A single linked list structure of <code>Node T</code> objects. These data
 * objects must be Comparable - i.e. they must provide the compareTo method.
 * Only the <code>T</code> value contained in the priority queue is visible
 * through the standard priority queue methods. Extends the
 * <code>SingleLink</code> class.
 *
 * @author David Brown
 * @version 2021-09-24
 * @param <T> this SingleList data type.
 */
public class SingleList<T extends Comparable<T>> extends SingleLink<T> {

    /**
     * Searches for the first occurrence of key in this SingleList. Private helper
     * methods - used only by other ADT methods.
     *
     * @param key The value to look for.
     * @return A pointer to the node previous to the node containing key.
     */
    private SingleNode<T> linearSearch(final T key) {

	// your code here
    	SingleNode<T> pre = null;
    	SingleNode<T> cur = this.front;
    	
    	while(cur != null && cur.getData().compareTo(key) != 0) {
    		pre = cur;
    		cur = cur.getNext();
    	}

	return pre;
    }

    /**
     * Appends data to the end of this SingleList.
     *
     * @param data The value to append.
     */
    public void append(final T data) {

	// your code here
    	SingleNode<T> pre = null;
    	SingleNode<T> cur = this.front;
    	
    	while(cur != null) {
    		pre = cur;
    		cur = cur.getNext();
    	} 
    	if(pre == null) {
    		this.front = new SingleNode<>(data, null);
    	} else {
    		pre.setNext(new SingleNode<>(data, null));
    	}
    	this.length++;

	return;
    }

    /**
     * Removes duplicates from this SingleList. The list contains one and only one
     * of each value formerly present in this SingleList. The first occurrence of
     * each value is preserved.
     */
    public void clean() {

	// your code here
    	SingleNode<T> keyNode = this.front;
    	SingleNode<T> pre = null;
    	SingleNode<T> cur = this.front;
    	
    	while(keyNode != null) {
    		pre = keyNode;
    		cur = keyNode.getNext();
    		
    		while(cur != null) {
        		if(cur.getData().compareTo(keyNode.getData()) == 0) {
        			this.length--;
        			pre.setNext(cur.getNext());
        		} else {
        			pre = cur;
        		}
        		cur = cur.getNext();
        	}
    		keyNode = keyNode.getNext();
    	}

	return;
    }

    /**
     * Combines contents of two lists into a third. Values are alternated from the
     * origin lists into this SingleList. The origin lists are empty when finished.
     * NOTE: data must not be moved, only nodes.
     *
     * @param left  The first list to combine with this SingleList.
     * @param right The second list to combine with this SingleList.
     */
    public void combine(final SingleList<T> left, final SingleList<T> right) {

	// your code here
    	while(left.front != null && right.front != null) {
    		this.moveFrontToFront(left);
    		this.moveFrontToFront(right);
    	}
    	while(left.front != null) {
    		this.moveFrontToFront(left);
    	}
    	while(right.front != null) {
    		this.moveFrontToFront(right);
    	}
    	this.reverse();

	return;
    }

    /**
     * Determines if this SingleList contains key.
     *
     * @param key The key value to look for.
     * @return true if key is in this SingleList, false otherwise.
     */
    public boolean contains(final T key) {

	// your code here
    	boolean found = false;
    	
    	if(this.length > 0) {
    		SingleNode<T> cur = this.front;
    		
    		while(cur != null && key.compareTo(cur.getData()) != 0) {
    			cur = cur.getNext();
    		}
    		found = cur != null;
    	}

	return found;
    }

    /**
     * Finds the number of times key appears in list.
     *
     * @param key The value to look for.
     * @return The number of times key appears in this SingleList.
     */
    public int count(final T key) {

	// your code here
    	int n = 0;
    	SingleNode<T> cur = this.front;
    	
    	while(cur != null) {
    		if(cur.getData().compareTo(key) == 0) {
    			n++;
    		}
    		cur = cur.getNext();
    	}

	return n;
    }

    /**
     * Finds and returns the value in list that matches key.
     *
     * @param key The value to search for.
     * @return The value that matches key, null otherwise.
     */
    public T find(final T key) {

	// your code here
    	T data = null;
    	
    	if(this.length > 0) {
    		final SingleNode<T> pre = this.linearSearch(key);
    		
    		if(pre == null) {
    			data = this.front.getData();
    		} else if(pre.getNext() != null) {
    			data = pre.getNext().getData();
    		}
    	}

	return data;
    }

    /**
     * Get the nth item in this SingleList.
     *
     * @param n The index of the item to return.
     * @return The nth item in this SingleList.
     * @throws ArrayIndexOutOfBoundsException if n is not a valid index.
     */
    public T get(final int n) throws ArrayIndexOutOfBoundsException {

	// your code here
    	T data = null;
    	SingleNode<T> cur = this.front;
    	int index = 0;
    	
    	for(index = 0; index < n && cur != null; index++) {
    		cur = cur.getNext();
    	}
    	if(cur == null) {
    		throw new ArrayIndexOutOfBoundsException("Invalid Index");
    	} else {
    		data = cur.getData();
    	}

	return data;
    }

    /**
     * Determines whether two lists are identical.
     *
     * @param source The list to compare against this SingleList.
     * @return true if this SingleList contains the same values in the same order as
     *         source, false otherwise.
     */
    public boolean identical(final SingleList<T> source) {

	// your code here
    	boolean isIdent = true;
    	
    	if(this.length != source.length) {
    		isIdent = false;
    	} else {
    		SingleNode<T> curThis = this.front;
    		SingleNode<T> curThat = source.front;
    		
    		while(curThis != null && curThis.getData().compareTo(curThat.getData()) == 0) {
    			curThis = curThis.getNext();
    			curThat = curThat.getNext();
    		}
    		isIdent = curThis ==  null;
    	}
    	
	return isIdent;
    }

    /**
     * Finds the first location of a value by key in this SingleList.
     *
     * @param key The value to search for.
     * @return The index of key in this SingleList, -1 otherwise.
     */
    public int index(final T key) {

	// your code here
    	int i = 0;
    	SingleNode<T> cur = this.front;
    	
    	for(i = 0; cur != null && cur.getData().compareTo(key) != 0; i++) {
    		cur = cur.getNext();
    	}
    	if(cur == null) {
    		i = -1;
    	}

	return i;
    }

    /**
     * Inserts value into this SingleList at index i. If i greater than the length
     * of this SingleList, append data to the end of this SingleList.
     *
     * @param i     The index to insert the new data at.
     * @param data The new value to insert into this SingleList.
     */
    public void insert(int i, final T data) {

	// your code here
    	if(i < 0) {
    		i = this.length + i;
    	}
    	int n = 0;
    	SingleNode<T> pre = null;
    	SingleNode<T> cur = this.front;
    	
    	while(n < i && cur != null) {
    		pre = cur;
    		cur = cur.getNext();
    		n++;
    	}
    	if(pre == null) {
    		this.front = new SingleNode<>(data, this.front);
    	} else {
    		pre.setNext(new SingleNode<>(data, cur));
    	}
    	this.length++;

	return;
    }

    /**
     * Creates an intersection of two other SingleLists into this SingleList. Copies
     * data to this SingleList. left and right SingleLists are unchanged. Values
     * from left are copied in order first, then values from right are copied in
     * order.
     *
     * @param left  The first SingleList to create an intersection from.
     * @param right The second SingleList to create an intersection from.
     */
    public void intersection(final SingleList<T> left, final SingleList<T> right) {

	// your code here
    	SingleNode<T> temp = left.front;
    	
    	while (temp != null) {
    		if (!this.contains(temp.getData()) && right.contains(temp.getData())) {
    			this.prepend(temp.getData());
    		}
    		temp = temp.getNext();
    	}
    	this.reverse();

	return;
    }

    /**
     * Finds the maximum value in this SingleList.
     *
     * @return The maximum value.
     */
    public T max() {

	// your code here
    	T data = this.front.getData();
    	SingleNode<T> cur = this.front.getNext();
    	
    	while(cur != null) {
    		if (cur.getData().compareTo(data) > 0) {
    			data = cur.getData();
    			
    		}
    		cur = cur.getNext();
    	}

	return data;
    }

    /**
     * Finds the minimum value in this SingleList.
     *
     * @return The minimum value.
     */
    public T min() {

	// your code here
    	T data = this.front.getData();
    	SingleNode<T> current = this.front.getNext();
    	while (current != null) {
    		if (current.getData().compareTo(data) < 0) {
    			data = current.getData();
    	 }
    	 current = current.getNext();
    	}


	return data;
    }

    /**
     * Inserts value into the front of this SingleList.
     *
     * @param data The value to insert into the front of this SingleList.
     */
    public void prepend(final T data) {

	// your code here
    	this.front = new SingleNode<>(data, this.front);
    	this.length++;

	return;
    }

    /**
     * Finds, removes, and returns the value in this SingleList that matches key.
     *
     * @param key The value to search for.
     * @return The value matching key, null otherwise.
     */
    public T remove(final T key) {

	// your code here
    	T data = null;

    	if (this.length > 0) {
	    	 final SingleNode<T> previous = this.linearSearch(key);
	    	 if (previous == null) {
	    		 data = this.front.getData();
	    		 this.front = this.front.getNext();
	    	 } else if (previous.getNext() != null) {
	    		 data = previous.getNext().getData();
	    		 previous.setNext(previous.getNext().getNext());
	    	 }
	    	 this.length--;
    	}
    	return data;

    }

    /**
     * Removes the value at the front of this SingleList.
     *
     * @return The value at the front of this SingleList.
     */
    public T removeFront() {

	// your code here
    	final T data = this.front.getData();
    	this.front = this.front.getNext();
    	this.length--;
    	return data;
    }

    /**
     * Finds and removes all values in this SingleList that match key.
     *
     * @param key The value to search for.
     */
    public void removeMany(final T key) {

	// your code here
    	SingleNode<T> previous = null;
    	SingleNode<T> current = this.front;
    	
    	while (current != null) {
    		
	    	 if (current.getData().compareTo(key) == 0) {
		    	this.length--;
		    	if (previous == null) {
		    		this.front = current.getNext();
		    	} else {
		    		previous.setNext(current.getNext());
		    	}
	    	 } else {
	    		 previous = current;
	    	 }
	    	 current = current.getNext();
    	}
	return;
    }

    /**
     * Reverses the order of the values in this SingleList.
     */
    public void reverse() {

	// your code here
    	SingleNode<T> previous = null;
    	SingleNode<T> current = this.front;
    	SingleNode<T> temp = null;
    	while (current != null) {
	    	 temp = current.getNext();
	    	 current.setNext(previous);
	    	 previous = current;
	    	 current = temp;
    	}
    	this.front = previous;
    	
	return;
    }

    /**
     * Splits the contents of this SingleList into the left and right SingleLists.
     * Moves nodes only - does not move value or call the high-level methods insert
     * or remove. this SingleList is empty when done. The first half of this
     * SingleList is moved to left, and the last half of this SingleList is moved to
     * right. If the resulting lengths are not the same, left should have one more
     * item than right. Order is preserved.
     *
     * @param left  The first SingleList to move nodes to.
     * @param right The second SingleList to move nodes to.
     */
    public void split(final SingleList<T> left, final SingleList<T> right) {

	// your code here
    	final int mid = this.length / 2 + this.length % 2;
    	
    	SingleNode<T> previous = null;
    	SingleNode<T> current = this.front;
    	
    	for (int i = 0; i < mid; i++) {
	    	 previous = current;
	    	 current = current.getNext();
    	}
    	if (previous != null) {
	    	 left.front = this.front;
	    	 left.length = this.length / 2 + this.length % 2;
	    	 previous.setNext(null);
	    	 right.front = current;
	    	 right.length = this.length / 2;
	    	 this.front = null;
	    	 this.length = 0;
    	}

	return;
    }

    /**
     * Splits the contents of this SingleList into the left and right SingleLists.
     * Moves nodes only - does not move value or call the high-level methods insert
     * or remove. this SingleList is empty when done. Nodes are moved alternately
     * from this SingleList to left and right. Order is preserved.
     *
     * @param left  The first SingleList to move nodes to.
     * @param right The second SingleList to move nodes to.
     */
    public void splitAlternate(final SingleList<T> left, final SingleList<T> right) {

	// your code here
    	if(this.length == 1) {
    		 	left.front = this.front;
    		} else if(this.length > 1) {
 
	    		 left.front = this.front;
	    		 this.front = this.front.getNext();
	    		 right.front = this.front;
	    		 this.front = this.front.getNext();
	    		 SingleNode<T> currLeft = left.front;
	    		 SingleNode<T> currRight = right.front;
	    		 while(this.front != null) {
		    		currLeft.setNext(front);
		    		currLeft = currLeft.getNext();
		    		this.front = this.front.getNext();
		    		if(this.front != null) {
			    		 currRight.setNext(front);
			    		 currRight = currRight.getNext();
			    		 this.front = this.front.getNext();
		    		}
	    		 }
	    		 currLeft.setNext(null);
	    		 currRight.setNext(null);
    		}
    		left.length = this.length / 2 + this.length % 2;
    		right.length = this.length / 2;
    		this.front = null;
    		this.length = 0;

	return;
    }

    /**
     * Creates a union of two other SingleLists into this SingleList. Copies value
     * to this list. left and right SingleLists are unchanged. Values from left are
     * copied in order first, then values from right are copied in order.
     *
     * @param left  The first SingleList to create a union from.
     * @param right The second SingleList to create a union from.
     */
    public void union(final SingleList<T> left, final SingleList<T> right) {

	// your code here
    	SingleNode<T> temp = left.front;
    	while (temp != null) {
	    	 if (!this.contains(temp.getData())) {
	    		 this.prepend(temp.getData());
	    	 }
	    	 temp = temp.getNext();
    	}
    	temp = right.front;
    	while (temp != null) {
	    	 if (!this.contains(temp.getData())) {
		    	this.prepend(temp.getData());
	    	 }
	    	 temp = temp.getNext();
    	}
    	this.reverse();

	return;
    }
}
