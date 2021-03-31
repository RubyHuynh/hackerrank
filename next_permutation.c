
void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void dump(int* nums, int numsSize) {
    int i = 0;
    for (;i< numsSize; ++i) {
        printf("%d \t", nums[i]);
    }
    printf("\n");
}

void reverse(int* nums, int numsSize) {
    int tmp[numsSize];
    int i =0;
    
    if (numsSize <=1) {
        return;
    }
    for (;i < numsSize; ++i) {
        tmp[i] = nums[numsSize -i -1];
    }
    memcpy(nums, &tmp, sizeof(tmp));
}



void nextPermutation(int* nums, int numsSize){
    int i = numsSize -1;
    int x = 0;
    
    while (i > 0 && nums[i] <= nums[i-1]) {
        i--;
    }
    
    if (i == 0 ) {
        reverse(nums, numsSize);
    }
    else {
        int j = i;
        x = i - 1;
        while (j < numsSize && (nums[x] < nums[j])) {
		    ++j;
	    }
	   
        swap(&nums[x], &nums[j-1]);
	    reverse(&nums[i], numsSize-i);
    }
}
