#include <stdio.h>

class TreeNode {
public:
    TreeNode(int x) {
        left = NULL;
        right = NULL;
        val = x;
    }

    int val;
    TreeNode* left;
    TreeNode* right;
};

void printTree_inorder(TreeNode* root)
{
    if (root == NULL)
        return;

    if (root->left)
        printTree_inorder(root->left);

    printf("%d ", root->val);
    
    if (root->right)
        printTree_inorder(root->right);
}

void treeInsert(TreeNode* root, int val) {
    if (val > root->val) {
        if (root->right)
            return treeInsert(root->right, val);
        root->right = new TreeNode(val);
        return;
    } else {
        if (root->left)
            return treeInsert(root->left, val);
        root->left = new TreeNode(val);
    }
}

void morrisTraverse_inorder(TreeNode* root)
{
    TreeNode* curr = root;

    while (curr) {
        if (curr->left == NULL) {
            printf("%d ", curr->val);
            curr = curr->right;
            continue;
        }

        TreeNode* p = curr->left;
        while (p->right != NULL && p->right != curr)
            p = p->right;

        if (p->right == NULL) {
            p->right = curr;
            curr = curr->left;
        } else {
            printf("%d ", curr->val);
            p->right = NULL;
            curr = curr->right;
        }
    }
}

void morrisTraverse_preorder(TreeNode* root)
{
    TreeNode* curr = root;
    
    while (curr) {
        if (curr->left == NULL) {
            printf("%d ", curr->val);
            curr = curr->right;
            continue;
        }

        TreeNode* p = curr->left;
        while (p->right != NULL && p->right != curr)
            p = p->right;

        if (p->right == NULL) {
            printf("%d ", curr->val);
            p->right = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
            p->right = NULL;
        }
    }
}

int main()
{
    TreeNode* root = new TreeNode(6);
    treeInsert(root, 2);
    treeInsert(root, 1);
    treeInsert(root, 4);
    treeInsert(root, 3);
    treeInsert(root, 5);
    treeInsert(root, 7);
    treeInsert(root, 9);
    treeInsert(root, 8);


    morrisTraverse_preorder(root);
    printf("\n");

    printTree_inorder(root);
    printf("\n");

    return 0;
}
