import java.util.Arrays;

public class SecureStack {
    private static final int INITIAL_CAPACITY = 10;
    private static final int MAX_STR_LENGTH = 100;

    private String[] data;
    private int size;

    public SecureStack() {
        this.data = new String[INITIAL_CAPACITY];
        this.size = 0;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int getSize() {
        return size;
    }

    public void push(String str) {
        // Validations
        if (str == null || str.isEmpty()) {
            throw new IllegalArgumentException("Invalid input: null or empty string");
        }
        if (str.length() > MAX_STR_LENGTH) {
            throw new IllegalArgumentException("String length exceeds maximum limit");
        }

        // Resize the array if it's full
        if (size == data.length) {
            expandCapacity();
        }

        // Push the string onto the stack
        data[size++] = str;
    }

    private void expandCapacity() {
        int newCapacity = data.length * 2;
        if (newCapacity < 0) { // Check for overflow
            throw new IllegalStateException("Stack size exceeds maximum capacity");
        }
        data = Arrays.copyOf(data, newCapacity);
    }

    public String pop() {
        if (isEmpty()) {
            throw new IllegalStateException("Stack is empty");
        }

        // Pop the string from the stack
        String poppedString = data[--size];
        data[size] = null; // Avoid memory leaks

        // Shrink the stack if needed
        if (size > 0 && size < data.length / 4) {
            shrinkCapacity();
        }

        return poppedString;
    }

    private void shrinkCapacity() {
        int newCapacity = Math.max(INITIAL_CAPACITY, data.length / 2);
        data = Arrays.copyOf(data, newCapacity);
    }

    public String[] toArray() {
        return Arrays.copyOf(data, size); // Defensive copying
    }
}
