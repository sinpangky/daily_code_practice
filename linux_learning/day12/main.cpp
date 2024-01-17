#include "compiler.h"
using namespace std;

vector<TokenWord> unit;
int row_cnt = 0;
jmp_buf env;
int comment_flag = 0;
unordered_map<string, int> keyword_map;

int main() {
  InitializeHashMap();

  // 读取文件
  string file_name =
      "/Users/cpq/Desktop/Cpp/cpp_learning/wang_dao_Linux/day12/example.c";
  ifstream file(file_name);
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return -1;
  }

  // 开始一行一行读文件内容
  string line;
  while (getline(file, line)) {
    row_cnt++;
    if (line.empty()) continue;
    // 切割句子放入不同的单元，为后面赋token值做准备，放入初始token
    SplitRowIntoUnit(unit, line, row_cnt);
  }

  // 根据vector<TokenWord> unit来进行token二次分配，包括unit中运算符的合并
  MergeUnit(unit);

  // 重新从开头遍历文件，并根据token值输出不同颜色
  file.clear();   
  file.seekg(0, ios::beg);
  row_cnt = 0;
  vector<TokenWord>::iterator it = unit.begin();
  while (getline(file, line)) {
    row_cnt++;
    int i =0;
    while(i!=line.size()) {
      if (line[i] == ' ' || line[i] == '\t') {
        cout << " ";
        i++;
      } else {
        Print(it->s, it->token);
        i = i + (it->s).size() ;
        if(distance(it,unit.end())>1)
          ++it;
      }
      
    }
    cout << "\n";
  }

  // 关闭文件
  file.close();
  /* 词法分析阶段+报错 */
  // string res;
  int jmp_val = setjmp(env);
  // switch (jmp_val) {
  //   // case HASH_CONFLICT: {
  //   //   cout<< "hash表初始化冲突" <<"\n"<< endl;
  //   //   break;
  //   // }
  //   case LEXING_SUCCESS:
  //     Compile(unit);  // 语法分析开始
  //   default:
  //     res = "\n==========成功 1 个，失败 0 个，跳过 0 个==========\n";
  // }

  return 0;
}