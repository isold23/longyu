//RedBlackTree_.h
#ifndef REDBLACKTREE_H_INCLUDE
#define REDBLACKTREE_H_INCLUDE

#include "RedBlack.h"
#include <assert.h>
#include <string>
#include <iostream>

template<typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::TreeMinIMUM(Node* x )
{
	while(x->left != NIL)
		x = x->left;
	return x;
}
template<typename T>
RedBlackTree<T>::Node*  RedBlackTree<T>::GetNode(void)
{
	return root;
}

template<typename T>
void RedBlackTree<T>::PrintTree(Node* x)
{   
	if(NIL != x){
		if(NIL != x->left)
		{
			PrintTree(x->left);
		}
		if(NIL != x->right)
		{
			PrintTree(x->right);
		}
		std::cout<<x->key<<std::endl;
	}
}

template<typename T>
void RedBlackTree<T>::DeleteTree(Node* x)
{
	if(x != NIL)
	{   
		if(NIL != x->left )
		{
			DeleteTree(x->left);
		}
		if(NIL != x->right  )
		{
			DeleteTree(x->right);
		}
		delete x;
		x = NULL;
	}
}

template<typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::TreeSearchNumber(Node* x, T k)
{
	if( x == NIL || k == x->key )
		return x;
	if( k < x->key )
		return TreeSearchNumber(x->left, k);
	else
		return TreeSearchNumber(x->right, k);
}

template<typename T>
RedBlackTree<T>::Node* RedBlackTree<T>::TreeSuccessor(Node* x)//存在两种情况:
{
	if (x->right != NIL)//如果结点x的右子树非空，则x的后继即右子树中的最左的结点。
		return TreeMinIMUM(x->right) ;
	Node* y = x->parent;//如果结点x的右子树为空，且x有一个后继y，则y是x的最低祖先结点，
	while( (y != NIL) && (x == x->right))//且y的左儿子也是x的祖先票篇 p154,p155《算法导论》
	{
		x = y;
		y = y->parent;
	}
	return y;
}
template<typename T>
void RedBlackTree<T>::LeftRotate(Node* x)
{  
	Node* y  = x->right; //y是x的右结点
	if(NIL == y)
		return;
	x->right = y->left;     //让x的右指针指向y的左结点。
	if(NIL != y->left)      //y的左结点不是哨兵
		y->left->parent = x;//让y的左结点的parent指向x
	y->parent = x->parent;  //让y的父子针指向x的父结点
	if(x->parent == NIL) //x为根结点
	{
		root = y;//让y成为根结点
	}
	else if(x == x->parent->left)//如果x为左子女
	{
		x->parent->left = y; //y便代替x成为左子女
	}
	else
		x->parent->right =y; //否则代替x成为右子女

	y->left = x;            //x成为y的左子女
	x->parent = y;          //y成为x的父结点
}
//______________________________________________________________//
//                                                              //
//     |                                 |                      //
//       X      left_Rotate(T,x)           Y                      //
//      /      ----------------->        /                      //
//   α  Y    <----------------        X  γ                    //
//      /     Right_Rotate(T,y)      /                        //
//       β γ                         α β                      //
//______________________________________________________________//

template<typename T>
void RedBlackTree<T>::RightRotate(Node* y )
{
	Node* x = y->left;
	if(NIL == x)
		return;
	y->left = x->right;
	if(x->right != NIL)
		x->right->parent = y;
	x->parent = y->parent;
	if(y->parent == NIL)
	{
		root = x;
	}
	else if (y == y->parent->right)
	{
		y->parent->right = x;
	}
	else
	{
		y->parent->left = x;
	}

	x->right  = y;
	y->parent = x;
}

