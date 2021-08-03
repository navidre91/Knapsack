#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

void print_vect(vector<vector<int>>V){
    int len1 = V.size();

    for(int i=0; i<len1; i++){
        vector<int> &v = V[i];
        int len2 = v.size();

        for(int j=0; j<len2; j++){
            cout<<v[j]<<',';
        }
        cout<<endl;
    }

}

class Knapsack{

    public:
    
    vector<vector<double>> items;
    vector<vector<double>> DP;
    double knapsack_size;
    double num_items; 
    string file_address;



    void set_items(){
        string row;
        ifstream infile; 
        infile.open(file_address);
        infile>>knapsack_size;
        infile>>num_items;
        getline(infile,row);

        while(infile.good()){
            double item_value;
            double item_size;
            getline(infile,row);
            stringstream s(row);
            s>>item_value;
            s>>item_size;
            vector<double> item = {item_value,item_size};
            items.push_back(item);
        }
    }

    void init_DP(){
        for (int x=0; x<=knapsack_size; x++){
            DP[0][x]=0;
        }
    }

    void set_DP(){
        for (int i=1; i<=num_items; i++){
            for (int x=1; x<=knapsack_size; x++){
                double vi = items[i-1][0];
                double wi = items[i-1][1];

                double i_1 = i - 1;
                double x_wi = x - wi;
                double A_i_1_x = DP[i_1][x];
                double A_i_1_x_wi;
                if (x_wi < 0){
                    A_i_1_x_wi = 0;
                }else{
                    A_i_1_x_wi = DP[i_1][x_wi]+vi;
                }

                DP[i][x] = max(A_i_1_x,A_i_1_x_wi);

            }
        }
    }

    Knapsack(string f_address){
        cout.precision(100);
        file_address = f_address;
        set_items();
        vector<double> init(knapsack_size+1,0);
        DP.resize(num_items+1,init);
        init_DP();
        set_DP();
        cout<<DP[num_items][knapsack_size];

    }



};




int main(){

    string file_address = "G:\\My Drive\\course\\Algorithm\\knapsack\\knapsack.txt";
    Knapsack npk(file_address);
    return 0; 
}

