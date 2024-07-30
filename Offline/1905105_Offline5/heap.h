# include <iostream>

using namespace std;

struct Node{
    int v;
    double key;
};

class Heap{
    int heap_size, capacity;
    Node *i_arr;
public:
    Heap(int vector_size);
    Heap(vector<Node> &v);
    void insert(Node);
    Node getMin();
    int size();
    void deleteKey();
    ~Heap();
};

Heap :: Heap(int vector_size){
    capacity = vector_size*2;
    i_arr = new Node[capacity+1];
    heap_size = 0;
}

Heap :: Heap(vector<Node> &v){
    capacity = v.size()*2;
    i_arr = new Node[capacity+1];
    heap_size = 0;
    for(int i = 0; i < v.size(); i++)
        insert(v[i]);
}

Heap :: ~Heap(){
    delete i_arr;
}

void Heap::insert(Node element){
    if(heap_size == capacity){
        cout << "Capacity reached" <<endl;
    }
    else{
        i_arr[++heap_size] = element;
        for(int i = heap_size; i!=0; i=i/2){
            if(i==1)
                break;
            if(i_arr[i].key<i_arr[i/2].key){
                swap(i_arr[i],i_arr[i/2]);
            }
            else{
                break;
            }
        }
    }
}

int Heap::size(){
    return heap_size;
}

Node Heap::getMin(){
    if(heap_size>0)
        return i_arr[1];
}

void Heap::deleteKey(){
    if(heap_size == 0)
        cout << "The heap is empty" <<endl;
    else{
        i_arr[1] = i_arr[heap_size--];
        int i = 1;
        while(true){
           int l = 2*i;
           int r = 2*i +1;
            if(l>heap_size)
                break;
            if(r>heap_size){
                if(i_arr[l].key<i_arr[i].key){
                    swap(i_arr[l],i_arr[i]);
                }
                break;
            }
            if(i_arr[l].key<i_arr[i].key||i_arr[r].key<i_arr[i].key){
                if(i_arr[l].key<i_arr[r].key){
                    swap(i_arr[l],i_arr[i]);
                    i = l;
                }
                else{
                    swap(i_arr[r],i_arr[i]);
                    i = r;
                }
            }
            else
                break;
        }
    }
}

void heapsort(vector<Node>&v){
    Heap h1(v);
    for(int i=0; i<v.size(); i++){
        v[i] = h1.getMin();
        h1.deleteKey();
    }
}


