#include <iostream>
#include <string>
#define DT char
#define MAXS 10
using namespace std;

/*
ASSUMPTIONS:
  1. The input consists only of operators [*, /, +, -], whole numbers, and
parantheses.
  2. Only single character operators are allowed. For ex. 3++6 -> will be
invalid.
  3. All tokens MUST BE SEPARATED BY SPACES.
*/

class Stack {
private:
  DT arr[MAXS];
  int topIndex;

public:
  Stack() { topIndex = -1; }

  bool isEmpty() { return topIndex == -1; }
  bool isFull() { return topIndex == MAXS - 1; }
  int count() { return topIndex + 1; }

  bool push(int v) {
    if (isFull())
      return false;
    arr[++topIndex] = v;
    return true;
  }

  DT pop() { return arr[topIndex--]; }

  DT top() { return arr[topIndex]; }

  void display() {
    for (int i = 0; i <= topIndex; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
};

bool validParantheses(string inp) {
  Stack s;

  for (int i = 0; i < inp.size(); i++) {
    if (inp[i] == ' ')
      continue;
    char c = inp[i];
    if (c == '{' || c == '(' || c == '[' || c == '<') {
      s.push(c);
    }

    if (c == '}' || c == ']' || c == ')' || c == '>') {
      if (s.isEmpty())
        return false;

      switch (c) {
      case '}':
        if (s.top() != '{')
          return false;
        break;
      case ']':
        if (s.top() != '[')
          return false;
        break;
      case '>':
        if (s.top() != '<')
          return false;
        break;
      case ')':
        if (s.top() != '(')
          return false;
        break;
      }

      s.pop();
    }
  }

  return s.isEmpty();
}

bool isParantheses(char c) {
  if (c == '[' || c == ']' || c == '(' || c == ')' || c == '<' || c == '>' ||
      c == '{' || c == '}')
    return true;
  return false;
}

bool isOperator(char c) {
  if (c == '*' || c == '/' || c == '+' || c == '-')
    return true;
  return false;
}

bool validExpression(string inp) {
  if (isOperator(inp[0]) || isOperator(inp[1]))
    return false; // first char must not be operator
  if (isOperator(inp[inp.size() - 1]))
    return false; // last char must not be operator
  int operators = 0, operands = 0;

  for (int i = 0; i < inp.size(); i++) {
    if (isdigit(inp[i])) {
      while (i < inp.size() && isdigit(inp[i]))
        i++;
      operands++;
    }

    if (isOperator(inp[i]))
      operators++;
  }

  if (operands - operators != 1)
    return false; // MORE OPERATORS THAN OPERANDS
  return true;
}

void closing_parantheses(Stack &stk, string &result, char open) {
  while (!stk.isEmpty() && stk.top() != open) {
    result.insert(result.end(), stk.pop());
    result.insert(result.end(), ' ');
  }
  stk.pop();
}

string convertor(string inp) {
  Stack stk;
  string result;

  for (int i = 0; i < inp.size(); i++) {
    string token = "";
    if (inp[i] == ' ')
      continue;

    if (isdigit(inp[i])) {
      while (i < inp.size() && (isdigit(inp[i]) || inp[i] == '.')) {
        token += inp[i];
        i++;
      }

      result.append(token);
      result.insert(result.end(), ' ');
      i--;
    }

    if (inp[i] == '*' || inp[i] == '/') {
      token = inp[i];
      while (stk.top() == '*' || stk.top() == '/') {
        result.insert(result.end(), stk.pop());
        result.insert(result.end(), ' ');
      }
      stk.push(inp[i]);
    }

    if (inp[i] == '+' || inp[i] == '-') {
      token = inp[i];
      while (!stk.isEmpty() && isOperator(stk.top())) {
        result.insert(result.end(), stk.pop());
        result.insert(result.end(), ' ');
      }
      stk.push(inp[i]);
    }

    if (inp[i] == '{' || inp[i] == '(' || inp[i] == '<' || inp[i] == '[') {
      stk.push(inp[i]);
    }

    switch (inp[i]) {
    case ')':
      closing_parantheses(stk, result, '(');
      break;
    case '}':
      closing_parantheses(stk, result, '{');
      break;
    case '>':
      closing_parantheses(stk, result, '<');
      break;
    case ']':
      closing_parantheses(stk, result, '[');
      break;
    default:
      break;
    }
  }

  while (!stk.isEmpty()) {
    result.insert(result.end(), stk.pop());
    result.insert(result.end(), ' ');
  }

  return result;
}

int main() {
  string inp, out;
  int option = 1;

  while (option) {
    cout << "\nMENU:\n0. Exit\n1. Expression" << endl;
    cin >> option;

    switch (option) {
    case 0:
      cout << "EXIT" << endl;
      break;
    case 1:
      cin.ignore();
      cout << "ENTER EXPRESSION: ";
      getline(cin, inp);
      if (!validParantheses(inp)) {
        cout << "UNSUCCESSFUL: invalid parantheses" << endl;
        break;
      }
      if (!validExpression(inp)) {
        cout << "UNSUCCESSFUL: incorrect syntax" << endl;
        break;
      }
      out = convertor(inp);
      cout << "POSTFIX: " << out << endl;
      break;
    default:
      cout << "INVALID OPTION" << endl;
      option = 1;
    }
  }
}
