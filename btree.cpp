#include <stdio.h>



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
	btree* get_parent() { return m_parent;}
	
	bool HasLeft() 	{ return (m_left != NULL); }
	bool HasRight() { return (m_right != NULL); }
	bool IsRoot()	{ return ((m_left == NULL) && (m_right == NULL)); }

	const T&	get_val()	{	return m_val;}
	
	// Do pre, in, post order traversal

	btree* get_leftmost(int &recursion_depth)
	{
		btree *retval;
	
		printf("get_leftmost: depth %d\n", recursion_depth);
		recursion_depth++;

		if (m_left != NULL)
			retval = m_left->get_leftmost(recursion_depth);
		else
			retval = this;

		return retval;	
	}

	void in_order(int &level, int &max_level)
	{

		// Left Node operation
		if (m_left != NULL)
		{
			level ++;
			if (level > max_level)
				max_level = level; 

			m_left->in_order(level, max_level);
		}
	
		// Root operation
		printf("In Order Node: %d level: %d, max_level: %d \n", 
				m_nodeID, level, max_level);

		// Right Operation
		if (m_right != NULL)
		{
			level ++;
			if (level > max_level)
				max_level = level; 

			m_right->in_order(level, max_level);
		}

		level --;
	}

	void pre_order(int &level, int &max_level)
	{
		// Root operation
		printf("Pre Order Node: %d level: %d, max_level: %d \n", 
				m_nodeID, level, max_level);

		// Left Node operation
		if (m_left != NULL)
		{
			level ++;
			if (level > max_level)
				max_level = level; 

			m_left->pre_order(level, max_level);
		}

		// Right Operation
		if (m_right != NULL)
		{
			level ++;
			if (level > max_level)
				max_level = level; 

			m_right->pre_order(level, max_level);
		}

		level --;
	}

	void post_order(int &level, int &max_level)
	{
		// Left Node operation
		if (m_left != NULL)
		{
			level ++;
			if (level > max_level)
				max_level = level; 

			m_left->post_order(level, max_level);
		}

		// Right Operation
		if (m_right != NULL)
		{
			level ++;
			if (level > max_level)
				max_level = level; 

			m_right->post_order(level, max_level);
		}
		
		// Root operation
		printf("Post Order Node: %d level: %d, max_level: %d \n", 
				m_nodeID, level, max_level);


		level --;
	}

	void level_order(int &level, int &max_level)

	// insertion
	


private:

	T m_val;

	int 	m_nodeID;

	btree *m_left;
	btree *m_right;
	btree *m_parent;

};



int main(void)
{
	int NodeID = 0;

	btree<int> bt(NodeID, 1);

	bt.create_left(NodeID, 2);
	bt.create_right(NodeID,3);

	bt.get_left()->create_left(NodeID,4);
	bt.get_left()->create_right(NodeID,5);

	bt.get_right()->create_left(NodeID,6);
	bt.get_right()->create_right(NodeID,7);

	int depth = 0;
	bt.get_leftmost(depth);

	int level = 0;
	int max_level = 0;
	
	printf("\n");
	bt.in_order(level, max_level);

	level = 0;
	max_level = 0;

	printf("\n");
	bt.pre_order(level, max_level);

	level = 0;
	max_level = 0;

	printf("\n");
	bt.post_order(level, max_level);

	// Perform sorted add



}
	
