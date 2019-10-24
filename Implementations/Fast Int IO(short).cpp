#ifdef _WIN32
    char next_char() {return _getchar_nolock();}
#else
    static const int BUFFSIZE = 1 << 14;
    char buf[BUFFSIZE];
    int sz = BUFFSIZE - 1;
    char next_char()
    {
        if (sz == BUFFSIZE - 1) {
            fread_unlocked(buf, sizeof(char), BUFFSIZE, stdin);
            sz = -1;
        }
        return buf[++sz];
    }
#endif

int read_int()
{
    int ans = 0;
    for (char c = next_char(); c >= '0'; c = next_char())
    {
        ans = 10 * ans + c - '0';
    }
    return ans;
}