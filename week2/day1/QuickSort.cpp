void QuickSort(vector<int>& vec, int left, int right)
{
  if (left >= right) return;

  int pivot = vec[(left+right)/2];
  int begin = left - 1, end = right + 1;
  while(begin < end)
  {
    do{
      begin++
    }while(vec[begin] < pivot);
    do{
      end--;
    }while(vec[end] > pivot);
    if (begin < end)
    {
      swap(vec[begin], vec[end]);
    }
  }
  QuickSort(vec, left, end);  // 此时end为mid
  QuickSort(vec, end+1, right);
}

// c++标准库——>std::sort
