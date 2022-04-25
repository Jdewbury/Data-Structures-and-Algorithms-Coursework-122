#include "avl-tree.h";
#include <cmath>
#include <stack>
#include <iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

// check height of the node
int AVLTree::depthBelow(Node *n)
{
    // If node is non-existent (NULL)
    if ( n == NULL )
    {
        return 0;
    }

    // Check if just root
    if ( n -> left == NULL && n -> right == NULL )
    {
        return 1;
    }

    // Introduce recursive call to iterate through depth
    int leftDepth = depthBelow( n -> left);
    int rightDepth = depthBelow( n -> right);

    // Return greater depth
    if (leftDepth > rightDepth )
    {
        return 1 + leftDepth;
    }
    else
    {
        return 1 + rightDepth;
    }

}

int AVLTree::difference(Node *n)
{
    // Return difference between depths
    return depthBelow( n -> left ) - depthBelow( n -> right );
}

bool AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild)
{
    // If rotating node is root
    if ( parentNode == NULL )
    {
        Node *root_ = *getRootNodeAddress();
        Node *nodeParent = root_;

        Node* rightChild = nodeParent -> right;
        Node* leftChildRight = rightChild -> left;
        rightChild -> left = nodeParent;
        nodeParent -> right = leftChildRight;

        Node **newRoot = getRootNodeAddress();
        *newRoot = rightChild;
        return true;
    }

    // If rotating node is leftChild of parent
    if ( isLeftChild )
    {
        Node* leftParent = parentNode -> left;
        Node* leftRightLeftChild = leftParent -> right -> left;
        parentNode->left = leftParent->right;
        parentNode->left->left = leftParent;
        leftParent->right = leftRightLeftChild;
        return true;
    }

    // if rotating node is rightChild of parent
    else
    {

        Node* rightParent = parentNode->right;
        Node* rightChild = rightParent -> right;
        Node* rightChildLeft = rightParent -> right -> left;
        rightChild -> left = rightParent;
        rightParent -> right = rightChildLeft;
        parentNode -> right = rightChild;
        return true;

    }


}

bool AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild)
{
    // If rotating node is root
    if ( parentNode == NULL )
    {
        Node *root_ = *getRootNodeAddress();
        Node *nodeParent = root_;

        Node* leftChild = nodeParent -> left;
        Node* rightChildLeft = leftChild -> right;
        leftChild -> right = nodeParent;
        nodeParent -> left = rightChildLeft;

        Node **newRoot = getRootNodeAddress();
        *newRoot = leftChild;
        return true;
    }

    // If rotating node is leftChild of parent
    if ( isLeftChild )
    {
        Node* rightParent = parentNode->right;
        Node* rightChild = rightParent->right;
        parentNode->right = rightParent->left;
        rightParent->left->right = rightParent;
        rightParent->right = rightChild;
        rightParent->left = NULL;
        return true;

    }

    // If rotating node is rightChild of parent
    if ( !isLeftChild )
    {
        Node* rightParent = parentNode -> right;
        Node* leftChild = rightParent -> left;
        Node* leftChildRight = leftChild -> right;
        leftChild -> right = rightParent;
        rightParent -> left = leftChildRight;
        parentNode -> right = leftChild;
        return true;

    }

}

bool AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild)
{

    // If rotating node is root
    if ( parentNode == NULL )
    {
        Node *root_ = *getRootNodeAddress();
        Node *nodeParent = root_;

        singleLeftRotation( nodeParent, true );
        singleRightRotation( NULL , true);
        return true;
    }

    if ( isLeftChild )
    {
        Node* leftChild = parentNode -> left;
        singleLeftRotation(leftChild, true);
        singleRightRotation( parentNode, true);
        return true;
    }

    else
    {
        Node* rightChild = parentNode -> right;
        singleLeftRotation(rightChild, true);
        singleRightRotation( parentNode, true);
        return true;
    }
    //Bam

}

bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
    // If rotating node is root
    if ( parentNode == NULL )
    {
        Node *root_ = *getRootNodeAddress();
        Node *nodeParent = root_;

        singleRightRotation(nodeParent, false);
        singleLeftRotation(NULL, true);
        return true;

    }

    if ( isLeftChild )
    {
        Node *leftChild = parentNode -> left;
        singleRightRotation(leftChild, true);
        singleLeftRotation( parentNode, true);
        return true;
    }

    else
    {
        Node* rightChild = parentNode -> right;
        singleRightRotation(rightChild, false);
        singleLeftRotation( parentNode, false);
        return true;
    }

}

// stack of path to inserted/deleted Node
std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val)
{
    // Get address of root
    Node *root_ = *getRootNodeAddress();
    Node *currentNode = root_;

    // Initiate stack
    std::stack<BinarySearchTree::Node*> *nodePath = new std::stack<BinarySearchTree::Node*>;

    // If empty
    if ( currentNode == NULL )
    {
        return nodePath;
    }

    // Goes up until it finds parent of node we want to find
    while ( currentNode -> val != val )
    {
        if ( val < currentNode -> val )
        {
            nodePath -> push(currentNode );

            // For remove cases if the node doesn't exist, so we can break out of loop
            if ( currentNode -> left == NULL )
            {
                break;
            }
            currentNode = currentNode -> left;
        }
        if ( val > currentNode -> val )
        {
            nodePath -> push(currentNode);

            // For remove cases if the node doesn't exist, so we can break out of loop
            if ( currentNode -> right == NULL )
            {
                break;
            }
            currentNode = currentNode -> right;
        }
    }
    return nodePath;

}

// generic function to updated tree balance of insertion/deletion
bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    // Initiate variables
    int balanceFactor = 1;
    Node *currentNode = NULL;

    // Pop through stack and examine through each node and respective sub tree
    while ( !pathToNode -> empty() )
    {
        // Declare currentNode and pop first node off of stack
        currentNode = pathToNode -> top();
        pathToNode -> pop();

        // calculate balance factor of the currentNode
        balanceFactor = difference( currentNode );

        if ( balanceFactor > 1 )
        {

            if ( difference( currentNode -> left ) > 0 )
            {
                if ( pathToNode -> empty() )
                {
                    singleRightRotation( NULL, true );
                }
                else
                {
                    // declare parentNode
                    Node* parentNode = pathToNode -> top();
                    singleRightRotation( parentNode ,  false );
                }

            }
            else
            {
                if ( pathToNode -> empty() )
                {
                    leftRightRotation( NULL , true );
                }
                else
                {
                    Node* parentNode = pathToNode -> top();

                    // check if it is a leftChild
                    if ( currentNode -> val < parentNode -> val )
                    {
                        leftRightRotation( parentNode, true);
                    }
                    else
                    {
                        leftRightRotation( parentNode, false);
                    }
                }
            }
        }

        else if ( balanceFactor < -1 )
        {

            if ( difference( currentNode -> right ) < 0 )
            {
                if ( pathToNode -> empty() )
                {
                    singleLeftRotation( NULL, false );
                }
                else
                {
                    // Declare parentNode
                    Node* parentNode = pathToNode -> top();
                    singleLeftRotation( parentNode ,  false );
                }
            }

            else if ( difference( currentNode -> right ) == 0 )
            {
                singleLeftRotation( NULL , false );
            }

            else
            {
                if ( pathToNode -> empty() )
                {
                    rightLeftRotation( NULL , true );
                }
                else
                {
                    // declare parentNode
                    Node* parentNode = pathToNode -> top();

                    // check if it is a leftChild
                    if ( currentNode -> val < parentNode -> val )
                    {
                        rightLeftRotation( parentNode, true);
                    }
                    else
                    {
                        rightLeftRotation( parentNode, false);
                    }
                }
            }
        }

    }
    return true;
}

bool AVLTree::insert(DataType val)
{
    // Call on insert from bst
    BinarySearchTree::insert( val );
    return updateNodeBalance( pathToNodeStack( val ), val );

}

bool AVLTree::remove(DataType val)
{
    // Call on remove from bst
    BinarySearchTree::remove( val );
    return updateNodeBalance(pathToNodeStack(val), val );
}
