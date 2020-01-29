#include <stdio.h>


int NodeID = 0;

template<typename T>
class btree;

template<typename T>
class btree
{
public:

	btree(int &nodeID, T val, btree* parent = NULL):
 		m_nodeID(nodeID),
		m_val(val), m_left(NULL), m_right(NULL), m_parent(parent) 
	{
		printf("Constructor: Creating Node %d\n", m_nodeID);
		nodeID++;
	}

	~btree()
	{
		delete_left();
		delete_right();
		printf("Destructor: Deleting Node %d\n", m_nodeID);
	}

	void create_left(int &nodeID, T val)
	{
		printf("Create Left Node: %d ", m_nodeID);
		m_left = new btree(nodeID, val, this);
	}

	void create_right(int &nodeID, T val)
	{
		printf("Create Right Node: %d ", m_nodeID);
		m_right = new btree(nodeID, val, this);
	}

	// Note: Recursion is built into the delete function
	//
	void delete_left()
	{
		if (m_left != NULL)
		{
			printf("Node: %d Deleting Left. ", m_nodeID);
			delete m_left;
		}
	}

	void delete_right()
	{
		if (m_right != NULL)
		{
			printf("Node: %d Deleting Right. ", m_nodeID);
			delete m_right;
		}
	}

	btree* get_left() { return m_left;}
	btree* get_right() { return m_right;}
	
	const T&	get_val()	{	return m_val;}
	
private:

	T m_val;

	int 	m_nodeID;

	btree *m_left;
	btree *m_right;
	btree *m_parent;

};



int main(void)
{
	btree<int> bt(NodeID, 1);

	bt.create_left(NodeID, 2);
	bt.create_right(NodeID,3);

	bt.get_left()->create_left(NodeID,4);
	bt.get_left()->get_left()->create_left(NodeID,5);
	bt.get_left()->get_left()->get_left()->create_left(NodeID,4);
	bt.get_left()->get_left()->get_left()->create_right(NodeID,4);

	// Perform sorted add
	// Do pre, in, post order traversal



}
	
