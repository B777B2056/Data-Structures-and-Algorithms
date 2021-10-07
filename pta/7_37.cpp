#include <iostream>
#include <string>
using namespace std;

/*本题还可以使用三向切割的快速排序算法，具体自行百度*/
struct Student
{ 
    int grade;
    string info[3]; 
};

// 比较函数
int cmp(const Student& a, const Student& b, const int C)
{
    int r;
    if(C != 3)
    {
        if(a.info[C] < b.info[C])
            r = -1;
        else if(a.info[C] == b.info[C])
            r = 0;
        else
            r = 1;
    }
    else
    {
        if(a.grade < b.grade)
            r = -1;
        else if(a.grade == b.grade)
            r = 0;
        else
            r = 1;
    }
    /*相同姓名或者相同成绩*/
    if(r == 0)
    {
        if(a.info[1] < b.info[1])
            r = -1;
        else if(a.info[1] == b.info[1])
            r = 0;
        else
            r = 1;
    }
    return r;
}

// 三点取中法选主元
void getPivot(Student *a, int left, int right, int C)
{
    int mid = (left + right) / 2;
    if ((cmp(a[left], a[mid], C) != 1) && (cmp(a[left], a[right], C) != -1)) 
        mid = left;
    else if ((cmp(a[right], a[mid], C) != 1) && (cmp(a[right], a[left], C) != -1)) 
        mid = right;
    Student temp = a[left];
    a[left] = a[mid];
    a[mid] = temp;
}

void quickSort(Student *a, int left, int right, int C)
{
    if(left >= right)
        return;
    getPivot(a, left, right, C);
    Student pivot = a[left];
    int i = left, j = right;
    while(i < j)
    {
        while((i < j) && (cmp(a[j], pivot, C) != -1))
            j--;
        if(i < j)
            a[i++] = a[j];
        while((i < j) && (cmp(a[i], pivot, C) == -1))
            i++;
        if(i < j)
            a[j--] = a[i];
    }
    a[i] = pivot;
    quickSort(a, left, i - 1, C);
    quickSort(a, i + 1, right, C);
}

void ex7_37()
{
    ios::sync_with_stdio(false);
    int i, N, C;
    cin >> N >> C;
    Student *s = new Student[N];
    for(i = 0; i < N; i++)
        cin >> s[i].info[1] >> s[i].info[2] >> s[i].grade;
    quickSort(s, 0, N - 1, C);
    for(i = 0; i < N; i++)
        cout << s[i].info[1] << " " << s[i].info[2] << " " << s[i].grade << "\n";
    delete []s;
}
