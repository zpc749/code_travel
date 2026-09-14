void MergeSort(vector<int>& vec, int left, int right)  // 包含右边，即right = size -1
{
  if (left >= right) return;

  int mid = (left+right)/2;
  MergeSort(vec, left, mid);
  MergeSort(vec, mid+1, right);

  int k = 0;
  int i = left, j = mid+1;
  vector<int> tmp;
  while( i <= mid && j <= right)
  {
    if (vec[i] <= vec[j])
    {
      tmp.push_back(vec[i++]);
    }
    else
    {
      tmp.push_back(vec[j++});
    }
  }
  while(i <= mid)
    tmp.push_back(vec[i++]);
  while(j <= right)
    tmp.push_back(vec[j++]);
  for (int i = left, k = 0;i<=right;i++)
  {
    vec[i] = tmp[k++];
  }
}

// c++标准库——>std::stable_sort
