// 汉诺塔问题

void hanoi(int n, char src, char tmp, char tgt)
{
  if (n == 1)
  {
    cout << "Move disk 1 from" << src << " to " << tgt << endl;
    return;
  }

  hanoi(n-1, src, tgt, tmp);
  cout << "Move disk" << n << "from" << src << "to" << tgt << endl;
  hanoi(n-1, tmp, src, tgt);
}




// 力扣08.06 汉诺塔问题
void hanota(vector<int>& A, vector<int>& B, vector<int>& C)
{
  int n= A.size();
  moveDisks(n, A, B, C);
}
void moveDisks(int n, vector<int>& A, vector<int>& B, vector<int>& C)
{
  if (n == 0) return;
  moveDisks(n-1, A, C, B);
  C.push_back(A.back());
  A.pop_back();
  moveDisks(n-1,B,A,C);
}
