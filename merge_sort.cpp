#include <stdio.h>


template<typename T>
bool compare(T left, T right)
{
	if (left < right)
		return true;
	
	return false;
}

template<typename T>
void merge_sort_kernel(T *left, size_t left_len, 
					   T *right, size_t right_len, 
					   T *out)
{
	size_t left_idx = 0;
	size_t right_idx = 0;

	while(true)
	{
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
	
		if (left_idx >= left_len)
		{
			for (int i = right_idx; i < right_len; i++)
			{
				*out = right[i];
				out ++;
			}
		}	
		else if (right_idx >= right_len)
		{
			for (int i = left_idx; i < left_len; i++)
			{
				*out = left[i];
				out ++;
			}
		}	

	}

}

template<typename T>
void merge_sort(T *in_array, size_t len, T *out_array, size_t *out_array_idx)
{

	if (len == 0)
		return;
	else if (len == 1)
	{
		*out_array = *in_array;
		*out_array_idx ++;
	}
	else if (len == 2)
	{
		merge_sort_kernel(in_array, 1, 
					      in_array + 1, 1, 
					   	  out_array + out_array_idx);
		*out_array_idx += 2;
	}
	else
	{
		T *left = in_array;
		int left_len = len/2;
		T *right = in_array + left_len;
		int right_len = len - left_len;

		// Left sort
		merge_sort(left, left_len, out_array, out_array_idx);

		// Right sort
		merge_sort(right, right_len, out_array, out_array_idx);


	}


}



int main(void)
{
	printf("hello wrld\n");

}
