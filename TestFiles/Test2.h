namespace Scanner
{
  class SemiExp : public ITokCollection
  {
  public:
    SemiExp(Toker* pToker = nullptr);
    SemiExp(const SemiExp&) = delete;
    SemiExp& operator=(const SemiExp&) = delete;
    bool get(bool clear = true);
    std::string& operator[](size_t n);
    std::string operator[](size_t n) const;
    size_t length();
    size_t find(const std::string& tok);
    void trimFront();
    void toLower();
    bool remove(const std::string& tok);
    bool remove(size_t n);
    void push_back(const std::string& tok);
    void clear();
    bool isComment(const std::string& tok);
    std::string show(bool showNewLines = false);
    size_t currentLineCount();
  private:
    bool isTerminator(const std::string& tok);
    bool getHelper(bool clear = false);
    bool isSemiColonBetweenParens();
    bool hasFor = false;
    std::vector<std::string> _tokens;
    Toker* _pToker;
  };
}
#endif
