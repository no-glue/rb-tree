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
  void insert_fixup(Node * leaf, Node * & root) {
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
  void remove(Str key, Node * & root) {
    // remove node from tree
    Node * to_remove = find(key, root), *successor, *child;
    if(to_remove) {
      if(!to_remove->left || !to_remove->right) successor = to_remove;
      else successor = successor(to_remove); // todo successor
      if(successor->left) child = successor->left;
      else child = successor->right;
      child->parent = successor->parent;
      if(!successor->parent) root = child;
      else {
        if(successor == successor->parent->left) {
          // if successor is left child
          successor->parent->left = child;
        } else {
          // if successor is right child
          successor->parent->right = child;
        }
      }
      if(child != to_remove) {
        to_remove->key = successor->key;
        to_remove->value = successor->value;
      }
      if(!successor->color) remove_fixup(child, root);
    }
  }
  void remove_fixup(Node * leaf, Node * & root) {
    // fixup after node removed
    Node * child;
    while(leaf != root && !leaf->color) {
      if(leaf == leaf->parent->left) {
        // leaf is on the left
        child = leaf->parent->right;
        // child is on the right
        if(child->color) {
          child->color = false;
          leaf->parent->color = true;
          left_rotate(leaf->parent, root);
          child = leaf->parent->right;
        }
        if(!child->left->color && !child->right->color) {
          child->color = true;
          leaf = leaf->parent;
        } else {
          if(!child->right->color) {
            child->left->color = false;
            child->color = true;
            right_rotate(child, root);
            child = leaf->parent->right;
          }
          child->color = leaf->parent->color;
          leaf->parent->color = false;
          child->right->color = false;
          left_rotate(leaf->parent, root);
          leaf = root;
        }
      } else {
        // leaf is on the right
        child = leaf->parent->left;
        // child is on the left
        if(child->color) {
          child->color = false;
          leaf->parent->color = true;
          right_rotate(leaf->parent, root);
          child  = leaf->parent->left;
        }
        if(!child->left->color && !child->right->color) {
          child->color = true;
          leaf = leaf->parent;
        } else {
          if(!child->left->color) {
            child->right->color = false;
            child->color = true;
            left_rotate(child, root);
            child = leaf->parent->left;
          }
          child->color = leaf->parent->color;
          leaf->parent->color = false;
          child->left->color = false;
          right_rotate(leaf->parent, root);
          leaf = root;
        }
      }
    }
    leaf->color = false;
  }
  void left_rotate(Node * leaf, Node * & root) {
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
  void right_rotate(Node * leaf, Node * & root) {
    // rotate to right, with left child
    Node * return_node = leaf->left;
    leaf->left = return_node->right;
    if(return_node->right) return_node->right->parent = leaf;
    return_node->parent = leaf->parent;
    if(!leaf->parent) root = return_node;
    else if(leaf == leaf->parent->right) leaf->parent->right = return_node;
    else leaf->parent->left = return_node;
    return_node->right = leaf;
    leaf->parent = return_node;
  }
  Node * successor(Node * subject) {
    // find node successor
    if(subject->right) return tree_min(subject); // todo tree_min
    Node * temp = subject->parent;
    while(temp && subject == temp->right) {
      subject = temp;
      temp = temp->parent;
    }
    return temp;
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