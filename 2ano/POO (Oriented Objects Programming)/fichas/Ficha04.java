import java.util.ArrayList;

public class Ficha04{

    public class Stack {
        private ArrayList<String> STACK = new ArrayList<>();

        public boolean empty() {
            return (STACK.isEmpty());
        }

        public String top() {
            if (empty()) return null;
            return STACK.get(STACK.size() - 1);
        }

        public void push(String a) {
            STACK.add(a);
        }

        public void pop() {
            STACK.remove(STACK.size() - 1);
        }

        public int length() {
            return (STACK.size());
        }
    }

    public class
}