#include "mySort.h"

void PrintArray(int a[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

// void BubbleSort(int a[], int size) {
//   for (int i = size - 1; i > 0; i--) {
//     int flag = 1;
//     for (int j = 0; j < i; j++) {
//       if (a[j] > a[j + 1]) {
//         SWAP(a[j], a[j + 1])
//         flag = 0;
//       }
//     }
//     if (flag == 1) break;
//   }
// }

// void InsertSort(int arr[], int size) {
//   int i, key, j;
//   for (i = 1; i < size; i++) {
//     key = arr[i];
//     j = i - 1;
//     while (j >= 0 && arr[j] > key) {
//       arr[j + 1] = arr[j];
//       j = j - 1;
//     }
//     arr[j + 1] = key;
//   }
// }

int QuickSortPartition(int a[], int left, int right) {
  int i, k = left;
  for (i = left; i < right; i++) {
    if (a[i] < a[right]) {
      SWAP(a[i], a[k])
      k++;
    }
  }
  SWAP(a[k], a[right])
  return k;
}

void QuickSort(int a[], int left, int right) {
  int pivot;
  if (left < right) {
    pivot = QuickSortPartition(a, left, right);
    QuickSort(a, left, pivot - 1);
    QuickSort(a, pivot + 1, right);
  }
}

void AdjustMaxHeap(int* a, int root, int len) {
  int dad = root;
  int son = 2 * dad + 1;
  while (son < len) {
    if (son + 1 < len && a[son] < a[son + 1]) {
      son++;
    }
    if (a[son] > a[dad]) {
      SWAP(a[son], a[dad])
      dad = son;
      son = 2 * dad + 1;
    } else {
      break;
    }
  }
}

void HeapSort(int a[], int size) {
  int i;

  // 调整堆为大根堆
  for (i = size / 2 - 1; i >= 0; i--) {
    AdjustMaxHeap(a, i, size);
  }
  // 交换堆顶和最后一个元素,并调整顶点,重新得到大根堆
  SWAP(a[0], a[size - 1])
  for (i = size - 1; i > 1; i--) {
    AdjustMaxHeap(a, 0, i);
    SWAP(a[0], a[i - 1]);
  }
}

void Merge(int array[], int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // 创建临时数组
  int L[n1], R[n2];

  // 将数据复制到临时数组 L[] 和 R[]
  for (i = 0; i < n1; i++) {
    L[i] = array[left + i];
  }
  for (j = 0; j < n2; j++) {
    R[j] = array[mid + 1 + j];
  }

  // 归并临时数组到 array[left..right]
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      array[k] = L[i];
      i++;
    } else {
      array[k] = R[j];
      j++;
    }
    k++;
  }

  // 复制剩余的元素
  while (i < n1) {
    array[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    array[k] = R[j];
    j++;
    k++;
  }
}

void MergeSort(int array[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    // 分割数组
    MergeSort(array, left, mid);
    MergeSort(array, mid + 1, right);

    // 归并已分割的数组
    Merge(array, left, mid, right);
  }
}

void CountingSort(int arr[], int size) {
  int max = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  int count[max + 1];
  for (int i = 0; i <= max; i++) {
    count[i] = 0;
  }
  for (int i = 0; i < size; i++) {
    count[arr[i]]++;
  }
  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }
  int output[size];
  for (int i = size - 1; i >= 0; i--) {
    output[count[arr[i]] - 1] = arr[i];
    count[arr[i]]--;
  }
  for (int i = 0; i < size; i++) {
    arr[i] = output[i];
  }
}

int CompareStruct(const void* first, const void* second) {
  pstu a = (pstu)first;
  pstu b = (pstu)second;
  return a->score - b->score;
}

int CompareIntegers(const void* first, const void* second) {
  int* a = (int*)first;
  int* b = (int*)second;
  return *b-*a;
}

int CompareStructPointer(const void* first, const void* second) {
  pstu a = *(pstu*)first;
  pstu b = *(pstu*)second;
  return b->score - a->score;
}

// void FindTheKMax(int arr[], int size, int k) {
//   // Build a min-heap with k nodes
//   for (int i = k / 2 - 1; i >= 0; i--) {
//     AdjustMaxHeap(arr, i, k);
//   }

//   // Find the kth largest element
//   for (int i = k; i < size; i++) {
//     if (arr[i] > arr[0]) {
//       std::swap(arr[i], arr[0]);
//       AdjustMaxHeap(arr, 0, k);
//     }
//   }
// }
