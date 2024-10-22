/*
SHOWS = 3
use QUEUE
seats = 20 (4 rows, 5 columns) naming starts from rows
functions:
  1. reserve_tickets(show_id, ticket_cnt) -> return reservation_id after
occupying seats. (fail = INT_MIN)
  2. cancel_reservation(show_id, reservation_id) -> should make the seats vacant
again. (fail = false)
  3. get_reserved_seats(show_id) -> return reserved seats of that show.
  4. get_available_seats(show_id) -> return vacant seats of that show.

output: MENU_BASED
*/

/*
ASSUMPTIONS:
1. Only the person who reserved first is allowed to ask for cancellation.
2. Others must wait their turn {first in first out}
3. Cancellation choice is only selected after reservation has been completed.
4. Correct reservation_id is entered at all times.
5. Correct show_id is entered at all times.
*/

#include <iostream>
#include <string>
using namespace std;

class Queue {
private:
  int available[20];
  int reserved[20];
  int frontA, rearA, countA;
  int frontR, rearR, countR;

public:
  Queue() {
    frontA = 0;
    rearA = 19;
    frontR = rearR = -1;
    countA = 20;
    countR = 0;

    for (int i = 0; i < 20; i++) {
      available[i] = i + 1;
    }
  }

  bool isEmptyA() { return countA == 0; }
  bool isEmptyR() { return countR == 0; }
  bool isFullA() { return countA == 20; }
  bool isFullR() { return countR == 20; }
  int counterA() { return countA; }
  int counterR() { return countR; }

  bool enQueueA(int v) {
    if (isFullA())
      return false;
    if (isEmptyA()) {
      frontA = rearA = 0;
    } else {
      rearA = ++rearA % 20;
    }

    available[rearA] = v;
    countA++;
    return true;
  }

  int deQueueA() {
    if (isEmptyA())
      return INT_MIN;
    int tmp = available[frontA];
    if (counterA() == 1) {
      frontA = rearA = -1;
    } else {
      frontA = ++frontA % 20;
    }
    countA--;
    return tmp;
  }

  bool enQueueR(int v) {
    if (isFullR())
      return false;
    if (isEmptyR()) {
      frontR = rearR = 0;
    } else {
      rearR = ++rearR % 20;
    }

    reserved[rearR] = v;
    countR++;
    return true;
  }

  int deQueueR() {
    if (isEmptyR())
      return INT_MIN;
    int tmp = reserved[frontR];
    if (counterR() == 1) {
      frontR = rearR = -1;
    } else {
      frontR = ++frontR % 20;
    }
    countR--;
    return tmp;
  }
};

class Show {
private:
  Queue s1, s2, s3;
  string show_1, show_2, show_3;

  int reservor(Queue &q, int count, string id) {

    // CREATING UNIQUE ID
    int reservation_id = int(id[1] - '0');
    reservation_id += 10 * q.counterR();
    reservation_id += 1000 * count;

    // KEEPING TRACK
    while (count--) {
      if (!q.enQueueR(q.deQueueA()))
        return INT_MIN;
    }
    return reservation_id;
  }

  bool cancelor(Queue &q, int r_id) {
    for (int i = 0; i < 3; i++) {
      r_id /= 10;
    }
    int count = r_id;
    while (count--) {
      if (!q.enQueueA(q.deQueueR()))
        return false;
    }

    return true;
  }

  int rs(Queue &q) { return q.counterR(); }

  int as(Queue &q) { return q.counterA(); }

public:
  Show() {
    show_1 = "S1";
    show_2 = "S2";
    show_3 = "S3";
  }

  int reserve_tickets(string show_id, int ticket_cnt) {
    if (show_id == show_1)
      return reservor(s1, ticket_cnt, show_id);
    if (show_id == show_2)
      return reservor(s2, ticket_cnt, show_id);
    return reservor(s3, ticket_cnt, show_id);
  }

  bool cancel_reservation(string show_id, int reservation_id) {
    if (show_id == show_1)
      return cancelor(s1, reservation_id);
    if (show_id == show_2)
      return cancelor(s2, reservation_id);
    return cancelor(s3, reservation_id);
  }

  int get_reserved_seats(string show_id) {
    if (show_id == show_1)
      return rs(s1);
    if (show_id == show_2)
      return rs(s2);
    return rs(s3);
  }

  int get_available_seats(string show_id) {
    if (show_id == show_1)
      return as(s1);
    if (show_id == show_2)
      return as(s2);
    return as(s3);
  }
};

int main() {
  int option = 1, cnt;
  string showId;
  Show s;
  cout << "NOTE: SHOW_IDS ARE: // Show_1 = S1 // Show_2 = S2 // Show_3 = S3"
       << endl;

  while (option) {
    cout << "\nMENU:\n0. Exit\n1. reserve_tickets\n2. cancel_tickets\n3. "
            "get_availble_seats\n4. get_reserved_seats"
         << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "EXITING...";
      break;
    case 1:
      cout << "ENTER SHOW ID: ";
      cin >> showId;
      cout << "Enter total tickets: ";
      cin >> cnt;
      cout << "RESERVATION: " << s.reserve_tickets(showId, cnt) << endl;
      break;
    case 2:
      cout << "ENTER SHOW ID: ";
      cin >> showId;
      cout << "Enter reservation id: ";
      cin >> cnt;
      cout << "CANCELLATION: "
           << (s.cancel_reservation(showId, cnt) ? "SUCCESSFUL"
                                                 : "UNSUCCESSFUL")
           << endl;
      break;
    case 3:
      cout << "ENTER SHOW ID: ";
      cin >> showId;
      cout << "AVAILABLE SEATS: " << s.get_available_seats(showId) << endl;
      break;
    case 4:
      cout << "ENTER SHOW ID: ";
      cin >> showId;
      cout << "RESERVED SEATS: " << s.get_reserved_seats(showId);
      break;
    default:
      cout << "INVALID OPTION" << endl;
      option = 1;
    }
  }

  return 0;
}
