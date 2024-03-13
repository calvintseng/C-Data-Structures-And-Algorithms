#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <condition_variable>


class Node {
public:
    int val;
    Node* next;

    Node(int val) {
        this->next = NULL;
        this->val = val;
    }
};

class My_Queue {
    Node* head;
    Node* tail;

    My_Queue() {
        this->head = NULL;
        this->tail = NULL;
    }

    void push(int val) {
        Node* temp = new Node(val);
        if (!head) {
            head = temp;
        }
        else {
            tail->next = temp;
        }
        tail = temp;
    }

    int check_front() {
        if (!head) return -1;
        return head->val;
    }

    void pop() {
        if (!head) {
            return;
        }
        Node* temp = front;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        delete temp;
    }
}

int main() {
    //ThreadSafeQueue<int> queue;
    My_Queue queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    return -1;
}