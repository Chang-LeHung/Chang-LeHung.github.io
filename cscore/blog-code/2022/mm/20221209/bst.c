

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define type char

/* 定义树的节点 */
struct TreeNode
{
    type data;
    int cnt;
    struct TreeNode* left;
    struct TreeNode* right;
};

/* 往树中加入一个新的节点 */
struct TreeNode* insert(struct TreeNode* root, type x)
{
    if(root == NULL)
    {
        // 申请节点的内存空间
        root = malloc(sizeof(struct TreeNode));
        root->data = x;
        root->cnt = 1;
        root->left = root->right = NULL;
    }
    else if(x < root->data)
        root->left = insert(root->left, x);
    else if(x > root->data)
        root->right = insert(root->right, x);
    else
        root->cnt++;
    return root;
}

/* 寻找对应的删除点 右子树的左子树的最小值*/
struct TreeNode* findMin(struct TreeNode* root)
{
    if(root == NULL)
    	return NULL;
    else if(root->left == NULL)
    	return root;
    else
    	return findMin(root->left);
}

struct TreeNode* findMax(struct TreeNode* root)
{
    if(root == NULL)
    	return NULL;
    else if(root->right == NULL)
    	return root;
    else
    	return findMax(root->right);
}

struct TreeNode* find(struct TreeNode* root, type x)
{
    if(root == NULL)
        return NULL;
    else if(x < root->data)
        return find(root->left, x);
    else if(x > root->data)
        return find(root->right, x);
    else
        return root;
}

/* 计算树的高度 */
int findHeight(struct TreeNode* root)
{
    int lefth, righth;
    if(root == NULL)
        return -1;
    lefth = findHeight(root->left);
    righth = findHeight(root->right);
    return (lefth > righth ? lefth : righth)+1;
}

/* 从树当中删除一个节点 */
struct TreeNode* delete(struct TreeNode* root, type x)
{
    struct TreeNode* temp;
    if(root == NULL)
        return NULL;
    else if(x < root->data)
        root->left = delete(root->left, x);
    else if(x > root->data)
        root->right = delete(root->right, x);
    else if(root->left && root->right)
    {
        // 如果左右子树都不为空 则寻找右子树的最小值 将其替换当前节点的值
        temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, root->data);
    }
    else
    {
        // 如果左右子树不全为非空
        temp = root;
        if(root->left == NULL)
            root = root->right;
        else if(root->right == NULL)
            root = root->left;
        free(temp);
    }
    return root;
}

/* 中序遍历二叉搜索树 */
void inorder(struct TreeNode* root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    printf("char = %c cnt = %d\n", root->data, root->cnt);
    inorder(root->right);
}

int main()
{
    struct TreeNode *root;
    struct TreeNode *temp;
    root = NULL;
    char str[1024];
    scanf("%s", str);
    printf("size of str = %ld\n", strlen(str));
    for(int i = 0; i < strlen(str); ++i)
    {
      root = insert(root, str[i]);
    }
    inorder(root);
    return 0;
}
