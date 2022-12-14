#include<bits/stdc++.h>
using namespace std;


string xor1(string a, string b)
{
	string result = "";
	int n = b.length();
	for(int i = 1; i < n; i++)
	{
		if (a[i] == b[i])
			result += "0";
		else
			result += "1";
	}
	return result;
}

string mod2div(string divident, string divisor)
{
	
	int pick = divisor.length();        			//divisor ki length pick
	
	string tmp = divident.substr(0, pick);          //divident ka substring in tmp with size pick aur pick mein size 1 se x tak hoga not 0 se x
	
	int n = divident.length();						//divident ki overall length
	
	while (pick < n)
	{
		if (tmp[0] == '1')
		
			tmp = xor1(divisor, tmp) + divident[pick];
		else
		
			tmp = xor1(string(pick, '0'), tmp) + divident[pick];
				
		pick += 1;
	}
	
	if (tmp[0] == '1')
		tmp = xor1(divisor, tmp);
	else
		tmp = xor1(string(pick, '0'), tmp);
		
	return tmp;
}

int main()
{
	string data,key;
	cout<<"Enter Data Word ";
	cin>>data;
	cout<<"Enter Polynomial in Binary Form : ";
	cin>>key;
	int l_key = key.length();
	
	string appended_data = (data + string(l_key - 1, '0'));
	
	string remainder = mod2div(appended_data, key);
	
	string codeword = data + remainder;
	cout << "CRC Bits : "<< remainder << "\n";
	cout << "CodeWord (Data + crc) : "<< codeword << "\n";
	
	return 0;
}
