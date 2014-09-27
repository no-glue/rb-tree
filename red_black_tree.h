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
    Node * inserted_node = new Node(key, value);
    bool inserted = tree_insert(inserted_node, root);
    if(inserted) insert_fixup_for(inserted_node, root); // todo insert_fixup_for
  }
  bool tree_insert(Node * inserted_node, Node * & root) {
    // scan the tree, insert node
    Node * parent = tree_find_last(inserted_node->key, root);
    return tree_insert_child(parent, inserted_node, root);
  }
  Node * tree_find_last(Str key, Node * & root) {
    // find place to insert new node
    Node * walk = root, * previous = NULL;
    while(walk) {
      previous = walk;
      if(key < walk->key && (walk = walk->left)) {}
      else if(key > walk->key && (walk = walk->right)) {}
      else return walk;
    }
    return previous;
  }
  bool tree_insert_child(Node * parent, Node * inserted_node, Node * & root) {
    // add child to parent
    if(!parent) root = inserted_node;
    else {
      if(inserted_node->key < parent->key) parent->left = inserted_node;
      else if(inserted_node->key > parent->key) parent->right = inserted_node;
      else return false;
    }
    inserted_node->parent = parent;
    return true;
  }
  void insert_fixup_for(Node * inserted_node, Node * & root) {
    // fixup for inserted node
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