template<typename T>
void RedBlackTree<T>::RBInsert(T data)
{     
	Node* x = root;
	Node* z = new Node(data,RED,NULL,NULL,NULL);//将要插入的结点
	assert(z != NULL);
	Node* y = NIL;

	while( x != NIL)
	{
		y = x;
		if(z->key < x->key)
		{
			if(x->left != NIL)
			{
				x = x->left;
			}
			else
			{
				break;
			}
		}
		else 
		{    
			if(x->right != NIL)
			{
				x = x->right;
			}
			else
			{
				break;
			}
		}
	}
	z->parent = y;
	if(y == NIL)
		root = z;
	else if(z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = NIL;
	z->right = NIL;
	z->color = RED;
	RBInsertFixup(z);
}

//在调用RBInsertFixup()，那些红黑树的性质可能会被破坏呢？性质1和性质3当然继续成立，
//因为新插入的结点的子女都是哨兵NIL。性质5即从一个制定结点开始的每条路径上黑结点的个数
//都是相等的，也会成立，因为结点z本身就是具有哨兵子女的红结点。因此，可能被破坏的就是根节点2，
//以及一个红结点不能有红子女的性质4。这两个可能的破坏是因为z被着为红色。如果z是根结点则破坏了性质2,
//如果z的父结点是红色就破坏了性质4.

template<typename T>
void RedBlackTree<T>::RBInsertFixup(Node* z)
{    
	Node* y = NIL;
	while( root != z && z->parent->color == RED)
	{
		if( z->parent == z->parent->parent->left)
		{
			y =  z->parent->parent->right;
			if(y != NIL && y->color == RED  )
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else 
			{
				if( z == z->parent->right)
				{
					z = z->parent;
					LeftRotate(z);
				}


				z->parent->color = BLACK;
				z->parent->parent->color = RED;//还没旋转
				RightRotate(z->parent->parent);
			}

		}

		else
		{     
			y =  z->parent->parent->left;
			if(y != NIL && y->color == RED  )
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else 
			{  
				if (z == z->parent->left)
				{
					z = z->parent;
					RightRotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotate(z->parent->parent);
			}

		}


	}//while

	root->color = BLACK;

}

template<typename T>
void RedBlackTree<T>::RBDelete(T data)
{     
	Node* x = NIL;
	Node* y = NIL;
	assert(TreeSearchNumber(root, data)->key == data);//查找看有没有值和同结点指示的一样
	Node* z = TreeSearchNumber(root, data);//找到此结点
	if((z->left == NIL) ||(z->right == NIL))
	{
		y = z;
	}
	else
	{
		y = TreeSuccessor(z);
	}
	if(y->left != NIL)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}

	x->parent = y->parent;
	if(y->parent == NIL)
		root = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if(y != z)
		z->key = y->key;

	if(y->color == BLACK && NIL != x)
		RBDeleteFixUp(x);

	delete y;
}

template<typename T>
void RedBlackTree<T>::RBDeleteFixUp(Node* x)
{   
	Node* y = NIL;
	Node* w = NIL;
	while(x != root && BLACK == x->color)
	{
		if(x == x->parent->left)
		{
			w = x->parent->right;
			if(NIL == w)
				continue;
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			if( NIL != w->left &&   BLACK == w->left->color && 
				NIL != w->right && BLACK == w->right->color)
			{
				w->color = RED;
				x = x->parent;
			}
			else 
			{
				if(NIL != w->right && BLACK == w->right->color)
				{
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = x->parent->right;
				}


				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(x->parent);
				x = root;
			}

		}

		else 
		{ 
			w = x->parent->left;
			if(NIL == w)
				continue;
			if(RED == w->color)
			{   
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(x->parent);
				y = x->parent->left;
			}
			if(NIL != w->left && BLACK == w->left->color &&
				NIL != w->right && BLACK == w->right->color)
			{  
				w->color = RED;
				x = x->parent;
			}
			else 
			{ 
				if(NIL != w->left && w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = x->parent->left;
				}

				w->color = w->parent->color;
				w->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(w->parent);
				x = root;
			}

		}
	}
	x->color = BLACK;
}

#endif