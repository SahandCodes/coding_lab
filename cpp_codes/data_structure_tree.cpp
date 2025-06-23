#include <iostream>
#include <memory>
#include <queue>
#include <vector>

struct BinaryTreeNode {
  BinaryTreeNode(int val) : value{val} {}

  int value;
  std::unique_ptr<BinaryTreeNode> left;
  std::unique_ptr<BinaryTreeNode> right;
};

struct TreeNode {
  TreeNode(int val) : value{val} {}

  int value;
  std::vector<std::shared_ptr<TreeNode>> children;
};

void printBinaryTree(BinaryTreeNode* node, int depth = 0) {
  if (!node) return;
  for (size_t i = 0; i < depth; ++i) std::cout << "  ";
  std::cout << node->value << std::endl;
  printBinaryTree(node->left.get(), depth + 1);
  printBinaryTree(node->right.get(), depth + 1);
}

void printTree(const TreeNode* node, int depth = 0) {
  if (!node) return;
  for (size_t i = 0; i < depth; ++i) std::cout << " ";
  std::cout << node->value << std::endl;
  for (const auto& child : node->children) {
    printTree(child.get(), depth + 1);
  }
}

// 1. Create binary tree
std::unique_ptr<BinaryTreeNode> makeBinaryTree() {
  auto root = std::make_unique<BinaryTreeNode>(1);
  root->left = std::make_unique<BinaryTreeNode>(2);
  root->right = std::make_unique<BinaryTreeNode>(3);
  root->right->left = std::make_unique<BinaryTreeNode>(4);

  printBinaryTree(root.get());
  return root;
}

// 2. Create  tree
std::unique_ptr<TreeNode> makeTree() {
  auto root = std::make_unique<TreeNode>(0);
  root->children.push_back(std::make_unique<TreeNode>(1));
  root->children.push_back(std::make_unique<TreeNode>(2));
  root->children.push_back(std::make_unique<TreeNode>(3));
  root->children[0]->children.push_back(std::make_unique<TreeNode>(5));

  printTree(root.get());
  return root;
}

// 3. DFS for binary tree
void dfsForBinaryTree(const BinaryTreeNode* node) {
  if (!node) return;
  std::cout << node->value << "  ";
  dfsForBinaryTree(node->left.get());
  dfsForBinaryTree(node->right.get());
}

// 4. BFS for binary tree
void bfsForBinaryTree(const BinaryTreeNode* root) {
  if (!root) return;
  std::queue<const BinaryTreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    const BinaryTreeNode* curr = q.front();
    q.pop();
    std::cout << curr->value << " ";
    if (curr->left) q.push(curr->left.get());
    if (curr->right) q.push(curr->right.get());
  }
}

// 5. DFS for tree
void dfsForTree(const TreeNode* node) {
  if (!node) return;
  std::cout << node->value << " ";
  for (const auto& child : node->children) {
    dfsForTree(child.get());
  }
}

// 6. BFS for tree
void bfsForTree(const TreeNode* root) {
  if (!root) return;
  std::queue<const TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    const TreeNode* curr = q.front();
    q.pop();
    std::cout << curr->value << " ";
    for (const auto& child : curr->children) {
      q.push(child.get());
    }
  }
}

int main() {
  // 1. Create binary tree
  std::cout << "1. Create binary tree" << std::endl;
  auto binaryTree = makeBinaryTree();

  // 2. Create tree
  std::cout << std::endl << "2. Create tree" << std::endl;
  auto tree = makeTree();

  // 3. DFS for binary tree
  std::cout << std::endl
            << "3. Depth-First search for binary tree" << std::endl;
  dfsForBinaryTree(binaryTree.get());
  std::cout << std::endl;

  // 4. BFS for binary tree
  std::cout << std::endl
            << "4. Breadth-First search for binary tree" << std::endl;
  bfsForBinaryTree(binaryTree.get());
  std::cout << std::endl;

  // 5. DFS for tree
  std::cout << std::endl << "5. Depth-First search for tree" << std::endl;
  dfsForTree(tree.get());
  std::cout << std::endl;

  // 6. BFS for tree
  std::cout << std::endl << "6. Breadth-First search for tree" << std::endl;
  bfsForTree(tree.get());
  std::cout << std::endl;
}
