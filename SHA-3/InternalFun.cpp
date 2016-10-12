#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "InternalFun.h"

using namespace std;


bitset<64> RC[24] = 
{ 
	0x0000000000000001,
	0x0000000000008082,
	0x800000000000808A,
	0x8000000080008000,
	0x000000000000808B,
	0x0000000080000001,
	0x8000000080008081,
	0x8000000000008009,
	0x000000000000008A,
	0x0000000000000088,
	0x0000000080008009,
	0x000000008000000A,
	0x000000008000808B,
	0x800000000000008B,
	0x8000000000008089,
	0x8000000000008003,
	0x8000000000008002,
	0x8000000000000080,
	0x000000000000800A,
	0x800000008000000A,
	0x8000000080008081,
	0x8000000000008080,
	0x0000000080000001,
	0x8000000080008008
};


int rhoTable[5][5]={
    {0,36,3,41,18},
    {1,44,10,45,2},
    {62,6,43,15,61},
    {28,55,25,21,56},
    {27,20,39,8,14}
};

int xpiTable[5][5]={
    {0,3,1,4,2},
    {1,4,2,0,3},
    {2,0,3,1,4},
    {3,1,4,2,0},
    {4,2,0,3,1}
};

int ypiTable[5]={0,1,2,3,4};

int Mod(int a,int b){
    if (a>=0) {
        return a%b;
    }
    else{
        while(a<0){
            a+=b;
        }
    }
    return a;
}


Binary internalFun(Binary stateVar) 
{
	string tmpRC="";
    for(int i=0; i<24; i++){
        //cout <<"Round "<<i<<": "<<endl;
        tmpRC = RC[i].to_string();
        reverse(tmpRC.begin(), tmpRC.end());
        bitset<64> realRC(tmpRC);
		stateVar = roundFun( stateVar, realRC ) ;
        //cout <<stateVar<<endl;
    }

	return stateVar ;
}




/*** Round function is modified in MSHA-3 ***/
Binary roundFun(Binary stateVar, bitset<64> singleRC)
{
    
	/*** TODO: Implement your MSHA3's 5 functions as follows ***/
    bitset<64> a[5][5];
    unsigned long int sVidx=1599;
    
    for (int j=0; j<5; j++) {
        for (int i=0; i<5; i++) {
            for (int k=0; k<64; k++) {
                a[i][j][k] = stateVar[sVidx];
                sVidx--;
            }
        }
    }
    /*
    for (int i=0; i<5; i++) {
        for (int j=0 ; j<5; j++) {
            cout << '('<<i<<j<<')'<<a[i][j]<<endl;
        }
    }*/
	
	/*** Theta ***/
    theta(a);
	/*** Rho  ***/
    rho(a);
	/*** Pi ***/	
    pi(a);
	/*** Xi ***/
    xi(a);
	/*** Iota ***/
    a[0][0] = a[0][0]^singleRC;
    

    Binary rul;
    string tmpRul="",tmpRev="";
    for (int j=0; j<5; j++) {
        for (int i=0; i<5; i++) {
            tmpRev =  a[i][j].to_string<char,string::traits_type,string::allocator_type>();
            reverse(tmpRev.begin(), tmpRev.end());
            tmpRul += tmpRev;
        }
    }
    reverse(tmpRul.begin(), tmpRul.end());
    for (int i=0; i<1600; i++) {
        rul[i] = tmpRul[i]&1;
    }
    return rul;
	
}

void theta(bitset<64> a[][5]){
    
    bitset<64> tmp[5][5];
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            tmp[i][j]=a[i][j];
        }
    }
    
    for (int j=0; j<5; j++) {
        for (int i=0; i<5; i++) {
            for (int k=0; k<5; k++) {
                a[i][j] = a[i][j] ^ tmp[Mod(i-1,5)][k];
            }
        }
    }
    
    for (int j=0; j<5; j++) {
        for (int i=0; i<5; i++) {
            for (int k=0; k<64; k++) {
                for (int m=0; m<5; m++) {
                    a[i][j][k] = a[i][j][k] ^ tmp[Mod(i+1,5)][m][Mod(k-1,64)];
                }
            }

        }
    }
    /*
    bitset<64> c[5],d[5];
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            c[i] = c[i]^tmp[i][j];
        }
    }
    for (int i=0; i<5; i++) {
        for (int k=0; k<64; k++) {
            d[i][k] = c[Mod(i-1, 5)][k]^c[Mod(i+1, 5)][Mod(k-1, 64)];
        }
    }
    for (int j=0;j<5; j++) {
        for (int i=0; i<5; i++) {
            for (int k=0; k<64; k++) {
                a[i][j][k] = a[i][j][k]^d[i][k];
            }
        }
    }*/
    
    /*
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            cout <<'('<<i<<','<<j<<')'<<a[i][j]<<endl;
        }
    }*/

}

void rho(bitset<64> a[][5]){
    
    bitset<64> tmp[5][5];
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            tmp[i][j] = a[i][j];
        }
    }
    
    for (int j=0; j<5; j++) {
        for (int i=0; i<5; i++) {
            for (int k=0; k<64; k++) {
                a[i][j][k] = tmp[i][j][Mod(k-rhoTable[i][j],64)];
                
            }
            //cout <<'('<<i<<','<<j<<')'<<a[i][j]<<endl;
            /*
            if (j==1 && i==0) {
                cout <<'('<<i<<','<<j<<')'<<a[i][j]<<endl;
            }*/
        }
    }
}


void pi(bitset<64> a[][5]){
    bitset<64> tmp[5][5];
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            tmp[i][j] = a[i][j];
        }
    }
    for (int i=0;i<5; i++) {
        for (int j=0; j<5; j++) {
            a[i][j] = tmp[xpiTable[i][j]][ypiTable[i]];
            //cout <<'('<<i<<','<<j<<')'<<a[i][j]<<endl;
        }
    }
}

void xi(bitset<64> a[][5]){
    bitset<64> tmp[5][5];
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            tmp[i][j] = a[i][j];
        }
    }
    
    for (int j=0; j<5; j++) {
        for (int i=0; i<5; i++) {
            a[i][j]=a[i][j]^(~tmp[(i+1)%5][j]&tmp[(i+2)%5][j]);
        }
    }
    /*
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            for (int k=0; k<64; k++) {
                a[i][j][k] = a[i][j][k]^(~tmp[(i+1)%5][j][k]&tmp[(i+2)%5][j][k]);
            }
        }
    }*/
}
