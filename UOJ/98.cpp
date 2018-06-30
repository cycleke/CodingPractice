#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define STACK_SIZE 10003
#define TOKENS_NUMBER 7003
#define VARIABLE_NUMBER 7003
#define FUNCTION_NUMBER 7003
#define MEMORY_SIZE (1 << 22 | 1)
#define INPUF_BUFFER_SIZE 10003

char buffer[INPUF_BUFFER_SIZE], *cur_char = buffer;

char i_stack[STACK_SIZE];
int i_stack_p = 0;

map<string, int> operations, keywards, variables;
int var_id = 0;
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
int tokens_p = 0, tokens_ptr = 0;

bool isName(char ch) {
  return isalpha(ch) || isdigit(ch) || ch == '_' || ch == '$';
}
int i_n, i_in[STACK_SIZE], i_in_p = 0;
int i_ReadInt() {
  int x = 0, sign = 1;
  while (!isdigit(*cur_char)) *cur_char++ == '-' ? sign = -1 : 0;
  while (isdigit(*cur_char)) x = x * 10 + *cur_char++ - '0';
  return x * sign;
}

struct Variable {
  int id, *data, size;
  vector<int> a;
  Variable() : id(0), data(NULL), size(1) {}
  void insert(int x) {
    a.push_back(x);
    size *= x;
  }
};
vector<Variable> var_now[VARIABLE_NUMBER];
int memory_pool[MEMORY_SIZE], *memory_it = memory_pool;
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
    int mx = *--memory_it;
    for (Variable &v : var_list) {
      memset(memory_it, 0, sizeof(int) * v.size);
      v.data = memory_it;
      memory_it += v.size;
      var_now[v.id].push_back(v);
    }
    *memory_it++ = mx + var_list.size();
  }
  void undef() {
    for (Variable &v : var_list) {
      var_now[v.id].pop_back();
      memory_it -= v.size;
    }
  }
  void undefs() {
    int mx = *--memory_it;
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
    while (tokens[tokens_ptr].equal(0, 2)) {
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
            NodePB().Sv(operations.back());
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
        NodePB().Rcall();
      } else {
        NodePB().Rvar();
      }
    }
    tokens_ptr++;
  }
  void Rkeyword() {
    if (tokens[tokens_ptr].value == 0) { // if
      type = 3;
      tokens_ptr += 2;
      NodePB().Rexpr();
      NodePB().Rblock();
      if (tokens[tokens_ptr].equal(3, 1)) { // else
        tokens_ptr++;
        NodePB().Rblock();
      }
    } else if (tokens[tokens_ptr].value == 2) { // while
      type = 4;
      tokens_ptr += 2;
      NodePB().Rexpr();
      NodePB().Rblock();
    } else if (tokens[tokens_ptr].value == 3) { // for
      type = 5;
      tokens_ptr += 2;
      NodePB();
      if (tokens[tokens_ptr].equal(3, 4)) {
        var_list.Rs();
        nodes.back().type = 12;
      } else {
        nodes.back().Rexpr();
      }
      NodePB().Rexpr();
      NodePB().Rexpr();
      NodePB().Rblock();
    } else { // return
      type = 6;
      tokens_ptr++;
      NodePB().Rexpr();
    }
  }
  void Rblock() {
    if (!tokens[tokens_ptr].equal(0, 4)) {
      if (tokens[tokens_ptr].type == 3) {
        Rkeyword();
      } else {
        Rexpr();
      }
      return;
    }
    type = 1;
    tokens_ptr++;
    while (!tokens[tokens_ptr].equal(0, 5)) {
      if (tokens[tokens_ptr].type == 3) {
        if (tokens[tokens_ptr].value == 4) {
          int left = var_list.var_list.size();
          var_list.Rs();
          int right = var_list.var_list.size();
          NodePB().Sd(left, right, var_list);
        } else {
          NodePB().Rkeyword();
        }
      } else {
        NodePB().Rblock();
      }
    }
    tokens_ptr++;
  }
  void Rfunc() {
    type = 0;
    tokens_ptr += 3;
    if (tokens[tokens_ptr].equal(0, 1)) {
      tokens_ptr++;
    } else {
      do {
        tokens_ptr++;
        var_list.R();
      } while (!tokens[tokens_ptr++].equal(0, 1));
    }
    NodePB().Rblock();
  }
} funcs[FUNCTION_NUMBER];

