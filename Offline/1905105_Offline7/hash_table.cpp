#include <bits/stdc++.h>

using namespace std;

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
    //cout << h << endl;
    for(int i=1; i<7; i++){
        h = s[i] + a*h ;
        //cout << h << endl;
    }
    //cout << h << endl;
    return h;
}

int hash_2(string s, int N){                 //HASH_2 (FUNCTION)
    long long int h = 0;
    for(int i=0; i<7; i++){
        h = h+int(s[i]);
    }
    h = 31*h + 43;
    return(h%N);
}

/* START OF SEPARATE CHAINING------------------------------------------------------------------------------------------------- */

class Separate_Chaining{
    int N;
    list<pair<string,int>> *arr;
public:
    Separate_Chaining(int N);
    pair<string,int> Search(string K);
    void insert(string B , int v);
    void del(string K);
};

Separate_Chaining::Separate_Chaining(int N){
    this->N = N;
    arr = new list<pair<string,int>>[N];
}

void Separate_Chaining::insert(string B , int v){
    long long int h = hash_1(B,N);
    int l = h%N;
    pair<string,int> NEW;
    NEW.first = B;
    NEW.second = v;
    arr[l].push_back(NEW);
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

// END OF SEPARATE CHAINING-------------------------------------------------------------------------------------------------------------

/* START OF LINEAR PROBING---------------------------------------------------------------------------------------------- */

class Linear_Probing{
    pair<string,int>* lin;
    int N;
public:
    Linear_Probing(int N);
    int Search(string K);
    void insert(string B , int v);
    void del(string K);
    int h(string k ,int m){
        return (hash_1(k,N)+m)%N;
    }
};

Linear_Probing :: Linear_Probing(int N){
    this->N = N;
    lin = new pair<string, int> [N];
    for(int i=0; i<N; i++){
        lin[i].first = "\0" ;
    }
    //cout << lin[0].first << endl;
}

void Linear_Probing :: insert(string B, int v){
    int m = 0;
    int l = h(B,m);
    while(lin[l].first != "\0" && lin[l].first != "DEL"){
        m = m+1;
        l = h(B,m);
    }
    lin[l].first = B;
    lin[l].second = v;
    //cout << lin[l].first << " " << lin[l].second;
}

void Linear_Probing::del(string K){
    int m = 0;
    int l = h(K,m);
    while(lin[l].first != "\0"){
        if(K == lin[l].first){
            lin[l].first = "DEL";
            break;
        }
        m = m+1;
        l = h(K,m);
    }
}

int Linear_Probing::Search(string K){
    int m = 0;
    int prob = 0;
    int l = h(K,m);
    pair<string,int> F;
    F.first = "NOT_F";
    F.second = -1;
    while(lin[l].first != "\0"){
        if(K == lin[l].first){
            F.first = lin[l].first;
            F.second = lin[l].second;
            break;
        }
        prob++;
        m = m+1;
        l = h(K,m);
    }
    return prob;
}

// END OF LINEAR PROBING-----------------------------------------------------------------------------------------------------------------

/* START OF QUADRATIC PROBING-----------------------------------------------------------------------------------------------------*/

class Quadratic_Probing{
    pair<string,int>* lin;
    int N;
public:
    Quadratic_Probing(int N);
    int Search(string K);
    void insert(string B , int v);
    void del(string K);
    int h(string k ,int m){
        return (hash_1(k,N)+ m*31 +(m*m*43))%N;
    }
};

Quadratic_Probing :: Quadratic_Probing(int N){
    this->N = N;
    lin = new pair<string, int> [N];
    for(int i=0; i<N; i++){
        lin[i].first = "\0" ;
    }
    //cout << lin[0].first << endl;
}

void Quadratic_Probing :: insert(string B, int v){
    int m = 0;
    int l = h(B,m);
    while(lin[l].first != "\0" && lin[l].first != "DEL"){
        m = m+1;
        l = h(B,m);
    }
    lin[l].first = B;
    lin[l].second = v;
    //cout << lin[l].first << " " << lin[l].second;
}

void Quadratic_Probing::del(string K){
    int m = 0;
    int l = h(K,m);
    while(lin[l].first != "\0"){
        if(K == lin[l].first){
            lin[l].first = "DEL";
            break;
        }
        m = m+1;
        l = h(K,m);
    }
}

int Quadratic_Probing::Search(string K){
    int m = 0;
    int prob = 0;
    int l = h(K,m);
    pair<string,int> F;
    F.first = "NOT_F";
    F.second = -1;
    while(lin[l].first != "\0"){
        if(K == lin[l].first){
            F.first = lin[l].first;
            F.second = lin[l].second;
            break;
        }
        prob++;
        m = m+1;
        l = h(K,m);
    }
    return prob;
}

// END OF QUADRATIC PROBING-----------------------------------------------------------------------------------------------------------------

/* START OF DOUBLE HASHING-----------------------------------------------------------------------------------------------------*/

class Double_Hash{
    pair<string,int>* lin;
    int N;
public:
    Double_Hash(int N);
    int Search(string K);
    void insert(string B , int v);
    void del(string K);
    int h(string k ,int m){
        return (hash_1(k,N)+ m*hash_2(k,N))%N;
    }
};

Double_Hash :: Double_Hash(int N){
    this->N = N;
    lin = new pair<string, int> [N];
    for(int i=0; i<N; i++){
        lin[i].first = "\0" ;
    }
    //cout << lin[0].first << endl;
}

void Double_Hash :: insert(string B, int v){
    int m = 0;
    int l = h(B,m);
    while(lin[l].first != "\0" && lin[l].first != "DEL"){
        m = m+1;
        l = h(B,m);
    }
    lin[l].first = B;
    lin[l].second = v;
    //cout << lin[l].first << " " << lin[l].second;
}

void Double_Hash::del(string K){
    int m = 0;
    int l = h(K,m);
    while(lin[l].first != "\0"){
        if(K == lin[l].first){
            lin[l].first = "DEL";
            break;
        }
        m = m+1;
        l = h(K,m);
    }
}

int Double_Hash::Search(string K){
    int m = 0;
    int prob = 0;
    int l = h(K,m);
    pair<string,int> F;
    F.first = "NOT_F";
    F.second = -1;
    while(lin[l].first != "\0"){
        if(K == lin[l].first){
            F.first = lin[l].first;
            F.second = lin[l].second;
            break;
        }
        prob++;
        m = m+1;
        l = h(K,m);
    }
    return prob;
}

// END OF DOUBLE HASHING-----------------------------------------------------------------------------------------------------------------

int main(){
    int N;
    cin >> N;
    freopen("output.csv","w",stdout);
    int t_s[6],t_s_1[6];
    pair<int,float> t_l[6], t_l_1[6];
    pair<int,float> t_q[6], t_q_1[6];
    pair<int,float> t_d[6], t_d_1[6];

/*----------------------------------------------------------------------------------------------------------------------------------*/

    float co = 0.4;
    int re = 0;
    cout << "                  Table:1  Separate_Chaining    " << endl;
    cout << ",Before Deletion,After Deletion" << endl;
    cout << "Load_Factor,AVG_Time,AVG_Time" << endl;
    while(co<1)
    {
        vector<string> words;
        vector<string> search_words;
        vector<string> del_words;
        int abcd = co*N;
        for(int i=0; i<abcd; i++)
        {
            string s1 =random(i);
            words.push_back(s1);
        }

        for(int i=0; i<(words.size()/10); i++)
        {
            search_words.push_back(words[(10*i)+(rand()%10)]);
        }

        for(int i=0; i<(search_words.size()/2); i++)
        {
            del_words.push_back(search_words[(2*i)+(rand()%2)]);
        }

        Separate_Chaining s1(N);
        int v = 1;
        for(int i=0; i<words.size(); i++)
        {
            s1.insert(words[i],v++);
        }
        auto start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            //cout << f_b << endl;
            s1.Search(search_words[i]);
        }
        //cout <<"ALARM" << f_b << endl;
        auto end = chrono::steady_clock::now();
        t_s[re] =  (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        cout <<co << ","<< (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << ",";
        for(int i=0; i<del_words.size(); i++)
        {
            s1.del(del_words[i]);
        }

        start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            //cout << f_b << endl;
            s1.Search(search_words[i]);
        }
        end = chrono::steady_clock::now();
        t_s_1[re] =  (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        cout <<(chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << endl;
        co += 0.1;
        re++;
    }
    cout << endl;
/*----------------------------------------------------------------------------------------------------------------------------------*/

    co = 0.4;
    re = 0;
    cout << "                  Table:2  Linear Probing    " << endl;
    cout << ",    Before Deletion,,     After Deletion" << endl;
    cout << "Load_Factor,AVG_Time,Num_OF_Probes,AVG_Time,Num_OF_Probes" << endl;
    while(co<1)
    {
        vector<string> words;
        vector<string> search_words;
        vector<string> del_words;
        int abcd = co*N;
        for(int i=0; i<abcd; i++)
        {
            string s1 =random(i);
            words.push_back(s1);
        }

        for(int i=0; i<(words.size()/10); i++)
        {
            search_words.push_back(words[(10*i)+(rand()%10)]);
        }

        for(int i=0; i<(search_words.size()/2); i++)
        {
            del_words.push_back(search_words[(2*i)+(rand()%2)]);
        }

        Linear_Probing l1(N);
        int v = 1;
        int f_b =0;
        for(int i=0; i<words.size(); i++)
        {
            l1.insert(words[i],v++);
        }
        auto start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            //cout << f_b << endl;
            f_b+=l1.Search(search_words[i]);
        }
        auto end = chrono::steady_clock::now();
        //cout <<"ALARM" << f_b << endl;
        t_l[re].first = (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        t_l[re].second = float(f_b)/(search_words.size());
        cout <<co << ","<< (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << ",";
        cout << float(f_b)/(search_words.size()) << "," ;

        for(int i=0; i<del_words.size(); i++)
        {
            l1.del(del_words[i]);
        }

        f_b = 0;
        start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            //cout << f_b << endl;
            f_b+=l1.Search(search_words[i]);
        }
        end = chrono::steady_clock::now();
        //cout <<"ALARM" << f_b << endl;
        t_l_1[re].first = (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        t_l_1[re].second = float(f_b)/(search_words.size());
        cout <<(chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << ",";
        cout << float(f_b)/(search_words.size()) << endl;
        co += 0.1;
        re++;
    }
    cout << endl;
/*----------------------------------------------------------------------------------------------------------------------------------*/

    co = 0.4;
    re = 0;
    cout << "                  Table:3  Quadratic Probing  " << endl;
    cout << ",    Before Deletion,,    After Deletion" << endl;
    cout << "Load_Factor,AVG_Time,Num_OF_Probes,AVG_Time,Num_OF_Probes" << endl;
    while(co<1)
    {
        vector<string> words;
        vector<string> search_words;
        vector<string> del_words;
        int abcd = co*N;
        for(int i=0; i<abcd; i++)
        {
            string s1 =random(i);
            words.push_back(s1);
        }

        for(int i=0; i<words.size()/10; i++)
        {
            search_words.push_back(words[(10*i)+(rand()%10)]);
        }

        for(int i=0; i<(search_words.size()/2); i++)
        {
            del_words.push_back(search_words[(2*i)+(rand()%2)]);
        }

        Quadratic_Probing q1(N);
        int v = 1;
        int f_b =0;
        for(int i=0; i<words.size(); i++)
        {
            q1.insert(words[i],v++);
        }
        auto start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            f_b+=q1.Search(search_words[i]);
        }
        auto end = chrono::steady_clock::now();
        t_q[re].first = (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        t_q[re].second = float(f_b)/(search_words.size());
        cout <<co << ","<< (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << ",";
        cout << float(f_b)/(search_words.size()) << ",";

        for(int i=0; i<del_words.size(); i++)
        {
            q1.del(del_words[i]);
        }

        f_b = 0;
        start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            f_b+=q1.Search(search_words[i]);
        }
        end = chrono::steady_clock::now();
        t_q_1[re].first = (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        t_q_1[re].second = float(f_b)/(search_words.size());
        cout <<(chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << ",";
        cout << float(f_b)/(search_words.size()) << endl;
        co += 0.1;
        re++;
    }
    cout << endl;
/*----------------------------------------------------------------------------------------------------------------------------------*/

    co = 0.4;
    re = 0;
    cout << "                  Table:4  Double Hashing    " << endl;
    cout << ",    Before Deletion,,     After Deletion" << endl;
    cout << "Load_Factor,AVG_Time,Num_OF_Probes,AVG_Time,Num_OF_Probes" << endl;
    while(co<1)
    {
        vector<string> words;
        vector<string> search_words;
        vector<string> del_words;
        int abcd = co*N;
        for(int i=0; i<abcd; i++)
        {
            string s1 =random(i);
            words.push_back(s1);
        }

        for(int i=0; i<(words.size()/10); i++)
        {
            search_words.push_back(words[(10*i)+(rand()%10)]);
        }

        for(int i=0; i<(search_words.size()/2); i++)
        {
            del_words.push_back(search_words[(2*i)+(rand()%2)]);
        }

        Double_Hash d1(N);
        int v = 1;
        int f_b =0;
        for(int i=0; i<words.size(); i++)
        {
            d1.insert(words[i],v++);
        }
        auto start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            //cout << f_b << endl;
            f_b+=d1.Search(search_words[i]);
        }
        auto end = chrono::steady_clock::now();
        //cout <<"ALARM" << f_b << endl;
        t_d[re].first = (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        t_d[re].second = float(f_b)/(search_words.size());
        cout <<co << ","<< (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << ",";
        cout << float(f_b)/(search_words.size()) << "," ;

        for(int i=0; i<del_words.size(); i++)
        {
            d1.del(del_words[i]);
        }

        f_b = 0;
        start = chrono::steady_clock::now();
        for(int i=0; i<search_words.size(); i++)
        {
            //cout << f_b << endl;
            f_b+=d1.Search(search_words[i]);
        }
        end = chrono::steady_clock::now();
        //cout <<"ALARM" << f_b << endl;
        t_d_1[re].first = (chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size();
        t_d_1[re].second = float(f_b)/(search_words.size());
        cout <<(chrono::duration_cast<chrono::nanoseconds>(end - start).count())/search_words.size()<< " ns" << ",";
        cout << float(f_b)/(search_words.size()) << endl;
        co += 0.1;
        re++;
    }
    cout << endl;
/*----------------------------------------------------------------------------------------------------------------------------------*/

    co = 0.4;
    re = 0;

    while(co<1){
        cout << "           Table: " << re+5 << "   LOAD FACTOR:" << co << endl;
        cout << ",    Before Deletion,,    After Deletion" << endl;
        cout << "Method,AVG_Time,Num_OF_Probes,AVG_Time,Num_OF_Probes" << endl;
        cout << "Separate Chaining," << t_s[re] << ",N/A," << t_s_1[re] <<",N/A" <<endl;
        cout << "Linear Probing," << t_l[re].first << ","<<t_l[re].second << "," << t_l_1[re].first <<"," <<t_l_1[re].second<<endl;
        cout << "Quadratic Probing," << t_q[re].first << ","<<t_q[re].second << "," << t_q_1[re].first <<"," <<t_q_1[re].second<<endl;
        cout << "Double Hashing," << t_d[re].first << ","<<t_d[re].second << "," << t_d_1[re].first <<"," <<t_d_1[re].second<<endl;
        co =co+0.1;
        re++;
        cout << endl;
    }

    return 0;
}
