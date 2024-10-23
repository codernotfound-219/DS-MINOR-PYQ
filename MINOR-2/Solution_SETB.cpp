#include <cmath>
#include <iostream>
using namespace std;
const double pi = 3.14159;

struct complexNumber {
  double length;
  double angle;
};

class priorityQueue {
private:
  complexNumber **arr;
  int size, index;

public:
  priorityQueue(int s) {
    size = s;
    index = -1;
    arr = new complexNumber *[size];
  }

  bool isEmpty() { return index == -1; }
  bool isFull() { return index == size - 1; }
  int count() { return index + 1; }

  complexNumber *returnSmallest(complexNumber *a, complexNumber *b) {
    double angleRad_a = a->angle * pi / 180;
    double angleRad_b = b->angle * pi / 180;

    double real_a = a->length * cos(angleRad_a);
    double real_b = b->length * cos(angleRad_b);
    double img_a = a->length * sin(angleRad_a);
    double img_b = b->length * sin(angleRad_b);

    if (real_a == real_b) {
      return img_a < img_b ? a : b;
    }

    return real_a < real_b ? a : b;
  }

  void heapify(int i) {
    int smallest = i;
    int left = 2 * i + 1, right = 2 * i + 2;

    if (left < count()) {
      if (arr[smallest] != returnSmallest(arr[smallest], arr[left]))
        smallest = left;
    }

    if (right < count()) {
      if (arr[smallest] != returnSmallest(arr[smallest], arr[right]))
        smallest = right;
    }

    if (smallest != i) {
      swap(arr[i], arr[smallest]);
      heapify(smallest);
    }
  }

  bool enQueue(complexNumber *v) {
    if (isFull())
      return false;
    arr[++index] = v;
    int i = index;

    while (i != 0 &&
           arr[(i - 1) / 2] != returnSmallest(arr[(i - 1) / 2], arr[i])) {
      swap(arr[i], arr[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
    return true;
  }

  complexNumber *peek() {
    if (isEmpty())
      return NULL;
    return arr[0];
  }

  complexNumber *deQueue() {
    if (isEmpty())
      return NULL;
    if (count() == 1) {
      return arr[index--];
    }

    complexNumber *rv = peek();
    swap(arr[0], arr[index]);
    index--;
    heapify(0);

    return rv;
  }

  void printVal(complexNumber *v) {
    cout << v->length << "L" << v->angle << " ";
  }

  void print() {
    for (int i = 0; i <= index; i++) {
      printVal(arr[i]);
    }
    cout << endl;
  }
};

int main() {
  int option = 1, size;
  cout << "ENTER SIZE: ";
  cin >> size;
  priorityQueue pq(size);

  while (option) {
    cout
        << "\nMENU:\n0. Exit  \t1. enQueue\n2. deQueue\t3. count\t4. printQueue"
        << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "Exiting... " << endl;
      break;
    case 1: {
      complexNumber *v = new complexNumber;
      cout << "Enter length: ";
      cin >> v->length;
      cout << "Enter angle (deg): ";
      cin >> v->angle;
      cout << (pq.enQueue(v) ? "SUCCESS" : "UNSUCCESSFUL: overflow") << endl;
      break;
    }
    case 2: {
      complexNumber *v = pq.deQueue();
      if (!v) {
        cout << "NONE" << endl;
        break;
      }
      cout << "DEQUEUE: ";
      pq.printVal(v);
      cout << endl;
      break;
    }
    case 3:
      cout << "COUNT: " << pq.count() << endl;
      break;
    case 4:
      cout << "QUEUE:" << endl;
      pq.print();
      break;
    default:
      cout << "Invalid choice";
      option = 1;
    }
  }

  return 0;
}
