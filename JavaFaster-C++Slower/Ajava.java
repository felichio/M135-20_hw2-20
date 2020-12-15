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

    public int aggregateSumLeft() {
        Node t = this.head;
        int sum = 0;
        while (t != null) {
            sum += t.getValue();
            t = t.getNext();
        }
        return sum;
    }

    public int aggregateSumRight() {
        Node t = this.tail;
        int sum = 0;
        while (t != null) {
            sum += t.getValue();
            t = t.getPrev();
        }
        return sum;
    }


    public static void main(String[] args) {
        long start = System.nanoTime();
        LinkedList s = new LinkedList();
        LinkedList s1 = new LinkedList();
        LinkedList s2 = new LinkedList();
        LinkedList dummy = new LinkedList();

        int block_n = 0;
        int block_circ = 0;
        int list_n = 0;

        for (int i = 0; i < LinkedList.num_of_objects; i++) {
            block_n = i / LinkedList.obj_per_page;
            block_circ = i % LinkedList.obj_per_page;
            list_n = block_n % 128;

            if (block_circ == LinkedList.middle_index && list_n == 0) {
                s1.append(i);
                continue;
            }
            if (block_circ == LinkedList.middle_index && list_n == 64) {
                s2.append(i);
                continue;
            }
            s.append(i);
        }
        

        s = null;
        for (int i = 0; i < 0.2 * LinkedList.num_of_objects; i++) {
            dummy.prepend(i);
        }
        dummy = null;
        long mid = System.nanoTime();
        System.out.println("Creation phase duration in ms: " + TimeUnit.NANOSECONDS.toMillis(mid - start));
        System.out.println(s1.getSize());
        System.out.println(s2.getSize());
        
        // upper bound on number of iterations
        for (int i = 0; i < 32000; i++) {
            int circ = i % 4;
            switch (circ) {
                case 0:
                    s1.changeToLeft(i);
                    break;
                case 1:
                    s2.changeToLeft(i);
                    break;
                case 2:
                    s1.changeToRight(31999 - i);
                    break;
                case 3:
                    s2.changeToRight(32000 - i);
                    break;
            }
        }

        int x = s1.aggregateSumRight();
        int y = s2.aggregateSumRight();
        
        System.out.println(x);
        System.out.println(y);
        long end = System.nanoTime();
        System.out.println("Calculation phase duration in ms: " + TimeUnit.NANOSECONDS.toMillis(end - mid));
        System.out.println("Total time duration in ms: " + TimeUnit.NANOSECONDS.toMillis(end - start));

    }
}