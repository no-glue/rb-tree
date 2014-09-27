template<typename Str, typename VectorString>class RedBlackNode {
public:
  Str key;
  // key to index a value
  VectorString value;
  // values for a key
  RedBlackNode * left;
  // left child
  RedBlackNode * right;
  // right child
  RedBlackNode * parent;
  // node's parent
  unsigned char color;
  // 0 red, 1 black
  bool visited;
  // is node visited, useful when searching
  RedBlackNode(Str key, Str init_value):key(key), left(NULL), right(NULL), parent(NULL), color(true), visited(0) {
    // set up bare bones node
    value.push_back(init_value);
  }
  RedBlackNode(Str key, Str init_value, unsigned char color):key(key), left(NULL), right(NULL), parent(NULL), color(color), visited(false) {
    // set up bare bones node
    value.push_back(init_value);
  }
  RedBlackNode(Str key, Str init_value, RedBlackNode * left, RedBlackNode * right, RedBlackNode * parent, unsigned char color, bool visited):key(key), left(left), right(right), parent(parent), color(color), visited(visited) {
    // set up node
    value.push_back(init_value);
  }
};