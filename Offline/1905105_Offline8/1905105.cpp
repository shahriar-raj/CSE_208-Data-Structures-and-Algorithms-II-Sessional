#include <bits/stdc++.h>

using namespace std;

class Matrix{
public:
    int n, f_r, f_c, serial, level, bound;
    vector<vector<char>> v;
    Matrix(int , int, int, int, int );
    Matrix( const Matrix &obj);
    Matrix();
    int getf_r();
    int getf_c();
    int getSerial();
    int getLevel();
    void setBound();
};

Matrix :: Matrix(int n_, int f_r_, int f_c_, int serial_, int level_){
    n = n_;
    f_r = f_r_;
    f_c = f_c_;
    serial = serial_;
    level = level_;
}

int Matrix ::getf_r(){
    return f_r;
}

int Matrix ::getf_c(){
    return f_c;
}

int Matrix ::getLevel(){
    return level;
}

int Matrix ::getSerial(){
    return serial;
}

void Matrix::setBound(){
    int b = 0;
    for(int i=f_c;i<n; i++){
        int cnt = 0;
        for(int j=f_r;j<n;j++){
            if(v[j][i]!='0')
                cnt++;
        }
        b = max(b, ((cnt+1)/2));
    }
    for(int i=f_r;i<n; i++){
        int cnt = 0;
        for(int j=f_c;j<n;j++){
            if(v[i][j]!='0')
                cnt++;
        }
        b = max(b, ((cnt+1)/2));
    }

    int x = 0;
    for(int i=0;i<f_c;i++){
        if(i<f_r){
            int cnt =0;
            for(int j=f_r; j<n; j++){
                if(v[j][i]!='0')
                    cnt++;
            }
            if(cnt!=0){
                x = max(x,cnt+(f_r-i));
            }
            else{
                int c = i;
                for(int k=i; k<f_r; k++){
                    if(v[k][i]!='0')
                        c = k;
                }
                x = max(x,1 + (c-i));
            }
        }
        else{
            int cnt = 0;
            for(int j=i; j<n; j++){
                if(v[j][i]!='0')
                    cnt++;
            }
            if(cnt==0){
                x = max(x,1);
            }
            else{
                x = max(x,cnt);
            }
        }
        int t = i;
        for(int m=i;m>=0;m--){
            if(v[m][i]!='0')
                t = m;
        }
        x = max(x, (i-t)+1);
    }

    for(int i=0;i<f_r;i++){
        int cnt =0;
        for(int j=f_c; j<n; j++){
            if(v[i][j]!='0')
                cnt++;
        }
        if(cnt!=0){
            x = max(x,cnt+(f_c-i));
        }
        else{
            int c = i;
            for(int k=i; k<f_c; k++){
                if(v[i][k]!='0')
                    c = k;
            }
            x = max(x,1 + (c-i));
        }
        int t = i;
        for(int m=i;m>=0;m--){
            if(v[i][m]!='0')
                t = m;
        }
        x = max(x, (i-t)+1);
    }
    bound = max(x,b);
}

Matrix :: Matrix( const Matrix &obj){
    n=obj.n;
    f_r=obj.f_r;
    f_c=obj.f_c;
    v = obj.v;
    serial = obj.serial;
    level = obj.level;
    bound = obj.bound;
}

Matrix :: Matrix(){

}

class comp{
public:
    bool operator()(const Matrix &p1, const Matrix &p2){
        if(p1.bound == p2.bound){
            if(p1.level==p2.level){
                if(p1.serial<p2.serial)
                    return true;
                else
                    return false;
            }
            else if(p1.level<p2.level){
                return true;
            }
            else
                return false;
        }
        else if(p1.bound>p2.bound){
            return true;
        }
        else{
            return false;
        }
    }
};

int main(){
    int n;
    cin >> n;
    Matrix A(n,0,0,0,0);
    for(int i=0; i<n; i++){
        vector<char> ab;
        for(int j=0; j<n; j++){
            char c;
            cin >> c;
            ab.push_back(c);
        }
        A.v.push_back(ab);
    }
    A.setBound();
    //cout << "The bound is: " <<A.bound<< endl;
    priority_queue <Matrix, vector<Matrix>, comp> mpq;
    mpq.push(A);
    Matrix B = mpq.top();
    cout << endl;
    while(1){
        Matrix C = mpq.top();
        mpq.pop();
        //cout << " The Parent matrix: " << endl;
        //cout << "Level: " << C.level << "Order: "<< C.serial << endl;
        if(C.f_c == C.f_r){
            for(int i=C.f_c; i<n; i++){
                //cout << "Frow:" << C.f_r << " Fcol:" << C.f_c+1 << " Order:" << i-C.f_c << " Level:" <<C.level+1 << endl;
                Matrix temp(n, C.f_r, C.f_c+1, i-C.f_c, C.level+1);
                temp.v = C.v;
                for(int j=0; j<n; j++){
                    temp.v[j][C.f_c] = C.v[j][i];
                    //cout << "C.f_c: " << C.f_c << " i:" << i <<endl;
                }
                int k = C.f_c;
                for(int j=C.f_c+1; j<n;){
                    if(i==k){
                        //cout <<" Skip:" <<  k <<" " <<j << endl;
                        k++;
                    }
                    else{
                        //cout << k <<" "<<j<<  endl;
                        for(int l=0; l<n; l++){
                            temp.v[l][j] = C.v[l][k];
                        }
                        k++;
                        j++;
                    }
                }
                temp.setBound();
                //cout << " the bound is: " << temp.bound << endl;
                mpq.push(temp);
            }
        }
        else{
                //cout<<C.bound<< " Bound" << endl;
            for(int i=C.f_r; i<n; i++){
                //cout << "Frow:" << C.f_r+1 << " Fcol:" << C.f_c << " Order:" << i-C.f_r << " Level:" <<C.level+1 << endl;
                Matrix temp(n, C.f_r+1, C.f_c, i-C.f_r, C.level+1);
                temp.v = C.v;
                for(int j=0; j<n; j++){
                    temp.v[C.f_r][j] = C.v[i][j];
                    //cout << "C.f_c: " << C.f_c << " i:" << i <<endl;
                }
                int k = C.f_r;
                for(int j=C.f_r+1; j<n;){
                    if(i==k){
                        //cout <<" Skip:" <<  k <<" " <<j << endl;
                        k++;
                    }
                    else{
                        //cout << k <<" "<<j<<  endl;
                        for(int l=0; l<n; l++){
                            temp.v[j][l] = C.v[k][l];
                        }
                        k++;
                        j++;
                    }
                }
                temp.setBound();
                //cout << " the bound is: " << temp.bound << endl;
                mpq.push(temp);
            }
        }

        int final_r = 0;
        if((mpq.top().f_c==n-1  && mpq.top().f_r==n-1)){
            Matrix F = mpq.top();
            final_r = mpq.top().bound;
            cout << endl;
            cout << final_r <<endl;
            for(int l=0; l<n;l++){
                for(int m=0; m<n; m++){
                    cout << C.v[l][m] << " ";
                }
                cout << endl;
            }
            cout << endl;
            //cout << "The result is: " << C.bound << endl;
            break;
        }
        //cout << mpq.size() << " Size" << endl;
    }
    return 0;
}
