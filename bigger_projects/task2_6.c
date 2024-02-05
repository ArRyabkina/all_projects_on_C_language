#include <stdio.h>
#include <stdlib.h>

struct Node {
    unsigned long long data;
    struct Node* left;
    struct Node* right;
};

unsigned long long stringToUnsignedInt(const char* str) {
    unsigned long long result = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
        i++;
    }

    return result;
}

struct Node* createNode(unsigned long long value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, unsigned long long value) {
    if (root == NULL) {
        return createNode(value);
    }
    else if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else {
        root->right = insert(root->right, value);
    }
    return root;
}

void deleteTree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%llu ", root->data);
        inOrderTraversal(root->right);
    }
}

struct Node* search(struct Node* root, unsigned long long value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (value < root->data) {
        return search(root->left, value);
    }
    return search(root->right, value);
}

struct Node* findMin(struct Node* root) {
    if (root == NULL) {
        return NULL;
    } else if (root->left == NULL) {
        return root;
    } else {
        return findMin(root->left);
    }
}

struct Node* deleteNode(struct Node* root, unsigned long long value) {
    if (root == NULL) {
        return root;
    } else if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            struct Node* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            struct Node* temp = root;
            root = root->left;
            free(temp);
        } else {
            struct Node* minRight = findMin(root->right);
            root->data = minRight->data;
            root->right = deleteNode(root->right, minRight->data);
        }
    }
    return root;
}

int main() {
    struct Node* root = NULL;
	unsigned long long number;
	char str[20000];
	struct Node* result;
	char c, not_end = 1;
    while(scanf("%s", str) == 1) {
			c = str[0];
			number = stringToUnsignedInt(str);
			result = search(root, number);
			if (c == '+') {
				if (result == NULL) {
					root = insert(root, number);
				}
			} else if (c == '-') {
				if (result) {
					root = deleteNode(root, number);
				}
			} else {
				if (result) {
					printf("\nyes");
				} else {
					printf("\nno");
				}
			}
	}
   
    // Печать дерева поиска
    inOrderTraversal(root);
    printf("\n");
    
	deleteTree(root);
    root = NULL;
    return 0;
}
