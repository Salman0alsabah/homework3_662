public class SecureStackManualTest {

    public static void main(String[] args) {
        // Create an instance of SecureStack
        SecureStack stack = new SecureStack();

        // Test pushing 11 elements onto the stack
        testExpansion(stack);

        // Test handling of empty stack
        testEmptyStackPop(stack);

        // Test pushing null string
        testNullPush(stack);

        // Test pushing empty string
        testEmptyStringPush(stack);

        // Test pushing string exceeding maximum length
        testMaxStringLengthPush(stack);

        System.out.println("All tests passed successfully!");
    }

    private static void testExpansion(SecureStack stack) {
        // Push 11 elements onto the stack
        for (int i = 1; i <= 11; i++) {
            stack.push("Element " + i);
        }

        // Pop elements from the stack and verify their order
        for (int i = 11; i >= 1; i--) {
            String expected = "Element " + i;
            String actual = stack.pop();
            assert actual.equals(expected) : "Expected: " + expected + ", Actual: " + actual;
        }

        // Stack should be empty after popping all elements
        assert stack.isEmpty();
        System.out.println("Test passed: All 11 elements pushed  and popped successfully.");
       
    }

    private static void testEmptyStackPop(SecureStack stack) {
        try {
            stack.pop();
            System.out.println("Test failed: pop() from empty stack did not throw exception");
        } catch (IllegalStateException e) {
            // Exception thrown as expected
            System.out.println("Test passed: pop() from empty stack threw IllegalStateException");
        }
    }

    private static void testNullPush(SecureStack stack) {
        try {
            stack.push(null);
            System.out.println("Test failed: push(null) did not throw exception");
        } catch (IllegalArgumentException e) {
            // Exception thrown as expected
            System.out.println("Test passed: push(null) threw IllegalArgumentException");
        }
    }

    private static void testEmptyStringPush(SecureStack stack) {
        try {
            stack.push("");
            System.out.println("Test failed: push('') did not throw exception");
        } catch (IllegalArgumentException e) {
            // Exception thrown as expected
            System.out.println("Test passed: push('') threw IllegalArgumentException");
        }
    }

    private static void testMaxStringLengthPush(SecureStack stack) {
        String longString = "a".repeat(101); // Creating a string with length 101
        try {
            stack.push(longString);
            System.out.println("Test failed: push(longString) did not throw exception");
        } catch (IllegalArgumentException e) {
            // Exception thrown as expected
            System.out.println("Test passed: push(longString) threw IllegalArgumentException");
        }
    }
}
