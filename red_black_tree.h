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
  void insert(Str key, Str value, Node * & root) {
    // insert key and value
    Node * inserted = new Node(key, value), * walk, * previous;
    if(!root) {
      inserted->red = false;
      root = inserted;
      return;
    }
    while(walk) {
      previous = walk;
      if(key < walk->key) walk = walk->left;
      else if(key > walk->key) walk = walk->right;
      else {walk->value.push_back(value); return;}
    }
    inserted->parent = previous;
    if(inserted->key < inserted->parent->key) inserted->parent->left = inserted;
    else inserted->parent->right = inserted;
    insert_fixup_for(inserted, root); // todo insert_fixup_for
  }
  void insert_fixup_for(Node * inserted, Node * & root) {
    // fixup tree for new node
    // todo change this
  }
  void rotate_with_left_child(Node * inserted, Node * & root) {
    // rotate with left child, to right
    // todo change this
    // left side is unchanged
  }
  void rotate_with_right_child(Node * inserted, Node * & root) {
    // rotate with right child, to left
    // todo change this
    // right side is unchanged
  }
  void transplant(Node * inserted, Node * child) {
    // add child to parent
    // todo change this
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