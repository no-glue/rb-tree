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
  bool red;
  // is node red
  bool visited;
  // is node visited, useful when searching
  RedBlackNode(Str key, Str init_value):key(key), left(NULL), right(NULL), parent(NULL), red(true), visited(false) {
    // set up bare bones node
    value.push_back(init_value);
  }
  RedBlackNode(Str key, Str init_value, bool red):key(key), left(NULL), right(NULL), parent(NULL), red(red), visited(false) {
    // set up bare bones node
    value.push_back(init_value);
  }
  RedBlackNode(Str key, Str init_value, RedBlackNode * left, RedBlackNode * right, RedBlackNode * parent, bool red, bool visited):key(key), left(left), right(right), parent(parent), red(red), visited(visited) {
    // set up node
    value.push_back(init_value);
  }
};