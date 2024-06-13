/*
** 9.42-9.43 Trie 树插入删除和查找
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_SIZE      20

/* Trie节点结构 */
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode, *TrieNodePtr;



/* 创建一个新的 Trie 节点 */
TrieNodePtr
GetNode(void)
{
    int i;
    TrieNodePtr pNode = (TrieNode *)malloc(sizeof(TrieNode));
    pNode->isEndOfWord = false;
    for (i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}



/* 插入一个键到Trie */
void
Insert(TrieNodePtr root, char *key)
{
    TrieNodePtr pCrawl = root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = GetNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}



/* 查找键在Trie中是否存在 */
bool
Search(TrieNode *root, char *key)
{
    TrieNode *pCrawl = root;
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}



/* 检查节点是否没有子节点 */
bool
isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}



/* 递归删除键 */
TrieNodePtr
RemoveKey(TrieNode* root, const char* key, int depth)
{
    if (!root)
        return NULL;

    /* 如果到达键的末尾 */
    if (depth == strlen(key)) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        /* 如果节点没有子节点，则删除它 */
        if (isEmpty(root)) {
            free(root);
            root = NULL;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = RemoveKey(root->children[index], key, depth + 1);

    /* 如果 root 不是键的末尾，并且 root 没有子节点，则删除 root */
    if (isEmpty(root) && root->isEndOfWord == false) {
        free(root);
        root = NULL;
    }
    return root;
}



int
main(void)
{
    int oper;
    char ch[MAX_SIZE];

    TrieNodePtr root = GetNode();

    while (scanf("%d%s", &oper, ch) == 2) {
        switch (oper) {
            case 1:
                Insert(root, ch);
                break;
            case 2:
                RemoveKey(root, ch, 0);
                break;
            case 3:
                printf(Search(root, ch) ? "True" : "False");
                printf("\n");
                break;
        }
    }
    return 0;
}