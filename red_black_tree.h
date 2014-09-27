template<class Node, typename Str>class RedBlackTree {
public:
  RedBlackTree():root(NULL) {}
  ~RedBlackTree() {
    make_empty(root);
    delete root;
  }
  void insert(Str key, Str value) {
    // insert key and value
    insert(key, value, root);
  }
  Node * find(Str key) {
    // find a node givem a key
    return find(key, root);
  }
private:
  Node * root;
  void insert(Str key, Str value) {
    // insert key and value
    Node * inserted_node = new Node(key, value);
    bool inserted = tree_insert(inserted_node); // todo insert_tree
    if(inserted) insert_fixup_for(inserted_node);
  }
  bool tree_insert(Node * inserted_node) {
    // scan the tree, insert node
    Node * parent = tree_find_last(inserted_node->key); // todo tree_find_last
    return tree_insert_child(parent, inserted_node); // todo tree_insert_child
  }
  Node * tree_find_last(Str key) {
    // find place to insert new node
  }
  bool tree_insert_child(Node * parent, Node * inserted_node) {
    // add child to parent
  }
  Node * find(Str key, Node * & root) {
    // find a node given a key
    Node * to_look = root;
    while(to_look) {
      if(key == to_look->key) return to_look;
      if(to_look->left && key < to_look->key) to_look = to_look->left;
      else if(to_look->right) to_look = to_look->right;
    }
    return NULL;
  }
  void make_empty(Node * & root) {
    // make tree empty
    if(root) {
      make_empty(root->left);
      make_empty(root->right);
      delete root;
    }
    root = NULL;
  }
};
// Every node is either black or red
// Every leaf is black
// If a node is red both children are black
// Every path from node to leaf contains same number of black nodes
// Based on 2, 4 (2, 3, 4) tree
// logn time