
 
template<typename T>
class list_object;
template<typename T>
class list_object
{
public:
  list_object(T val): m_val(val), m_next(NULL){}
  ~list_object() {}

  list_object *get_next()  { return m_next };
  T  get_data()  { return m_val; }
  void set_next(list_object *in) { m_next = in };

private:

  T m_val;
  list_object *m_next;

};


template<typename T>
class list;
template<typename T>
class list
{
public:
  list(): m_list(NULL), m_head(NULL), m_tail(NULL), m_size(0) {}

  list(T val): m_list(NULL), m_head(NULL), m_tail(NULL), m_size(0) 
  {
    m_list = new list_object<t>(val);
    m_head = m_list;
    m_tail = m_list; 
    m_size = 1;
  }
 
  ~list()
  {
    while (m_head != NULL)
    {
      list_object *temp = m_head;  
      m_head = m_head->get_next();
      delete temp;
      m_size --;
    }
  }

  void push_front(T val)
  {
    list_object *temp = new list_object<t>(val);

    temp->set_next(m_head);
    m_head = temp;
    m_size ++;
  } 

  void push_back(T val)
  {
    list_object *temp = new list_object<t>(val);
    
    m_tail->set_next(temp);
    m_tail = temp;
    m_size ++;
  } 

  T pop_front()
  {
    list_object *temp = m_head;

    if (temp == NULL)
    m_head = m_head->get_next();
    delete temp;
    m_size --;
  } 

  T pop_back()
  {
    list_object *temp = m_head;

    while (true)
    {
      if (temp->get_next() == 

    }

    m_head = m_head->get_next();
    delete temp;
    m_size --;
  } 

private:
 
  list_object *m_list;
  list_object *m_head;
  list_object *m_tail;
  
  size_t size;
};



