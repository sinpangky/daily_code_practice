#include "compiler.h"

using namespace std;

extern int comment_flag;
extern jmp_buf env;
extern unordered_map<string, int> keyword_map;

void InitializeHashMap() {
  // 哈希表的初始化
  keyword_map.insert(make_pair("+", TK_PLUS));
  keyword_map.insert(make_pair("-", TK_MINUS));
  keyword_map.insert(make_pair("*", TK_MUL));
  keyword_map.insert(make_pair("/", TK_DIVIDE));
  keyword_map.insert(make_pair("%", TK_MOD));
  keyword_map.insert(make_pair("==", TK_EQ));
  keyword_map.insert(make_pair("!", TK_MARK));
  keyword_map.insert(make_pair("!=", TK_NEQ));
  keyword_map.insert(make_pair("<", TK_LT));
  keyword_map.insert(make_pair("<=", TK_LEQ));
  keyword_map.insert(make_pair(">", TK_GT));
  keyword_map.insert(make_pair(">=", TK_GEQ));
  keyword_map.insert(make_pair("=", TK_ASSIGN));
  keyword_map.insert(make_pair("->", TK_POINTSTO));
  keyword_map.insert(make_pair(".", TK_DOT));
  keyword_map.insert(make_pair("&", TK_AND));
  keyword_map.insert(make_pair("(", TK_OPENPA));
  keyword_map.insert(make_pair(")", TK_CLOSEPA));
  keyword_map.insert(make_pair("[", TK_OPENBR));
  keyword_map.insert(make_pair("]", TK_CLOSEBR));
  keyword_map.insert(make_pair("{", TK_BEGIN));
  keyword_map.insert(make_pair("}", TK_END));
  keyword_map.insert(make_pair(";", TK_SEMICOLON));
  keyword_map.insert(make_pair(",", TK_COMMA));
  keyword_map.insert(make_pair("|", TK_VER_BAR));
  keyword_map.insert(make_pair("End_Of_File", TK_EOF));
  keyword_map.insert(make_pair("//", TK_REF));
  keyword_map.insert(make_pair("整型常量", TK_CINT));
  keyword_map.insert(make_pair("字符常量", TK_CCHAR));
  keyword_map.insert(make_pair("字符串常量", TK_CSTR));
  keyword_map.insert(make_pair("char", KW_CHAR));
  keyword_map.insert(make_pair("short", KW_SHORT));
  keyword_map.insert(make_pair("int", KW_INT));
  keyword_map.insert(make_pair("void", KW_VOID));
  keyword_map.insert(make_pair("struct", KW_STRUCT));
  keyword_map.insert(make_pair("if", KW_IF));
  keyword_map.insert(make_pair("else", KW_ELSE));
  keyword_map.insert(make_pair("for", KW_FOR));
  keyword_map.insert(make_pair("while", KW_WHILE));
  keyword_map.insert(make_pair("continue", KW_CONTINUE));
  keyword_map.insert(make_pair("break", KW_BREAK));
  keyword_map.insert(make_pair("return", KW_RETURN));
  keyword_map.insert(make_pair("sizeof", KW_SIZEOF));
  keyword_map.insert(make_pair("__align", KW_ALIGN));
  keyword_map.insert(make_pair("__cdecl", KW_CDECL));
  keyword_map.insert(make_pair("__stdcall", KW_STDCALL));
}

void Print(string ch, int token) {
  if (-1 == ch[0]) {  // end of the .c file
    cout << "\033[0m" << '\n' << "End of this file" << endl;
  } else if (token == TK_IDENT_V) {  // varials are cyan
    cout << "\033[36m" << ch;
  } else if (token == TK_IDENT_F) {  // funtions are white
    cout << "\033[37m" << ch;
  } else if (token > TK_CSTR) {  // keywords are green
    cout << "\033[32m" << ch;
  } else if (token > TK_EOF) {  // constants are yellow
    cout << "\033[33m" << ch;
  } else if (token == TK_REF) {  // keywords are bright green
    cout << "\033[92m" << ch;
  } else {  // operators are red
    cout << "\033[31m" << ch;
  }
}

int MapValue(const unordered_map<string, int> &keyword_map, const string &key) {
  unordered_map<string, int>::const_iterator it = keyword_map.find(key);
  if (it != keyword_map.end()) {
    return it->second;
  } else {
    return -1;
  }
}

