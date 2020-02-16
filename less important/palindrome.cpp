#include <iostream>
#include <cstring>
using namespace std;

int isPalindrome(int start, int end, string str)
{
    if (start >= end){
        return 1;
    }
    if (str[start] != str[end]){
    	return 0;
    	
    }
    return isPalindrome(++start, --end, str);   
}

int main(){
	cout << isPalindrome(0, 18,"ablewasiereisawelba") << endl;
	cout << isPalindrome(0, 2, "cat")<< endl;
	return 0;
}
