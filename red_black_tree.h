template<class Node, typename Str>class RedBlackTree {
public:
  RedBlackTree():root(NULL) {}
  ~RedBlackTree() {
    make_empty(root);
    delete root;
  }
  void insert(Str key, Str value) {
    // insert key and value
    insert(key, value, root, current, parent, grand, great);
  }
  void remove(Str key) {
    // remove node from tree
    remove(key, root);
  }
  Node * find(Str key) {
    // find a node givem a key
    return find(key, root);
  }
private:
  Node * root;
  Node * current;
  // ... current, 
  // parent, 
  // grand, 
  // great 
  // used when inserting a node ...
  Node * parent;
  Node * grand;
  Node * great;
  void insert(Str key, Str value, Node * & root, Node * & current, Node * & parent, Node * & grand, Node * & great) {
    // insert key and value to the tree
    current = parent = grand = root;
    while(current && (current->key != key)) {
      great = grand; grand = parent; parent = current;
      current = key < current->key ? current->left : current->right;
      if(current && current->left->color && current->right->color) handle_reorient(key, value, root, current, parent, grand, great);
    }
    if(current) return;
    // current is there, nothing to do
    current = new Node(key, value);
    if(key < parent->key) parent->left = current;
    else parent->right = current;
    handle_reorient(key, value, root, current, parent, grand, great);
  }
  void handle_reorient(Str key, Str value, Node * & root, Node * & current, Node * & parent, Node * & grand, Node * & great) {
    // handle reorient
    current->color = true;
    current->left->color = false;
    current->right->color = false;
    // flip color
    if(parent->color) {
      // have to rotate
      grand->color = true;
      if(key < grand->key != key < parent->key) {
        parent = rotate(key, value, grand); // todo rotate(key, value, grand...)
        // do double rotate
      }
      current = rotate(item, great);
      current->color = false;
    }
    root->right->color = false;
    // make root black
  }
  void remove(Str key, Node * & root) {
    // remove node from tree
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
};
// Every node is either black or red
// Every leaf is black
// If a node is red both children are black
// Every path from node to leaf contains same number of black nodes
// Based on 2, 4 (2, 3, 4) tree
// logn time