void SplitRowIntoUnit(vector<TokenWord> &unit, const string str, int row) {
  int i = 0;
  if (comment_flag) {  // 跨行注释
    string s_temp;

    while (i < str.size()) {
      s_temp.push_back(str[i]);
      if (str[i - 1] == '*' && str[i] == '/') {
        comment_flag = 0;
        i++;
        break;
      }
      i++;
    }
    TokenWord temp = {TK_REF, s_temp, row};  // 添加注释的token
    unit.push_back(temp);
  }
  while (i < str.size()) {
    if (isspace(str[i])) {  // 遇空格跳过
      i++;
    } else if (str[i] == '/' &&
               (str[i + 1] == '/' ||
                str[i + 1] == '*')) {  // 遇注释把后面的内容都放到一个unit里面
      if (str[i + 1] == '*') {
        comment_flag = 1;
      }
      string s_temp;
      for (; i < str.size(); i++) {
        s_temp.push_back(str[i]);
      }
      TokenWord temp = {TK_REF, s_temp, row};  // 添加注释的token
      unit.push_back(temp);
    } else if (isalpha(str[i]) ||
               str[i] == '_') {  // 遇字母开头的话，会有关键字，标识符等
      string s_temp;
      while (isalnum(str[i]) || str[i] == '_') {
        s_temp.push_back(str[i]);
        i++;
      }
      TokenWord temp = {
          TK_IDENT_V, s_temp,
          row};  // 先加上变量的token，后面统计完之后再来细分函数，变量，关键字
      unit.push_back(temp);
    } else if (isdigit(str[i])) {  // 遇数字开头
      string s_temp;
      while (isdigit(str[i])) {
        s_temp.push_back(str[i]);
        i++;
      }
      if (str[i] == '.') {
        s_temp.push_back(str[i]);
        i++;
        while (isdigit(str[i])) {
          s_temp.push_back(str[i]);
          i++;
        }
      }
      TokenWord temp = {TK_CINT, s_temp, row};
      unit.push_back(temp);
    } else if (str[i] == '"') {  // "开头的字符串常量
      string s_temp;
      s_temp.push_back(str[i]);
      i++;
      while (str[i] != '"') {
        s_temp.push_back(str[i]);
        i++;
        if (str[i] == '\\' && str[i + 1] == '"') {  // 防止有转义字符
          s_temp.push_back(str[i]);
          s_temp.push_back(str[i + 1]);
          i += 2;
        }
        if (i == str.size()) {
          longjmp(env, QUOTES_ERROR);
        }
      }
      s_temp.push_back(str[i]);
      i++;
      TokenWord temp = {TK_CSTR, s_temp, row};  // 添加上字符串的token
      unit.push_back(temp);
    } else if (str[i] == '\'') {  // '开头的字符常量
      string s_temp;
      if (str[i + 1] == '\\') {  // 有转义字符
        s_temp.push_back(str[i]);
        i++;
        if (str[i + 1] == '\\' || str[i + 1] == '\'' || str[i + 1] == 'n' ||
            str[i + 1] == 'r' || str[i + 1] == 't' || str[i + 1] == 'b' ||
            str[i + 1] == '0') {  // 可输入的转义字符
          s_temp.push_back(str[i]);
          s_temp.push_back(str[i + 1]);
          i += 2;
          if (str[i] != '\'') {
            longjmp(env, APOSTROPHE_ERROR);
          } else {
            s_temp.push_back(str[i]);
            i++;
          }
        } else {
          longjmp(env, ESCAPE_CHAR_ERROR);
        }
      } else {
        s_temp.push_back(str[i]);
        i++;
        if (str[i + 1] != '\'') {  // 缺少右单引号错误
          longjmp(env, APOSTROPHE_ERROR);
        } else {  // 普通字符常量
          s_temp.push_back(str[i]);
          s_temp.push_back(str[i + 1]);
          i += 2;
        }
      }
      TokenWord temp = {TK_CCHAR, s_temp, row};  // 添加上字符的token
      unit.push_back(temp);
    } else {  // 其他的运算符号，符合的话就添加单个并后续进行合并，不符合的话报错
      string s_temp;
      s_temp.push_back(str[i]);
      i++;
      int token = MapValue(keyword_map, s_temp);
      if (token >= TK_PLUS && token <= TK_EOF) {
        TokenWord temp = {token, s_temp, row};  // 添加对应单个运算符的token
        unit.push_back(temp);
      } else {
        longjmp(env, UNKNOWN_SYMBOL);
      }
    }
  }
}

bool NextToken(vector<TokenWord> &unit, vector<TokenWord>::iterator it,
               int next_token) {
  bool ret = false;
  if (distance(it, unit.end()) > 1) {
    vector<TokenWord>::iterator next_it = next(it);
    if (next_it->token == next_token) {
      ret = true;
    }
  }
  return ret;
}

void MergeNext(vector<TokenWord> &unit, vector<TokenWord>::iterator &it) {
  if (distance(it, unit.end()) > 1) {
    vector<TokenWord>::iterator next_it = next(it);
    string stemp;
    stemp = next_it->s;
    it->s.append(stemp);
    unit.erase(next_it);
  }
}

// 进行小单元的合并以及关键字的分类
void MergeUnit(vector<TokenWord> &unit) {
  vector<TokenWord>::iterator it = unit.begin();
  while (it != unit.end()) {
    if (it->token == TK_IDENT_V) {
      int token = MapValue(keyword_map, it->s);
      if (token == -1) {
        if (NextToken(unit, it, TK_OPENPA)) {
          it->token = TK_IDENT_F;
        }
      } else {  // 修改关键字的token
        it->token = token;
      }
    } else if (it->token == TK_ASSIGN) {  // 判断是不是'=='
      if (NextToken(unit, it, TK_ASSIGN)) {
        it->token = TK_EQ;
        MergeNext(unit, it);
      }
    } else if (it->token == TK_MINUS) {  // 判断是不是'->'
      if (NextToken(unit, it, TK_GT)) {
        it->token = TK_POINTSTO;
        MergeNext(unit, it);
      }
    } else if (it->token == TK_MARK) {  // 判断是不是'!='
      if (NextToken(unit, it, TK_EQ)) {
        it->token = TK_NEQ;
        MergeNext(unit, it);
      }
    } else if (it->token == TK_LT) {  // 判断是不是'<='
      if (NextToken(unit, it, TK_EQ)) {
        it->token = TK_LEQ;
        MergeNext(unit, it);
      }
    } else if (it->token == TK_GT) {  // 判断是不是'>='
      if (NextToken(unit, it, TK_EQ)) {
        it->token = TK_GEQ;
        MergeNext(unit, it);
      }
    }
    ++it;
  }
}

void Compile(vector<TokenWord> unit) {}