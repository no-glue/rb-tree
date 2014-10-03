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
      insert_case1(my_grandparent, root);
    } else {
      insert_case4(inserted, root);
    }
  }
  void insert_case4(Node * inserted, Node * & root) {
    // put things in right place, do rotations
    Node * my_grandparent = grandparent(inserted);
    if(!my_grandparent) return;
    if(inserted == inserted->parent->right && inserted->parent == my_grandparent->left) {
      rotate_with_right_child(inserted->parent, root); // todo rotate with right ch
      inserted = inserted->left;
    } else if(inserted == inserted->parent->left && inserted->parent == my_grandparent->right) {
      rotate_with_left_child(inserted->parent, root); // todo rotate with left ch
      inserted = inserted->right;
    }
    insert_case5(inserted, root);
  }
  void insert_case5(Node * inserted, Node * & root) {
    // adjust colors and do rotations again
    Node * my_grandparent(inserted);
    if(!my_grandparent) return;
    inserted->parent->red = false;
    my_grandparent->red = true;
    if(inserted == inserted->parent->left && inserted->parent == my_grandparent->left) {
      rotate_with_left_child(my_grandparent, root);
    } else if(inserted == inserted->parent->right && inserted->parent == my_grandparent->right) {
      rotate_with_right_child(my_grandparent, root);
    }
  }
  void remove(Str key, Node * & root) {
    // remove node from tree
    Node * there = find(key, root), * child, * predecessor;
    if(!there) return;
    if(there->left && there->right) {
      predecessor = max_key(there->left);
      if(!predecessor) return;
      there->key = predecessor->key;
      there->value = predecessor->value;
      there = predecessor;
    }
    if(!there->left || !there->right) {} else return;
    child = (!there->right) ? there->left : there->right;
    if(!is_red(there)) {
      there->red = is_red(child);
      // delete_case1
    }
    replace(there, child, root);
    if(!there->parent && child) child->red = false;
    // child is root
    delete there;
  }
  void rotate_with_right_child(Node * & inserted, Node * & root) {
    // rotate with right child
    Node * return_node = inserted->right;
    replace(inserted, return_node, root);
    inserted->right = return_node->left;
    return_node->left = inserted;
    inserted->parent = return_node;
    inserted = return_node;
  }
  void rotate_with_left_child(Node * & inserted, Node * & root) {
    // rotate with left child
    Node * return_node = inserted->left;
    replace(inserted, return_node, root);
    inserted->left = return_node->right;
    return_node->right = inserted;
    inserted->parent = return_node;
    inserted = return_node;
  }
  void replace(Node * prev_child, Node * current_child, Node * & root) {
    // replace child
    if(!prev_child->parent) root = current_child;
    else {
      if(prev_child == prev_child->parent->left) prev_child->parent->left = current_child;
      else prev_child->parent->right = current_child;
    }
    if(current_child) current_child->parent = prev_child->parent;
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
  Node * max_key(Node * inserted) {
    // get max key
    if(!inserted) return NULL;
    while(inserted->right) inserted = inserted->right;
    return inserted;
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
      if(key < to_look->key) to_look = to_look->left;
      else to_look = to_look->right;
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