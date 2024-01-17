#include <iostream>
#include <fstream>
// #include <stack>
#include <string>
#include <vector>
#include <cctype>
#include <csetjmp>
#include <unordered_map>
#define MAX 1234

enum TokenCode {
  /* 运算符及分隔符 */
  TK_PLUS,       // + 加号
  TK_MINUS,      // - 减号
  TK_MUL,        // * 星号
  TK_DIVIDE,     // / 除号
  TK_MOD,        // % 求余运算符
  TK_EQ,         // == 等于号               v
  TK_MARK,       // ! 取非
  TK_NEQ,        // != 不等于号       v
  TK_LT,         // < 小于号
  TK_LEQ,        // <= 小于等于号      v
  TK_GT,         // > 大于号
  TK_GEQ,        // >= 大于等于号      v
  TK_ASSIGN,     // = 赋值运算符
  TK_POINTSTO,   // -> 指向结构体成员运算符   v
  TK_DOT,        // . 结构体成员运算符
  TK_AND,        // & 地址与运算符
  TK_OPENPA,     // ( 左圆括号
  TK_CLOSEPA,    // ) 右圆括号
  TK_OPENBR,     // [ 左方括号
  TK_CLOSEBR,    // ] 右方括号
  TK_BEGIN,      // { 左花括号
  TK_END,        // } 右花括号
  TK_SEMICOLON,  // ; 分号
  TK_COMMA,      // , 逗号
  TK_VER_BAR,    // ｜ 竖线
  TK_EOF,        // 文件结束符
  TK_REF,        // // 注释
  /* 常量 */
  TK_CINT,   // 整型常量，浮点型赋值同一个Token
  TK_CCHAR,  // 字符常量
  TK_CSTR,   // 字符串常量
  /* 关键字 */
  KW_CHAR,      // char 关键字
  KW_SHORT,     // short关键字
  KW_INT,       //  int关键字
  KW_VOID,      // void关键字
  KW_STRUCT,    // struct关键字
  KW_IF,        // if关键字
  KW_ELSE,      // else关键字
  KW_FOR,       // for关键字
  KW_WHILE,     // while关键字
  KW_CONTINUE,  // continue关键字
  KW_BREAK,     // break关键字
  KW_RETURN,    // return关键字
  KW_SIZEOF,    // sizeof关键字
  KW_ALIGN,     // _align关键字
  KW_CDECL,     // _cdecl关键字 standard c call
  KW_STDCALL,   // __stdcall 关键字 pascal c call
  /* 标识符 */
  TK_IDENT_F,  // 函数名
  TK_IDENT_V   // 变量名
};

enum ErrorType {
  LEXING_SUCCESS,          // 执行语法分析
  // HASH_CONFLICT,  //哈希表冲突，采用unordered_map后无需担心
  APOSTROPHE_ERROR, // 缺少右单引号
  ESCAPE_CHAR_ERROR,  // 转义字符错误
  UNKNOWN_SYMBOL,  // 出现未知符号
  QUOTES_ERROR, // 缺少右双引号
  ELSE_ERROR,  // 其他错误
};

typedef struct Token {
  int token;
  std::string s;
  int row;
} TokenWord, *pTokenWord;

// 词法分析
void InitializeHashMap();
void Print(std::string ch, int token);
void SplitRowIntoUnit(std::vector<TokenWord> &unit,const std::string str, int row);
void MergeUnit(std::vector<TokenWord> &unit);

// 语法分析
void Compile(std::vector<TokenWord> unit);
