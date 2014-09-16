template<typename Str, class Ostream>class DecoratorMessage {
  public:
    Ostream & stream;
    DecoratorMessage(Ostream & stream):stream(stream) {}
    void message(Str m) {
      // show message
      stream<<m<<"\n";
    }
};