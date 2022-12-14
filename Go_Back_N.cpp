#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
void frame_sent(int f,int size,int & no_trans,int dup){
	for(int i=0;i<size;i++){
		if(f<=dup){
			cout<<"Frame sent "<<f++<<endl;
			no_trans++;
		}
		else {
			break;
		}
	}
	
}
int main(){
	int frame,window_size,loop,no_trans=1,f=0,dup;
	srand(time(NULL));
	cout<<"Enter the number of frame : ";
	cin>>frame;
	cout<<"Enter the window size : ";
	cin>>window_size;
	int x=window_size-1;
	dup=frame;

	frame_sent(0,window_size,no_trans,dup);
	while(frame!=-1){
			loop=rand()%2;
			if(loop==1){
				cout<<"Acknowledgement received "<<f++<<endl;
				x++;
				frame--;
				if(x<=dup){
					cout<<"Frame sent "<<x<<endl; 	
				}
					
			}
			else{
				cout<<"Frame  "<<f<<" not received "<<endl;
				cout<<"Retransmitting frame \n";
				frame_sent(f,window_size,no_trans,dup);
			}
			
	}
		

return 0;
}

