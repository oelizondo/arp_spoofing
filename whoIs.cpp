#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct arpPacket{
  string option;
  string sMac;
  string sIp;

  arpPacket(string op, string mac, string ip) : option(op), sMac(mac), sIp(ip){}

};


void readFile(ifstream myFile, string fileName, vector<arpPacket> v){

  myFile.open(fileName);
  string sOption;
  string sMac;
  string sIp;

  while (myFile >> sOption >> sMac >> sIp) {

    arpPacket aux(sOption, sMac, sIp);
    v.push_back(aux);
  }

  myFile.close();
}

int main() {


  ifstream myFile;
  string fileName = "arp.txt";
  vector<arpPacket> packets;

  readFile(myFile, fileName, packets);

  //cout << packets[1].option << endl;
  //cout << packets[2].option << endl;



}
