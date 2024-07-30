#include <bits/stdc++.h>

using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;

    return true;
}

char* random(int T){                            //WORD GENERATOR
    char* word = new char[7];
    int r;
    srand(T);
    for(int i=0;i<7;i++){
        r = rand()%26;
        word[i] = char('a' + r);
    }
    return word;
}

long long int hash_1(string s, int N){         //HASH_1 (FUNCTION)
    long long int h = 0;
    int a = 37;
    h = s[0];
    for(int i=1; i<7; i++){
        h = s[i] + a*h ;
    }
    return h;
}

class Separate_Chaining{
    int N;
    list<pair<string,int>> *arr;
    int *chain;
public:
    Separate_Chaining(int N);
    pair<string,int> Search(string K);
    void insert(string B , int v);
    void del(string K);
    void rehash();
};

Separate_Chaining::Separate_Chaining(int N){
    this->N = N;
    arr = new list<pair<string,int>>[N];
    chain = new int[N];\
    for(int x=0; x<N; x++)
        chain[x] =0;
}

void Separate_Chaining::insert(string B , int v){
    long long int h = hash_1(B,N);
    int l = h%N;
    pair<string,int> NEW;
    NEW.first = B;
    NEW.second = v;
    arr[l].push_back(NEW);
    chain[l]++;
}

void Separate_Chaining::del(string K){
    long long int h = hash_1(K,N);
    int l = h%N;
    list<pair<string,int>> :: iterator i;
    for(i = arr[l].begin(); i!= arr[l].end(); i++){
        if((*i).first == K){
            arr[l].erase(i);
            break;
        }
    }
}

pair<string,int> Separate_Chaining:: Search(string K){
    long long int h = hash_1(K,N);
    int l = h%N;
    pair<string,int> F;
    F.first = "N_F";
    F.second = -1;
    list<pair<string,int>> :: iterator i;
    for(i = arr[l].begin(); i!= arr[l].end(); i++){
        if((*i).first == K){
            F.first = (*i).first;
            F.second = (*i).second;
            break;
        }
    }
    return F;
}

void Separate_Chaining :: rehash(){
    sort(chain,chain+N);
    if(chain[N-1]>10){
        int temp = N;
        N = 1.2*N;
        while(!isPrime(N)){
            N++;
        }
        list<pair<string, int>> *new_arr = new list<pair<string, int>>[N];
        for(int z=0; z<temp; z++){
            if(arr[z]!=nullptr){
                list<pair<string,int>> :: iterator i;
                for(i = arr[z].begin(); i!= arr[z].end(); i++){
                    s2.insert((*i).first,(*i).second);
                }
            }
        }
        return s2;
    }
    else{
        return *this;
    }
}

int main(){
    int N;
    float p;
    cin >> N >> p;
    vector<string> words;
    vector<string> search_words;
    vector<string> del_words;
    int abcd = p*N;
    for(int i=0; i<abcd; i++)
    {
        string s1 =random(i);
        words.push_back(s1);
    }

    for(int i=0; i<(words.size()/10); i++)
    {
        search_words.push_back(words[(10*i)+(rand()%10)]);
    }

    Separate_Chaining s1(N);
    int v = 1;
    for(int i=0; i<words.size(); i++)
    {
        if(i%100==0 && i!=0 ){
            s1 = s1.rehash();
        }
        s1.insert(words[i],v++);
    }

    return 0;
}
