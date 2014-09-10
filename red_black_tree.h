template<class Node, typename Str>class RedBlackTree {
public:
  RedBlackTree():root(NULL) {}
  ~RedBlackTree() {
    make_empty(root); // todo make empty
    delete root;
  }
  void insert(Str key, Str value) {
    // insert key and value
    insert(key, value, root);
  }
private:
  Node * root;
  void insert(Str key, Str value, Node * & root) {
    // insert key and value to the tree
    Node * to_add = new Node(key, value);
    if(!root) {
      root = to_add;
    } else {
      Node * walk = root;
      while(walk) {
        to_add->parent = walk;
        if(key < walk->key) walk = walk->left;
        else if(key > walk->key) walk = walk->right;
        else {walk->value.push_back(value); return;}
      }
      if(key < to_add->parent->key) to_add->parent->left = to_add;
      else to_add->parent->right = to_add;
    }
    insert_fixup(to_add, root);
  }
  void insert_fixup(Node * & leaf, Node * & root) {
    // fix insert, bottom up
    Node * uncle;
    while(leaf->parent && leaf->parent->parent && leaf->parent->color) {
      if(leaf->parent == leaf->parent->parent->left) {
        // fix left side
        uncle = leaf->parent->parent->right;
        if(uncle && uncle->color) {
          // checks for red uncle case 1
          leaf->parent->color = uncle->color = false;
          leaf->parent->parent->color = true;
        } else if(leaf == leaf->parent->right) {
          // case 2
          leaf = leaf->parent;
          left_rotate(leaf, root);
          leaf->parent->color = false;
          leaf->parent->parent->color = true;
          right_rotate(leaf->parent->parent, root);
        } else {
          // case 3
          leaf->parent->color = false;
          leaf->parent->parent->color = true;
          right_rotate(leaf->parent->parent, root);
        }
      }
      if(leaf->parent == leaf->parent->parent->right) {
        // fix right side
        uncle = leaf->parent->parent->left;
        if(uncle && uncle->color) {
          // checks for red uncle case 1
          leaf->parent->color = uncle->color = false;
          leaf->parent->parent->color = true;
          leaf = leaf->parent->parent;
        } else if(leaf == leaf->parent->left) {
          // case 2
          leaf = leaf->parent;
          right_rotate(leaf, root);
          leaf->parent->color = false;
          leaf->parent->parent->color = true;
          left_rotate(leaf->parent->parent, root);
        } else {
          // case 3
          leaf->parent->color = false;
          leaf->parent->parent->color = true;
          left_rotate(leaf->parent->parent, root);
        }
      }
    }
    root->color = false;
  }
  void left_rotate(Node * & leaf, Node * & root) {
    // rotate to left, with right child
    Node * return_node = leaf->right;
    leaf->right = return_node->left;
    if(return_node->left) return_node->left->parent = leaf;
    return_node->parent = leaf->parent;
    if(!leaf->parent) root = return_node;
    else if(leaf == leaf->parent->left) leaf->parent->left = return_node;
    else leaf->parent->right = return_node;
    return_node->left = leaf;
    leaf->parent = return_node;
  }
  void right_rotate(Node * & leaf, Node * & root) {
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