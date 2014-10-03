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
  void remove(Str key) {
    // remove node from tree
    remove(key, root);
  }
  Node * find(Str key) {
    // find a node givem a key
    return find(key, root);
  }
  Node * get_root() {
    // get root
    return root;
  }
private:
  Node * root;
  void insert(Str key, Str value, Node * & root) {
    // insert key and value to the tree
    Node * inserted = new Node(key, value), * walk = root;
    if(!root) {
      root = inserted;
    } else {
      while(true) {
        if(key == walk->key) {
          walk->value.push_back(value);
          return;
        } else if(key < walk->key) {
          if(!walk->left) {
            walk->left = inserted;
            break;
          } else walk = walk->left;
        } else {
          if(!walk->right) {
            walk->right = inserted;
            break;
          }
          else walk = walk->right;
        }
      }
      inserted->parent = walk;
    }
    insert_case1(inserted, root);
  }
  void insert_case1(Node * inserted, Node * & root) {
    // there is only root
    if(!inserted->parent) inserted->red = false;
    else {
      insert_case2(inserted, root);
    }
  }
  void insert_case2(Node * inserted, Node * & root) {
    // parent is black, single child
    if(!is_red(inserted->parent)) return;
    else {
      insert_case3(inserted, root);
    }
  }
  void insert_case3(Node * inserted, Node * & root) {
    // parent and uncle are red, flip colors
    Node * my_uncle = uncle(inserted), * my_grandparent = grandparent(inserted);
    if(!my_uncle || !my_grandparent) return;
    // if there is no uncle or grandparent don't do anything
    if(is_red(my_uncle)) {
      inserted->parent->red = false;
      my_uncle->red = false;
      my_grandparent->red = true;
      insert_case1(inserted, my_grandparent);
    } else {
      // insert case 4
    }
  }
  bool is_red(Node * inserted) {
    // see if node is red
    return (inserted) ? inserted->red : false;
  }
  Node * uncle(Node * inserted) {
    // get uncle
    if(!inserted) return NULL;
    if(!inserted->parent) return NULL;
    if(!inserted->parent->parent) return NULL;
    return brother(inserted->parent);
  }
  Node * brother(Node * inserted) {
    // get brother
    if(!inserted) return NULL;
    if(!inserted->parent) return NULL;
    return (inserted == inserted->parent->left) ? inserted->parent->right : inserted->parent->left;
  }
  Node * grandparent(Node * inserted) {
    // grandparent
    if(!inserted) return NULL;
    if(!inserted->parent) return NULL;
    if(!inserted->parent->parent) return NULL;
    return inserted->parent->parent;
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