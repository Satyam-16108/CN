#include<bits/stdc++.h>

using namespace std;

 char classss(string str){
 
     int i=0;
     char arr[4];
     while (str[i] != '.')
 {
  arr[i] = str[i];
  i++;
 }
 i--;

    int w = 0, j = 1;
 while (i >= 0)
 {
  w = (str[i] - '0') * j + w;
  j = j * 10;
  i--;
 }

      if(w>=0 && w<=127){
          return 'A';
      }
      else if(w>=128 && w<=191){
          return 'B';
      }
      else if(w>=192 && w<=223){
          return 'C';
      }
      else if(w>=224 && w<=239){
          return 'D';
      }
      else if(w>=240 && w<=255){
          return 'E';
      }
      else{
        return 'I';
      }
 }
string ipadresss(string ip,char classs){
      if(classs=='A'){
          string net="";
          for(int i=0;i<ip.size();i++){
              if(ip[i]=='.'){
                  break;
              }
              net+=ip[i];
          }
          string netip=net+".0.0.0";

          string brodip=net+".255.255.255";
         
          string output=netip+" "+brodip;
          return output;
      }
      if(classs=='B'){
          string net="";
          int cnt=0;
          for(int i=0;i<ip.size();i++){
              if(cnt==2){
                  break;
              }
              if(ip[i]=='.'){
                  cnt++;
              }
              net+=ip[i];
            }
            string netip=net+"0.0";
            string brodip=net+"255.255";
            string output=netip+" "+brodip;
            return output;
           
          }
         
          if(classs=='C'){
          string net="";
          int cnt=0;
          for(int i=0;i<ip.size();i++){
              if(cnt==3){
                  break;
              }
              if(ip[i]=='.'){
                  cnt++;
              }
              net+=ip[i];
            }
            string netip=net+"0";
            string brodip=net+"255";
            string output=netip+" "+brodip;
            return output;
           
          }
          if(classs=='D'){
         
            string output="no net id and host id";
            return output;
          }
          if(classs=='E'){
         
            string output="reserved for future purpose";
            return output;
          }

      }
     
         
     
 
 
using namespace std;
int main(){
    cout<<"Enter the IPV4 address "<<endl;
    string s;
    cin>>s;
   
   
    char anschar=classss(s);

    if(anschar=='I'){
        cout<<"Invalid ip address"<<endl;
    }
    else{
        cout<<"The class of ip address is : "<<anschar<<endl;
        
         string ans=ipadresss(s,anschar);
         cout<<ans;
    }
  

    return 0;
}
