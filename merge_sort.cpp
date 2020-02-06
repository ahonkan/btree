#include <stdio.h>

void print_array(int *array, int len)
{
  for (int idx = 0; idx < len; idx ++)
  {
    printf("%d ", array[idx]);
  }
  printf("\n");
}

template<typename T>
bool compare(T left, T right)
{
	if (left < right)
		return true;
	
	return false;
}

template<typename T>
void merge(T *left, size_t left_len, 
					   T *right, size_t right_len, 
					   T *out)
{
	size_t left_idx = 0;
	size_t right_idx = 0;

  printf("Merge: L: %llx %ld  R: %llx %ld OUT: %llx\n",
      (unsigned long long)left, left_len,
      (unsigned long long)right, right_len,
      (unsigned long long)out);
      

	while((left_idx < left_len) && (right_idx < right_len))
	{
    printf("Merge Compare L:%ld R:%ld\n", left_idx, right_idx);
		if (compare(left[left_idx], right[right_idx]))
		{
			*out = left[left_idx];
			out ++;
			left_idx ++;
		}
		else
		{
			*out = right[right_idx];
			out ++;
			right_idx ++;
		}
  }
	
  if (left_idx >= left_len)
	{
		for (int i = right_idx; i < right_len; i++)
		{
      printf("Flush Right L:%ld R:%d\n", left_idx, i);
			*out = right[i];
			out ++;
		}
	}	
	else if (right_idx >= right_len)
	{
		for (int i = left_idx; i < left_len; i++)
		{
      printf("Flush Left L:%d R:%ld\n", i, right_idx);
			*out = left[i];
			out ++;
		}
	}	
  
}

template<typename T>
void merge_sort(T *in_array, size_t len, T *out_array)
{
  static int level = 0;

  printf("%d in: %llx out: %llx len: %ld\n",
            level, 
            (unsigned long long)in_array, 
            (unsigned long long)out_array,
            len); 
  level ++;

	if (len == 0)
		return;
	else if (len == 1)
	{
		*out_array = *in_array;
		out_array ++;
	}
	else if (len == 2)
	{
	  if (compare(in_array[0], in_array[1]))
		{
			*out_array = in_array[0];
			out_array ++;
			*out_array = in_array[1];
			out_array ++;
		}
		else
		{
			*out_array = in_array[1];
			out_array ++;
			*out_array = in_array[0];
			out_array ++;
		}
    
	}
	else
	{
		T *left = in_array;
		int left_len = len/2;
		T *right = in_array + left_len;
		int right_len = len - left_len;

		// Left sort
		merge_sort(left, left_len, out_array);
    printf("%d: left\n", level);
    print_array(left, left_len);

		// Right sort
		merge_sort(right, right_len, out_array + left_len);
    printf("%d: right\n", level);
    print_array(right, right_len);

/*
    merge(out_array, left_len, 
					out_array + left_len, right_len, 
					in_array);
*/
    merge(left, left_len, 
					right, right_len, 
					out_array);
    
    printf("merged\n");
    print_array(in_array, len);
	}

  level --;

}


int main(void)
{
//  int left[] = {0,3,6,10,15,21,28,36,41}; 
  int left[] = {0,4,5,6,11,15,18,20}; 
  int right[] = {1,2,3,7,8,9,19};
  int in[] = {2,1,3,9,5,4};
  int out[100] = {0};

  size_t left_len = sizeof(left)/sizeof(left[0]);
  size_t right_len = sizeof(right)/sizeof(right[0]);
  size_t in_len = sizeof(in)/sizeof(in[0]);

//  merge<int>(left, left_len, right, right_len, out);

  merge_sort<int>(in, in_len, out);
  
  printf("sorted\n");
  print_array(in, in_len);
}
