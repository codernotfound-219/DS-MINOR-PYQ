#include <iostream>
using namespace std;

class Node {
public:
  int val;
  Node *next;
  Node *prev;
};

class DLL {
private:
  Node *head;

public:
  DLL() { head = NULL; }

  bool isEmpty() { return head == NULL; }
  int count() {
    int c = 0;
    Node *tmp = head;
    while (tmp != NULL) {
      tmp = tmp->next;
      c++;
    }

    return c;
  }

  bool insertAtBegin(int v) {
    Node *nn = new Node;
    if (nn == NULL)
      return false;

    nn->val = v;
    nn->next = head;
    nn->prev = NULL;

    if (isEmpty()) {
      head = nn;
      return true;
    }

    head->prev = nn;
    head = nn;
    return true;
  }

  bool insertAtEnd(int v) {
    if (isEmpty())
      return insertAtBegin(v);

    Node *nn = new Node;
    if (nn == NULL)
      return false;
    Node *tmp = head;

    while (tmp->next != NULL) {
      tmp = tmp->next;
    }

    nn->val = v;
    nn->next = NULL;
    nn->prev = tmp;
    tmp->next = nn;
    return true;
  }

  bool insertAtPosition(int p, int v) {
    if (p > count() + 1 || p <= 0)
      return false;
    if (p == 1)
      return insertAtBegin(v);
    if (p == count() + 1)
      return insertAtEnd(v);

    Node *nn = new Node;
    if (nn == NULL)
      return false;
    nn->val = v;

    Node *tmp = head;

    p--;
    while (--p) {
      tmp = tmp->next;
    } // STOPS ONE POSITION BEFORE INSERT

    nn->prev = tmp;
    nn->next = tmp->next;
    tmp->next->prev = nn;
    tmp->next = nn;
    return true;
  }

  Node *search(int sv) {
    Node *tmp = head;

    while (tmp) {
      if (tmp->val == sv)
        return tmp;
      tmp = tmp->next;
    }

    return NULL;
  }

  bool insertAfterValue(int v, int sv) {
    Node *tmp = search(sv);
    if (tmp == NULL)
      return false;
    if (tmp->next == NULL)
      return insertAtEnd(v);
    Node *nn = new Node;

    if (nn == NULL)
      return false;
    nn->val = v;
    nn->next = tmp->next;
    nn->prev = tmp;
    tmp->next->prev = nn;
    tmp->next = nn;
    return true;
  }

  int deleteAtBegin() {
    if (isEmpty())
      return INT_MIN;
    Node *del = head;
    int rv = del->val;
    head = head->next;

    if (head == NULL) {
      delete del;
      return rv;
    }

    head->prev = NULL;
    delete del;
    return rv;
  }

  int deleteAtEnd() {
    if (isEmpty())
      return INT_MIN;
    if (count() == 1)
      return deleteAtBegin();

    Node *tmp = head;
    while (tmp->next != NULL)
      tmp = tmp->next;
    Node *del = tmp;

    tmp->prev->next = NULL;
    int rv = del->val;
    delete del;
    return rv;
  }

  int deleteAtPosition(int p) {
    if (p > count() || p <= 0)
      return INT_MIN;
    if (p == 1)
      return deleteAtBegin();
    if (p == count())
      return deleteAtEnd();

    Node *tmp = head;
    p--;
    while (--p) {
      tmp = tmp->next;
    }

    Node *del = tmp->next;
    tmp->next = del->next;
    del->next->prev = tmp;
    int rv = del->val;
    delete del;
    return rv;
  }

  int deleteAfterValue(int sv) {
    Node *tmp = search(sv);
    if (tmp == NULL)
      return INT_MIN;
    if (tmp->next == NULL)
      return INT_MIN;
    Node *del = tmp->next;
    int rv = del->val;
    tmp->next = del->next;
    if (del->next != NULL)
      del->next->prev = tmp;
    delete del;
    return rv;
  }

  void display() {
    Node *tmp = head;
    cout << "NULL <-> ";
    while (tmp) {
      cout << tmp->val << " <-> ";
      tmp = tmp->next;
    }
    cout << "NULL" << endl;
  }
};

int main() {
  int option = 1, val, pos, target;
  DLL d;

  while (option) {
    cout << "\nMENU:\n0. Exit\n1. Insert\n2. Delete\n3. Print" << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "EXITING..";
      break;
    case 1:
      cout << "ENTER: 1. InsertAtBegin // 2. InsertAtEnd // 3. "
              "InsertAtPosition // 4. InsertAfterValue"
           << endl;
      cin >> option;
      cout << "ENTER VAL: ";
      cin >> val;

      switch (option) {
      case 1:
        if (!d.insertAtBegin(val))
          cout << "UNSUCCESSFUL" << endl;
        else
          cout << "SUCCESS" << endl;
        break;
      case 2:
        if (!d.insertAtEnd(val))
          cout << "UNSUCCESSFUL" << endl;
        else
          cout << "SUCCESS" << endl;
        break;
      case 3:
        cout << "ENTER POS: ";
        cin >> pos;
        if (!d.insertAtPosition(pos, val))
          cout << "UNSUCCESSFUL" << endl;
        else
          cout << "SUCCESS" << endl;
        break;
      case 4:
        cout << "ENTER TARGET: ";
        cin >> target;
        if (!d.insertAfterValue(val, target))
          cout << "UNSUCCESSFUL" << endl;
        else
          cout << "SUCCESS" << endl;
        break;
      default:
        cout << "INVALID CHOICE" << endl;
        option = 1;
      }
      break;
    case 2:
      cout << "ENTER: 1. DeleteAtBegin // 2. DeleteAtEnd // 3. "
              "DeleteAtPosition // 4. DeleteAfterValue"
           << endl;
      cin >> option;

      switch (option) {
      case 1:
        cout << "DELETED: " << d.deleteAtBegin() << endl;
        break;
      case 2:
        cout << "DELETED: " << d.deleteAtEnd() << endl;
        break;
      case 3:
        cout << "ENTER POS: ";
        cin >> pos;
        cout << "DELETED: " << d.deleteAtPosition(pos) << endl;
        break;
      case 4:
        cout << "ENTER TARGET: ";
        cin >> target;
        cout << "DELETED: " << d.deleteAfterValue(target) << endl;
        break;
      default:
        cout << "INVALID CHOICE" << endl;
        option = 1;
      }
      break;
    case 3:
      cout << "DLL:" << endl;
      d.display();
      break;
    default:
      cout << "INVALID OPTION" << endl;
      option = 1;
    }
  }
}
