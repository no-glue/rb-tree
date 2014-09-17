#include <iostream>
#include <string>
#include <vector>
#include "red_black_node.h"
#include "red_black_tree.h"

using namespace std;

int main() {
  RedBlackTree<RedBlackNode<string, vector<string> >, string> * tree = new RedBlackTree<RedBlackNode<string, vector<string> >, string>();
  tree->insert("a", "a");
  tree->insert("b", "b");
  tree->insert("c", "c");
  tree->insert("d", "d");
  tree->insert("e", "e");
  delete tree;
  return 0;
}