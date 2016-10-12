#include <iostream>
#include <string>
#include <string.h>
#include "Sponge.h"
#include "InternalFun.h"
#include <ctime>
#include <algorithm>
using namespace std;

#define bitRate   576 
#define capacity  1024

unsigned long int roundCnt;


void SpongeConstruction(string inputString, int outputLen) 
{
	// Transform the input string into binary bits
	BinaryTransfer( inputString ) ;
						
	// Padding using Multirate
	vector< Binary > Message = Padding( inputString ) ; 	
	
	//Initialize the state variable
	Binary stateVar ;
		
		
	// Absorbing phase
	/*** TODO: Implement your MSHA3's absorbing phase here ***/
    for (int i=0; i<Message.size(); i++) {
        stateVar = stateVar ^ Message[i];
        //PrintHex(Message[i].to_string());
        //cout <<endl;
        stateVar = internalFun(stateVar);
        //PrintHex(stateVar.to_string());
        //cout <<endl;
    }
	
	// Squeezing phase
	string hashVal = ""; // The final output value
	/*** TODO: Implement your MSHA3's squeezing phase here ***/
    int num = outputLen/576;
    int res = outputLen%576;
    for (int i=0; i<num; i++) {
        hashVal += stateVar.to_string<char, string::traits_type, string::allocator_type>().substr(0,576);
        stateVar = internalFun(stateVar);
    }
    if (res!=0) {
            hashVal += stateVar.to_string<char, string::traits_type, string::allocator_type>().substr(0,res);
    }


	 //Print the hash value to the stdout
	PrintHex( hashVal.substr(0, outputLen) ) ;
}


void BinaryTransfer(string& inputString)
{
	string binary = "" ;
	
	for(int i=0; i<inputString.length(); i++)
	{
		for(int k=7; k>=0; k--)
			if( ((inputString[i] >> k) & 0x01) )
				binary += "1" ;
			else
				binary += "0" ;
	}	
	//binary +="00000110";
	inputString = binary ;
    //cout << binary<<endl;
}



vector< Binary > Padding(string inputString) 
{
	/*** TODO: Implement with Multirate padding ***/
    //cout <<inputString.length()<<endl;
    unsigned long int blockNum = (inputString.length()/576)+1;
    vector<Binary> blocks(blockNum);
    unsigned long int cnt = 0;
    for (int i =0; i<blockNum-1; i++) {
        for (int j=0; j<576; j++) {
            blocks[i][j]=inputString[cnt]&1;
            cnt++;
        }
    }
    if (inputString.length()%576 !=0) {
        for (int i = 0; i<(inputString.length()%576); i++) {
            blocks[blockNum-1][i]=inputString[cnt]&1;
            cnt++;
        }
        blocks[blockNum-1][inputString.length()%576]=1;
        blocks[blockNum-1][575]=1;
    }
    else{
        blocks[blockNum-1][0]=1;
        blocks[blockNum-1][575]=1;
    }
    /*
    for (int i=0; i<blockNum; i++) {
        cout <<blocks[i]<<endl;
    }*/
    
    vector<Binary> rul;
    for (int i=0;i<blockNum; i++) {
        string tmp = blocks[i].to_string<char, string::traits_type,  string::allocator_type>();
        reverse(tmp.begin(), tmp.end());
        Binary tmp1(tmp);
        rul.push_back(tmp1);
    }
    /*
    for (int i=0; i<blockNum; i++) {
        cout <<rul[i]<<endl;
    }*/
    return rul;
}


/*** Print the hash value in hex ***/
void PrintHex(string hashVal) 
{
    for(int i=0; i<hashVal.length(); i+=4)
	{
		string Ahex = hashVal.substr(i, 4) ; 
		int Val = 0 ;
		
		for(int k=0; k<4; k++)
			if( Ahex[k]-'0' )	
				Val += (1 << (3-k)) ;
		
		if( Val < 10 )	cout << Val ;
		else	cout << (char)(Val+55) ;			
	}
}
