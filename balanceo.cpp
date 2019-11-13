#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

void obtenerLista(struct node *root, vector<int> &lista){
  if (root == NULL)
        return;
    printf("%d \n", root->key);
    obtenerLista(root->left, lista);
    lista.push_back(root->key);
    obtenerLista(root->right, lista);
}

void preOrder(struct node *root)
{
    if (root == NULL)
        return;
    printf("%d \n", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

struct node *insert(struct node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    /* return the (unchanged) node pointer */
    return node;
}

struct node *minValueNode(struct node *node)
{
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node *deleteNode(struct node *root, int key)
{
    // base case
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void postOrder(struct node *root)
{
    if (root == NULL)
        return;

    // primero se recorre el lado izquierdo
    postOrder(root->left);

    // luego se recorre el lado derecho
    postOrder(root->right);

    // se imprime el valor del nodo.
    printf("%d \n", root->key);
}
//Función para balancear el árbol;

struct node *balance(vector<int> &nueva, int inicio, int ultimo){
  if(inicio>ultimo) return NULL;
  int mitad = (inicio+ultimo)/2;
  node *root = newNode(nueva[mitad]);
  root->left=balance(nueva, inicio, mitad-1);
  root->right=balance(nueva, mitad+1, ultimo);

  return root;
}

int main()
{
    struct node *root = NULL;
    root = insert(root, 2);
    insert(root, 1);
    insert(root, 8);
    insert(root, 7);
    insert(root, 6);
    insert(root, 5);
    insert(root, 4);

    //Creo el vector al que meteré los elementos
    vector<int> lista;
    obtenerLista(root, lista);
    int tama = lista.size()-1;
    cout << "El número de elementos en el árbol es de: " << tama+1 << endl;
    //Falta validación por si fuera un arreglo de tamaño par
    root = balance(lista, 0, tama);
    preOrder(root);
    return 0;
}
