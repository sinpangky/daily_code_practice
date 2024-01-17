int split(vector<string> &word, const string str) {
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == 34) {
      string temp;
      temp.push_back(str[i]);
      i++;
      while (str[i] != 34) {
        temp.push_back(str[i]);
        i++;
      }
      temp.push_back(str[i]);
      word.push_back(temp);
    } else if (ispunct(str[i]) || str[i] == '\\') {
      string temp;
      temp.push_back(str[i]);
      word.push_back(temp);
    } else if (isdigit(str[i])) {
      string temp;
      while (isdigit(str[i])) {
        temp.push_back(str[i]);
        ++i;
      }
      if (str[i] == '.') {
        ++i;
        if (isdigit(str[i])) {
          temp.push_back('.');
          while (isdigit(str[i])) {
            temp.push_back(str[i]);
            i++;
          }
        } else {
          return -1;
        }
      }
      word.push_back(temp);
      --i;
    } else if (isalpha(str[i])) {
      string temp;
      while (isalnum(str[i])) {
        temp.push_back(str[i]);
        i++;
      }
      word.push_back(temp);
      --i;
    } else if (str[i] == '\t') {
      string temp = "    ";
      word.push_back(temp);
    }
  }
}