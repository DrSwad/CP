// For windows system use getchar() instead of getchar_unlocked()
inline void input_string(string &s) {
  char ip;
  do {
    ip = getchar_unlocked();
  } while (ip < 'a' or ip > 'z');
  while (ip >= 'a' and ip <= 'z') {
    s.push_back(ip);
    ip = getchar_unlocked();
  }
}

// For windows system use getchar() instead of getchar_unlocked()
inline int input_int() {
  int ret = 0, flag = 1, ip = getchar_unlocked();
  for (; ip < 48 || ip > 57; ip = getchar_unlocked()) {
    if (ip == 45) {
      flag = -1;
      ip = getchar_unlocked();
      break;
    }
  }
  for (; ip > 47 && ip < 58; ip = getchar_unlocked())
    ret = ret * 10 + ip - 48;
  return flag * ret;
}