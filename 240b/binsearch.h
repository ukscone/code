int bin_search(int a[], int start, int end, int size, int target);

int bin_search(int a[], int start, int end, int size, int target)
{
	if(size == 1) {
		if(a[start] == target) return start;
		else 					return -1;
	}
	
	if(target < a[start + size/2]) {
		return bin_search(a, start, 0, size/2, target);
	}
	else {
		return bin_search(a, start + size/2, 0, size - size/2, target);
	}
}
