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
    Node * inserted = new Node(key, value), * walk = root, * previous;
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
    Node * uncle;
    while(inserted->parent->red) {
      if(inserted->parent == inserted->parent->parent->left) {
        // parent is on the left, uncle is on the right
        uncle = inserted->parent->parent->right;
        if(uncle->red) {
          // case 1, parent and uncle of inserted are red
          inserted->parent->red = uncle->red = false;
          inserted->parent->parent->red = true;
          inserted = inserted->parent->parent;
        } else {
          if(inserted == inserted->parent->right) {
            // case 2 inserted is on the right side and uncle is red, need to rotate with right child
            inserted = inserted->parent;
            rotate_with_right_child(inserted); 
          }
          inserted->parent->red = false;
          inserted->parent->parent->red = true;
          rotate_with_left_child(inserted->parent->parent);
        }
      } else {
        uncle = inserted->parent->parent->left;
      }
    }
  }
  void rotate_with_left_child(Node * inserted) {
    // rotate with left child, to right
    // todo change this
    Node * return_node = inserted->left;
    transplant(inserted, return_node);
    left_child(inserted, return_node->right);
    right_child(return_node, inserted);
    // left side is unchanged
  }
  void rotate_with_right_child(Node * inserted) {
    // rotate with right child, to left
    // todo change this
    Node * return_node = inserted->right;
    transplant(inserted, return_node);
    right_child(inserted, return_node->left); // todo right_child
    left_child(return_node, inserted); // todo left_child
    // right side is unchanged
  }
  void transplant(Node * inserted, Node * child) {
    // add child to parent
    // todo change this
    if(inserted == inserted->parent->left) left_child(inserted->parent, child);
    else right_child(inserted->parent, child);
  }
  void left_child(Node * parent, Node * child) {
    // set left child
    parent->left = child;
    child->parent = parent;
  }
  void right_child(Node * parent, Node * child) {
    // set right child
    parent->right = child;
    child->parent = parent;
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
      if(root->left) make_empty(root->left);
      if(root->right) make_empty(root->right);
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