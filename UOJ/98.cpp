#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define STACK_SIZE 10003
#define TOKENS_NUMBER 7000
#define VARIABLE_NUMBER 7000
#define MEMORY_SIZE (1 << 21 | 1)
#define INPUF_BUFFER_SIZE 10003

char buffer[INPUF_BUFFER_SIZE], *cur_char = buffer;

char i_stack[STACK_SIZE];
int i_stack_p(0);

map<string, int> operations, keywards, variables;
int var_id(0);
const int rk[] = {115, 115, 116, 116, 2, 2, 3, 3, 3,  4,  4,  4,  5,  5,
                  6,  6,  6,  6,  7, 7, 8, 9, 10, 11, 12, 12, 13, 14};
int rk_count[28];

struct Token {
  int type;
  int value;

  void init(int _type, int _value = 0) {
    type = _type;
    if (_type == 0) {
      value = operations[string(i_stack)];
      if ((value == 7 || value == 8) &&
          (this[-1].type == 1 || this[-1].type == 2 || this[-1].equal(0, 1) ||
           this[-1].equal(0, 3)))
        value += 5;
    } else if (_type == 1) {
      value = _value;
    } else {
      string s(i_stack);
      static map<string, int>::iterator it;
      it = keywards.find(s);
      if (it != keywards.end()) {
        type = 3;
        value = it->second;
        return;
      }
      it = variables.find(s);
      if (it != variables.end()) {
        value = it->second;
      } else {
        value = variables[s] = ++var_id;
      }
    }
  }
  bool equal(int a, int b) { return type == a && value == b; }
} tokens[TOKENS_NUMBER];
int tokens_p(0), tokens_ptr(0);

bool isName(char ch) {
  return isalpha(ch) || isdight(ch) || ch == '_' || ch == '$';
}
int i_n, i_in[STACK_SIZE], i_in_p(0);
int i_ReadInt() {
  int x = 0, sign = 1;
  while (!isdight(*cur_char)) cur_char++;
  if (cur_char[-1] == '-') sign = -1;
  while (isdight(*cur_char)) x = x * 10 + *cur_char++ - '0';
  return x * sign;
}

struct Variable {
  int id, *data, size;
  vector<int> a;
  Variable() { size = 1； id = 0; }
  void insert(int x) {
    a.push_back(x);
    size *= x;
  }
};
vector<Variable> var_now[VARIABLE_NUMBER];
int memory_pool[MEMORY_SIZE], *memory_it(memory_pool);
struct VariableList {
  vector<Variable> var_list;
  void def(bool init = true) {
    for (Variable &v : var_list) {
      if (init) {
        memset(memory_it, 0, sizeof(int) * v.size);
      }
      v.data = memory_it;
      memory_it += v.size;
      var_now[v.id].push_back(v);
    }
  }
  void defs() {
    int mx = *--mp;
    for (Variable &v : var_list) {
      memset(memory_it, 0, sizeof(int) * v.size);
      v.data = memory_it;
      memory_it += v.size;
      var_now[v.id].push_back(v);
    }
    *mp++ = mx + var_list.size();
  }
  void undef() {
    for (Variable &v : var_list) {
      var_now[v.id].pop_back();
      memory_it -= v.size;
    }
  }
  void undefs() {
    int mx = *--mp;
    for (int i = 0; i < mx; i++) {
      var_now[var_list[i].id].pop_back();
      memory_it -= var_list[i].size;
    }
  }
  void ins(int id) {
    Variable w;
    w.id = id;
    var_list.push_back(w);
  }
  void R() {
    Variable v;
    v.id = tokens[tokens_ptr++].value;
    while (tokens.equal(0, 2)) {
      v.insert(tokens[tokens_ptr + 1].value);
      tokens_ptr += 3;
    }
    var_list.push_back(v);
  }
  void Rs() {
    tokens_ptr++;
    while (true) {
      R();
      if (tokens[tokens_ptr++].value == 27) break;
    }
  }
} glob_var;

struct Node {
  int type, value;
  VariableList var_list;
  vector<Node> nodes;
  Node& NodePB() {
    nodes.push_back(Node());
    return nodes.back();
  }
  void Rvar() {
    type = 7;
    value = tokens[tokens_ptr++].value;
  }
  void Rint() {
    type = 8;
    value = tokens[tokens_ptr++].value;
  }
  void Rcall() {
    type = 9;
    value = tokens[tokens_ptr].value;
    tokens_ptr += 2;
    while (!tokens[tokens_ptr - 1].equal(0, 1)) NodePB().Rexpr();
  }
  void Sv(int v) {
    type = 10;
    value = v;
  }
  void Sd(int left, int right, VariableList &vs) {
    type = 13;
    for (int i = left; i < right; i++) {
      var_list.var_list.push_back(vs.var_list[i]);
    }
  }
  void Rexpr() {
    type = 2;
    vector<int> operations;
    operations.push_back(0);
    while (true) {
      if (tokens[tokens_ptr].type == 0) {
        if (tokens[tokens_ptr].value >= 26) {
          while (operations.back()) {
            NodePB().Sv(operations.back());
            operations.pop_back();
          }
          break;
        }
        int value = tokens[tokens_ptr].value;
        if (value == 0 || value == 2) {
          operations.push_back(value);
        } else if (value == 1) {
          while (operations.back()) {
            NodePB.Sv(operations.back());
            operations.pop_back();
          }
          operations.pop_back();
          if (operations.empty()) break;
        } else if (value == 3) {
          int c;
          do {
            c = operations.back();
            NodePB().Sv(c);
            operations.pop_back();
          } while (c != 2);
        } else {
          while (rk[operations.back()] + rk_count[value] <= rk[value]) {
            NodePB().Sv(operations.back());
            operations.pop_back();
          }
          operations.push_back(value);
        }
        tokens_ptr++;
      } else if (tokens[tokens_ptr].type == 1) {
        NodePB().Rint();
      } else if (tokens[tokens_ptr + 1].equal(0, 0)) {
        NodePB.Rcall();
      } else {
        NodePB().Rvar();
      }
    }
    tokens_ptr++;
  }
  void Rkeyword() {

  }
};

void LoadKeyWords() {
  // todo
}

void PreWork() {
  i_n = i_ReadInt();
  for (int i = 0; i < i_n; i++) {
    i_in[i] = i_ReadInt();
  }
  while (*cur_char != ';') {
    cur_char++;
  }
  cur_char++;
  while (true) {
    while (*cur_char != EOF && *cur_char < 33) {
      cur_char++;
    }
    if (cur_char == EOF) break;
    i_stack_p = 0;
    if (isalpha(*cur_char)) {
      while (isName(*cur_char)) {
        i_stack[i_stack_p++] = *cur_char++;
      }
      i_stack[i_stack_p] = 0;
      tokens[tokens_p++].init(2);
    } else if (isdight(*cur_char)) {
      tokens[tokens_p++].init(1, i_ReadInt());
    } else {
      i_stack[i_stack_p++] = *cur_char++;
      i_stack[1] = *cur_char;
      i_stack[2] = 0;
      if (operations.find(string(i_stack)) != operations.end())
        ++cur_char;
      else
        i_stack[1] = 0;
      tokens[tokens_p].init(0);
      tokens_p++;
    }
  }
}

void BuildTree() {
  //todo
}

int main() {
  LoadKeyWords();
  buffer[fread(buffer, 1, sizeof(buffer), stdin)] = EOF;
  PreWork();
  BuildTree();
  glob_var.ins(1);
  glob_var.ins(2);
  glob_var.ins(3);
  glob_var.def();
  run(funcs[vars["main"]]);
  return 0;
}
