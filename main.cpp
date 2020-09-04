#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
using namespace std;
typedef long long ll;
typedef long long ull;
typedef unsigned int ui;
vector<ll> primes;
const ll MAXN=8e8+100;
const string str = "results"+to_string(rand())+".txt";
ofstream fos_gl(str);
/*
ull mul(ull x,ull y,ull m){
    ull shift = 16;
    ull a = x&((1ull << shift)-1);
    ull b = (x>>shift);
    ull c = y&((1ull << shift)-1);
    ull d = (y>>shift);

    ull answer = a*c;
    answer%=m;
    ull q = (a+b)%m;
    ull p = (c+d)%m;
    ull t = (q*p)%m;
    t = (t+(m-a*c+m)%m)%m;
    t = (t+(m-b*d+m)%m)%m;
    answer = (answer + (t<<shift))%m;
    ull z = (b*d)%m;
    z = (z<<shift)%m;
     z = (z<<shift)%m;
     answer = (answer +z)%m;
     return answer;
}*/
/*
ull mul(ull a, ull b, ull m) {

    ull res = 0;
    ull temp_b;


    if (b >= m) {
        if (m > UINT64_MAX / 2u)
            b -= m;
        else
            b %= m;
    }

    while (a != 0) {
        if (a & 1) {

            if (b >= m - res)
                res -= m;
            res += b;
        }
        a >>= 1;

        temp_b = b;
        if (b >= m - b)
            temp_b -= m;
        b += temp_b;
    }


    return res;
}
*/
ull mul(ull a, ull b, ull m) {
    if(a>m){
        a%=m;
    }
    if(b>m){
        b%=m;
    }
    ull c = (long double)a * b / m - 1;
    ull d = a * b - c * m;

    return d >= m ? d % m : d;
}
ull binpow (ull a, ull n, ull m) {
    ull res = 1;
    while (n) {
        if (n & 1) {
            res = mul(res,a,m);
            res %= m;
        }
        a = mul(a,a,m);
        a %= m;
        n >>= 1;
    }
    return res % m;
}

struct key{
    ull e=0,d=0,n=0;
};
bool b[MAXN];
void resheto(ll n){
    for(ll i = 2 ; i<=n;i++){
        if(!b[i]){
            if(i>3e8)
                primes.push_back(i);
            for(ll j = i+i;j<=n;j+=i){
                b[j]=true;
            }
        }
    }
}


ull gcd(ull a,ull b){
    return (a==0?b:gcd(b%a,a));
}

