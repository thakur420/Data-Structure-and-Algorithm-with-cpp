#include<bits/stdc++.h>
using namespace std;
const int N = 4000;
const int base = 31;
const int mod = 1e9 + 7;

class ModArithmetic{
public:
    static int add(int a,int b,int mod){
        int res = (a + b) % mod;
        if(res < 0)
            res += mod;
        return res;
    }
    static int mult(int a,int b,int mod){
        int res = (a * 1LL * b) % mod;
        if(res < 0)
            res += mod;
        return res;
    }
    static int pow(int a,int b,int mod){
        int res = 1;
        while(b){
            if(b&1){
                res = mult(res,a,mod);
            }
            a = mult(a,a,mod);
            b /= 2;
        }
    	return res;
    }
};
 
class StringHash{
    
    string str;
    int pw[N],inv[N],hash[N];
public:
    StringHash(string str):str(str){
        precompute();
        build();
    }
 
    void precompute(){
        pw[0] = 1;
        // cout << "printing pw[i] .....\n";
        for(int i=1;i<N;i++){
            pw[i] = ModArithmetic::mult(base,pw[i-1],mod);
            // cout << pw[i] <<" ";
        }
		cout << "\n";
        int base_inv = ModArithmetic::pow(base,mod-2,mod);
        inv[0] = 1;
        // cout << "printing inv[i] .....\n";
        for(int i=1;i<N;i++){
            inv[i] = ModArithmetic::mult(inv[i-1],base_inv,mod);
            // cout << inv[i] << " ";
        }
    }
    void build(){
        int n = str.length();
        for(int i=0;i<n;i++){
            int prev_hash = (i==0? 0 : hash[i-1]);
            hash[i] = ModArithmetic::add(prev_hash,ModArithmetic::mult(str[i]-'a'+1,pw[i],mod),mod);
        }
        cout << "len => "<< n <<"\n";
    }
 
    int getHash(int i,int j){
        if(i == 0)
            return hash[j];
        int res = ModArithmetic::add(hash[j],-hash[i-1],mod);
        res = ModArithmetic::mult(res,inv[i],mod);
    	return res;
    }
 
};
 
 
 
int main() {
	string s1 = "abcdebcdf";
	StringHash stringHash(s1);
	cout << stringHash.getHash(1,3) <<"," <<stringHash.getHash(5,7) <<"\n";
	
	return 0;
}
