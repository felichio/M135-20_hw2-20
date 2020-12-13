public class Node {
    private Node next;
    private Node prev;
    private int value;

    public Node(int val) {
        this.value = val;
    }

    public int getValue() {
        return this.value;
    }

    public void setNext(Node t) {
        next = t;
    }

    public void setPrev(Node t) {
        prev = t;
    }

    public Node getNext() {
        return this.next;
    }

    public Node getPrev() {
        return this.prev;
    }

    public void setValue(int x) {
        this.value = x;
    }
}
