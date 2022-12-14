#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

char class_of_ip(char str[])
{
	//Storing first octet
	char arr[4];
	int i=0;
	while(str[i]!='.')
	{
		arr[i]=str[i];
		i++;
	}
	int top = i + 1;
	i--;
	
	int ip=0;
	int second=0;
	int third=0;
	int fourth=0;
	int j=1;
	
	while(i>=0)
	{
		ip=ip+(arr[i]-'0')*j;
		j=j*10;
		i--;
	}
	//storing second octet
	char arr2[4];
	i = top;
	int k = 0;	
	while(str[i]!='.')
	{
		arr2[k]=str[i];
		i++;
		k++;
	}
	top = i + 1;
	k--;
	j = 1;
	while(k>=0)
	{
		second=second+(arr2[k]-'0')*j;
		j=j*10;
		k--;
	}
	
	/*int countingDot=0;
	while(countingDot<2)
	{
		if(str[j]=='.')
		{
			countingDot++;
		}
	}
	cout << i;
	while(countingDot>0&&countingDot<2)
	{
		second=second+(str[i]-'0')*j;
		j=j*10;
		i--;
	}
	cout << i;
	*/
	//storing third octet
	char arr3[4];
	i = top;
	k = 0;	
	while(str[i]!='.')
	{
		arr3[k]=str[i];
		i++;
		k++;
	}
	top = i + 1;
	k--;
	j = 1;
	while(k>=0)
	{
		third=third+(arr3[k]-'0')*j;
		j=j*10;
		k--;
	}
	
	//storing fourth octet
	char arr4[4];
	i = top;
	k = 0;	
	while(str[i]!='\0')
	{
		arr4[k]=str[i];
		i++;
		k++;
	}
	top = i + 1;
	k--;
	
	j = 1;
	while(k>=0)
	{
		fourth=fourth+(arr4[k]-'0')*j;
		j=j*10;
		k--;
	}
	
	if(second>255)
	{
		cout<<"*Invalid IP address*";
	}
	
	else if(third>255)
	{
		cout<<"*Invalid IP address*";
	}
	
	else if(fourth>255)
	{
		cout<<"*Invalid IP address*";
	}
	
	else
	{
		//CLASS A
	if(ip>=0 && ip<=127)
	{
		return 'A';
	}
	//CLASS B
	else if(ip>=128 && ip<=191)
	{
		return 'B';
	}
	//CLASS C
	else if(ip>=192 && ip<=223)
	{
		return 'C';
	}
	//CLASS D
	else if(ip>=224 && ip<=239)
	{
		return 'D';
	}
	//CLASS E
	else if(ip>=240 && ip<=255)
	{
		return 'E';
	}
	else
	{
		cout<<"*Invalid IP address*";
	}
	}
}

//FUNCTION TO SEPERATE NETWORK ID AND HOST ID
void seperate(char str[], char ipclass)
{
	char network[12];
	char host[12];
	for(int k=0; k<12; k++)
	{
		network[k]=host[k]='\0';
	}
	
	//For A
	if(ipclass=='A')
	{
		int i=0;
		int j=0;
		while(str[j]!='.')
		{
			network[i++]=str[j++];
		}
		i=0;
		j++;
		while(str[j]!='\0')
		{
			host[i++]=str[j++];
		}
		cout<<"Network id is: "<<network<<endl;;
		cout<<"Host id is: "<<host<<endl;
	}
	
	//For B
	else if(ipclass=='B')
	{
		int i=0;
		int j=0;
		int countingDot=0;
		while(countingDot<2)
		{
			network[i++]=str[j++];
			if(str[j]=='.')
			{
				countingDot++;
			}
		}
		i=0;
		j++;
		while(str[j]!='\0')
		{
			host[i++]=str[j++];
		}
		cout<<"Network id is: "<<network<<endl;;
		cout<<"Host id is: "<<host<<endl;
	}
	
	//For C
	else if(ipclass=='C')
	{
		int i=0;
		int j=0;
		int countingDot=0;
		while(countingDot<3)
		{
			network[i++]=str[j++];
			if(str[j]=='.')
			{
				countingDot++;
			}
		}
		i=0;
		j++;
		while(str[j]!='\0')
		{
			host[i++]=str[j++];
		}
		cout<<"Network id is: "<<network<<endl;;
		cout<<"Host id is: "<<host<<endl;
	}
	
	//For D and E
	else if(ipclass=='D'||ipclass=='E')
	{
		cout<<"*There is no network id and host id*";
	}
	else
	{
		cout<<"*Not known*";
	}
}

int main()
{
	char str[32];
	cout<<"Enter IP address in the form of IP format(e.g. 192.226.12.11): ";
	cin>>str;
	char ipclass=class_of_ip(str);
	cout<<"\nGiven IP belongs to class: "<<ipclass<<endl;
	seperate(str, ipclass);
	return 0;
}
