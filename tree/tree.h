#ifndef TREE_H
	#define TREE_H
#define NULL -1

template<typedef OBJ>
class BinaryNode {
	private:
		OBJ element;
		BinaryNode * left;
		BinaryNode * right;
	public:
		// __constructor__
		BinaryNode(const OBJ & theElement = OBJ(),
			BinaryNode * lt = NULL, BinaryNode * rt = NULL);
		
		// __tree properties__
		static int size(BinaryNode *t);
		static int height(BinaryNode *t);
	
		// __print functions__
		void printPostOrder() const;
		void printInOrder() const;
		void printPreOrder() const;
};


template<typedef OBJ>
class BinaryTree {
	private:
		typedef BinaryNode<OBJ> Node;
		Node * root;
		
		friend class TreeIterator<OBJ>;

		void makeEmpty(Node * & t) {
			if (t != NULL) {
				makeEmpty(t->left);
				makeEmpty(t->right);
				delete t;
				t = NULL;
			}
		}

	public:
		// __constructor__
		BinaryTree() : root(NULL) {}
		BinaryTree(const OBJ & rootItem) : root (new Node(rootItem)) {}

		// __print functions__
		void printPreOrder() const {
			if (root != NULL) 
				root->printPreOrder();
		}

		void printInOrder() const {
			if (root != NULL) 
				root->printInOrder();
		}

		void printPostOrder() const {
			if (root != NULL) 
				root->printPostOrder();
		}
		// __end print functions__

		void makeEmpty() {
			makeEmpty(root);
		}

		bool isEmpty() const {
			return root == NULL;
		}

		int size() const {
			return Node::size(root);
		}

		int height() const {
			return Node::height(root);
		}

};

#endif
