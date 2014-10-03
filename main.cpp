#include <iostream>
#include <string>
#include <vector>
#include "red_black_node.h"
#include "red_black_tree.h"

using namespace std;

int main() {
  RedBlackTree<RedBlackNode<string, vector<string> >, string> * tree = new RedBlackTree<RedBlackNode<string, vector<string> >, string>();
  RedBlackNode<string, vector<string> > * root;
  RedBlackNode<string, vector<string> > * found;
  string value;
  tree->insert("a", "a");
  tree->insert("b", "b");
  tree->insert("c", "c");
  tree->insert("d", "d");
  tree->insert("e", "e");
  tree->insert("f", "f");
  tree->insert("g", "g");
  tree->insert("h", "h");
  tree->insert("i", "i");
  tree->insert("j", "j");
  tree->insert("k", "k");
  tree->insert("l", "l");
  tree->insert("m", "m");
  tree->insert("n", "n");
  tree->insert("o", "o");
  tree->insert("p", "p");
  root = tree->get_root();
  cout<<"root red "<<root->red<<endl;
  found = tree->find("g");
  cout<<"found "<<found->value[0]<<endl;
  tree->remove("g");
  found = tree->find("g");
  value = (found) ? found->value[0] : "no";
  cout<<"found "<<value<<endl;
  // funny thing infinite loop without balance
  delete tree;
  return 0;
}