ll evklid(ll a, ll b, ll & x, ll & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    ll x1, y1;
    ll d = evklid(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
bool isPrime(ull x){
    for(ull i = 2; i*i<=x;i++){
        if(!b[i] && x%i==0){
            return false;
        }
    }
    return true;
}
key keygen(){
    ull n;
    ull q,p;
    /*
    do{
        q=rand()%primes.size();
        p=rand()%primes.size();
    }while(q==p || primes[p]*primes[q]<(1ull<<56)||primes[p]*primes[q]>(1ull<<57));
    p= primes[p];
    q= primes[q];*/
    //ll t=1;
    /*
    while(!isPrime(q)){
        q++;
    }
    while(!isPrime(p)){
        p++;
    }*/
    p = 291001999;
    q = 291001993;
    n = q*p;
    cout<<n<<" "<<q<<" "<<p<<endl;
    ull fi = (q-1)*(p-1);
    ull e =2;

    while(gcd(e,fi)!=1){
        e++;
    }
    ull d,y;
    ull g =evklid(e,fi,d,y);
    if (g != 1){

    }
    else {
        d = (d % fi + fi) % fi;
    }
    //cout<<e*d%fi<<endl;
    key k;
    k.e=e;
    k.d=d;
    k.n=n;
    return k;
}

void w(){
    freopen("primes.txt","w",stdout);
    for(auto e :primes){
        //if(e>1e){
        cout<<e<<"\n";
        //}
    }
}
void r(){
    ifstream fis("primes.txt");
    ull r;
    while(fis>>r){
        primes.push_back(r);
    }
}
void generate_primes(ll n){
    resheto(n);
    w();
}
ull encrypt(key k,ull r){
    return binpow(r,k.d,k.n);
}
int len=0;

//void write(ostream * fos, ull a, int bytes) {
//    unsigned char * chars = (unsigned char *) &a;
//    for (int i)
//}

void writeToFileEnc(vector<ull> &res,string file2){
    ofstream fos(file2,ios::binary);
    len = res.size();
    while(res.size()%8!=0){
        res.push_back(0ull);
    }

    for(int i = 0 ; i < res.size();i+=8){
        ull temp =0;
        temp|=(res[i]&(1ull<<56))>>(56-7);
        temp|=(res[i+1]&(1ull<<56))>>(56-6);
        temp|=(res[i+2]&(1ull<<56))>>(56-5);
        temp|=(res[i+3]&(1ull<<56))>>(56-4);
        temp|=(res[i+4]&(1ull<<56))>>(56-3);
        temp|=(res[i+5]&(1ull<<56))>>(56-2);
        temp|=(res[i+6]&(1ull<<56))>>(56-1);
        temp|=(res[i+7]&(1ull<<56))>>(56);
        fos.write((char*)&res[i],7);
        fos.write((char*)&res[i+1],7);
        fos.write((char*)&res[i+2],7);
        fos.write((char*)&res[i+3],7);
        fos.write((char*)&res[i+4],7);
        fos.write((char*)&res[i+5],7);
        fos.write((char*)&res[i+6],7);
        fos.write((char*)&res[i+7],7);
        fos.write((char*)&temp,1);
    }
    fos.close();
}
pair<bool, ull> read(ifstream & ifs, int bytes) {
    char * a = new char[bytes];
    if(!ifs.read(a, bytes)) {
        return {false, 0};
    }
    ll res = 0;
    for (int i = 0; i < bytes; i++) {
        long long cur = (unsigned char)a[i];
        cur = cur << (i * 8);
        res |= cur;
    }
    return {true, res};
}

vector<ull> readFromFileEnc(string file){
    ifstream fis(file,ios::binary);
    vector<ull> arr;
    // ull temp;
    int i = 0;
    int am =0;
    while(true){
        auto [check1, temp1] = read(fis,7);
        if (!check1) {
            break;
        }
        arr.push_back(temp1);
        // fis.read((char*)&temp,7);
        auto [check2, temp2] = read(fis,7);
        arr.push_back(temp2);
        auto [check3, temp3] = read(fis,7);
        arr.push_back(temp3);
        auto [check4, temp4] = read(fis,7);
        arr.push_back(temp4);
        auto [check5, temp5] = read(fis,7);
        arr.push_back(temp5);
        //fis.read((char*)&temp,7);
        auto [check6, temp6] = read(fis,7);
        //fis.read((char*)&temp,7);
        arr.push_back(temp6);
        auto [check7, temp7] = read(fis,7);;
        arr.push_back(temp7);
        auto [check8, temp8] = read(fis,7);;
        arr.push_back(temp8);
        auto [check, temp] = read(fis,1);
        arr[i]|=((temp&(1ull<<8-1))>>8-1<<56);
        arr[i+1]|=((temp&(1ull<<8-2))>>8-2<<56);
        arr[i+2]|=((temp&(1ull<<8-3))>>8-3<<56);
        arr[i+3]|=((temp&(1ull<<8-4))>>8-4<<56);
        arr[i+4]|=((temp&(1ull<<8-5))>>8-5<<56);
        arr[i+5]|=((temp&(1ull<<8-6))>>8-6<<56);
        arr[i+6]|=((temp&(1ull<<8-7))>>8-7<<56);
        arr[i+7]|=((temp&(1ull<<8-8))>>8-8<<56);
        i+=8;
    }

    vector<ull> res;
    for(int i = 0 ; i < len;i++){
        res.push_back(arr[i]);
    }
    //cout<<"read from enc file\n";
    //cout<<res.size()<<endl;
    for(auto e : res){
        // cout<<e<<" ";
    }
    //cout<<endl;
    //cout<<endl<<"readed am"<<am<<endl;
    fis.close();
    return res;
}
//vector<ull> readFromFileEnc(string file){
//    ifstream fis(file,ios::binary);
//    vector<ull> arr;
//    ull temp;
//    int i = 0;
//    int am =0;
//    while(fis.read((char*)&temp,7)){
//        cout << temp;
//        return vector<ull>();
//        arr.push_back(temp);
//        fis.read((char*)&temp,7);
//        arr.push_back(temp);
//        fis.read((char*)&temp,7);
//        arr.push_back(temp);
//        fis.read((char*)&temp,7);
//        arr.push_back(temp);
//        fis.read((char*)&temp,7);
//        arr.push_back(temp);
//        fis.read((char*)&temp,7);
//        arr.push_back(temp);
//        fis.read((char*)&temp,7);
//        arr.push_back(temp);
//        fis.read((char*)&temp,7);
//        arr.push_back(temp);
//        fis.read((char*)&temp,1);
//        arr[i]|=((temp&(1ull<<8-1))>>8-1<<56);
//        arr[i+1]|=((temp&(1ull<<8-2))>>8-2<<56);
//        arr[i+2]|=((temp&(1ull<<8-3))>>8-3<<56);
//        arr[i+3]|=((temp&(1ull<<8-4))>>8-4<<56);
//        arr[i+4]|=((temp&(1ull<<8-5))>>8-5<<56);
//        arr[i+5]|=((temp&(1ull<<8-6))>>8-6<<56);
//        arr[i+6]|=((temp&(1ull<<8-7))>>8-7<<56);
//        arr[i+7]|=((temp&(1ull<<8-8))>>8-8<<56);
//        i+=8;
//    }
//
//    vector<ull> res;
//    for(int i = 0 ; i < len;i++){
//        res.push_back(arr[i]);
//    }
//    //cout<<"read from enc file\n";
//    //cout<<res.size()<<endl;
//    for(auto e : res){
//        //cout<<e<<" ";
//    }
//    //cout<<endl;
//    //cout<<endl<<"readed am"<<am<<endl;
//    fis.close();
//    return res;
//}
bool f[7];
vector<ull> readFromFileNormal(string file){
    ifstream input( file, std::ios::binary );
    vector<unsigned char> buffer(istreambuf_iterator<char>(input), {});
    // cout<<endl<<"buffer sixe read from normal :"<<buffer.size()<<endl;
    vector<ull> result;
    ull r;
    ull s = buffer.size();

    ull i=0;
    if(s>=7)
        for(i = 0 ; i<s-6;i+=7){
            r = (ull)buffer[i] + ((ull)buffer[i+1] << 8) + ((ull)buffer[i+2] << 16)+ ((ull)buffer[i+3] << 24)+ ((ull)buffer[i+4] << 32)+ ((ull)buffer[i+5] << 40)+ ((ull)buffer[i+6] << 48);
            result.push_back(r);
        }
    //cout<<"here"<<endl;

    if(i==s-1){
        r = (ull)buffer[i];
        result.push_back(r);
        f[0]=true;

    }else if(i==s-2){
        r = (ull)buffer[i]+ ((ull)buffer[i+1] << 8);
        result.push_back(r);
        f[1]=true;
    }else if(i==s-3){
        r = (ull)buffer[i]+ ((ull)buffer[i+1] << 8) + ((ull)buffer[i+2] << 16);
        result.push_back(r);
        f[2]=true;
    }else if(i==s-4){
        r = (ull)buffer[i]+ ((ull)buffer[i+1] << 8) + ((ull)buffer[i+2] << 16) + ((ull)buffer[i+3] << 24);
        result.push_back(r);
        f[3]=true;
    }else if(i==s-5){
        r = (ull)buffer[i]+ ((ull)buffer[i+1] << 8) + ((ull)buffer[i+2] << 16) + ((ull)buffer[i+3] << 24) + ((ull)buffer[i+4] << 32);
        result.push_back(r);
        f[4]=true;
    }else if(i==s-6){
        r = (ull)buffer[i]+ ((ull)buffer[i+1] << 8) + ((ull)buffer[i+2] << 16) + ((ull)buffer[i+3] << 24) + ((ull)buffer[i+4] << 32) + ((ull)buffer[i+5] << 40);
        result.push_back(r);
        f[5]=true;
    }
    //cout<<"read fom file"<<endl;
    //cout<<result.size()<<endl;
    for(auto e : result){
        //cout<<e<<" ";
    }
//cout<<endl;
    //cout<<endl<<result.size()<<endl;
    return result;
}
void writeToNormalFile(vector<ull> arr,string file){
    ofstream fos(file,ios::binary);
    //cout<<endl<<len<<endl;
    int am = 0 ;
    for(int i = 0 ; i < len-1;i++){
        // cout<<arr[i]<<" ";
        //if(arr[i]==0)cout<<"\nfuck "<<i<<"\n";
        //if(i%9!=0 || i==0){
        fos.write((char*)&arr[i],7);
        am++;
        //}
        //cout<<i<<endl;

    }

    bool was = false;

    for(int i = 0 ; i < 6; i++){
        if(f[i]){
            //cout<<"\nfuck--------kkkkkkkkkk---------kkkkkkk" <<i<<endl;
            was=true;
            //cout<<arr[len-1]<<" ";
            fos.write((char*)&arr[len-1],1+i);
            am++;
            return;
        }
    }
    if(!was) {
        //cout<<"-----------------here\n";
        //cout<<arr[len-1+len/57]<<" ";
        fos.write((char*)&arr[len-1],7);
        am++;
    }
    fos.close();
    //cout<<"write to normal "<<am<<endl;
}
void encrypt(key k,string file1,string file2){
    cout<<"encryption\n";
    clock_t begin ;
    clock_t end;
    double elapsed_secs;
    auto read = readFromFileNormal(file1);
    vector<ull> result;
    begin = clock();
    for(auto e:read){
        result.push_back(encrypt(k,e));
    }


    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    //cout<<"encrypted\n";
    //cout<<result.size()<<endl;
    for(auto e : result){
        // cout<<e<<" ";
    }
    //cout<<endl;
    writeToFileEnc(result,file2);
    fos_gl<<"encrypted : "<<elapsed_secs<<" sec."<<endl;
}
ull decrypt(key k,ull r){
    return binpow(r,k.e,k.n);
}
void decrypt(key k,string file1,string file2){
    clock_t begin ;
    clock_t end;
    double elapsed_secs;


    auto buffer = readFromFileEnc(file1);
    // cout<<"\n"<<buffer.size()<<endl;
    // for(auto e : buffer){
    //   cout<<e<<" ";
    //}
    cout<<endl;
    ll s = buffer.size();
    ui i;
    ull r;
    vector<ull> result;
    begin = clock();
    cout<<"decryption : \n";
    for(i = 0 ;i<s;i+=1){
        r = buffer[i];
        ull res = decrypt(k,r);
        result.push_back(res);
        //fos.write((char*) &(a), 3);
        //cout<<i/8<<"\n";
    }

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    writeToNormalFile(result,file2);
    fos_gl<<"decrypted : "<<elapsed_secs<<" sec."<<endl;
}

int main(int argc, char *argv[]) {
    //generate_primes(5e8+10);
    //resheto(1e8);
    //w();
    //r();
    key k =keygen();
    //

    //cout<<k.e<<" "<<k.d<<endl;

    fos_gl<<k.e<<" "<<k.d<<endl;


    //console

    for(int i =1; i<argc; i++){
        string e = string(argv[i]);
        fos_gl<<"from : "<<e<<" to : "<<e+".enc"<<" ; to : "<<e+".dec"<<endl;
        encrypt(k,e,e+".enc");
        decrypt(k,e+".enc",e+".dec");
        fos_gl<<"---------------\n\n";
    }
    fos_gl.close();

    //encrypt(k,"1.mp3","11.mp3");
    //decrypt(k,"11.mp3","111.mp3");
    return 0;
}
