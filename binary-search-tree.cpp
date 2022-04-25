#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    // Initialize node values when making a node
    left = NULL;
    right = NULL;
    val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    // If node is non-existent (NULL)
    if ( n == NULL )
    {
        return -1;
    }

    // Check if just root
    if ( size_ == 1 )
    {
        return 0;
    }

    // Introduce recursive call to iterate through depth
    int leftDepth = getNodeDepth( n -> left);
    int rightDepth = getNodeDepth( n -> right);

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

BinarySearchTree::BinarySearchTree()
{
    // Initialize tree
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    queue<Node*> bft;
    if (root_ && root_ != NULL)
    {
        bft.push(root_);
    }
    while (!bft.empty() )
    {
        Node *cur = bft.front();
        if ( cur -> left != NULL )
        {
            bft.push(cur -> left);
        }
        if ( cur -> right != NULL )
        {
            bft.push(cur -> right);
        }
        bft.pop();
        delete cur;
    }
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

DataType BinarySearchTree::max() const
{
    // Create pointer starting at root
    Node *currentNode = root_;

    // Iterate and move pointer down until it reaches the bottom right leaf
    while (currentNode -> right != NULL)
    {
        currentNode = currentNode -> right;
    }
    return currentNode -> val;

}

DataType BinarySearchTree::min() const
{
    // Create pointer starting at root
    Node *currentNode = root_;

    // Iterate and move pointer down until it reaches the bottom left leaf
    while (currentNode -> left != NULL)
    {
        currentNode = currentNode -> left;
    }
    return currentNode -> val;

}

unsigned int BinarySearchTree::depth() const
{
    // Call on function
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const
{
}

bool BinarySearchTree::exists(DataType val) const
{
    // Create pointer starting at root
    Node *currentNode = root_;

    // Go through tree to find the value
    // It is an ordered list, so we can follow the general rules (if smaller go left child, if larger go right child)
    // Return false if we hit NULL, meaning that the node does not exist
    while ( currentNode -> val != val )
    {
        if ( val < currentNode -> val  )
        {
            if ( currentNode -> left == NULL )
            {
                return false;
            }
            currentNode = currentNode -> left;
        }
        else if ( val > currentNode -> val  )
        {
            if ( currentNode -> right == NULL )
            {
                return false;
            }
            currentNode = currentNode -> right;
        }
    }
    // If we find the value, return true
    if ( currentNode -> val == val )
    {
        return true;
    }
}

Node* BinarySearchTree::getRootNode()
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    // Create node that contains value you want to insert
    // Create pointer starting at root
    Node* insertNode = new Node(val);
    Node *currentNode = root_;

    //Check for empty tree
    if ( size_ == 0 || root_ == NULL)
    {
        root_ = insertNode;
        size_++;
        return true;
    }
    //Iterate through until you can find the insert spot
    //If you come across the same value, break out of loop
    while (currentNode->val != val)
    {
        if (val < currentNode->val)
        {
            // Found insert spot
            if (currentNode->left == NULL)
            {
                currentNode->left = insertNode;
                size_++;
                return true;
            }
            currentNode = currentNode->left;
        }

        else if (val > currentNode->val)
        {
            // Found insert spot
            if (currentNode->right == NULL)
            {
                currentNode->right = insertNode;
                size_++;
                return true;
            }
            currentNode = currentNode->right;
        }
    }
    //If you find repeat value, delete the node we made prior and return false
    delete insertNode;
    return false;

}

Node* findPredecessor(Node* ptr)
{
    // Predecessor is the furthest right leaf in the left tree
    ptr = ptr -> left;

    while ( ptr -> right != NULL )
    {
        ptr = ptr -> right;
    }
    return ptr;
}

bool BinarySearchTree::remove(DataType val)
{
    // Create pointer starting at root node
    // Create pointer that follows one node behind currentNode (keeps track of parent node we want to remove)
    Node *currentNode = root_;
    Node *parentNode = currentNode;

    // Check if only root is left
    if ( size_ == 1 && val == root_ -> val )
    {
        delete root_;
        root_ = NULL;
        size_--;
        return true;
    }

    // Check if empty tree
    if ( size_ == 0 )
    {
        return false;
    }

    // Iterate through and make sure value exists
    while ( currentNode->val != val )
    {
        if (val < currentNode->val)
        {
            // Value does not exist in tree
            if (currentNode->left == NULL)
            {
                return false;
            }

            else
            {
                parentNode = currentNode;
                currentNode = currentNode->left;
            }
        }

        if (val > currentNode->val)
        {
            // Value does not exist in tree
            if (currentNode->right == NULL)
            {
                return false;
            }

            else
            {
                parentNode = currentNode;
                currentNode = currentNode->right;
            }
        }
    }

    // Check for 2 children, and find predecessor
    if ( currentNode -> right != NULL && currentNode -> left != NULL )
    {
        //Create deleteNode which points to the predecessor
        //Make currentNode's value equal to our predecessor, and then we want to delete the predecessor
        Node *deleteNode = findPredecessor( currentNode );
        currentNode -> val = deleteNode -> val;

        //Want to go and find the parent node of our predecessor, so we can set deleted node to NULL, and restructure
        // any pointers if necessary
        if ( parentNode -> left != deleteNode && parentNode -> left != NULL )
        {
            parentNode = parentNode -> left;

            if ( parentNode != currentNode )
            {

                while ( parentNode -> right -> right != NULL )
                {
                    parentNode = parentNode -> right;
                }
            }
        }
        // If predecessor node has a left child
        if ( deleteNode -> left != NULL )
        {
            parentNode -> right = deleteNode -> left;
        }

        // If predecessor node has a right child
        if ( deleteNode -> right != NULL && deleteNode -> left == NULL )
        {
            parentNode -> right = deleteNode -> right;
        }

        // If predecessor node has no child
        if ( deleteNode -> left == NULL && deleteNode -> right == NULL )
        {
            if ( parentNode -> left == deleteNode )
            {
                delete deleteNode;
                parentNode -> left = NULL;
            }

            if ( parentNode -> right == deleteNode )
            {
                delete deleteNode;
                parentNode -> right = NULL;
            }

            if ( currentNode -> left == deleteNode )
            {
                delete deleteNode;
                currentNode -> left = NULL;
            }
            size_--;
            return true;
        }
        delete deleteNode;
        size_--;
        return true;



    }
    // Check for leaf node
    if ( currentNode -> right == NULL && currentNode -> left == NULL )
    {
        if (parentNode -> left != currentNode )
        {
            delete currentNode;
            parentNode -> right = NULL;
        }

        else
        {
            delete currentNode;
            parentNode -> left = NULL;
        }
        size_--;
        return true;
    }

    // Single Child
    if ( currentNode -> right == NULL || currentNode -> left == NULL  )
    {
        if (currentNode -> left == NULL )
        {
            currentNode -> val = currentNode -> right -> val;
            delete currentNode -> right;
            currentNode -> right = NULL;
        }
        else if (currentNode -> right == NULL )
        {
            currentNode -> val = currentNode -> left -> val;
            delete currentNode -> left;
            currentNode -> left = NULL;
        }
        size_--;
        return true;
    }
}