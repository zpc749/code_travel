// 最近点对问题
思路：
1. 分解：按x排序，从中点mid分成左右两半
2. 解决：递归求左边最近距离dL，右边最近距离dR
3. 合并：令d=min（dL，dR），检查横跨中线的点对，看是否有小于d的

struct Point
{
  double x,y;
}
double dist(const Point& a, const Point& b)
{
  return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
vector<Point> byY;
double closestUtil(vector<Point>& pts, int l, int r, vector<Point>& tmp)
{
  if (r - l <= 3)
  {
    double d = DBL_MAX;
    for (int i = 1;i <= r; i++)
    {
      for (int j = i+1; j <= r;j++)
      {
        d = min(d, dist(pts[i], pts[j]));
      }
    }
    sort(pts.begin() + L, pts.begin() + r + l, [](const Point& a, const Point& b){return a.y < b.y;});
    return d;
  }
  int mid = l + (r-l)/2;
  double midX = pts[mid].x;
  double dL = closestUtil(pts, l, mid, tmp);
  double dR = closestUtil(pts, mid+1, r, tmp);
  double d = min(dL, dR);
  int i = l, j = mid +1, k = l;
  while(i <= mid && j <= r)
  {
    if (pts[i].y <= pts[j].y)
      tmp[k++] = pts[i++];
    else
      tmp[k++] = pts[j++];
  } 
  while(i <= mid) tmp[k++] = pts[i++];
  while(j <= r) tmp[k++] = pts[j++];
  for (int p = l; p <= r; p++) pts[p] = tmp[p];

  vector<Point> strip;
  for (int p = l; p <= r; p++)
  {
    if (fabs(pts[p].x - midx) < d)
      strip.push_back(pts[p]);
  }
  for (int i = 0;i<strip.size();i++)
  {
    for (int j = i+1;j < strip.size() && strip[j].y - strip[i].y < d; j++)
    {
      d = min(d, dist(strip[i], strip[j]));
    }
  }
  return d;
}

double closestPair(vector<Poinr>& pts)
{
  sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {return a.x < b.x});
  return closestUtil(pts, 0, pts.size()-1);
}