#define run(x) _runs[(x).type](x)
int (*_runs[30])(Node&);
void (*_ops[30])();
bool returned(false);

// Define Keywords begin

void push(int x) {
  *memory_it++ = -1;
  *memory_it++ = x;
  *memory_it++ = 0;
}
int &pop() {
  memory_it -= 3;
  return *memory_it < 0 ? memory_it[1] : var_now[*memory_it].back().data[memory_it[2]];
}
int _func(Node &w) {
  w.var_list.def(0);
  int res = run(w.nodes[0]);
  w.var_list.undef();
  returned = false;
  push(res);
  return res;
}
int _block(Node &w) {
  *memory_it++ = 0;
  int r = 0;
  for (int i = 0; i < (int)w.nodes.size() && !returned; i++) {
    r = run(w.nodes[i]);
  }
  w.var_list.undefs();
  return r;
}
int _expr(Node &w) {
  if (w.nodes.empty()) return 1;
  for (int i = 0; i < (int)w.nodes.size(); i++) {
    run(w.nodes[i]);
  }
  return pop();
}
int _if(Node &w) {
  int res = 0;
  if (run(w.nodes[0])) {
    res = run(w.nodes[1]);
  } else if (w.nodes.size() == 3) {
    res = run(w.nodes[2]);
  }
  return res;
}
int _while(Node &w) {
  int res = 0;
  while (!returned && run(w.nodes[0])) {
    res = run(w.nodes[1]);
  }
  return res;
}
int _for(Node &w) {
  int res = 0;
  w.var_list.def();
  run(w.nodes[0]);
  while (!returned && run(w.nodes[1])) {
    res = run(w.nodes[3]);
    run(w.nodes[2]);
  }
  w.var_list.undef();
  return res;
}
int _return(Node &w) {
  int res = run(w.nodes[0]);
  returned = true;
  return res;
}
int _var(Node &w) {
  *memory_it++ = w.value;
  *memory_it++ = 0;
  *memory_it++ = 0;
  return 0;
}
int _int(Node &w) {
  push(w.value);
  return 0;
}
int _nod(Node &w) {
  return 0;
}
int _call(Node &w) {
  for (auto i : w.nodes) {
    *memory_it++ = run(i);
  }
  memory_it -= w.nodes.size();
  return run(funcs[w.value]);
}
void _arr() {
  int x = pop();
  memory_it[-1] *= var_now[memory_it[-3]].back().a[memory_it[-2]++];
  memory_it[-1] += x;
}
void _not() {
  push(!pop());
}
void _pos() {
  push(pop());
}
void _neg() {
  push(-pop());
}
void _mul() {
  int b = pop(), a = pop();
  push(a * b);
}
void _div() {
  int b = pop(), a = pop();
  push(a / b);
}
void _mod() {
  int b = pop(), a = pop();
  push(a % b);
}
void _add() {
  int b = pop(), a = pop();
  push(a + b);
}
void _sub() {
  int b = pop(), a = pop();
  push(a - b);
}
void _leq() {
  int b = pop(), a = pop();
  push(a <= b);
}
void _meq() {
  int b = pop(), a = pop();
  push(a >= b);
}
void _lss() {
  int b = pop(), a = pop();
  push(a < b);
}
void _mre() {
  int b = pop(), a = pop();
  push(a > b);
}
void _eq() {
  int b = pop(), a = pop();
  push(a == b);
}
void _neq() {
  int b = pop(), a = pop();
  push(a != b);
}
void _xor() {
  int b = pop(), a = pop();
  push(!a + !b == 1);
}
void _and() {
  int b = pop(), a = pop();
  push(a && b);
}
void _or() {
  int b = pop(), a = pop();
  push(a || b);
}
void _set() {
  int b = pop();
  pop() = b;
  push(b);
}
void _in() {
  pop() = i_in[i_in_p++];
}
void _out() {
  int x = pop();
  if (memory_it[0] == 3) {
    puts("");
  } else {
    printf("%d", x);
  }
}
int _op(Node &w) {
  _ops[w.value]();
  return 0;
}
int _vdi(Node &w) {
  w.var_list.defs();
  return 0;
}
int _putchar(Node &w) {
  int c = *memory_it;
  putchar(c);
  push(c);
  return c;
}
// Define end

