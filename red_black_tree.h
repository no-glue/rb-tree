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
    if(!root) {
      root = new Node(key, value, false);
      return;
    }
    current = new Node(key, value);
    grand = NULL;
    great = current;
    great->right = root;
    parent = NULL;
    Node * walk = great.rigth;
    int direction = 0, direction_great = 0, last = 0;
    // direction 0 left, 1 right
    while(true) {
      if(!walk) {
        walk = new Node(key, value);
        if(direction) parent->right = walk; else parent->left = walk;
      } else if(walk->left->color && walk->right->color) {
        // color flip, make parent red and children black
        walk->color = true;
        walk->left->color = walk->right->color = false;
      }
      if(walk->color && parent->color) {
        // fix red violation
        if(great->right == grand) direction_great = 1; else direction_great = 0;
        if((last && parent->right == walk) || (!last && parent->left == walk)) {
          single_rotation(great, grand); // todo single_rotation
        } else {
          double_rotation(great, grand); // todo double_rotation
        }
      }
      if(key == walk->key) {walk->value.push_back(value); return;}
      last = direction;
      direction = (key < walk->key) ? 0 : 1;
      if(grand) great = grand;
      grand = parent;
      parent = walk;
      walk = (direction) walk->right : walk->left;
    }
    root = current->right;
    root->color = false;
  }
  void handle_reorient(Str key, Node * & root, Node * & current, Node * & parent, Node * & grand, Node * & great) {
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