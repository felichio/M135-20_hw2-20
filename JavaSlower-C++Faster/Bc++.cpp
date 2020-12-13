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
        virtual long int aggregateSumLeft();
        virtual long int aggregateSumRight();
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

long int LinkedList::aggregateSumLeft() {
    Node *t = this->head;
    long int sum = 0;
    while (t != NULL) {
        sum += t->getValue();
        t = t->getNext();
    }
    return sum;
}

long int LinkedList::aggregateSumRight() {
    Node *t = this->tail;
    long int sum = 0;
    while (t != NULL) {
        sum += t->getValue();
        t = t->getPrev();
    }
    return sum;
}




int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    LinkedList *s = new LinkedList();
    LinkedList *dummy = new LinkedList();
    LinkedList *dummy2 = new LinkedList();
    LinkedList *dummy3 = new LinkedList();
    LinkedList *dummy4 = new LinkedList();


    for (int i = 0; i < LinkedList::num_of_objects; i++) {
        dummy->append(i);
    }
    delete dummy;

    for (int i = 0; i < LinkedList::num_of_objects; i++) {
        dummy2->append(i);
    }
    delete dummy2;

    for (int i = 0; i < LinkedList::num_of_objects; i++) {
        dummy3->append(i);
    }
    delete dummy3;

    for (int i = 0; i < LinkedList::num_of_objects; i++) {
        dummy4->append(i);
    }
    delete dummy4;

    for (int i = 0; i < LinkedList::num_of_objects; i++) {
        s->append(i);
    }
    
    

    auto mid = std::chrono::high_resolution_clock::now();        
    std::cout << "Creation phase duration in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(mid - start).count()<< std::endl;
    
        
    long int x = s->aggregateSumLeft();
    long int y = s->aggregateSumRight();
    std :: cout << x << std::endl;
    std :: cout << y << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Calculation phase duration in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - mid).count()<< std::endl;
    std::cout << "Total time duration in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<< std::endl;

}
