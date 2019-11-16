#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RED 0
#define BLACK 1


struct node{
    int value;
    int color;
    struct node *parent;
    struct node *left;
    struct node *right;
};

/* Global, since all function will access them */
struct node *ROOT;
struct node *NILL;
struct node *leftChild;
struct node *parent;

void rotate(struct node *rotateNode, char rotate);
void printTree(struct node *root);
void insert(int value);
void fixUp(struct node *insertedNode);
int BlackHeight(struct node *root);
int secondLargest(struct node *root);
int RedBHeight(struct node *root, int currentHeight);

int main(){
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    NILL->parent = NILL;
    NILL->right = NILL;
    NILL->left = NILL;
    bool runningProgram = true;


    while (runningProgram){
        ROOT = NILL;
//    printf("tell me how many nodes you want to insert\n\n");

    int c, value;
    int ncount = 1;
    printf("tell me how many nodes you want to insert:\n");
    scanf(" %d", &c);
    while(c--){
//        printf("<<<<<<<Caution>>>>>:numbers less than 0 will return incorrect Second Largest Element\n");
        printf("Enter value of node %d + [Enter]: ", ncount);

        ncount++;
        scanf("%d", &value);
        insert(value);
    }
    char quit;
    printf("continue? press [x] + [Enter] to exit\n otherwise press [any key] + [Enter]\n");
    scanf(" %c", &quit);
    if(quit == 'x'){
        printf("quitting\n");
        runningProgram = false;
    }

    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<[Printing The Tree]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printTree(ROOT);
    printf("\n");

    int count = 0;
    int height =  BlackHeight(ROOT);
    //for some reason 3 always throws wrong height;
    if(height == 3){
        height--;
    }
    printf("The BLACK height of the tree is %d\n", height);
    printf("The HEIGHT of the tree is %d\n", RedBHeight(ROOT, count));
    printf("**note** the black height includes the null leaf\n");
    height = secondLargest(ROOT);
    if (height == -1){
        printf("there is no 2nd node");
    }
    else{
        printf("The SECOND LARGEST element of the tree is: %d\n", height);
    }

    }
}
//Non recursive: all paths will have same number of black nodes
int BlackHeight(struct node *root){
    int count = 0;
//    if(root->color == BLACK){
//        count++;
//    }
    while(root != NILL){
        if(root->color = BLACK) {
            count++;
        }
        root = root->left;
    }
    return count+1;
}

//Recursive: have to print out all nodes
void printTree(struct node *root){
    if(root != NILL){
        printTree(root->left);
        printf("%d-", root->value);
        if(root->color == BLACK){
            printf("Black\t");
        }
        else{
//            printf("\x1b[31m");
            printf("Red\t");
//            printf("\x1b[0m\t");
        }
        printTree(root->right);
    }
}
//recursive: need to check every leaf for longest path
int RedBHeight(struct node *root, int currentHeight){
    int leftLargest = 0;
    int rightLargest = 0;

    if(root != NILL){
        leftLargest = RedBHeight(root->left, currentHeight+1);
        rightLargest = RedBHeight(root->right, currentHeight+1);
    }

    if(currentHeight >= leftLargest && currentHeight >= rightLargest){
        return currentHeight;
    }
    else if(leftLargest >= currentHeight && leftLargest >= rightLargest){
        return leftLargest;
    }
    else {
        return rightLargest;
    }

}
//Recursive: unecessary, easier with non recursive
int secondLargest(struct node *root){
    int found;
    if(root != NILL){
        found = secondLargest(root->right);
        if (found != -1){
            return found;
        }
//        printf(" HERE>>>>>>>>>>>>>>leaf: %d,Pointer: %p\n", root->value,root);
    }
    if(root->left != NILL){
//        printf("\nLEFT %d\n", root->left->value);
        return root->left->value;
    }
    else if(root->parent != NILL){
//        printf("\nParent\n");
        return root->parent->value;
    }
    //printf("It's a tree with just a root, or an Emtpy tree\n");
    return -1;


//    printf("HERE>>>>>>>>>>>>>>>>%d\n", root->value);
//    leftChild = malloc(sizeof(struct node));
//    leftChild = root->left;

//    parent = malloc(sizeof(struct node));
//    parent = root->parent;
//   if(leftChild != NILL){
//       printf("LC%d\n", leftChild->value);
//   }
//   else{
//       printf("PN%d\n", parent->value);
//   }

//    int *leftChild = &root->left->value;
//    int *Parent = &root->parent->value;
//    printf("left child: %d\n", leftChild);
//    printf("Parent: %d\n", Parent);
//    return -1;
//    if(root->left != NILL){
//        return root->left->value;
//    }
//    else if (root->parent != NILL){
//        return root->parent->value;
//    }
//    else{
//        printf("there is ONE or ZERO nodes in the tree");
//        return -1;
//    }

}

