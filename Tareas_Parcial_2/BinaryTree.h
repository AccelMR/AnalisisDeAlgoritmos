/************************************************************************/
/**
 * @file BinaryTree.h
 * @author AccelMR
 * @date 2019/07/10
 * @brief binary tree template class 
 */
 /************************************************************************/
#pragma once

/************************************************************************/
/*
 * Includes
 */                                                                     
/************************************************************************/
#include <iostream>

/* =^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=   =^..^=  */
/* =^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=   =^..^=  */
template <typename T>
class BinaryTree  
{
  /** 
   * @brief Nested class that contains the leaf 
   */
  template <typename T>
  class NNode
  {
  public:
    NNode(T _data): m_data(_data) {}

    /** 
     * @brief insert recursive function
     * 
     * NOTE: it doesn't re-balance the tree yet
     */
    inline void
    insert(T data) {

      if (data < m_data)
      {
        if (nullptr ==  m_left)
        {
          m_left = new NNode<T>(data);
          m_left->m_parent = this;
        }
        else
        {
          m_left->insert(data);
        }
      }
      else
      {
        if (nullptr == m_right)
        {
          m_right = new NNode<T>(data);
          m_right->m_parent = this;
        }
        else
        {
          m_right->insert(data);
        }
      }
    }

    void
    inOrder() {
      if (nullptr != m_left)
      {
        m_left->inOrder();
      }
      std::cout << m_data << ", ";
      if(nullptr !=  m_right)
      {
        m_right->inOrder();
      }
    }

    void
    postOrder() {
      if(nullptr != m_left)
      {
        m_left->preOrder();
      }
      if(nullptr != m_right)
      {
        m_right->preOrder();
      }
      std::cout << m_data << ", ";
    }

    void 
    preOrder() {
      std::cout << m_data << ", ";
      if (nullptr != m_left )
      {
        m_left->preOrder();
      }
      if(nullptr != m_right)
      {
        m_right->preOrder();
      }
    }

    NNode<T>*
    find(T data) {
      if (m_data == data)
      {
        return this;
      }
      else if(data > m_data)
      {
        return m_right->find(data);
      }
      else if(data < m_data)
      {
        return m_left->find(data);
      }
      else
      {
        //TODO: error, data not found
        return nullptr;
      }
    }

    NNode<T>*
    getParent() const {
      return m_parent;
    }

    NNode<T>*
    getLeft() {
      return m_left;
    }

    NNode<T>*
    getRight() {
      return m_right;
    }

    void
    setLeft(NNode<T>* node) {
      m_left = node;
    }

    void
    setRight(NNode<T>* node) {
      m_right = node;
    }

    void
    setParent(NNode<T>* node) {
      m_parent = node;
    }

    NNode<T>*
    getLastLeft() {
      if (nullptr != m_left)
      {
        return m_left->getLastLeft();
      }
      return this;
    }

    inline T 
    getData() const { return m_data; }

  private:
    T m_data;
    NNode<T>* m_left = nullptr;
    NNode<T>* m_right = nullptr;
    NNode<T>* m_parent;
  };

 public:
 /*
  * @brief Default constructor
  */
  BinaryTree() = default;

 /*
  * @brief Default destructor
  */
  ~BinaryTree();

  void
  initialize(T);

  void
  insert(T);

  void
  remove(T);


  void
  printInOrder() {
    if (nullptr != m_root)
    {
      std::cout << "InOrder() :\t" ;
      m_root->inOrder();
      std::cout << "\n\n";
    }
  }

  void
  printPostOrder() {
    if(nullptr != m_root)
    {
      std::cout << "PostOrder() :\t";
      m_root->postOrder();
      std::cout << "\n\n";
    }
  }

  void
  printPreOrder()
  {
    if(nullptr != m_root)
    {
      std::cout << "PreOrder() :\t";
      m_root->preOrder();
      std::cout << "\n\n";
    }
  }

private:

  inline NNode<T>*
  find(const T& data) {
    return m_root->find(data);
  }


 private:

   NNode<T>* m_root;

};

/*
*/
template <typename T>
void
BinaryTree<T>::remove(T data)
{
  NNode<T>* d = m_root->find(data);
  NNode<T>* dR = d->getRight();
  NNode<T>* dL = d->getLeft();

  if(d != nullptr) {
    NNode<T>* parent = d->getParent();

    if (nullptr == dR && nullptr == dL)
    {
      (parent->getLeft() == d) ? parent->setLeft(nullptr) : parent->setRight(nullptr);
    }
    else if(nullptr != dR && nullptr != dL)
    {
      NNode<T>* nP = dR->getLastLeft();
      (parent->getLeft() == d) ? parent->setLeft(dR) : parent->setRight(dR);

      dL->setParent(nP);
      nP->setLeft(dL);
    }
    else if(nullptr != dL)
    {
      dL->setParent(parent);
      (parent->getLeft() == d) ? parent->setLeft(dL) : parent->setRight(dL);
    }
    else if (nullptr != dR)
    {
      dR->setParent(parent);
      (parent->getLeft() == d) ? parent->setLeft(dR) : parent->setRight(dR);
    }
  }
}

/*
*/
template <typename T>
void
BinaryTree<T>::insert(T data)
{
   if (nullptr != m_root)
   {
     m_root->insert(data);
   }
   else
   {
     m_root = new NNode<T>(data);
   }
}

/*
*/
template <typename T>
void
BinaryTree<T>::initialize(T data)
{
  m_root = new NNode<T>(data);
}

/*
*/
template <typename T>

BinaryTree<T>::~BinaryTree()
= default;
