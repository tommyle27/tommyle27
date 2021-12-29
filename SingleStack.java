package cp213;

/**
 * A single linked stack structure of <code>Node T</code> objects. Only the
 * <code>T</code> value contained in the stack is visible through the standard
 * stack methods. Extends the <code>SingleLink</code> class. Note that the rear
 * attribute should be ignored as the rear is not used in a stack.
 *
 * @author David Brown
 * @version 2021-09-24
 * @param <T> the SingleStack data type.
 */
public class SingleStack<T> extends SingleLink<T> {

    /**
     * Combines the contents of the left and right SingleStacks into the current
     * SingleStack. Moves nodes only - does not refer to values in any way, or call
     * the high-level methods pop or push. left and right SingleStacks are empty
     * when done. Nodes are moved alternately from left and right to this
     * SingleStack.
     *
     * You have two source stacks named left and right. Move all nodes from these
     * two stacks to the current stack. It does not make a difference if the current
     * stack is empty or not, just get nodes from the right and left stacks and add
     * them to the current stack. You may use any appropriate SingleLink helper
     * methods available.
     *
     * Do not assume that both right and left stacks are of the same length.
     *
     * @param left  The first SingleStack to extract nodes from.
     * @param right The second SingleStack to extract nodes from.
     */
    public void combine(final SingleStack<T> left, final SingleStack<T> right) {

	// your code here
    	int con = 1;
    	while(left.length != 0 || right.length != 0) {
    		if (con%2 != 0 && left.length != 0) {
    			final SingleStack<T> source = left;
    			this.moveFrontToFront(source);
    		} else if(con%2==0 && right.length != 0) {
    				final SingleStack<T> source = right;
    				this.moveFrontToFront(source);
    			}
    		con++;
    	}
 
	return;
    }

    /**
     * Returns the top value of the stack and removes that value from the stack. The
     * next node in the stack becomes the new top node. Decrements the stack length.
     *
     * @return The value at the top of the stack.
     */
    public T pop() {

	// your code here
    	final T data = this.front.getData();
    	this.front = this.front.getNext();
    	this.length--;
    	
	return data;
    }

    /**
     * Adds data to the top of the stack. Increments the stack length.
     *
     * @param data The value to add to the top of the stack.
     */
    public void push(final T data) {

	// your code here
    	final SingleNode<T> node = new SingleNode<>(data, this.front);
    	this.length++;
    	this.front = node;
    	
	return;
    }

    /**
     * Splits the contents of the current SingleStack into the left and right
     * SingleStacks. Moves nodes only - does not move value or call the high-level
     * methods insert or remove. this SingleStack is empty when done. Nodes are
     * moved alternately from this SingleStack to left and right. left and right may
     * already contain values.
     *
     * This is the opposite of the combine method.
     *
     * @param left  The first SingleStack to move nodes to.
     * @param right The second SingleStack to move nodes to.
     */
    public void splitAlternate(final SingleStack<T> left, final SingleStack<T> right) {

	// your code here
    	int count = 1;
    	while (this.length != 0) {

    		if(count%2 != 0) {
    			left.length ++;
    			if(left.rear == null) {
    				SingleNode<T> next = null;
    	    		SingleNode<T> newNode = new SingleNode(this.front.getData(), next);
    	    		this.front = this.front.getNext();
    	    		this.length -= 1;
    				left.front = newNode;
    				left.rear = newNode;
    			} else {
    				SingleNode<T> newNode = new SingleNode(this.front.getData(), left.front);
    				left.front = newNode;
    				this.front = this.front.getNext();
    	    		this.length -= 1;
    			}
    		} else {
    			right.length ++;
    			if(right.rear == null) {
    				SingleNode<T> next = null;
    	    		SingleNode<T> newNode = new SingleNode(this.front.getData(), next);
    	    		this.front = this.front.getNext();
    	    		this.length -= 1;
    				right.front = newNode;
    				right.rear = newNode;
    			} else {
    				SingleNode<T> newNode = new SingleNode(this.front.getData(), right.front);
    				right.front = newNode;
    				this.front = this.front.getNext();
    	    		this.length -= 1;
    			}
    		}
    		count++;
    	}

	return;
    }
}