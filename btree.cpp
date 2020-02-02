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

	bool level_order(int desired_level, int current_level)
  {
    bool result = false;

    if (current_level == desired_level)
    {
      printf("Level Order Node: %d level: %d ", m_nodeID, current_level); 
      result = true;
    }
    else
    {
      bool left_traverse_result = false;
      bool right_traverse_result = false;

      current_level++;

      if (m_left != NULL)
        left_traverse_result = m_left->level_order(desired_level, current_level);
      
      if (m_right != NULL)
        right_traverse_result = m_right->level_order(desired_level, current_level);
    
      result = left_traverse_result | right_traverse_result;
    }

    return result;
  }
  
  void level_order(void)
  {
    for (int i = 0; i < 10; i++)
    {
      bool result = level_order(i, 0);
  
      printf("::: Level: %d results in %d\n", i, result);
      if (result == false)
        break;
    }
  }

	// insertion
	bool level_order_insert(int &nodeID, T val, int desired_level, int current_level, bool &do_insert)
  {
    bool result = false;

    if (current_level == desired_level)
    {
      printf("Level Order Node Present: %d level: %d ", m_nodeID, current_level); 
      result = true;
    }
    else
    {
      bool left_traverse_result = false;
      bool right_traverse_result = false;

      current_level++;

      if (m_left != NULL)
        left_traverse_result = m_left->level_order_insert(nodeID, val, desired_level, current_level, do_insert);
      else if (do_insert)
      {
        printf("Level Order Left Node created: %d level: %d ", m_nodeID, current_level); 
        m_left = new btree(nodeID, val, this);
        do_insert = false;
      }
      
      if (m_right != NULL)
        right_traverse_result = m_right->level_order_insert(nodeID, val, desired_level, current_level, do_insert);
      else if (do_insert)
      {
        printf("Level Order Right Node created: %d level: %d ", m_nodeID, current_level); 
        m_right = new btree(nodeID, val, this);
        do_insert = false;
      }    

      result = left_traverse_result | right_traverse_result;
		
    }

    return result;
  }

  void level_order_insert(int &nodeID, T val)
	{
    bool do_insert = true;

    for (int i = 0; i < 10; i++)
    {
	    bool result = level_order_insert(nodeID, val, i, 0, do_insert);
  
      printf("::: Level: %d results in %d\n", i, result);
      if (result == false)
        break;
    }

	}

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


  bt.level_order();

  bt.level_order_insert(NodeID, 8);
  bt.level_order_insert(NodeID, 9);
  bt.level_order_insert(NodeID, 10);
  bt.level_order_insert(NodeID, 11);

  bt.level_order_insert(NodeID, 12);
  bt.level_order_insert(NodeID, 13);
  bt.level_order_insert(NodeID, 14);
  bt.level_order_insert(NodeID, 15);
  
  bt.level_order_insert(NodeID, 16);

  bt.level_order();




	// Perform sorted add



}
	
