#include <iostream>
#include <chrono>

class Node {
    private:
        Node *next;
        Node *prev;
        int value;
    public:
        Node(int val): value {val}, next {NULL}, prev {NULL} {}
        virtual int getValue();
        virtual void setNext(Node *t);
        virtual void setPrev(Node *t);
        virtual void setValue(int x);
        virtual Node *getNext();
        virtual Node *getPrev();
        ~Node() = default;
};

class LinkedList {
    private:
        int size;
        
    public:
        Node *head;
        Node *tail;
        LinkedList(): head {NULL}, tail {NULL}, size{0} {}
        virtual void append(int x);
        virtual void prepend(int y);
        virtual void changeToLeft(int x);
        virtual void changeToRight(int y);
        virtual int aggregateSumLeft();
        virtual int aggregateSumRight();
        virtual void traverse();
        virtual int get_size();
        ~LinkedList();
        static const int size_per_obj = 40;
        static const int obj_per_page = 4096 / size_per_obj;
        static const int num_of_objects = 200000000;   // 200M objects * ~40byte/Object  =~ 8GB
        static const int middle_index = obj_per_page / 2;
};


void Node::setValue(int x) {
    this->value = x;
}

int Node::getValue() {
    return this->value;
}

void Node::setNext(Node *t) {
    this->next = t;
}

void Node::setPrev(Node *t) {
    this->prev = t;
}

Node *Node::getNext() {
    return this->next;
}

Node *Node::getPrev() {
    return this->prev;
}


LinkedList::~LinkedList() {
    Node *cur = this->head;
    while (cur) {
        Node *t = cur;
        cur = cur->getNext();
        delete t;
    }
}

int LinkedList::get_size() {
    return this->size;
}

void LinkedList::append(int x) {
    Node *t = new Node(x);
    t->setPrev(this->tail);
    t->setNext(NULL);
    if (this->tail != NULL) {
        (this->tail)->setNext(t);
    }
    this->tail = t;
    if (this->head == NULL) {
        this->head = t;
    }
    ++this->size;
}


void LinkedList::prepend(int x) {
    Node *t = new Node(x);
    t->setNext(this->head);
    t->setPrev(NULL);
    if (this->head != NULL) {
        (this->head)->setPrev(t);
    }
    this->head = t;
    if (this->tail == NULL) {
        this->tail = t;
    }
    ++this->size;
}

void LinkedList::traverse() {
    Node *t = this->head;
    while (t != NULL) {
        std::cout << t->getValue() << std::endl;
        t = t->getNext(); 
    }
}

void LinkedList::changeToLeft(int x) {
    Node *t = this->head;
    while (t != NULL) {
        t->setValue(x);
        t = t->getNext();
    }
}

void LinkedList::changeToRight(int x) {
    Node *t = this->tail;
    while (t != NULL) {
        t->setValue(x);
        t = t->getPrev();
    }
}

int LinkedList::aggregateSumLeft() {
    Node *t = this->head;
    int sum = 0;
    while (t != NULL) {
        sum += t->getValue();
        t = t->getNext();
    }
    return sum;
}

int LinkedList::aggregateSumRight() {
    Node *t = this->tail;
    int sum = 0;
    while (t != NULL) {
        sum += t->getValue();
        t = t->getPrev();
    }
    return sum;
}




int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    LinkedList *s = new LinkedList();
    LinkedList *s1 = new LinkedList();
    LinkedList *s2 = new LinkedList();
    LinkedList *dummy = new LinkedList();
    int block_n = 0;
    int block_circ = 0;
    int list_n = 0;
    
    for (int i = 0; i < LinkedList::num_of_objects; i++) {
            block_n = i / LinkedList::obj_per_page;
            block_circ = i % LinkedList::obj_per_page;
            list_n = block_n % 2;

            if (block_circ == LinkedList::middle_index && list_n == 0) {
                s1->append(i);
                continue;
            }
            if (block_circ == LinkedList::middle_index && list_n == 1) {
                s2->append(i);
                continue;
            }
            s->append(i);
    }
    
    delete s;

    for (int i = 0; i < 0.2 * LinkedList::num_of_objects; i++) {
        dummy->prepend(i);
    }

    delete dummy;

    auto mid = std::chrono::high_resolution_clock::now();        
    std::cout << "Creation phase duration in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(mid - start).count()<< std::endl;
    
    std :: cout << s1->get_size() << std::endl;
    std :: cout << s2->get_size() << std::endl;

    for (int i = 0; i < 800; i++) {
        int circ = i % 4;
        switch (circ) {
            case 0:
                s1->changeToLeft(i);
                break;
            case 1:
                s2->changeToLeft(i);
                break;
            case 2:
                s1->changeToRight(799 - i);
                break;
            case 3:
                s2->changeToRight(800 - i);
                break;
        }
    }
        
    int x = s1->aggregateSumRight();
    int y = s2->aggregateSumRight();
    std :: cout << x << std::endl;
    std :: cout << y << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Calculation phase duration in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - mid).count()<< std::endl;
    std::cout << "Total time duration in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<< std::endl;

}
