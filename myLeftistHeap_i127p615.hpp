#ifndef MYLEFTISTHEAP_HPP
#define MYLEFTISTHEAP_HPP

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <queue>

template<typename Comparable>
class myLeftistHeap
{
  public:
    myLeftistHeap() : root{nullptr}
    {
    }
    myLeftistHeap(const myLeftistHeap & rhs)
    {
      root = nullptr;
      *this = rhs;
    }
    myLeftistHeap(myLeftistHeap && rhs)
    {
      root = nullptr;
      root = std::move(rhs);
      rhs.root = nullptr;
    }

    ~myLeftistHeap()
    {
      makeEmpty();
    }

    myLeftistHeap & operator=(const myLeftistHeap & rhs)
    {
      if(this != &rhs)
      {
        makeEmpty();
        root = clone(rhs.root);
      }
      return *this;
    }
    myLeftistHeap & operator=(myLeftistHeap && rhs)
    {
      if(this != &rhs)
      {
        makeEmpty();
        root = clone(std::move(rhs.root));
        rhs.root = nullptr;
      }
      return *this;
    }

    bool isEmpty() const
    {
      return root == nullptr;
    }
    const Comparable & findMin() const
    {
      if(isEmpty())
        std::cerr << "Caught error: Cannot find min of an empty leftist heap\n";
      else
        return root->element;
    }

    void insert(const Comparable & x)
    {
      root = merge(new LeftistNode{x}, root);
    }
    void insert(Comparable && x)
    {
      root = merge(new LeftistNode{std::move(x)}, root);
    }
    void deleteMin()
    {
      if(isEmpty())
        std::cerr << "Caught error: Unable to delete min from an empty leftist heap\n";
      else
      {
        LeftistNode * oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
      }
    }
    void deleteMin(Comparable & minItem)
    {
      minItem = findMin();
      deleteMin();
    }
    void makeEmpty()
    {
      reclaimMemory(root);
      root = nullptr;
    }
    void merge(myLeftistHeap & rhs)
    {
      if(this == &rhs) // Avoid aliasing problems
        return;

      root = merge(root, rhs.root);
      rhs.root = nullptr;
    }

    void printInOrder()
    {
      printInOrder(root);
    }
    void printLevelOrder()
    {
      if(isEmpty())
        return;

      std::queue<LeftistNode *> theQueue;
      theQueue.push(root); // Start with the root

      while(theQueue.size() > 0)
      {
        LeftistNode * current = theQueue.front();
        theQueue.pop(); // Grab the earliest node

        if(current->left != nullptr) // Push the earliest node's left child. . .
          theQueue.push(current->left);
        if(current->right != nullptr) // . . . and right child
          theQueue.push(current->right);
        std::cout << current->element << std::endl;
      }
    }

  private:
    struct LeftistNode
    {
      Comparable    element;
      LeftistNode * left;
      LeftistNode * right;
      int           npl;

      LeftistNode(const Comparable & e, LeftistNode * lt = nullptr,
                  LeftistNode * rt = nullptr, int np = 0)
        : element{e}, left{lt}, right{rt}, npl{np} { }

      LeftistNode(Comparable && e, LeftistNode * lt = nullptr,
                  LeftistNode * rt = nullptr, int np = 0)
        : element{std::move(e)}, left{lt}, right{rt}, npl{np} { }
    };

    LeftistNode * root;

    LeftistNode * merge(LeftistNode * h1, LeftistNode * h2)
    {
      if(h1 == nullptr)
        return h2;
      if(h2 == nullptr)
        return h1;
      if(h1->element < h2->element)
        return merge1(h1, h2);
      else
        return merge1(h2, h1);
    }
    LeftistNode * merge1(LeftistNode * h1, LeftistNode * h2)
    {
      if(h1->left == nullptr) // Single node
        h1->left = h2;        // Other fields in h1 already accurate
      else
      {
        h1->right = merge(h1->right, h2);
        if(h1->left->npl < h1->right->npl)
          swapChildren(h1);
        h1->npl = h1->right->npl + 1;
      }
      return h1;
    }

    void swapChildren(LeftistNode * t)
    {
      if(t == nullptr)
        return;

      LeftistNode * temp = t->left;
      t->left = t->right;
      t->right = temp;
    }
    void reclaimMemory(LeftistNode * t)
    {
      if(t == nullptr)
        return; // End of branching

      reclaimMemory(t->left);
      reclaimMemory(t->right);
      delete t;

    }
    LeftistNode * clone(LeftistNode * t) const
    {
      if(t == nullptr)
        return nullptr; // End of branching

        return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
    }

    void printInOrder(LeftistNode * t) const
    {
      if(t == nullptr)
        return; // End of branching
      if(t->left != nullptr)
        printInOrder(t->left);
      std::cout << t->element << std::endl;
      if(t->right != nullptr)
        printInOrder(t->right);
    }
};

#endif
