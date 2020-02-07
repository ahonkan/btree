#include <stdio.h>
#include <stdlib.h> 

void print_array(int *array, int len)
{
  for (int idx = 0; idx < len; idx ++)
  {
    printf("%d ", array[idx]);
  }
  printf("\n");
}

template<typename T>
bool do_swap(T left, T right)
{
	if (left > right)
		return true;
	
	return false;
}

template<typename T>
void merge(T *in_array, size_t left_len, size_t right_len, 
					   T *temp)
{
	size_t left_idx = 0;
	size_t right_idx = 0;
  T *left = in_array;
  T *right = in_array + left_len;
  T *out = in_array;

  printf("Merge: L: %llx %ld  R: %llx %ld OUT: %llx\n",
      (unsigned long long)left, left_len,
      (unsigned long long)right, right_len,
      (unsigned long long)temp);
      
  for (int i = 0; i < left_len; i++)
    temp[i] = left[i];

  left = temp;

	while((left_idx < left_len) && (right_idx < right_len))
	{
    printf("Merge Compare L:%ld R:%ld\n", left_idx, right_idx);
		if (do_swap(left[left_idx], right[right_idx]))
		{
			*out = right[right_idx];
			out ++;
			right_idx ++;
		}
		else
		{
			*out = left[left_idx];
			out ++;
			left_idx ++;
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
void merge_sort(T *in_array, size_t len, T *temp)
{
  static int level = 0;

  printf("%d in: %llx out: %llx len: %ld\n",
            level, 
            (unsigned long long)in_array, 
            (unsigned long long)temp,
            len); 
  level ++;

	if (len == 0)
		return;
	else if (len == 1)
     return;
	else if (len == 2)
	{
	  if (do_swap(in_array[0], in_array[1]))
		{
      temp[0] = in_array[0];
      in_array[0] = in_array[1];
      in_array[1] = temp[0];
		}
		else
		{
      return;
		}
    
	}
	else
	{
		T *left = in_array;
		int left_len = len/2;
		T *right = in_array + left_len;
		int right_len = len - left_len;

		// Left sort
		merge_sort(left, left_len, temp);
    printf("%d: left\n", level);
    print_array(left, left_len);

		// Right sort
		merge_sort(right, right_len, temp);
    printf("%d: right\n", level);
    print_array(right, right_len);


    merge(in_array, left_len, right_len, 
					temp);

    printf("merged\n");
    print_array(in_array, len);
	}

  level --;

}


int main(void)
{
  int in[100] = {0};
  int temp[100] = {0};
  int in_len = sizeof(in)/sizeof(in[0]);
  
  for (int i = 0; i < in_len; i++)
    in[i] = rand() % 100;

  merge_sort<int>(in, in_len, temp);
  
  printf("sorted\n");
  print_array(in, in_len);
}
