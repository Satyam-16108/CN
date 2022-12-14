#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
int m, r, size;
int *hammingCode;
int *dw;
int *rB;
int *cW;
void getCW() {
	cout << "Enter length of dataword: ";
	cin >> m;
	r = 1;
	while (pow(2, r) < m + r + 1) {
		r++;
	}
	cout << "Redundant bits: " << r << endl;
	size = m + r;
	dw = new int[m];
	cW = new int[size];
	cout << "Enter data word: ";
	for (int i = m-1; i >= 0; --i) {
		cin >> dw[i];
	}
	int k = 0;
	for (int i = 1; i <= size; i++) {
		cW[i - 1] = 0;
		for (int j = 0; j < r; j++) {
			if (i == pow(2, j)) {
				cW[i - 1] = -1;
			}
		}	
	}
	for (int i = 0; i < size; i++) {
		if (cW[i] != -1) {
			cW[i] = dw[k];
			k++;
		}
	}
	
	//parity bit pt2
	int a, parity;
	for (int i = 0; i < r; i++) {
		a = pow(2, i);
		parity = 0;
		for (int j = a - 1; j < size; j = j + a) {
			for (int w = 0; w < a; w++) {
				if (cW[j] == -1) {
					j++;
					continue;
				}
				else if (cW[j] == 1){
					parity++;
					j++;
				}
				else {
					j++;
				}
				
			}
			//j = j + a;
		}
		if (parity % 2 == 0) {
			cW[a - 1] = 0;
		}
		else {
			cW[a - 1] = 1;
		}
	}
}

void errorGen()
{
	int rN=rand()%(m+r);
	cout<<rN<<endl;
	hammingCode=new int[m+r];
	for(int i=m+r-1; i>=0; --i)
	{
		hammingCode[i]=cW[i];
	}
	if(rN>m+r)
	{
		cout<<"*No error generated*"<<endl;
	}
	else
	{
		if(cW[rN]==0)
		{
			hammingCode[rN]=1;
		}
		else
		{
			hammingCode[rN]=0;
		}
		cout<<"*ERROR GENERATED*\n";
		cout<<"**Error CodeWord is: \n";
		for(int i=(m+r)-1; i>=0; --i)
		{
			cout<<hammingCode[i]<<" ";
		}
		cout<<endl;
//		cout<<"Error generated at: "<<rN-1<<endl;
		getCW();
	}

}
int main() {
	getCW();
//	errorGen();
	cout << "Correct Codeword is: \n";
	for (int i = size - 1; i >= 0; --i) {
		cout << cW[i]<<" ";
	}
	
	return 0;
}
