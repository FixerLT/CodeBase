#include <bits/stdc++.h>
using namespace std;

/*
 * first sorted fragment is [start1, start2) and second is [start2, end)
 * they are merged in growing order and stored in [start1, end)
 */
void mergeFragments(vector<int> &src, int start1, int start2, int end){
    vector<int> sortedFragments(end - start1);
    for(int i=0, first=start1, second=start2; i<sortedFragments.size(); i++){
        if(first==start2){
            sortedFragments[i] = src[second];
            second++;
        } else if (second == end){
            sortedFragments[i] = src[first];
            first++;
        } else if(src[first] < src[second]){
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

void mergeSort(vector<int> &src){
    for(int step = 1; step < src.size(); step*=2){
        for(int i=0; i<src.size(); i+=step*2){
            int j = min(i+step, (int)src.size());
            int end = min(j+step, (int)src.size());
            mergeFragments(src, i, j, end);
        }
    }
}

void testMergeSort(){
    vector<int> randomData(rand() % 1000);
    for(int i=0; i<randomData.size(); i++)
        randomData[i] = rand()%5000;
    vector<int> copyOfRandomData(randomData);
    sort(copyOfRandomData.begin(), copyOfRandomData.end());
    mergeSort(randomData);
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