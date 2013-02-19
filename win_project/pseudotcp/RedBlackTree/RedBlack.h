//RedBlack.h
#ifndef REDBLACK_INCLUDE
#define REDBLACK_INCLUDE

template<typename T>
class RedBlackTree
{
	struct Node
	{
		T       key;
		bool    color;
		Node*   parent;
		Node*   left;
		Node*   right;
		Node(T data_, bool  color_, Node* p, Node* l, Node* r)
			:key(data_),color(color_),parent(p),left(l),right(r){}
	};     
	Node* NIL;
	Node* root;
	bool  RED   ;
	bool  BLACK ;

public:

	RedBlackTree(T data=0, bool str=false, Node* p=NULL, Node* q=NULL, Node* e=NULL)
		:RED(true),BLACK(false)
	{   

		NIL =  new Node(0, BLACK, NIL, NIL, NIL);//из╠Ь╫А╣Ц
		root = NIL;

	}
	~RedBlackTree()
	{
		DeleteTree(root);
		delete NIL;
	}

	void  LeftRotate(Node* x);
	void  RightRotate(Node* y);
	void  RBInsert(T  data);
	void  RBInsertFixup(Node* z);
	void  RBDelete(T data);
	void  RBDeleteFixUp(Node* x);
	Node* TreeSearchNumber(Node* x, T k);
	Node* TreeSuccessor(Node* x);
	void  DeleteTree(Node* x);
	void  PrintTree(Node* x);
	Node* GetNode(void);
	Node* TreeMinIMUM(Node* x );

};

#endif //REDBLACK_INCLUDE