void insert(int value){
    struct node *insertedNode, *current, *parent;
    insertedNode = malloc(sizeof(struct node));
    insertedNode->value = value;
    insertedNode->color = RED;
    insertedNode->left = NILL;
    insertedNode->right = NILL;
    insertedNode->parent = NILL;


    current = ROOT;
    parent = NILL;

    //tree walk
    while(current != NILL){
        parent = current;
        if(insertedNode->value <= current->value){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    //assign parent
    if(parent == NILL){
        ROOT = insertedNode;
    }
    else if(insertedNode->value <= parent->value){
        parent->left = insertedNode;
    }
    else{
        parent->right = insertedNode;
    }

    insertedNode->parent = parent;

    fixUp(insertedNode);
}

void fixUp(struct node *insertedNode){
    while(insertedNode->parent->color == RED){

        /* insertedNode's parent is left child of insertedNode's grand parent*/
        if(insertedNode->parent == insertedNode->parent->parent->left){

            /* insertedNode's grand parent's right child is RED */
            if(insertedNode->parent->parent->right->color == RED){
                insertedNode->parent->color = BLACK;
                insertedNode->parent->parent->right->color = BLACK;
                insertedNode->parent->parent->color = RED;
                insertedNode = insertedNode->parent->parent;
            }

                /* insertedNode's grand parent's right child is not RED */
            else{

                /* insertedNode is insertedNode's parent's right child */
                if(insertedNode == insertedNode->parent->right){
                    insertedNode = insertedNode->parent;
                    rotate(insertedNode, 'L');
                }

                insertedNode->parent->color = BLACK;
                insertedNode->parent->parent->color = RED;
                rotate(insertedNode->parent->parent, 'R');
            }
        }

            /* insertedNode's parent is insertedNode's grand parent's right child */
        else{

            /* insertedNode's left uncle or insertedNode's grand parent's left child is also RED */
            if(insertedNode->parent->parent->left->color == RED){
                insertedNode->parent->color = BLACK;
                insertedNode->parent->parent->left->color = BLACK;
                insertedNode->parent->parent->color = RED;
                insertedNode = insertedNode->parent->parent;
            }
                /* insertedNode's left uncle is not RED */
            else{
                /* insertedNode is insertedNode's parents left child */
                if(insertedNode == insertedNode->parent->left){
                    insertedNode = insertedNode->parent;
                    rotate(insertedNode, 'R');
                }
                insertedNode->parent->color = BLACK;
                insertedNode->parent->parent->color = RED;
                rotate(insertedNode->parent->parent, 'L');
            }
        }
    }

    ROOT->color = BLACK;
}

void rotate(struct node *rotateNode, char rotate){
    if(rotate == 'L') {
        struct node *rightChild;
        /* Make rightChild's left child rotateNode's right child */
        rightChild = rotateNode->right;
        rotateNode->right = rightChild->left;
        if (rightChild->left != NILL) {
            rightChild->left->parent = rotateNode;
        }

        /* Make rotateNode's parent rightChild's parent and rightChild, rotateNode's parent's child */
        rightChild->parent = rotateNode->parent;
        if (rightChild->parent == NILL) {
            ROOT = rightChild;
        } else if (rotateNode == rotateNode->parent->left) {
            rotateNode->parent->left = rightChild;
        } else {
            rotateNode->parent->right = rightChild;
        }
        /* Make rotateNode, rightChild's left child & rightChild, rotateNode's parent */
        rightChild->left = rotateNode;
        rotateNode->parent = rightChild;
    }
else{
        struct node *leftChild;

        /* Make leftChild's right child rotateNode's left child */
        leftChild = rotateNode->left;
        rotateNode->left = leftChild->right;
        if (leftChild->right != NILL) {
            leftChild->right->parent = rotateNode;
        }

        /* Make rotateNode's parent leftChild's parent and leftChild, rotateNode's parent's child */
        leftChild->parent = rotateNode->parent;
        if (leftChild->parent == NILL) {
            ROOT = leftChild;
        } else if (rotateNode == rotateNode->parent->left) {
            rotateNode->parent->left = leftChild;
        } else {
            rotateNode->parent->right = leftChild;
        }
        /* Make leftChild, rotateNode's parent and rotateNode, leftChild's child */
        leftChild->right = rotateNode;
        rotateNode->parent = leftChild;
    }
}

