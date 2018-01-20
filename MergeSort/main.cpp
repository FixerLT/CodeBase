#include <bits/stdc++.h>
using namespace std;

/*
 * first sorted fragment is [start1, start2) and second is [start2, end)
 * they are merged in growing order and stored in [start1, end)
 */
template <class MyClass>
void mergeFragments(vector<MyClass> &src, int start1, int start2, int end, bool less(MyClass, MyClass)){
    vector<MyClass> sortedFragments(end - start1);
    for(int i=0, first=start1, second=start2; i<sortedFragments.size(); i++){
        if(first==start2){
            sortedFragments[i] = src[second];
            second++;
        } else if (second == end){
            sortedFragments[i] = src[first];
            first++;
        } else if(less(src[first], src[second])){
            sortedFragments[i] = src[first];
            first++;
        } else {
            sortedFragments[i] = src[second];
            second++;
        }
    }
    for(int i=0, j=start1; j<end; i++, j++)
        src[j] = sortedFragments[i];
}

template <class MyClass>
void mergeSort(vector<MyClass> &src, bool less(MyClass, MyClass)){
    for(int step = 1; step < src.size(); step*=2){
        for(int i=0; i<src.size(); i+=step*2){
            int j = min(i+step, (int)src.size());
            int end = min(j+step, (int)src.size());
            mergeFragments(src, i, j, end, less);
        }
    }
}

void testMergeSort(){
    vector<int> randomData(rand() % 1000);
    for(int i=0; i<randomData.size(); i++)
        randomData[i] = rand()%5000;
    vector<int> copyOfRandomData(randomData);
    sort(copyOfRandomData.begin(), copyOfRandomData.end());
    mergeSort<int>(randomData, [](int a, int b){return a<b;});
    for(int i=0; i<randomData.size(); i++){
        if(randomData[i] != copyOfRandomData[i]){
            cout<<"Merge sort:\n";
            for(int j : randomData)
                cout<<j<<' ';
            cout<<"\nEtalon:\n";
            for(int j : copyOfRandomData)
                cout<<j<<' ';
            cout<<"\n\n";
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    for(int i=0; i<10; i++)
        testMergeSort();
    return 0;
}