void LoadKeywords() {
  _runs[0] = _func;
  _runs[1] = _block;
  _runs[2] = _expr;
  _runs[3] = _if;
  _runs[4] = _while;
  _runs[5] = _for;
  _runs[6] = _return;
  _runs[7] = _var;
  _runs[8] = _int;
  _runs[9] = _call;
  _runs[10] = _op;
  _runs[11] = _putchar;
  _runs[12] = _nod;
  _runs[13] = _vdi;
  _ops[2] = _arr;
  _ops[6] = _not;
  _ops[7] = _pos;
  _ops[8] = _neg;
  _ops[9] = _mul;
  _ops[10] = _div;
  _ops[11] = _mod;
  _ops[12] = _add;
  _ops[13] = _sub;
  _ops[14] = _leq;
  _ops[15] = _meq;
  _ops[16] = _lss;
  _ops[17] = _mre;
  _ops[18] = _eq;
  _ops[19] = _neq;
  _ops[20] = _xor;
  _ops[21] = _and;
  _ops[22] = _or;
  _ops[23] = _set;
  _ops[24] = _out;
  _ops[25] = _in;
  rk_count[6] = rk_count[7] = rk_count[8] = rk_count[23] = 1;
  operations["("] = 0;
  operations[")"] = 1;
  operations["["] = 2;
  operations["]"] = 3;
  operations["{"] = 4;
  operations["}"] = 5;
  operations["!"] = 6;
  operations["+"] = 7;
  operations["-"] = 8;
  operations["*"] = 9;
  operations["/"] = 10;
  operations["%"] = 11;
  operations["<="] = 14;
  operations[">="] = 15;
  operations["<"] = 16;
  operations[">"] = 17;
  operations["=="] = 18;
  operations["!="] = 19;
  operations["^"] = 20;
  operations["&&"] = 21;
  operations["||"] = 22;
  operations["="] = 23;
  operations["<<"] = 24;
  operations[">>"] = 25;
  operations[","] = 26;
  operations[";"] = 27;
  keywards["if"] = 0;
  keywards["else"] = 1;
  keywards["while"] = 2;
  keywards["for"] = 3;
  keywards["int"] = 4;
  keywards["return"] = 5;
  variables["cin"] = ++var_id;
  variables["cout"] = ++var_id;
  variables["endl"] = ++var_id;
  funcs[variables["putchar"] = ++var_id].type = 11;
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
    if (*cur_char == EOF) break;
    i_stack_p = 0;
    if (isalpha(*cur_char)) {
      while (isName(*cur_char)) {
        i_stack[i_stack_p++] = *cur_char++;
      }
      i_stack[i_stack_p] = 0;
      tokens[tokens_p++].init(2);
    } else if (isdigit(*cur_char)) {
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
  while (tokens_ptr < tokens_p) {
    if (tokens[tokens_ptr + 2].equal(0, 0)) {
      funcs[tokens[tokens_ptr + 1].value].Rfunc();
    } else {
      glob_var.Rs();
    }
  }
}

int main() {
  LoadKeywords();
  buffer[fread(buffer, 1, sizeof(buffer), stdin)] = EOF;
  PreWork();
  BuildTree();
  glob_var.ins(1);
  glob_var.ins(2);
  glob_var.ins(3);
  glob_var.def();
  run(funcs[variables["main"]]);
  return 0;
}
