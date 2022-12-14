#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

using namespace std;

class packet{
	public :
			int data;
};

class frame{
	public:
			packet pdata;
			int seq;
};

int receiver(frame f,int cases){
	packet p;
	int d;
	int se;
	cout<<"\n****Receiver end****\n";
	if(cases==5){
		cout<<"Frame discarded ";
	}else{
		p=f.pdata;
		cout<<"Frame is received from physical layer of receiver ";
		d=p.data;
		cout<<"with info: "<<d<<" and seq no."<<f.seq;
		p=f.pdata;
		se=f.seq;
		
		cout<<"\nFrame is converted to packet ";
	}
	
	if(se==0){
		se=1;
	}else if(se==1){
		se=0;
	}
	
	cout<<"\nACKNOWLWDGEMENT TRANSMISSION \n";
	cout<<"Acknowledgement "<<se<<" is now converted to packet\n";
	cout<<"Packet is now converted to frame with sequence no. "<<se<<endl;
	cout<<"Acknowledgement is send to sender \n";
	return se;
}
int sender(int data ,int seque,int cases){
	int check;
	packet p;
	p.data=data;
	
	cout<<"\n****Sender end****\n";
	cout<<"Data "<<p.data<<" is converted to packet \n";
	frame f;
	f.pdata=p;
	f.seq=seque;
	cout<<"Packet is coverted into frame with sequence number "<<seque<<endl;
	cout<<"Frame is send to receiver \n";
	if(cases==1||cases==2||cases==3){
		cout<<"Acknowledgement not received \n";
		return -1;
	}
	else if(cases==4){
		check=receiver(f,4);
		if(check>1){
			cout<<"Acknownledgement failed \n";
			
		}else{
			cout<<"Acknowledge is recieved by sender to send Data frame with seq.number "<<check<<endl<<endl;
		}
	}
	else {
		check=receiver(f,0);
		if(check>1){
			cout<<"Acknownledgement failed ";
			
		}else{
			cout<<"Acknowledge is recieved by sender to send Data frame with seq.number \n\n"<<check<<endl<<endl;
		}
	}
}

int main(){
	int n,r,ch;
	cout<<"Enter the number of input data: ";
	cin>>n;
	int data[n];
	cout<<"\nEnter the data: ";
	for (int i=0;i<n;i++){
		cin>>data[i];
	}
	for (int i=0;i<n;i++){
		cout<<"\nFOR DATA : "<<data[i];
		srand(time(NULL));
		r=rand()%4;
		if(r==1){
			cout<<"\nAcknowledgement is lost\n";
			ch=sender(data[i],i%2,r);
			if(ch==-1){
				cout<<"Frame is sent again \n";
				ch=sender(data[i],i%2,4);
			}
		}
		else if(r==2){
			cout<<"\nFrame is lost\n";
			ch=sender(data[i],i%2,r);
			if(ch==-1){
				cout<<"Frame is sent again \n";
				ch=sender(data[i],i%2,0);
			}
		}
		else if(r==3){
			cout<<"\nFrame get damage \n";
			ch=sender(data[i],i%2,r);
			if(ch==-1){
				cout<<"Frame is sent again \n";
				ch=sender(data[i],i%2,0);
			}
		}
		else{
			cout<<"Normal frame \n";
			sender(data[i],i%2,r);
			
		}
	}
	cout<<"\nStop and wait complete \n";


return 1;
}

