#include <iostream>
using namespace std;

struct complexNumber {
    double real;
    double img;
};

class priorityQueue {
private:
    complexNumber** arr;
    int size;
    int index;
public:
    priorityQueue(int s) {
        size = s;
        index = -1;
        arr = new complexNumber*[size];
    }
    
    int count() {
        return index+1;
    }
    
    bool isEmpty() {
        return index == -1;
    }
    
    bool isFull() {
        return index == size-1;
    }
    
    complexNumber* returnSmallest(complexNumber* a, complexNumber* b) {
        if (a->real == b->real) {
            return a->img < b->img ? a : b;
        }
        return a->real < b->real ? a : b;
    }
    
    void heapify(int i) {
        int smallest = i;
        int left = 2*i + 1, right = 2*i + 2;
        
        if (left < count()) {
            if (arr[smallest] != returnSmallest(arr[left], arr[smallest])) smallest = left;
        }
        
        if (right < count()) {
            if (arr[smallest] != returnSmallest(arr[right], arr[smallest])) smallest = right;
        }
        
        if (smallest != i) {
            swap(arr[smallest], arr[i]);
            heapify(smallest);
        }
    }
    
    bool enQueue(complexNumber* v) {
        if (isFull()) return false;
        arr[++index] = v;
        
        int i = index;
        
        while (i != 0 && arr[(i-1)/2] != returnSmallest(arr[i], arr[(i-1)/2])) {
            swap(arr[i], arr[(i-1)/2]);
            i = (i-1)/2;
        }
        return true;
    }
    
    complexNumber* peek() {
        if (isEmpty()) return NULL;
        return arr[0];
    }
    
    complexNumber* deQueue() {
        if (isEmpty()) return NULL;
        if (count() == 1) {
            return arr[index--];
        }
        
        complexNumber* rv = peek();
        swap(arr[0], arr[index]);
        index--;
        heapify(0);
        return rv;
    }
    
    void print() {
        for (int i = 0; i < count(); i++) {
            cout << arr[i]->real << "+i" << arr[i]->img << " ";
        }
        cout << endl;
    }
};

int main() {
    int option=1, size;
    cout << "Enter size: "; cin >> size;
    priorityQueue pq(size);
    
    while(option) {
        cout << "\nMENU:\n0. Exit\n1. enQueue\n2. deQueue\n3. count\n4. print" << endl;
        cin >> option;
        
        switch(option) {
            case 0:
                cout << "exitin...";
                break;
            case 1:
            {
                complexNumber *v = new complexNumber;
                cout << "Enter real part: "; cin >> v->real;
                cout << "Enter img part: "; cin >> v->img;
                cout << (pq.enQueue(v) ? "SUCCESS" : "UNSUCCESFUL: OVERFLOW") << endl;
                break;
            }
            case 2:
            {
                complexNumber *v = pq.deQueue();
                if (!v) {
                    cout << "NONE" << endl;
                    break;
                }
                cout << "DEQUEUE: ";
                cout << v->real << "+i" << v->img << endl;
                break;
            }
            case 3:
                cout << "COUNT: " << pq.count() << endl;
                break;
            case 4:
                cout << "Queue: " << endl;
                pq.print();
                break;
            default:
                cout << "Invalid choice" << endl;
                option =1;
        }
    }
    
    return 0;
}
