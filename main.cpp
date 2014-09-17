#include <iostream>
#include <string>
#include <vector>
#include "red_black_node.h"
#include "red_black_tree.h"

using namespace std;

int main() {
  RedBlackTree<RedBlackNode<string, vector<string> >, string> * tree = new RedBlackTree<RedBlackNode<string, vector<string> >, string>();
  RedBlackNode<string, vector<string> > * found;
  tree->insert("a", "a");
  tree->insert("b", "b");
  tree->insert("c", "c");
  tree->insert("d", "d");
  tree->insert("e", "e");
  found = tree->find("e");
  cout<<"found "<<found->value[0]<<endl;
  delete tree;
  return 0;
}