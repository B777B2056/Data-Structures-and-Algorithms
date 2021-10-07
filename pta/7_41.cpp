#include <iostream>
#include <vector>
using namespace std;

/*重点看cmp函数，怎么实现"相同值的元素排名一致"，以及自定义cmp函数与快排等排序算法的结合*/

struct Student
{
    string id;
    int grade, num;
    int rankPoint, rankAll;
    Student(string a, int b, int c) : id(a), grade(b), num(c) {}
};

// 从大到小排序
int cmp(Student& a, Student& b)
{
    int result;
    result = b.grade - a.grade;
    if(result == 0)
    {
        if(a.id < b.id)
            return -1;
        else if(a.id == b.id)
            return 0;
        else
            return 1;
    }
    return result;
}

void quickSort(vector<Student>& v, int l, int r)
{
    if(l >= r)
        return;
    Student pivot = v[l];
    int i = l, j = r;
    while(i < j)
    {
        while((i < j) && (cmp(v[j], pivot) >= 0))
            j--;
        if(i < j)
            v[i++] = v[j];
        while((i < j) && (cmp(v[i], pivot) < 0))
            i++;
        if(i < j)
            v[j--] = v[i];
    }
    v[i] = pivot;
    quickSort(v, l, i - 1);
    quickSort(v, i + 1, r);
}

void ex7_41()
{
    unsigned int i, j, grade, N, K;
    string id;
    cin >> N;
    vector<Student> vec[N];
    vector<Student> all;
    for(i = 0; i < N; i++)
    {
        cin >> K;
        for(j = 0; j < K; j++)
        {
            cin >> id >> grade;
            vec[i].push_back(Student(id, grade, i + 1));
        }
    }
    // 先对各考点排序,计算各考点的排名
    for(i = 0; i < N; i++)
    {
        quickSort(vec[i], 0, vec[i].size() - 1);
        vec[i][0].rankPoint = 1;
        all.push_back(vec[i][0]);
        for(j = 1; j < vec[i].size(); j++)
        {
            if(vec[i][j - 1].grade == vec[i][j].grade)
                vec[i][j].rankPoint = vec[i][j - 1].rankPoint;
            else
                vec[i][j].rankPoint = j + 1;
            all.push_back(vec[i][j]);
        }
    }
    // 再进行总排序
    quickSort(all, 0, all.size() - 1);
    all[0].rankAll = 1;
    cout << all.size() << endl;
    for(j = 1; j < all.size(); j++)
    {
        if(all[j - 1].grade == all[j].grade)
            all[j].rankAll = all[j - 1].rankAll;
        else
            all[j].rankAll = j + 1;
    }
    // 输出
    for(Student st : all)
    {
        cout << st.id << " " << st.rankAll << " " << st.num << " " << st.rankPoint << endl;
    }
}