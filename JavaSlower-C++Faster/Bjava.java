import java.util.concurrent.TimeUnit;

class LinkedList {
    public final static int size_per_obj = 40;
    public final static int  obj_per_page = 4096 / size_per_obj;
    public final static int num_of_objects = 200000000;  // 20M objects * ~40byte/Object  =~ 8GB
    public final static int middle_index = obj_per_page / 2;
    

    private Node head;
    private Node tail;
    private int size;

    public LinkedList() {
        head = null;
        tail = null;
        size = 0;
    }

    public int getSize() {
        return this.size;
    }

    public void append(int x) {
        Node t = new Node(x);
        t.setPrev(this.tail);
        t.setNext(null);
        if (this.tail != null) {
            this.tail.setNext(t);
        }
        this.tail = t;
        if (this.head == null) {
            this.head = t;
        }
        ++this.size;
    }

    public void prepend(int x) {
        Node t = new Node(x);
        t.setPrev(null);
        t.setNext(this.head);
        if (this.head != null) {
            this.head.setPrev(t);
        }
        this.head = t;
        if (this.tail == null) {
            this.tail = t;
        }
        ++this.size;
    }

    

    public void traverse() {
        Node t = this.head;
        while (t != null) {
            System.out.println(t.getValue());
            t = t.getNext();
        }
    }

    public void changeToLeft(int x) {
        Node t = this.head;
        while (t != null) {
            t.setValue(x);
            t = t.getNext();
        }
    }

    public void changeToRight(int x) {
        Node t = this.tail;
        while (t != null) {
            t.setValue(x);
            t = t.getPrev();
        }
    }

    public long aggregateSumLeft() {
        Node t = this.head;
        long sum = 0;
        while (t != null) {
            sum += t.getValue();
            t = t.getNext();
        }
        return sum;
    }

    public long aggregateSumRight() {
        Node t = this.tail;
        long  sum = 0;
        while (t != null) {
            sum += t.getValue();
            t = t.getPrev();
        }
        return sum;
    }


    public static void main(String[] args) {
        long start = System.nanoTime();
        LinkedList s = new LinkedList();
        LinkedList dummy = new LinkedList();
        LinkedList dummy2 = new LinkedList();
        // LinkedList dummy3 = new LinkedList();
        // LinkedList dummy4 = new LinkedList();

        for (int i = 0; i < LinkedList.num_of_objects; i++) {
            dummy.append(i);
        }
        dummy = null;

        for (int i = 0; i < LinkedList.num_of_objects; i++) {
            dummy2.append(i);
        }
        dummy2 = null;

        // for (int i = 0; i < LinkedList.num_of_objects; i++) {
        //     dummy3.append(i);
        // }
        // dummy3 = null;

        // for (int i = 0; i < LinkedList.num_of_objects; i++) {
        //     dummy4.append(i);
        // }
        // dummy4 = null;

        for (int i = 0; i < LinkedList.num_of_objects; i++) {
            s.append(i);
        }
        
        
        long mid = System.nanoTime();
        System.out.println("Creation phase duration in ms: " + TimeUnit.NANOSECONDS.toMillis(mid - start));
        
        long x = s.aggregateSumLeft();
        long y = s.aggregateSumRight();
        
        
        System.out.println(x);
        System.out.println(y);
        
        long end = System.nanoTime();
        System.out.println("Calculation phase duration in ms: " + TimeUnit.NANOSECONDS.toMillis(end - mid));
        System.out.println("Total time duration in ms: " + TimeUnit.NANOSECONDS.toMillis(end - start));

    }
}