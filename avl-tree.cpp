#include <iostream>

using namespace std;

template <typename T>
class AVL
{
public:
    class node
    {
    public:
        T key;
        int height;
        node *left;
        node *right;

        node(T k)
        {
            height = 1;
            key = k;
            left = NULL;
            right = NULL;
        }
    };

    node *root = NULL;

    void insert(T x)
    {
        root = insertUtil(root, x);
    }

    void remove(T x)
    {
        root = removeUtil(root, x);
    }

    node *search(T x)
    {
        return searchUtil(root, x);
    }

    void inOrder()
    {
        inOrderUtil(root);
        cout << endl;
    }

private:
    int height(node* head)
    {
        if (head == NULL)
            return 0;
        else
            return head->height;
    }

    node* rightRotation(node* head)
    {
        node* newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));

        return newhead;
    }

    node* leftRotation(node* head)
    {
        node* newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));

        return newhead;
    }

    void inOrderUtil(node* head)
    {
        if (head == NULL)
            return;
        
        inOrderUtil(head->left);
        cout << head->key << " ";
        inOrderUtil(head->right);
    }

    node* insertUtil(node* head, T x)
    {
        if (head == NULL)
        {
            node* temp = new node(x);
            return temp;
        }

        if (x < head->key)
            head->left = insertUtil(head->left, x);
        else if (x > head->key)
            head->right = insertUtil(head->right, x);

        int bf = height(head->left) - height(head->right);

        if (bf > 1)
        {
            if (x < head->left->key)
                return rightRotation(head);
            else
            {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }
        else if (bf < -1)
        {
            if (x > head->right->key)
                return leftRotation(head);
            else
            {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }

    node* removeUtil(node* head, T x)
    {
        if (head == NULL)
            return NULL;
        
        if (x < head->key)
        {
            head->left = removeUtil(head->left, x);
        }
        else if (x > head->key)
        {
            head->right = removeUtil(head->right, x);
        }
        else
        {
            node* r = head->right;

            if (head->right == NULL)
            {
                node* l = head->left;
                delete(head);
                head = l;
            }
            else if (head->left == NULL)
            {
                delete(head);
                head = r;
            }
            else
            {
                while (r->left != NULL)
                    r = r->left;
                
                head->key = r->key;
                head->right = removeUtil(head->right, r->key);
            }
        }
        if (head == NULL)
            return head;

        head->height = 1 + max(height(head->left), height(head->right));

        int bf = height(head->left) - height(head->right);

        if (bf > 1)
        {
            if (height(head->left) >= height(head->right))
                return rightRotation(head);
            else
            {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }
        else if (bf < -1)
        {
            if (height(head->right) >= height(head->left))
                return leftRotation(head);
            else
            {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }

    node* searchUtil(node* head, T x)
    {
        if (head == NULL)
            return NULL;

        T k = head->key;
        if (k == x)
            return head;
        else if (k > x)
            return searchUtil(head->left, x);
        else if (k < x)
            return searchUtil(head->right, x);
    }
};

int main()
{
    AVL<float> t;
    t.insert(1.3);
    t.insert(2.4);
    t.insert(3.5);
    t.insert(4.6);
    t.insert(5.7);
    t.insert(6.8);
    t.insert(7.9);
    t.inOrder();
    t.remove(6.8);
    t.inOrder();
}